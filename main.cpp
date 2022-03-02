#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // TODO: So long as your program works on all the sample inputs, you should then prioritize improving UI to be
    // a bit more professional looking since this would make a good impression on the TA's
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
