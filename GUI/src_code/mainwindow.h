#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // browse
    void on_browseInput_clicked();
    void on_browseOutput_clicked();

    // operations
    void on_verifyBtn_clicked();
    void on_miniBtn_clicked();
    void on_prettifyBtn_clicked();
    void on_jsonBtn_clicked();
    void on_compressBtn_clicked();
    void on_decompressBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
