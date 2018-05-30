#include "AppLayer.h"
#include "HMIFrameWork/HMIFrameWork.h"
AppLayer::AppLayer(QWidget *parent)
    :QWidget(parent)
{
    this->setStyleSheet("QWidget{background:transparent;}");

    setGeometry(QRect(0,0,800,480));

    this->show();
}

AppLayer::~AppLayer()
{
}

