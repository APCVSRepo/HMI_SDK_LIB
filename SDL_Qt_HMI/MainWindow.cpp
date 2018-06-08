#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Home/app/Home.h"
#include "QuickLanuch/app/QuickLanuch.h"
#include "StatusBar/app/StatusBar.h"
#include "PopUp/app/PopUp.h"
#include "Prompt/app/Prompt.h"
#include "SDLApps/app/SDLApps.h"
#include "HVAC/app/HVAC.h"
#include "Phone/app/Phone.h"
#include "Message/app/Message.h"
#include "Navigation/app/Navigation.h"
#include "Media/app/Media.h"
#include "VR/app/VR.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setGeometry(QRect(0,0,800,480));
    this->resize(800,480);
    this->setStyleSheet("QMainWindow{border-image:url(:/Home/Source/images/bg.png);background:transparent;}");
    m_pAppLayer = new AppLayer(this);
    m_pAppLayer->setGeometry(QRect(0,0,800,480));
    m_pAppLayer->show();
    HMIFrameWork::Inst()->SetMain(reinterpret_cast<void*>(m_pAppLayer));

    InitHome();
    InitStatusBar();
    InitQuickLanuch();
    InitPopUp();
    InitPrompt();
    InitSDLApps();
    InitHVAC();
    InitPhone();
    InitMessage();
    InitNavigation();
    InitMedia();
    InitVR();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitHome()
{

    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (Home::Inst()));
    HMIFrameWork::Inst()->AppShow(HOME_ID,"BootAnimation");
//    HMIFrameWork::Inst()->AppShow(HOME_ID);


}

void MainWindow::InitQuickLanuch()
{
    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (QuickLanuch::Inst()),this);
//    HMIFrameWork::Inst()->AppShow(QUICKLANUCH_ID);
}

void MainWindow::InitStatusBar()
{
    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (StatusBar::Inst()),this);
//    HMIFrameWork::Inst()->AppShow(STATUSBAR_ID);
}

void MainWindow::InitPopUp()
{
    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (PopUp::Inst()),this);
    map<string,string> p;
    p.insert(make_pair("Register","Finish"));
    HMIFrameWork::Inst()->Notify(POPUP_ID,p);
}

void MainWindow::InitPrompt()
{
    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (Prompt::Inst()),this);
    map<string,string> p;
    p.insert(make_pair("Register","Finish"));
    HMIFrameWork::Inst()->Notify(PROMPT_ID,p);
}

void MainWindow::InitSDLApps()
{
    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (SDLApps::Inst()));
}

void MainWindow::InitHVAC()
{
    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (HVAC::Inst()));
}

void MainWindow::InitPhone()
{
    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (Phone::Inst()));

}

void MainWindow::InitMessage()
{
    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (Message::Inst()));
}

void MainWindow::InitNavigation()
{
    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (Navigation::Inst()));
}

void MainWindow::InitMedia()
{
    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (Media::Inst()));
}

void MainWindow::InitVR()
{
    HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (VR::Inst()));
}


void MainWindow::testPopup()
{
    map<string,string> p;
    p.insert(make_pair("PopUpType","General"));
    p.insert(make_pair("PopUpId","test2"));
    p.insert(make_pair("Show","True"));
    p.insert(make_pair("FromAppId",HOME_ID));
    p.insert(make_pair("ContextA","Waiting for \"xiaomi\" to be paired"));
    p.insert(make_pair("ContextALight","\"xiaomi\""));
    p.insert(make_pair("ContextB","Please make sure the code displayed on the \"xiaomi\" matches the following code"));
    p.insert(make_pair("ContextBLight","\"xiaomi\""));
    p.insert(make_pair("Password","123456"));
    //p.insert(make_pair("Title","AAAAAAAAA"));

    p.insert(make_pair("ButtonA","Comfrim"));
    p.insert(make_pair("ReplyButtonA","Comfrim"));

    // p.insert(make_pair("Time","3000"));
    HMIFrameWork::Inst()->Notify(POPUP_ID,p);
}

void MainWindow::testPrompt()
{

    map<string,string> p;
    p.insert(make_pair("PromptType","PromptNav"));
    p.insert(make_pair("PromptId","test2"));
    p.insert(make_pair("Show","True"));
    p.insert(make_pair("FromAppId",HOME_ID));
    p.insert(make_pair("ButtonA",""));
    p.insert(make_pair("ReplyButtonA","enterNav"));
    p.insert(make_pair("NavDirection","AAAA"));
    p.insert(make_pair("NavDistance","180 m"));
    p.insert(make_pair("NavSceneDescription","Get into"));
    p.insert(make_pair("NavDestination","Cao Dong branch"));
   // p.insert(make_pair("Time","3000"));
    HMIFrameWork::Inst()->Notify(PROMPT_ID,p);

    map<string,string> p2;
    p2.insert(make_pair("PromptType","PromptMessage"));
    p2.insert(make_pair("PromptId","test1"));
    p2.insert(make_pair("Show","True"));
    p2.insert(make_pair("FromAppId",HOME_ID));
    p2.insert(make_pair("ButtonA",""));
    p2.insert(make_pair("ReplyButtonA","enterText"));
    p2.insert(make_pair("ButtonB","Ignore"));
    p2.insert(make_pair("ReplyButtonB","Ignore"));
    p2.insert(make_pair("MessageName","AAAA"));
    p2.insert(make_pair("MessageTime","12:12"));
    p2.insert(make_pair("MessageContent","afasgasgasdfasdgawgvasdfasrefsadfefadsf3esdfdasadfadsfe"));
    //p2.insert(make_pair("Time","3000"));
    HMIFrameWork::Inst()->Notify(PROMPT_ID,p2);
}

