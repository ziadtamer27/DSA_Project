#pragma once

#include <QMainWindow>
#include <memory>

class QComboBox;
class QLineEdit;
class QPushButton;
class QTextEdit;

class PreviewWindow;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
private slots:
    void onBrowseIn();
    void onBrowseOut();
    void onRun();
    void onOpenXmlPreview();
    void onOpenJsonPreview();
    void onOpenLog();
private:
    void appendLog(const QString& text);

    QComboBox* cmdCombo;
    QLineEdit* inEdit;
    QLineEdit* outEdit;
    QPushButton* runBtn;

    std::unique_ptr<PreviewWindow> xmlPreview;
    std::unique_ptr<PreviewWindow> jsonPreview;
    std::unique_ptr<PreviewWindow> logWindow;
};
