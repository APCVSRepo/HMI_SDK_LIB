#include "AppViewManager.h"
#include "HMIFrameWork/HMIFrameWork.h"
AppViewManager::AppViewManager(QWidget *parent)
    :QWidget(parent)
{
    this->setStyleSheet("QWidget{background:transparent;}");

    setGeometry(QRect(0,0,800,480));

    this->show();
}

AppViewManager::~AppViewManager()
{
}

