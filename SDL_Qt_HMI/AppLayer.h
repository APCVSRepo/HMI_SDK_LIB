#ifndef APPLAYER_H
#define APPLAYER_H

#include <QWidget>
#include <Home/UI/HomeView.h>
#include <QProcess>
#include "HMIFrameWork/AppConfig.h"
#include "SDLApps/Templates/UIManager.h"
#include "SDLApps/Templates/Common/AppBase.h"
#include <QDialog>
#include "HMIFrameWork/AppManager.h"

class AppLayer:public QWidget
{
    Q_OBJECT

public:
    AppLayer(QWidget *parent = 0);
    ~AppLayer();

};

#endif // APPLAYER_H
