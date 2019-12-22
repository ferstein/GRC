#include "widget.h"
#include <QApplication>

#include <QString>
#include <QLockFile>
#include <QDir>

int main(int argc, char *argv[])
{
    QString tmpDir = QDir::tempPath();
    QLockFile lockFile(tmpDir + "/gimbal-remote-control.lock");

    if(!lockFile.tryLock(100))
    {
        printf("\r\n"
               "You already have this app running.\r\n"
               "Only one instance is allowed.\r\n");
        return 1;
    }
    else
    {
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
    }
}
