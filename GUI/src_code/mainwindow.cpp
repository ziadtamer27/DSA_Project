#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include <fstream>
#include <map>
#include <string>

#include "CheckXmlFile.h"
#include "CompressingXML.h"
#include "DecompressingXML.h"
#include "MinifyingXMLFile.h"
#include "XMLtoTree.h"
#include "XMLtoJSON.h"
#include "PrettifyingXMLFile.h"
#include "Network_JPG.h"
#include "NetworkBuilder.h"
#include "NetworkAnalysis.h"
#include "PostSearch.h"

using namespace std;

// ---------- shared types ----------
using DictType = map<unsigned char, string>;

// ---------- file helpers ----------
static string readFileQt(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw runtime_error("Cannot open input file");
    QTextStream in(&file);
    return in.readAll().toStdString();
}

static void writeFileQt(const QString &path, const string &content)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        throw runtime_error("Cannot open output file");
    QTextStream out(&file);
    out << QString::fromStdString(content);
}

// ---------- input chooser ----------
static string getInputXML(Ui::MainWindow *ui)
{
    if (!ui->inputText->toPlainText().trimmed().isEmpty())
        return ui->inputText->toPlainText().toStdString();

    if (!ui->inputPath->text().isEmpty())
        return readFileQt(ui->inputPath->text());

    throw runtime_error("No input provided (paste XML or choose file)");
}

// ---------- ctor / dtor ----------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ---------- browse ----------
void MainWindow::on_browseInput_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select XML File");
    if (!path.isEmpty()) {
        ui->inputPath->setText(path);
        ui->inputText->setPlainText(QString::fromStdString(readFileQt(path)));
    }
}

void MainWindow::on_browseOutput_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "Select Output File");
    if (!path.isEmpty())
        ui->outputPath->setText(path);
}

// ---------- VERIFY ----------
void MainWindow::on_verifyBtn_clicked()
{
    try {
        string xml = getInputXML(ui);
        string report = Checkxmlfile(xml);
        ui->outputView->setPlainText(QString::fromStdString(report));
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

// ---------- MINI ----------
void MainWindow::on_miniBtn_clicked()
{
    try {
        string xml = getInputXML(ui);
        string mini = Minifyingxmlfile(xml);
        ui->outputView->setPlainText(QString::fromStdString(mini));

        if (!ui->outputPath->text().isEmpty())
            writeFileQt(ui->outputPath->text(), mini);
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

// ---------- PRETTIFY ----------
void MainWindow::on_prettifyBtn_clicked()
{
    try {
        string xml = getInputXML(ui);
        string p = PrettifyingXMLFile(xml);
        ui->outputView->setPlainText(QString::fromStdString(p));

        if (!ui->outputPath->text().isEmpty())
            writeFileQt(ui->outputPath->text(), p);
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

// ---------- JSON ----------
void MainWindow::on_jsonBtn_clicked()
{
    try {
        string xml = getInputXML(ui);
        Node *root = XMLtoTree(xml);
        string json = XMLtoJSON(root);
        ui->outputView->setPlainText(QString::fromStdString(json));

        if (!ui->outputPath->text().isEmpty())
            writeFileQt(ui->outputPath->text(), json);
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

// ---------- COMPRESS ----------
void MainWindow::on_compressBtn_clicked()
{
    try {
        string xml = getInputXML(ui);
        string s = CompressingXMLFile(xml);
        auto e = BytePairEncoding(s);

        if (ui->outputPath->text().isEmpty())
            throw runtime_error("Output file required for compression");

        ofstream out(ui->outputPath->text().toStdString(),
                     ios::binary | ios::trunc);
        if (!out.is_open())
            throw runtime_error("Cannot open output file");

        uint32_t dictSize = e.second.size();
        out.write(reinterpret_cast<const char*>(&dictSize), sizeof(dictSize));

        for (auto &kv : e.second) {
            unsigned char symbol = kv.first;
            uint32_t len = kv.second.size();
            out.write(reinterpret_cast<const char*>(&symbol), sizeof(symbol));
            out.write(reinterpret_cast<const char*>(&len), sizeof(len));
            out.write(kv.second.data(), len);
        }

        uint32_t dataSize = e.first.size();
        out.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));
        out.write(e.first.data(), dataSize);
        out.close();

        ui->outputView->setPlainText("Compression completed successfully.");
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

// ---------- DECOMPRESS ----------
void MainWindow::on_decompressBtn_clicked()
{
    try {
        if (ui->inputPath->text().isEmpty())
            throw runtime_error("Decompression requires input file");

        if (ui->outputPath->text().isEmpty())
            throw runtime_error("Output file required");

        ifstream in(ui->inputPath->text().toStdString(), ios::binary);
        if (!in.is_open())
            throw runtime_error("Cannot open input file");

        DictType dict;
        uint32_t dictSize = 0;
        in.read(reinterpret_cast<char*>(&dictSize), sizeof(dictSize));

        for (uint32_t i = 0; i < dictSize; i++) {
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
        writeFileQt(ui->outputPath->text(), restored);
        ui->outputView->setPlainText(QString::fromStdString(restored));
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_drawBtn_clicked()
{
    try {
        string xml = getInputXML(ui);

        Network_JPG(XMLtoGraph(xml));
        ui->outputView->setPlainText("Graph saved");
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_mostActiveBtn_clicked()
{
    try {
        string xml = getInputXML(ui);
        auto g = XMLtoGraph(xml);
        auto users = addusers(xml);
        auto res = mostActiveUser(g, users);
        ui->outputView->setPlainText(QString("Most Active User\nID: %1\nName: %2").arg(res.first).arg(QString::fromStdString(res.second)));
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_mostInfluencerBtn_clicked()
{
    try {
        string xml = getInputXML(ui);
        auto g = XMLtoGraph(xml);
        auto users = addusers(xml);
        ui->outputView->setPlainText(QString::fromStdString(mostInfluencer(g, users)));
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_mutualBtn_clicked()
{
    try {
        string xml = getInputXML(ui);
        QString idsText = ui->idsInput->text();
        if (idsText.isEmpty()) throw runtime_error("Enter at least two comma-separated IDs");

        QVector<int> ids;
        for (auto &s : idsText.split(',')) ids.push_back(s.trimmed().toInt());

        if (ids.size() < 2) throw runtime_error("Need at least two IDs");

        ui->outputView->setPlainText(QString::fromStdString(mutualUsers(ids[0], ids[1], XMLtoGraph(xml))));
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_suggestBtn_clicked()
{
    try {
        string xml = getInputXML(ui);
        bool ok;
        int id = ui->idInput->text().toInt(&ok);
        if (!ok) throw runtime_error("Enter valid user ID");

        ui->outputView->setPlainText(QString::fromStdString(suggestUser(id, XMLtoGraph(xml))));
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_searchWordBtn_clicked()
{
    try {
        string xml = getInputXML(ui);
        QString word = ui->wordInput->text();
        if (word.isEmpty()) throw runtime_error("Enter search word");

        ui->outputView->setPlainText(QString::fromStdString(PostSearchWord(xml, word.toStdString())));
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_searchTopicBtn_clicked()
{
    try {
        string xml = getInputXML(ui);
        QString topic = ui->wordInput->text();
        if (topic.isEmpty()) throw runtime_error("Enter search topic");

        ui->outputView->setPlainText(QString::fromStdString(PostSearchTopic(xml, topic.toStdString())));
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
