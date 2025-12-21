#include "PreviewWindow.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

PreviewWindow::PreviewWindow(const QString& title, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(title);
    resize(700, 500);

    editor = new QTextEdit();
    saveBtn = new QPushButton("Save As...");
    connect(saveBtn, &QPushButton::clicked, this, &PreviewWindow::onSave);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(editor);
    layout->addWidget(saveBtn);
    setLayout(layout);
}

void PreviewWindow::setText(const QString& txt) { editor->setPlainText(txt); }
void PreviewWindow::appendText(const QString& txt) { editor->append(txt); }

void PreviewWindow::onSave()
{
    QString path = QFileDialog::getSaveFileName(this, "Save preview");
    if (path.isEmpty()) return;
    QFile f(path);
    if (f.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&f);
        out << editor->toPlainText();
    }
}
