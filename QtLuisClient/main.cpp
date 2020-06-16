#include "MainForm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"Main thread : "<<QThread::currentThreadId();
    MainForm w;
    w.show();

    return a.exec();
}
