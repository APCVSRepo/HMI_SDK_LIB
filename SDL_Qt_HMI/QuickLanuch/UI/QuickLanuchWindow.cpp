#include "QuickLanuchWindow.h"

QuickLanuchWindow::QuickLanuchWindow()
{
    this->setStyleSheet("QWidget{background:transparent;}");

    setGeometry(QRect(0,0,170,480));

    this->hide();
}
