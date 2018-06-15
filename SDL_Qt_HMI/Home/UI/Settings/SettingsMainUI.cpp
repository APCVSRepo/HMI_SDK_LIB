#include "SettingsMainUI.h"
#include "HMIFrameWork/log_interface.h"
#include "Home/app/Home.h"
#include "Home/data/Settings/SettingsDateTimeData.h"
#include "Home/data/Settings/SettingsRoutineSettingData.h"
#include "Home/data/Settings/SettingsDisplayData.h"
#include "Home/data/Settings/SettingsMobileApplicationsData.h"
#include "Home/data/Settings/SettingsEmergencyData.h"
#include "Home/data/Settings/SettingsBTData.h"
#include "Home/data/Settings/SettingsWifiData.h"

SettingsMainUI::SettingsMainUI(QWidget *parent)
    :QWidget(parent)
    ,CView(Home::eViewId_Settings_Main)
{
    this->setGeometry(QRect(0,40,800,440));
    this->setStyleSheet("QWidget{border:none;background:transparent;}");
    m_pBackgroundLabel = new QLabel(this);
    m_pBackgroundLabel->setGeometry(QRect(0,0,800,440));
    m_pBackgroundLabel->setStyleSheet("QLabel{border-image:url(:/images/bg.png);background:transparent;}");
    m_pBackgroundLabel->lower();
    m_pBackgroundLabel->show();

    m_pVlist = new CVListWidget(this);
    m_pVlist->setGeometry(54,28,718,386);
    m_pVlist->SetLeftMargin(0);
    m_pVlist->SetSplitLine(":/Settings/line.png",":/Settings/line.png");
    m_pVlist->SetScrollBarStyle(4);
    m_pVlist->SetItemBackgroundInfo("",":/Settings/list_push_bg.png","");
    QStringList titieList;
    titieList <<tr("Sound effect setting") << tr("Time and date") << tr("Routine setting") << \
                 tr("Speech recogniton") << tr("Wi-Fi") << tr("Bluetooth") << tr("Display settings") <<\
                 tr("Mobile applications") << tr("Emergency rescue");
    QStringList textList;
    textList <<tr("Custom") << tr("12h") << tr("English") << \
                 tr("Detailed speech primpt") << tr("Close") << tr("Close") << tr("Auto") <<\
                 tr("Open") << tr("Open");
    for(int i = 0 ; i < titieList.size() ;i++)
    {
        CListWidgetItem item (QSize(718,57));
        QStringList list;
        list<<"none"<<"none"<<"none";
        item.SetSpecifiedID(-1);
        item.AddText(QRect(0,0,300,57),titieList.at(i),Qt::AlignLeft|Qt::AlignVCenter,24);
        item.AddText(QRect(300,0,377,57),textList.at(i),Qt::AlignRight|Qt::AlignVCenter,22,QColor(255,255,255,204));
        item.AddIcon(QRect(692,0,22,57),QPixmap(":/Settings/select_a.png"));
        m_pVlist->InsertItem(i,item);
    }
    m_pVlist->show();

    InitConnect();
}

SettingsMainUI::~SettingsMainUI()
{

}

void SettingsMainUI::InitConnect()
{
    connect(m_pVlist,SIGNAL(listButtonReleased(int,int)),this,SLOT(OnListBtnClick(int,int)),Qt::UniqueConnection);
    connect(m_pVlist,SIGNAL(listItemReleased(int)),this,SLOT(OnListClick(int)),Qt::UniqueConnection);
    connect(SettingsDateTimeData::Inst(),SIGNAL(Hour12Or24Change(bool)),this,SLOT(OnHour12Or24(bool)),Qt::UniqueConnection);
    connect(SettingsRoutineSettingData::Inst(),SIGNAL(LanguageChannge(QString)),this,SLOT(OnLanguageChange(QString)),Qt::UniqueConnection);
    connect(SettingsDisplayData::Inst(),SIGNAL(PatternChannge(QString)),this,SLOT(OnPatternChange(QString)),Qt::UniqueConnection);
    connect(SettingsMobileApplicationsData::Inst(),SIGNAL(MobileApplicationsStatusChange(QString)),this,SLOT(OnMobileApplicationsStatus(QString)),Qt::UniqueConnection);
    connect(SettingsEmergencyData::Inst(),SIGNAL(EmergencRescueStatusChange(QString)),this,SLOT(OnEmergencRescueStatus(QString)),Qt::UniqueConnection);
    connect(SettingsBTData::GetInstance(),SIGNAL(BTStatusChanged(QString)),this,SLOT(OnBTStatusChanged(QString)),Qt::UniqueConnection);
    connect(SettingsWifiData::GetInstance(),SIGNAL(WifiStatusChanged(QString)),this,SLOT(OnWifiStatusChanged(QString)),Qt::UniqueConnection);
}

void SettingsMainUI::viewAction(int state)
{

}



void SettingsMainUI::OnListBtnClick(int index, int btnIndex)
{
    INFO()<<"SettingsMainUI index = " << index <<" btnIndex = " <<btnIndex;
}

void SettingsMainUI::OnListClick(int index)
{
    switch (index) {
    case 0:
   {
        Home::Inst()->ViewForwardById(Home::eViewId_Settings_Sound);
   }
    break;
    case 1:
    {
        Home::Inst()->ViewForwardById(Home::eViewId_Settings_DataTime);
    }
        break;
    case 2:
    {
        Home::Inst()->ViewForwardById(Home::eViewId_Settings_RoutineSetting);

    }
        break;
    case 3:
    {
        Home::Inst()->ViewForwardById(Home::eViewId_Settings_SpeechRecogniton);

    }
        break;
    case 4:
    {
        Home::Inst()->ViewForwardById(Home::eViewId_Settings_Wifi);
    }
        break;
    case 5:
    {
        Home::Inst()->ViewForwardById(Home::eViewId_Settings_BT);
    }
        break;
    case 6:
    {
        Home::Inst()->ViewForwardById(Home::eViewId_Settings_Display);
    }
        break;
    case 7:
    {
        Home::Inst()->ViewForwardById(Home::eViewId_Settings_MobileApplications);
    }
        break;
    case 8:
    {
        Home::Inst()->ViewForwardById(Home::eViewId_Settings_Emergency);
    }
        break;
    default:
        break;
    }
}

void SettingsMainUI::OnHour12Or24(bool bHour12Or24)
{
    if(bHour12Or24)
        m_pVlist->UpdateItemText(1,tr("12h"),1);
    else
        m_pVlist->UpdateItemText(1,tr("24h"),1);

}

void SettingsMainUI::OnLanguageChange(QString language)
{
    m_pVlist->UpdateItemText(2,language,1);
}

void SettingsMainUI::OnPatternChange(QString pattern)
{
    m_pVlist->UpdateItemText(6,pattern,1);
}

void SettingsMainUI::OnMobileApplicationsStatus(QString status)
{
    m_pVlist->UpdateItemText(7,status,1);
}

void SettingsMainUI::OnEmergencRescueStatus(QString status)
{
    m_pVlist->UpdateItemText(8,status,1);
}

void SettingsMainUI::OnBTStatusChanged(QString status)
{
    m_pVlist->UpdateItemText(5,status,1);
}

void SettingsMainUI::OnWifiStatusChanged(QString status)
{
    m_pVlist->UpdateItemText(4,status,1);
}
