#ifndef APPVIEWMANAGER_H
#define APPVIEWMANAGER_H

#include <QWidget>
#include <Home/UI/HomeView.h>
#include <QProcess>
#include "HMIFrameWork/AppConfig.h"
#include "SDLApps/Gen3UIManager.h"
#include "SDLApps/Common/AppBase.h"
#include <QDialog>
#include "HMIFrameWork/AppManager.h"

class AppViewManager:public QWidget
{
    Q_OBJECT

public:
    AppViewManager(QWidget *parent = 0);
    ~AppViewManager();

};

#endif // APPVIEWMANAGER_H
