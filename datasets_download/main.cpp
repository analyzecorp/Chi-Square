#include <QApplication>
#include <QDir>

#include "httpwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QIcon icon("/usr/share/datasets/datasetsIcon.svg");

    HttpWindow httpWin;
    httpWin.setFixedSize(832, 416); //width = 832px or 52em, height = 416px or 26em
    httpWin.showNormal();
    httpWin.setWindowTitle("Datasets");
    httpWin.setWindowIcon(icon);
    httpWin.show();
    return app.exec();
}
