#include <QCoreApplication>
#include <QDebug>
#include "ftpcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FTPcontroller f("127.0.0.1", 1234);

    f.start();
    return a.exec();
}
