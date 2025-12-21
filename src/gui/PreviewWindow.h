#pragma once

#include <QDialog>

class QTextEdit;
class QPushButton;

class PreviewWindow : public QDialog {
    Q_OBJECT
public:
    PreviewWindow(const QString& title, QWidget* parent = nullptr);
    void setText(const QString& txt);
    void appendText(const QString& txt);
private slots:
    void onSave();
private:
    QTextEdit* editor;
    QPushButton* saveBtn;
};
