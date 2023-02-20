#include "mainwindow.h"
//#include <QTextStream>>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/resources/icon2.png"));

    MainWindow w;    

    w.show();
    return a.exec();
}
