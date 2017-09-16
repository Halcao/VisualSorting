#include <iostream>
#include <QApplication>
#include "mainwindow.h"
using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
//    w.setFixedWidth(640);
//    w.setFixedHeight(640);
    w.setFixedWidth(800);
    w.setFixedHeight(800);
//    w.setBaseSize(640, 640);
////    w.resize(QSize(800, 600));
//    w.setsize
    w.show();
    return app.exec();
}
