

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //初始化资源，在一些平台上当资源是以静态库存在的时候此宏是必要的
    Q_INIT_RESOURCE(editabletreemodel);

    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
