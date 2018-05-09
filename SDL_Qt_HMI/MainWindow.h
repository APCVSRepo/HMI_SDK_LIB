#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Home/app/Home.h"
#include "QuickLanuch/app/QuickLanuch.h"
#include "HMIFrameWork/AppManager.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "AppViewManager.h"
#include "SDLApps/app/SDLApps.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void InitHome();
    void InitQuickLanuch();
    void InitSDLApps();

private:
    Ui::MainWindow *ui;
    AppViewManager *m_pAppViewManager;
};

#endif // MAINWINDOW_H
