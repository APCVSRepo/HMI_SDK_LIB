#include <QApplication>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QDialog>
#include <QTimer>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
#endif

    qRegisterMetaType<string>("string");
    qRegisterMetaType< map<string,string> >("map<string,string>");

    MainWindow w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.resize(800,480);
    w.show();
    return a.exec();
}
