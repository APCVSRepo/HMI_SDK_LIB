#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "HMIFrameWork/AppManager.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "AppLayer.h"
#include <QLabel>
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
    void InitStatusBar();
    void InitPopUp();
    void InitSDLApps();
    void InitHVAC();
    void InitPhone();

private:
    Ui::MainWindow *ui;
    QLabel *m_pBackgroundLabel;
    AppLayer *m_pAppLayer;

};

#endif // MAINWINDOW_H
