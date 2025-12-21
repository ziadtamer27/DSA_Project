#include "MainWindow.h"
#include "PreviewWindow.h"

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QMessageBox>

#include <fstream>
#include <streambuf>

// include project headers
#include "../header/CLI.h"
#include "../header/CheckXmlFile.h"
#include "../header/MinifyingXMLFile.h"
#include "../header/PrettifyingXMLFile.h"
#include "../header/XMLtoTree.h"
#include "../header/XMLtoJSON.h"
#include "../header/CompressingXML.h"
#include "../header/DecompressingXML.h"

using namespace std;

static string readFile(const string& path)
{
    ifstream f(path);
    if (!f.is_open()) return string();
    stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

static void writeFileBinary(const string& path, const string& data)
{
    ofstream f(path, ios::out | ios::binary | ios::trunc);
    f.write(data.data(), (streamsize)data.size());
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget();
    setCentralWidget(central);

    cmdCombo = new QComboBox();
    cmdCombo->addItems({"verify", "mini", "json", "prettify", "compress", "decompress"});

    inEdit = new QLineEdit();
    QPushButton* inBtn = new QPushButton("Browse...");
    connect(inBtn, &QPushButton::clicked, this, &MainWindow::onBrowseIn);

    outEdit = new QLineEdit();
    QPushButton* outBtn = new QPushButton("Browse...");
    connect(outBtn, &QPushButton::clicked, this, &MainWindow::onBrowseOut);

    runBtn = new QPushButton("Run");
    connect(runBtn, &QPushButton::clicked, this, &MainWindow::onRun);

    QHBoxLayout* inLayout = new QHBoxLayout();
    inLayout->addWidget(new QLabel("Input:"));
    inLayout->addWidget(inEdit);
    inLayout->addWidget(inBtn);

    QHBoxLayout* outLayout = new QHBoxLayout();
    outLayout->addWidget(new QLabel("Output:"));
    outLayout->addWidget(outEdit);
    outLayout->addWidget(outBtn);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(new QLabel("Command:"));
    mainLayout->addWidget(cmdCombo);
    mainLayout->addLayout(inLayout);
    mainLayout->addLayout(outLayout);
    mainLayout->addWidget(runBtn);

    central->setLayout(mainLayout);

    // Menu to open windows
    QMenu* winMenu = menuBar()->addMenu("Windows");
    QAction* xmlAct = new QAction("XML Preview", this);
    connect(xmlAct, &QAction::triggered, this, &MainWindow::onOpenXmlPreview);
    winMenu->addAction(xmlAct);

    QAction* jsonAct = new QAction("JSON Preview", this);
    connect(jsonAct, &QAction::triggered, this, &MainWindow::onOpenJsonPreview);
    winMenu->addAction(jsonAct);

    QAction* logAct = new QAction("Log", this);
    connect(logAct, &QAction::triggered, this, &MainWindow::onOpenLog);
    winMenu->addAction(logAct);

    xmlPreview = make_unique<PreviewWindow>("XML Preview");
    jsonPreview = make_unique<PreviewWindow>("JSON Preview");
    logWindow = make_unique<PreviewWindow>("Log");
}

void MainWindow::appendLog(const QString& text)
{
    logWindow->appendText(text);
}

void MainWindow::onBrowseIn()
{
    QString path = QFileDialog::getOpenFileName(this, "Select input file");
    if (!path.isEmpty()) inEdit->setText(path);
}

void MainWindow::onBrowseOut()
{
    QString path = QFileDialog::getSaveFileName(this, "Select output file");
    if (!path.isEmpty()) outEdit->setText(path);
}

void MainWindow::onRun()
{
    QString cmd = cmdCombo->currentText();
    QString inPath = inEdit->text();
    QString outPath = outEdit->text();

    if (inPath.isEmpty()) {
        QMessageBox::warning(this, "Missing input", "Please select an input file.");
        return;
    }

    string xml = readFile(inPath.toStdString());

    try {
        if (cmd == "verify") {
            string report = Checkxmlfile(xml);
            appendLog("verify: done");
            if (outPath.isEmpty()) {
                logWindow->appendText(QString::fromStdString(report));
            } else {
                ofstream f(outPath.toStdString());
                f << report;
                appendLog("report saved");
            }
        } else if (cmd == "mini") {
            string copyXml = xml;
            string mini = Minifyingxmlfile(copyXml);
            appendLog("mini: done");
            if (outPath.isEmpty()) xmlPreview->setText(QString::fromStdString(mini));
            else writeFileBinary(outPath.toStdString(), mini);
        } else if (cmd == "json") {
            Node* root = XMLtoTree(xml);
            string json = XMLtoJSON(root);
            appendLog("json: done");
            if (outPath.isEmpty()) jsonPreview->setText(QString::fromStdString(json));
            else writeFileBinary(outPath.toStdString(), json);
        } else if (cmd == "prettify") {
            string p = PrettifyingXMLFile(xml);
            appendLog("prettify: done");
            if (outPath.isEmpty()) xmlPreview->setText(QString::fromStdString(p));
            else writeFileBinary(outPath.toStdString(), p);
        } else if (cmd == "compress") {
            string s = CompressingXMLFile(xml);
            auto e = BytePairEncoding(s);
            // write as CLI: dict size, entries, data size, data
            ofstream out(outPath.toStdString(), ios::binary | ios::trunc);
            if (!out.is_open()) throw runtime_error("Cannot open output file");
            uint32_t dictSize = (uint32_t)e.second.size();
            out.write(reinterpret_cast<const char*>(&dictSize), sizeof(dictSize));
            for (auto &kv : e.second) {
                unsigned char symbol = kv.first;
                uint32_t len = (uint32_t)kv.second.size();
                out.write(reinterpret_cast<const char*>(&symbol), sizeof(symbol));
                out.write(reinterpret_cast<const char*>(&len), sizeof(len));
                out.write(kv.second.data(), len);
            }
            uint32_t dataSize = (uint32_t)e.first.size();
            out.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));
            out.write(e.first.data(), dataSize);
            out.close();
            appendLog("compress: saved to " + QString::fromStdString(outPath.toStdString()));
        } else if (cmd == "decompress") {
            // read .comp file
            ifstream in(inPath.toStdString(), ios::binary);
            if (!in.is_open()) throw runtime_error("Cannot open input file");
            map<unsigned char, string> dict;
            uint32_t dictSize = 0;
            in.read(reinterpret_cast<char*>(&dictSize), sizeof(dictSize));
            for (uint32_t i = 0; i < dictSize; ++i) {
                unsigned char symbol;
                uint32_t len;
                in.read(reinterpret_cast<char*>(&symbol), sizeof(symbol));
                in.read(reinterpret_cast<char*>(&len), sizeof(len));
                string value(len, '\0');
                in.read(&value[0], len);
                dict[symbol] = value;
            }
            uint32_t dataSize = 0;
            in.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
            string comp(dataSize, '\0');
            in.read(&comp[0], dataSize);
            in.close();
            string restored = DecompressingXMLFile(comp, dict);
            appendLog("decompress: done");
            if (outPath.isEmpty()) xmlPreview->setText(QString::fromStdString(restored));
            else writeFileBinary(outPath.toStdString(), restored);
        }
    } catch (const exception& ex) {
        appendLog(QString::fromUtf8("Error: ") + ex.what());
        QMessageBox::critical(this, "Error", ex.what());
    }
}

void MainWindow::onOpenXmlPreview() { xmlPreview->show(); }
void MainWindow::onOpenJsonPreview() { jsonPreview->show(); }
void MainWindow::onOpenLog() { logWindow->show(); }
