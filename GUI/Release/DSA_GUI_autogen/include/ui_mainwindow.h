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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionClear;
    QAction *actionSettings;
    QAction *actionAbout;
    QWidget *centralwidget;
    QVBoxLayout *centralLayout;
    QHBoxLayout *inputLayout;
    QLabel *inputLabel;
    QLineEdit *inputPath;
    QPushButton *browseInput;
    QHBoxLayout *outputLayout;
    QLabel *outputLabel;
    QLineEdit *outputPath;
    QPushButton *browseOutput;
    QFrame *divider;
    QGridLayout *buttonsLayout;
    QPushButton *verifyBtn;
    QPushButton *miniBtn;
    QPushButton *prettifyBtn;
    QPushButton *jsonBtn;
    QPushButton *compressBtn;
    QPushButton *decompressBtn;
    QLabel *editorLabel;
    QSplitter *splitter;
    QWidget *inputContainer;
    QVBoxLayout *inputContainerLayout;
    QLabel *inputTitle;
    QPlainTextEdit *inputText;
    QWidget *outputContainer;
    QVBoxLayout *outputContainerLayout;
    QLabel *outputTitle;
    QPlainTextEdit *outputView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuTools;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 800);
        MainWindow->setMinimumSize(QSize(900, 600));
        MainWindow->setStyleSheet(QString::fromUtf8("/* Modern Dark Theme */\n"
"QMainWindow {\n"
"    background-color: #0f172a;\n"
"}\n"
"\n"
"QWidget {\n"
"    background-color: transparent;\n"
"    color: #e2e8f0;\n"
"    font-family: 'Segoe UI', 'Inter', sans-serif;\n"
"    font-size: 11pt;\n"
"}\n"
"\n"
"/* Card-style containers */\n"
"QWidget#centralwidget {\n"
"    background-color: #0f172a;\n"
"}\n"
"\n"
"/* Labels */\n"
"QLabel {\n"
"    color: #94a3b8;\n"
"    font-weight: 500;\n"
"    padding: 2px;\n"
"    font-size: 10.5pt;\n"
"}\n"
"\n"
"/* Input fields */\n"
"QLineEdit {\n"
"    background-color: #1e293b;\n"
"    border: 1.5px solid #334155;\n"
"    border-radius: 6px;\n"
"    padding: 10px 12px;\n"
"    selection-background-color: #3b82f6;\n"
"    color: #f1f5f9;\n"
"    font-size: 10.5pt;\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"    border-color: #475569;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #3b82f6;\n"
"    background-color: #1e293b;\n"
"    outline: none;\n"
"}\n"
"\n"
"QLineEdit:disabled {\n"
"    background-color: #1e293b;\n"
""
                        "    color: #64748b;\n"
"    border-color: #334155;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: #64748b;\n"
"}\n"
"\n"
"/* Buttons */\n"
"QPushButton {\n"
"    background-color: #3b82f6;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 6px;\n"
"    padding: 10px 20px;\n"
"    font-weight: 600;\n"
"    font-size: 10.5pt;\n"
"    min-width: 100px;\n"
"    transition: all 0.2s ease;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2563eb;\n"
"    transform: translateY(-1px);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1d4ed8;\n"
"    transform: translateY(0);\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: #334155;\n"
"    color: #94a3b8;\n"
"}\n"
"\n"
"/* Special button variants */\n"
"QPushButton#verifyBtn {\n"
"    background-color: #10b981;\n"
"}\n"
"\n"
"QPushButton#verifyBtn:hover {\n"
"    background-color: #059669;\n"
"}\n"
"\n"
"QPushButton#verifyBtn:pressed {\n"
"    background-color: #047857;\n"
"}\n"
"\n"
"QPushButton#compres"
                        "sBtn {\n"
"    background-color: #8b5cf6;\n"
"}\n"
"\n"
"QPushButton#compressBtn:hover {\n"
"    background-color: #7c3aed;\n"
"}\n"
"\n"
"QPushButton#compressBtn:pressed {\n"
"    background-color: #6d28d9;\n"
"}\n"
"\n"
"QPushButton#decompressBtn {\n"
"    background-color: #8b5cf6;\n"
"}\n"
"\n"
"QPushButton#decompressBtn:hover {\n"
"    background-color: #7c3aed;\n"
"}\n"
"\n"
"QPushButton#decompressBtn:pressed {\n"
"    background-color: #6d28d9;\n"
"}\n"
"\n"
"/* Text editors */\n"
"QPlainTextEdit {\n"
"    background-color: #1e293b;\n"
"    border: 1.5px solid #334155;\n"
"    border-radius: 8px;\n"
"    padding: 12px;\n"
"    selection-background-color: #3b82f6;\n"
"    color: #f1f5f9;\n"
"    font-family: 'Cascadia Code', 'Consolas', 'Monaco', monospace;\n"
"    font-size: 10.5pt;\n"
"    line-height: 1.4;\n"
"}\n"
"\n"
"QPlainTextEdit:hover {\n"
"    border-color: #475569;\n"
"}\n"
"\n"
"QPlainTextEdit:focus {\n"
"    border-color: #3b82f6;\n"
"}\n"
"\n"
"QPlainTextEdit::placeholder {\n"
"    color: "
                        "#64748b;\n"
"}\n"
"\n"
"/* Splitter */\n"
"QSplitter::handle {\n"
"    background-color: #334155;\n"
"    width: 2px;\n"
"}\n"
"\n"
"QSplitter::handle:hover {\n"
"    background-color: #475569;\n"
"}\n"
"\n"
"QSplitter::handle:horizontal {\n"
"    margin: 0 4px;\n"
"}\n"
"\n"
"/* Menu bar */\n"
"QMenuBar {\n"
"    background-color: #0f172a;\n"
"    padding: 4px;\n"
"    border-bottom: 1px solid #1e293b;\n"
"}\n"
"\n"
"QMenuBar::item {\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    color: #94a3b8;\n"
"}\n"
"\n"
"QMenuBar::item:selected {\n"
"    background-color: #1e293b;\n"
"    color: #e2e8f0;\n"
"}\n"
"\n"
"QMenuBar::item:pressed {\n"
"    background-color: #334155;\n"
"}\n"
"\n"
"/* Menu */\n"
"QMenu {\n"
"    background-color: #1e293b;\n"
"    border: 1px solid #334155;\n"
"    border-radius: 6px;\n"
"    padding: 4px;\n"
"}\n"
"\n"
"QMenu::item {\n"
"    padding: 8px 24px 8px 12px;\n"
"    border-radius: 4px;\n"
"    color: #e2e8f0;\n"
"}\n"
"\n"
"QMenu::item:selected {\n"
"    background-"
                        "color: #3b82f6;\n"
"    color: white;\n"
"}\n"
"\n"
"QMenu::item:disabled {\n"
"    color: #64748b;\n"
"}\n"
"\n"
"QMenu::separator {\n"
"    height: 1px;\n"
"    background-color: #334155;\n"
"    margin: 4px 8px;\n"
"}\n"
"\n"
"/* Status bar */\n"
"QStatusBar {\n"
"    background-color: #0f172a;\n"
"    color: #94a3b8;\n"
"    border-top: 1px solid #1e293b;\n"
"    padding: 8px;\n"
"    font-size: 10pt;\n"
"}\n"
"\n"
"QStatusBar::item {\n"
"    border: none;\n"
"}\n"
"\n"
"/* Layout spacing */\n"
"QHBoxLayout, QVBoxLayout, QGridLayout {\n"
"    spacing: 12px;\n"
"    margin: 0;\n"
"}\n"
"\n"
"/* Grid layout specific */\n"
"QGridLayout {\n"
"    margin-top: 8px;\n"
"    margin-bottom: 8px;\n"
"}\n"
"\n"
"/* Tooltip */\n"
"QToolTip {\n"
"    background-color: #1e293b;\n"
"    color: #e2e8f0;\n"
"    border: 1px solid #334155;\n"
"    border-radius: 4px;\n"
"    padding: 8px;\n"
"    font-size: 10pt;\n"
"}\n"
"\n"
"/* Scrollbars */\n"
"QScrollBar:vertical {\n"
"    border: none;\n"
"    background-color: #1e293"
                        "b;\n"
"    width: 10px;\n"
"    border-radius: 5px;\n"
"    margin: 2px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background-color: #475569;\n"
"    border-radius: 5px;\n"
"    min-height: 20px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background-color: #64748b;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"    border: none;\n"
"    background: none;\n"
"    height: 0px;\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"    background: none;\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"    border: none;\n"
"    background-color: #1e293b;\n"
"    height: 10px;\n"
"    border-radius: 5px;\n"
"    margin: 2px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal {\n"
"    background-color: #475569;\n"
"    border-radius: 5px;\n"
"    min-width: 20px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal:hover {\n"
"    background-color: #64748b;\n"
"}"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName("actionCopy");
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName("actionPaste");
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName("actionClear");
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName("actionSettings");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralLayout = new QVBoxLayout(centralwidget);
        centralLayout->setSpacing(16);
        centralLayout->setObjectName("centralLayout");
        centralLayout->setContentsMargins(24, 20, 24, 20);
        inputLayout = new QHBoxLayout();
        inputLayout->setSpacing(12);
        inputLayout->setObjectName("inputLayout");
        inputLabel = new QLabel(centralwidget);
        inputLabel->setObjectName("inputLabel");
        inputLabel->setMinimumSize(QSize(80, 0));

        inputLayout->addWidget(inputLabel);

        inputPath = new QLineEdit(centralwidget);
        inputPath->setObjectName("inputPath");

        inputLayout->addWidget(inputPath);

        browseInput = new QPushButton(centralwidget);
        browseInput->setObjectName("browseInput");

        inputLayout->addWidget(browseInput);


        centralLayout->addLayout(inputLayout);

        outputLayout = new QHBoxLayout();
        outputLayout->setSpacing(12);
        outputLayout->setObjectName("outputLayout");
        outputLabel = new QLabel(centralwidget);
        outputLabel->setObjectName("outputLabel");
        outputLabel->setMinimumSize(QSize(80, 0));

        outputLayout->addWidget(outputLabel);

        outputPath = new QLineEdit(centralwidget);
        outputPath->setObjectName("outputPath");

        outputLayout->addWidget(outputPath);

        browseOutput = new QPushButton(centralwidget);
        browseOutput->setObjectName("browseOutput");

        outputLayout->addWidget(browseOutput);


        centralLayout->addLayout(outputLayout);

        divider = new QFrame(centralwidget);
        divider->setObjectName("divider");
        divider->setStyleSheet(QString::fromUtf8("background-color: #334155; border: none; height: 1px; margin: 8px 0;"));
        divider->setFrameShape(QFrame::Shape::HLine);
        divider->setFrameShadow(QFrame::Shadow::Sunken);

        centralLayout->addWidget(divider);

        buttonsLayout = new QGridLayout();
        buttonsLayout->setSpacing(12);
        buttonsLayout->setObjectName("buttonsLayout");
        verifyBtn = new QPushButton(centralwidget);
        verifyBtn->setObjectName("verifyBtn");

        buttonsLayout->addWidget(verifyBtn, 0, 0, 1, 1);

        miniBtn = new QPushButton(centralwidget);
        miniBtn->setObjectName("miniBtn");

        buttonsLayout->addWidget(miniBtn, 0, 1, 1, 1);

        prettifyBtn = new QPushButton(centralwidget);
        prettifyBtn->setObjectName("prettifyBtn");

        buttonsLayout->addWidget(prettifyBtn, 0, 2, 1, 1);

        jsonBtn = new QPushButton(centralwidget);
        jsonBtn->setObjectName("jsonBtn");

        buttonsLayout->addWidget(jsonBtn, 0, 3, 1, 1);

        compressBtn = new QPushButton(centralwidget);
        compressBtn->setObjectName("compressBtn");

        buttonsLayout->addWidget(compressBtn, 1, 0, 1, 2);

        decompressBtn = new QPushButton(centralwidget);
        decompressBtn->setObjectName("decompressBtn");

        buttonsLayout->addWidget(decompressBtn, 1, 2, 1, 2);


        centralLayout->addLayout(buttonsLayout);

        editorLabel = new QLabel(centralwidget);
        editorLabel->setObjectName("editorLabel");
        editorLabel->setStyleSheet(QString::fromUtf8("font-weight: 600; font-size: 11.5pt; color: #e2e8f0; padding: 4px;"));

        centralLayout->addWidget(editorLabel);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Orientation::Horizontal);
        splitter->setHandleWidth(2);
        splitter->setChildrenCollapsible(false);
        inputContainer = new QWidget(splitter);
        inputContainer->setObjectName("inputContainer");
        inputContainerLayout = new QVBoxLayout(inputContainer);
        inputContainerLayout->setSpacing(4);
        inputContainerLayout->setObjectName("inputContainerLayout");
        inputContainerLayout->setContentsMargins(0, 0, 0, 0);
        inputTitle = new QLabel(inputContainer);
        inputTitle->setObjectName("inputTitle");
        inputTitle->setStyleSheet(QString::fromUtf8("color: #94a3b8; font-size: 10pt; padding-left: 4px;"));

        inputContainerLayout->addWidget(inputTitle);

        inputText = new QPlainTextEdit(inputContainer);
        inputText->setObjectName("inputText");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(inputText->sizePolicy().hasHeightForWidth());
        inputText->setSizePolicy(sizePolicy1);
        inputText->setMinimumSize(QSize(200, 300));

        inputContainerLayout->addWidget(inputText);

        splitter->addWidget(inputContainer);
        outputContainer = new QWidget(splitter);
        outputContainer->setObjectName("outputContainer");
        outputContainerLayout = new QVBoxLayout(outputContainer);
        outputContainerLayout->setSpacing(4);
        outputContainerLayout->setObjectName("outputContainerLayout");
        outputContainerLayout->setContentsMargins(0, 0, 0, 0);
        outputTitle = new QLabel(outputContainer);
        outputTitle->setObjectName("outputTitle");
        outputTitle->setStyleSheet(QString::fromUtf8("color: #94a3b8; font-size: 10pt; padding-left: 4px;"));

        outputContainerLayout->addWidget(outputTitle);

        outputView = new QPlainTextEdit(outputContainer);
        outputView->setObjectName("outputView");
        sizePolicy1.setHeightForWidth(outputView->sizePolicy().hasHeightForWidth());
        outputView->setSizePolicy(sizePolicy1);
        outputView->setMinimumSize(QSize(200, 300));
        outputView->setReadOnly(true);

        outputContainerLayout->addWidget(outputView);

        splitter->addWidget(outputContainer);

        centralLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 48));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuTools = new QMenu(menubar);
        menuTools->setObjectName("menuTools");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setSizeGripEnabled(false);
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionClear);
        menuTools->addAction(actionSettings);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "XML Editor", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "&Open...", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("MainWindow", "&Save Output", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("MainWindow", "E&xit", nullptr));
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("MainWindow", "Alt+F4", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCopy->setText(QCoreApplication::translate("MainWindow", "&Copy", nullptr));
#if QT_CONFIG(shortcut)
        actionCopy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPaste->setText(QCoreApplication::translate("MainWindow", "&Paste", nullptr));
#if QT_CONFIG(shortcut)
        actionPaste->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClear->setText(QCoreApplication::translate("MainWindow", "C&lear All", nullptr));
#if QT_CONFIG(shortcut)
        actionClear->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSettings->setText(QCoreApplication::translate("MainWindow", "&Settings...", nullptr));
#if QT_CONFIG(shortcut)
        actionSettings->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Alt+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAbout->setText(QCoreApplication::translate("MainWindow", "&About", nullptr));
#if QT_CONFIG(shortcut)
        actionAbout->setShortcut(QCoreApplication::translate("MainWindow", "F1", nullptr));
#endif // QT_CONFIG(shortcut)
        inputLabel->setText(QCoreApplication::translate("MainWindow", "Input Path:   ", nullptr));
        inputPath->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter path or drag file here...", nullptr));
#if QT_CONFIG(tooltip)
        browseInput->setToolTip(QCoreApplication::translate("MainWindow", "Select input XML file", nullptr));
#endif // QT_CONFIG(tooltip)
        browseInput->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        outputLabel->setText(QCoreApplication::translate("MainWindow", "Output Path:", nullptr));
        outputPath->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter output file path...", nullptr));
#if QT_CONFIG(tooltip)
        browseOutput->setToolTip(QCoreApplication::translate("MainWindow", "Select output file location", nullptr));
#endif // QT_CONFIG(tooltip)
        browseOutput->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
#if QT_CONFIG(tooltip)
        verifyBtn->setToolTip(QCoreApplication::translate("MainWindow", "Validate XML structure", nullptr));
#endif // QT_CONFIG(tooltip)
        verifyBtn->setText(QCoreApplication::translate("MainWindow", "\342\234\223 Verify", nullptr));
#if QT_CONFIG(tooltip)
        miniBtn->setToolTip(QCoreApplication::translate("MainWindow", "Remove whitespace and compress XML", nullptr));
#endif // QT_CONFIG(tooltip)
        miniBtn->setText(QCoreApplication::translate("MainWindow", "Minify", nullptr));
#if QT_CONFIG(tooltip)
        prettifyBtn->setToolTip(QCoreApplication::translate("MainWindow", "Format XML with proper indentation", nullptr));
#endif // QT_CONFIG(tooltip)
        prettifyBtn->setText(QCoreApplication::translate("MainWindow", "Prettify", nullptr));
#if QT_CONFIG(tooltip)
        jsonBtn->setToolTip(QCoreApplication::translate("MainWindow", "Convert XML to JSON format", nullptr));
#endif // QT_CONFIG(tooltip)
        jsonBtn->setText(QCoreApplication::translate("MainWindow", "To JSON", nullptr));
#if QT_CONFIG(tooltip)
        compressBtn->setToolTip(QCoreApplication::translate("MainWindow", "Compress XML data", nullptr));
#endif // QT_CONFIG(tooltip)
        compressBtn->setText(QCoreApplication::translate("MainWindow", "Compress", nullptr));
#if QT_CONFIG(tooltip)
        decompressBtn->setToolTip(QCoreApplication::translate("MainWindow", "Decompress XML data", nullptr));
#endif // QT_CONFIG(tooltip)
        decompressBtn->setText(QCoreApplication::translate("MainWindow", "Decompress", nullptr));
        editorLabel->setText(QCoreApplication::translate("MainWindow", "Editor", nullptr));
        inputTitle->setText(QCoreApplication::translate("MainWindow", "Input XML", nullptr));
        inputText->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter XML content here or load from file...", nullptr));
        outputTitle->setText(QCoreApplication::translate("MainWindow", "Output", nullptr));
        outputView->setPlaceholderText(QCoreApplication::translate("MainWindow", "Results will appear here...", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "&Edit", nullptr));
        menuTools->setTitle(QCoreApplication::translate("MainWindow", "&Tools", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "&Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
