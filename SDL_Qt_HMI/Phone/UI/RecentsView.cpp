#include "Phone/UI/RecentsView.h"
#include "HMIFrameWork/log_interface.h"
#include<unistd.h>
#include <QFont>
#include "HVAC/app/HVAC.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HVAC/data/HVACData.h"
#include "Phone/app/Phone.h"
#include "Phone/data/PhoneData.h"
RecentsView::RecentsView(QWidget *parent)
    :QWidget(parent)
    ,CView(Phone::eViewId_Recents)
    ,m_InputText("")
{
    this->setGeometry(QRect(0,0,800,480));
    this->show();
    InitRecentsView();


    InitConnect();
}

RecentsView::~RecentsView()
{

}

void RecentsView::viewAction(int state)
{
    INFO("[Phone] RecentsView  viewAction state = %d .",state);
    switch (state) {
    case eviewStatus_Init:
    {

    }
        break;
    case eViewStatus_Active:
        PhoneData::Inst()->SetViewId(Phone::eViewId_Recents);
        UpdataData();
        this->show();
        break;
    default:
        break;
    }
}

void RecentsView::InitRecentsView()
{
    m_pKeyboard = new CPushButton(this);
    m_pKeyboard->setGeometry(QRect(29,58,160,33));
    m_pKeyboard->setFocusPolicy(Qt::NoFocus);
    m_pKeyboard->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
    m_pKeyboard->setText("Keyboard");
    m_pKeyboard->show();

    m_pContacts = new CPushButton(this);
    m_pContacts->setGeometry(QRect(223,58,160,33));
    m_pContacts->setFocusPolicy(Qt::NoFocus);
    m_pContacts->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
    m_pContacts->setText("Contacts");
    m_pContacts->show();

    m_pCRecents = new CPushButton(this);
    m_pCRecents->setGeometry(QRect(417,58,160,33));
    m_pCRecents->setFocusPolicy(Qt::NoFocus);
    m_pCRecents->setStyleSheet("QPushButton{border:none;color:#008AFF;font-size:24px;background:transparent;}");
    m_pCRecents->setText("Recents");
    m_pCRecents->show();

    m_pBTSetting = new CPushButton(this);
    m_pBTSetting->setGeometry(QRect(611,58,160,33));
    m_pBTSetting->setFocusPolicy(Qt::NoFocus);
    m_pBTSetting->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
    m_pBTSetting->setText("Bt setting");
    m_pBTSetting->show();


    m_pBlueLineLabel = new  QLabel(this);
    m_pBlueLineLabel->setGeometry(QRect(459,107,76,3));
    m_pBlueLineLabel->setStyleSheet("QLabel{border-image:url(:/Phone/Source/images/underline_of_the_title.png);background:transparent;}");
    m_pBlueLineLabel->show();

    m_pWhiteLineLabel = new  QLabel(this);
    m_pWhiteLineLabel->setGeometry(QRect(54,110,692,3));
    m_pWhiteLineLabel->setStyleSheet("QLabel{border-image:url(:/Phone/Source/images/dotted_line.png);background:transparent;}");
    m_pWhiteLineLabel->show();


    m_pRecentsList = new CVListWidget(this);
    m_pRecentsList->setGeometry(QRect(54,114,724,350));
    m_pRecentsList->SetLeftMargin(0);
    m_pRecentsList->SetSplitLine(":/Phone/Source/images/thins_line.png",":/Phone/Source/images/thins_line.png");
    m_pRecentsList->SetScrollBarStyle(4);
    m_pRecentsList->SetItemBackgroundInfo("",":/Phone/Source/images/phone_list_push.png","");
    m_pRecentsList->show();
}



void RecentsView::InitConnect()
{
    connect(m_pKeyboard,SIGNAL(clicked()),this,SLOT(OnKeyBoard()),Qt::UniqueConnection);
    connect(m_pContacts,SIGNAL(clicked()),this,SLOT(OnContants()),Qt::UniqueConnection);
    connect(m_pBTSetting,SIGNAL(clicked()),this,SLOT(OnBTSetting()),Qt::UniqueConnection);
    connect(m_pRecentsList,SIGNAL(listItemReleased(int)),this,SLOT(OnListClick(int)),Qt::UniqueConnection);

}

void RecentsView::UpdataData()
{
    m_pRecentsList->RemoveAllItems();
    for(int i =0 ; i < PhoneData::Inst()->GetRecentsInfo().size();i++)
    {
        CListWidgetItem item(QSize(692,70));
        if(eIncomingCall_Answer ==  PhoneData::Inst()->GetRecentsInfo().at(i)->status)
        {
            item.AddIcon(QRect(0,20,31,31),QPixmap(":/Phone/Source/images/answer_the_phone.png"));
        }
        else if(eIncomingCall_NotAnswer ==  PhoneData::Inst()->GetRecentsInfo().at(i)->status)
        {
            item.AddIcon(QRect(0,20,31,31),QPixmap(":/Phone/Source/images/answer_the_phone_red.png"));
        }
        else if(eDialCall ==  PhoneData::Inst()->GetRecentsInfo().at(i)->status)
        {
            item.AddIcon(QRect(0,20,31,31),QPixmap(":/Phone/Source/images/call.png"));
        }

        QString name = "";
        if("" == PhoneData::Inst()->GetRecentsInfo().at(i)->LastName)
        {
            name =PhoneData::Inst()->GetRecentsInfo().at(i)->FirstName;
        }
        else
        {
            name =PhoneData::Inst()->GetRecentsInfo().at(i)->FirstName+" "+PhoneData::Inst()->GetRecentsInfo().at(i)->LastName;
        }
        QString contacts = "Contacts " + name;
        item.AddText(QRect(47,18,300,52),contacts,Qt::AlignLeft|Qt::AlignTop,24,QColor(255,255,255));
        int days = DiddDays(PhoneData::Inst()->GetRecentsInfo().at(i)->date,QDateTime::currentDateTime().date());
        QString strDays = "";
        if(0 == days)
        {
            strDays =  "today";
        }else
        {
            strDays = QString::number(days) + tr(" days ago");
        }
        item.AddText(QRect(350,18,342,52),strDays,Qt::AlignRight|Qt::AlignTop,24,QColor(255,255,255));

        m_pRecentsList->InsertItem(i,item);
        m_pRecentsList->SetSpecifiedText(i,name);
        m_pRecentsList->SetSpecifiedText2(i,PhoneData::Inst()->GetRecentsInfo().at(i)->number);
    }
}

int RecentsView::DiddDays(QDate destDate, QDate CompareDate)
{
    int destDays = 0;
    for(int  i=1;i<destDate.month() ;i++)
    {
        QDate temp(destDate.year(),i,1);
        destDays += temp.daysInMonth();
    }
     destDays += destDate.day();


    int CompareDateDays = 0;
    for(int i=1;i<CompareDate.month();i++)
    {
        QDate temp(CompareDate.year(),i,1);
        CompareDateDays += temp.daysInMonth();
    }
    CompareDateDays += CompareDate.day();


    return CompareDateDays - destDays;
}

void RecentsView::OnKeyBoard()
{
    Phone::Inst()->ViewForwardById(Phone::eViewId_KeyBoard);

}

void RecentsView::OnContants()
{
    Phone::Inst()->ViewForwardById(Phone::eViewId_Contacts);

}

void RecentsView::OnBTSetting()
{
    PhoneData::Inst()->SetViewId(Phone::eViewId_BTSetting);
    map<string,string> p;
    p.insert(make_pair("BTSetting","Show"));
    p.insert(make_pair("FromAppId",PHONE_ID));
    HMIFrameWork::Inst()->Notify(HOME_ID,p);

}

void RecentsView::OnListClick(int index)
{
    PhoneData::Inst()->SetCallName(m_pRecentsList->GetSpecifiedText(index));
    PhoneData::Inst()->SetCallNumber(m_pRecentsList->GetSpecifiedText2(index));
    PhoneData::Inst()->SetCallStatus("Call");
    PhoneData::Inst()->SetCallTime(0);
    SPhoneInfo* info = PhoneData::Inst()->findContactsByNumber(m_pRecentsList->GetSpecifiedText2(index));

    INFO("RecentsView::OnListClick name = %s , number = %s",m_pRecentsList->GetSpecifiedText(index).toStdString().c_str(),m_pRecentsList->GetSpecifiedText2(index).toStdString().c_str());
    if(NULL != info)
    {
        INFO("RecentsView  find  %s yes.",info->FirstName.toStdString().c_str());

        info->date = QDate::currentDate();
        info->time = QTime::currentTime();
        info->status = eDialCall;
        info->number = m_pRecentsList->GetSpecifiedText2(index);
        PhoneData::Inst()->SetCallInfo(*info);
    }else{
        SPhoneInfo info;
        info.date = QDate::currentDate();
        info.time = QTime::currentTime();
        info.status = eDialCall;
        info.number = m_pRecentsList->GetSpecifiedText2(index);
        info.FirstName = m_pRecentsList->GetSpecifiedText(index);;
        PhoneData::Inst()->SetCallInfo(info);
    }
    Phone::Inst()->ViewForwardById(Phone::eViewId_Calling);
}





