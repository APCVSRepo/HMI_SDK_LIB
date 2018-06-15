#include "SettingsDateTimeUI.h"
#include "Home/app/Home.h"
#include "Home/data/Settings/SettingsDateTimeData.h"
#include "HMIFrameWork/log_interface.h"
#include "HMIFrameWork/HMIFrameWork.h"
SettingsDateTimeUI::SettingsDateTimeUI(QWidget *parent)
    :QWidget(parent)
    ,CView(Home::eViewId_Settings_DataTime)
    ,m_pBackBtn(NULL)
    ,m_pTitleLabel(NULL)
    ,m_pLineTime(NULL)
    ,m_pDateTime(NULL)
    ,m_pYearLabel(NULL)
    ,m_pMonLabel(NULL)
    ,m_pDayLabel(NULL)
    ,m_pColonLabel(NULL)
    ,m_pVList(NULL)
{

    this->setGeometry(QRect(0,40,800,440));
    m_pBackBtn = new CPushButton(this);
    m_pBackBtn->setStyleSheet("QPushButton{border:none;background:transparent;}");
    m_pBackBtn->setGeometry(QRect(16,21,198,29));
    m_pBackBtn->SetText(QRect(38,0,160,29),tr("Setting"),22,Qt::AlignLeft|Qt::AlignVCenter,QColor(255,255,255,204));
    m_pBackBtn->SetIcon(QRect(0,0,29,29),":/Settings/button_back.png");
    m_pBackBtn->setFocusPolicy(Qt::NoFocus);
    m_pBackBtn->show();

    m_pTitleLabel = new QLabel(this);
    m_pTitleLabel->setGeometry(QRect(220,21,360,29));
    m_pTitleLabel->setStyleSheet("QLabel{color:#4BA9FF;font-size:24px;border:none;background:transparent;}");
    m_pTitleLabel->setAlignment(Qt::AlignCenter);
    m_pTitleLabel->setText(tr("Time and date"));
    m_pTitleLabel->show();


    m_pLineTime = new QLabel(this);
    m_pLineTime->setGeometry(QRect(54,193,692,51));
    m_pLineTime->setStyleSheet("QLabel{color:#4BA9FF;font-size:24px;border-image:url(:/Settings/line_time.png);background:transparent;}");
    m_pLineTime->show();

    m_pDateTime = new DateTimePicker(this);
    m_pDateTime->setGeometry(QRect(54,121,675,195));
    m_pDateTime->SetItemCountPerPage(3);
    m_pDateTime->CreateYearPicker(2013,2098,QSize(120,65));
    m_pDateTime->SetYearPickerGeometry(0,0,120,195);

    QDate::currentDate();

    m_pDateTime->CreateMonthPicker(QSize(50,65),DateTimePicker::eChineseText);
    m_pDateTime->SetMonthPickerGeometry(182,0,50,195);
    m_pDateTime->CreateDayPicker(QDate::currentDate().daysInMonth(),QSize(50,65));
    m_pDateTime->SetDayPickerGeometry(336,0,50,195);
    m_pDateTime->SetCurrentDate(QDate::currentDate());

    m_pDateTime->CreateHourPicker(QSize(50,65));
    m_pDateTime->SetHourPickerGeometry(466,0,50,195);
    m_pDateTime->CreateMinutePicker(QSize(50,65));
    m_pDateTime->SetMinutePickerGeometry(563,0,50,195);
    m_pDateTime->CreateAMPMPicker(QSize(50,65),3);
    m_pDateTime->SetAMPMPickerGeometry(625,0,50,195);

    INFO() << QTime::currentTime().hour()<<"  " <<TimeTo12HourClock(QTime::currentTime().hour());
    m_pDateTime->SetCurrentHour(TimeTo12HourClock(QTime::currentTime().hour()),true);
    m_pDateTime->SetCurrentMinute(QTime::currentTime().minute(),true);
    m_pDateTime->SetCurrentAMPM(GetAmOrPm(QTime::currentTime().hour()),true);
    m_pDateTime->show();

    m_pYearLabel = new QLabel(this);
    m_pYearLabel->setGeometry(QRect(138,186,96,65));
    m_pYearLabel->setStyleSheet("QLabel{color:rgb(255,255,255);font-size:24px;background:transparent;}");
    m_pYearLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_pYearLabel->setText("Year");
    m_pYearLabel->show();
    m_pMonLabel = new QLabel(this);
    m_pMonLabel->setGeometry(QRect(282,186,96,65));
    m_pMonLabel->setStyleSheet("QLabel{color:rgb(255,255,255);font-size:24px;background:transparent;}");
    m_pMonLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_pMonLabel->setText("Month");
    m_pMonLabel->show();

    m_pDayLabel = new QLabel(this);
    m_pDayLabel->setGeometry(QRect(435,186,96,65));
    m_pDayLabel->setStyleSheet("QLabel{color:rgb(255,255,255);font-size:24px;background:transparent;}");
    m_pDayLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_pDayLabel->setText("Day");
    m_pDayLabel->show();

    m_pColonLabel = new QLabel(this);
    m_pColonLabel->setGeometry(QRect(585,186,26,65));
    m_pColonLabel->setStyleSheet("QLabel{color:rgb(255,255,255);font-size:24px;background:transparent;}");
    m_pColonLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_pColonLabel->setText(":");
    m_pColonLabel->show();


    m_pVList = new CVListWidget(this);
    m_pVList->setGeometry(54,311,718,129);
    m_pVList->SetLeftMargin(0);
    m_pVList->SetSplitLine(":/Settings/line.png",":/Settings/line.png");
    m_pVList->SetScrollBarStyle(4);
    QStringList titieList;
    titieList <<tr("Automatic date and time") << tr("Use 24 hour system");
    for(int i = 0 ; i < titieList.size() ;i++)
    {
        CListWidgetItem item (QSize(718,57));
        if(0 == i)
        {
            QStringList list;
            list<<":/Settings/button_h_on.png"<<""<<"";
            item.SetSpecifiedID(-1);
            item.SetSpecifiedIDStatus(1);
            item.AddText(QRect(0,0,300,57),titieList.at(i),Qt::AlignLeft|Qt::AlignVCenter,24);
            item.AddButton(QRect(647,0,71,57),list);
            m_pDateTime->setEnabled(false);
        }else if(1 == i)
        {
            QStringList list;
            list<<":/Settings/button_h_close.png"<<""<<"";
            item.SetSpecifiedID(-1);
            item.SetSpecifiedIDStatus(0);
            item.AddText(QRect(0,0,300,57),titieList.at(i),Qt::AlignLeft|Qt::AlignVCenter,24);
            item.AddButton(QRect(647,0,71,57),list);
        }
        m_pVList->InsertItem(i,item);
    }
    m_pVList->show();

    m_timer.setInterval(1000);

    InitConnect();

}

SettingsDateTimeUI::~SettingsDateTimeUI()
{

}

void SettingsDateTimeUI::viewAction(int state)
{
    switch (state) {
    case eViewStatus_Active:
        break;
    case eViewStatus_Inactive:
        break;
    default:
        break;
    }
}

bool SettingsDateTimeUI::GetAmOrPm(int hour)
{
    int nhour = hour;
    if(nhour>=0 && nhour < 12)
    {
        return true;
    }else
    {
        return false;
    }
}

int SettingsDateTimeUI::TimeTo12HourClock(int hour)
{
    int nhour = hour;
    if(nhour>=0 && nhour < 12)
    {
        if(0 == nhour)
        {
            nhour = 12;
        }
    }else
    {
        nhour -= 12;
        if(0 == nhour)
        {
            nhour =12;
        }
    }
    return nhour;
}

void SettingsDateTimeUI::InitConnect()
{
    connect(m_pBackBtn,SIGNAL(clicked()),this,SLOT(OnBack()),Qt::UniqueConnection);
    connect(m_pVList,SIGNAL(listButtonReleased(int,int)),this,SLOT(OnListBtnRelease(int,int)),Qt::UniqueConnection);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(OnTimer()),Qt::UniqueConnection);
    m_timer.start();
}

void SettingsDateTimeUI::OnBack()
{
    Home::Inst()->ViewBack();
}

void SettingsDateTimeUI::OnListBtnRelease(int index, int btnIndex)
{
    INFO() <<" SettingsDateTimeUI";
    switch (index) {
    case 0:
    {
        int idStatus =  m_pVList->GetSpecifiedIDStatus(index);
        if(0 == idStatus)
        {
            QStringList list;
            list<<":/Settings/button_h_on.png"<<"none"<<"none";
            m_pVList->SetItemButtonPixmap(index,btnIndex,list);
            m_pVList->SetSpecifiedIDStatus(index,1);
            m_pDateTime->SetCurrentDate(QDateTime::currentDateTime().date(),true);
            if(m_pDateTime->GetIs12HourSystem())
            {
                m_pDateTime->SetCurrentHour(TimeTo12HourClock(QTime::currentTime().hour()),true);
                m_pDateTime->SetCurrentAMPM(GetAmOrPm(QTime::currentTime().hour()),true);
            }else {
                m_pDateTime->SetCurrentHour(QTime::currentTime().hour(),true);
            }
            m_pDateTime->SetCurrentMinute(QTime::currentTime().minute(),true);
            m_timer.start();
            m_pDateTime->setEnabled(false);
        }
        else if(1 == idStatus )
        {
            QStringList list;
            list<<":/Settings/button_h_close.png"<<"none"<<"none";
            m_pVList->SetItemButtonPixmap(index,btnIndex,list);
            m_pVList->SetSpecifiedIDStatus(index,0);
            m_timer.stop();
            m_pDateTime->setEnabled(true);
        }
    }
        break;
    case 1:
    {
        int idStatus =  m_pVList->GetSpecifiedIDStatus(index);
        if(0 == idStatus)
        {
            QStringList list;
            list<<":/Settings/button_h_on.png"<<"none"<<"none";
            m_pVList->SetItemButtonPixmap(index,btnIndex,list);
            m_pVList->SetSpecifiedIDStatus(index,1);
            m_pDateTime->CreateHourPicker(QSize(50,65),false);
            m_pDateTime->SetCurrentHour(QTime::currentTime().hour(),true);
            SettingsDateTimeData::Inst()->SetHour12Or24(false);
            map<string,string> p;
            p.insert(make_pair("HourSystem","24h"));
            HMIFrameWork::Inst()->Notify(STATUSBAR_ID,p);
        }
        else if(1 == idStatus)
        {
            QStringList list;
            list<<":/Settings/button_h_close.png"<<"none"<<"none";
            m_pVList->SetItemButtonPixmap(index,btnIndex,list);
            m_pVList->SetSpecifiedIDStatus(index,0);
            m_pDateTime->CreateHourPicker(QSize(50,65),true);
            m_pDateTime->SetCurrentHour(TimeTo12HourClock(QTime::currentTime().hour()),true);
            SettingsDateTimeData::Inst()->SetHour12Or24(true);
            map<string,string> p;
            p.insert(make_pair("HourSystem","12h"));
            HMIFrameWork::Inst()->Notify(STATUSBAR_ID,p);
        }
    }
        break;
    default:
        break;
    }
}

void SettingsDateTimeUI::OnTimer()
{
    m_pDateTime->SetCurrentDate(QDateTime::currentDateTime().date(),true);
    if(m_pDateTime->GetIs12HourSystem())
    {
        m_pDateTime->SetCurrentHour(TimeTo12HourClock(QTime::currentTime().hour()),true);
        m_pDateTime->SetCurrentAMPM(GetAmOrPm(QTime::currentTime().hour()),true);
    }else {
        m_pDateTime->SetCurrentHour(QTime::currentTime().hour(),true);
    }
    m_pDateTime->SetCurrentMinute(QTime::currentTime().minute(),true);
}
