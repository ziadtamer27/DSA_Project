#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits\stdc++.h>

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include "CheckXmlFile.h"
#include "CompressingXML.h"
#include "DecompressingXML.h"
#include "MinifyingXMLFile.h"
#include "XMLtoTree.h"
#include "XMLtoJSON.h"
#include "PrettifyingXMLFile.h"

using namespace std;
using DictType = map<unsigned char, string>;


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
    QString path = QFileDialog::getOpenFileName(this, "Select Input File");
    if (!path.isEmpty())
        ui->inputPath->setText(path);
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
        string xml = readFileQt(ui->inputPath->text());
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
        string xml = readFileQt(ui->inputPath->text());
        string mini = Minifyingxmlfile(xml);
        writeFileQt(ui->outputPath->text(), mini);
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

// ---------- PRETTIFY ----------
void MainWindow::on_prettifyBtn_clicked()
{
    try {
        string xml = readFileQt(ui->inputPath->text());
        string p = PrettifyingXMLFile(xml);
        writeFileQt(ui->outputPath->text(), p);
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

// ---------- JSON ----------
void MainWindow::on_jsonBtn_clicked()
{
    try {
        string xml = readFileQt(ui->inputPath->text());
        Node *root = XMLtoTree(xml);
        string json = XMLtoJSON(root);
        writeFileQt(ui->outputPath->text(), json);
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

// ---------- COMPRESS ----------
void MainWindow::on_compressBtn_clicked()
{
    try {
        string xml = readFileQt(ui->inputPath->text());
        string s = CompressingXMLFile(xml);
        auto e = BytePairEncoding(s);

        ofstream out(ui->outputPath->text().toStdString(),
                     ios::binary | ios::trunc);
        if (!out.is_open())
            throw runtime_error("Cannot open output file");

        uint32_t dictSize = (uint32_t)e.second.size();
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
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

// ---------- DECOMPRESS ----------

void MainWindow::on_decompressBtn_clicked()
{

    try {
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
    } catch (exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }

}

