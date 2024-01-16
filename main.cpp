#include <QtGui/QApplication>
#include "MainWindow.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString cssString;
    QFile cssFile(QApplication::applicationDirPath()+"/style.css");
    cssFile.open(QIODevice::ReadOnly | QIODevice::Text);
    cssString = cssFile.readAll();
    cssFile.close();

    MainWindow w(argc > 1 ? argv[1] : "");
    w.setStyleSheet(cssString);
    w.show();

    return a.exec();
}
