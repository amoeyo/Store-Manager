#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("仓库管理系统服务器");
    w.setWindowFlags( w.windowFlags() & ~Qt::WindowMaximizeButtonHint);
    w.show();

    return a.exec();
}
