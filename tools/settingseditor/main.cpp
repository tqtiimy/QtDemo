#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Settings Editor");//设置应用程序名
    //设置应用程序的版本，如果没有设置，默认是特定的平台值，由主执行程序或包决定
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    Mainwindow mainWin;
    mainWin.show();

    return app.exec();
}
