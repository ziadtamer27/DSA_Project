#include "mainwindow.h"
#include "CLI.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    if(argc==1){
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
    else return run_cli(argc, argv);
}
