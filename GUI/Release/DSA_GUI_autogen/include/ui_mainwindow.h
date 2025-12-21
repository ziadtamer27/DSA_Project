/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *inputPath;
    QPushButton *browseInput;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *outputPath;
    QPushButton *browseOutput;
    QVBoxLayout *verticalLayout_3;
    QPlainTextEdit *outputView;
    QGridLayout *gridLayout_2;
    QPushButton *compressBtn;
    QPushButton *decompressBtn;
    QPushButton *jsonBtn;
    QPushButton *verifyBtn;
    QPushButton *miniBtn;
    QPushButton *prettifyBtn;
    QMenuBar *menubar;
    QMenu *menuXMLeditor;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(955, 637);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        inputPath = new QLineEdit(centralwidget);
        inputPath->setObjectName("inputPath");

        horizontalLayout->addWidget(inputPath);

        browseInput = new QPushButton(centralwidget);
        browseInput->setObjectName("browseInput");

        horizontalLayout->addWidget(browseInput);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        outputPath = new QLineEdit(centralwidget);
        outputPath->setObjectName("outputPath");

        horizontalLayout_3->addWidget(outputPath);

        browseOutput = new QPushButton(centralwidget);
        browseOutput->setObjectName("browseOutput");

        horizontalLayout_3->addWidget(browseOutput);


        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        outputView = new QPlainTextEdit(centralwidget);
        outputView->setObjectName("outputView");
        outputView->setReadOnly(true);

        verticalLayout_3->addWidget(outputView);


        gridLayout->addLayout(verticalLayout_3, 7, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        compressBtn = new QPushButton(centralwidget);
        compressBtn->setObjectName("compressBtn");

        gridLayout_2->addWidget(compressBtn, 1, 1, 1, 1);

        decompressBtn = new QPushButton(centralwidget);
        decompressBtn->setObjectName("decompressBtn");

        gridLayout_2->addWidget(decompressBtn, 1, 2, 1, 1);

        jsonBtn = new QPushButton(centralwidget);
        jsonBtn->setObjectName("jsonBtn");

        gridLayout_2->addWidget(jsonBtn, 1, 0, 1, 1);

        verifyBtn = new QPushButton(centralwidget);
        verifyBtn->setObjectName("verifyBtn");

        gridLayout_2->addWidget(verifyBtn, 0, 0, 1, 1);

        miniBtn = new QPushButton(centralwidget);
        miniBtn->setObjectName("miniBtn");

        gridLayout_2->addWidget(miniBtn, 0, 1, 1, 1);

        prettifyBtn = new QPushButton(centralwidget);
        prettifyBtn->setObjectName("prettifyBtn");

        gridLayout_2->addWidget(prettifyBtn, 0, 2, 1, 1);


        gridLayout->addLayout(gridLayout_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 955, 25));
        menuXMLeditor = new QMenu(menubar);
        menuXMLeditor->setObjectName("menuXMLeditor");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuXMLeditor->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        browseInput->setText(QCoreApplication::translate("MainWindow", "Browse Input", nullptr));
        browseOutput->setText(QCoreApplication::translate("MainWindow", "Browse Output", nullptr));
        compressBtn->setText(QCoreApplication::translate("MainWindow", "Compress", nullptr));
        decompressBtn->setText(QCoreApplication::translate("MainWindow", "Decompress", nullptr));
        jsonBtn->setText(QCoreApplication::translate("MainWindow", "To JSON", nullptr));
        verifyBtn->setText(QCoreApplication::translate("MainWindow", "Verify", nullptr));
        miniBtn->setText(QCoreApplication::translate("MainWindow", "Minify", nullptr));
        prettifyBtn->setText(QCoreApplication::translate("MainWindow", "Prettify", nullptr));
        menuXMLeditor->setTitle(QCoreApplication::translate("MainWindow", "XMLeditor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
