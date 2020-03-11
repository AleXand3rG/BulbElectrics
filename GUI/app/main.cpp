#include "mainwindow.h"
#include "newelementdialog.h"
#include "editelementdialog.h"

//Qt
#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QDesktopWidget>

int main (int argc, char *argv[]) {
    QApplication App(argc, argv);
    MainWindow w;

    //Center QMainWindow
    int width = w.frameGeometry().width();
    int height = w.frameGeometry().height();
    QDesktopWidget wid;
    int screenWidth = wid.screen()->width();
    int screenHeight = wid.screen()->height();
    w.setGeometry((screenWidth/2)-(width/2),(screenHeight/2)-(height/2),width,height);

    w.show();
    return App.exec();
}
