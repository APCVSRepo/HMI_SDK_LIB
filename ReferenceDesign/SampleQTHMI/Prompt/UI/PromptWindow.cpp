#include "PromptWindow.h"

PromptWindow::PromptWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setStyleSheet("QWidget{background:transparent;}");

    setGeometry(QRect(0,40,800,440));

    this->hide();
}
