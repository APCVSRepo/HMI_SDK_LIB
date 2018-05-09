#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(800,480);

    m_pAppLayer = new AppLayer(this);
    m_pAppLayer->setGeometry(QRect(0,0,800,480));
    m_pAppLayer->show();
    HMIFrameWork::Inst()->SetMain(reinterpret_cast<void*>(m_pAppLayer));

    InitHome();
    InitQuickLanuch();
    InitSDLApps();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitHome()
{

    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (Home::Inst()));
    HMIFrameWork::Inst()->AppShow(HOME_ID);
}

void MainWindow::InitQuickLanuch()
{
    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (QuickLanuch::Inst()),this);
    HMIFrameWork::Inst()->AppShow(QUICKLANUCH_ID);
}

void MainWindow::InitSDLApps()
{
    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (SDLApps::Inst()));
}

