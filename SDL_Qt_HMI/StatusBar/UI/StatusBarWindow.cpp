#include "StatusBarWindow.h"

StatusBarWindow::StatusBarWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setStyleSheet("QWidget{background:transparent;}");

    setGeometry(QRect(0,0,800,40));

    this->hide();
}
