#include "SDLAppsWindow.h"

SDLAppsWindow::SDLAppsWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setStyleSheet("QWidget{background:transparent;}");

    setGeometry(QRect(0,0,800,480));

    this->hide();
}
