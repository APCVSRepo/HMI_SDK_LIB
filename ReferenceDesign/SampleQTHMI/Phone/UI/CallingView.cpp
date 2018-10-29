#include "Phone/UI/CallingView.h"
#include "HMIFrameWork/log_interface.h"
#include<unistd.h>
#include <QFont>
#include "HVAC/app/HVAC.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HVAC/data/HVACData.h"
#include "Phone/app/Phone.h"
#include "Phone/data/PhoneData.h"
CallingView::CallingView(QWidget *parent)
    :QWidget(parent)
    ,CView(Phone::eViewId_Calling)
    ,m_InputText("")
{
    this->setGeometry(QRect(0,0,800,480));
    this->show();
    InitCallingView();


    InitConnect();
}

CallingView::~CallingView()
{

}

void CallingView::viewAction(int state)
{
    INFO("CallingView  viewAction state = %d .", state);
    switch (state) {
    case eviewStatus_Init:
    {

    }
        break;
    case eViewStatus_Active:
        if(PhoneData::Inst()->GetAddNewCall())
        {
            PhoneData::Inst()->SetAddNewCall(false);
            UpdateData();
            AddCall();
            PhoneData::Inst()->SetCallingStatus(true);

            map<string,string> p;
            p.insert(make_pair("PhoneCallStatus","true"));
            HMIFrameWork::Inst()->Notify(SDLAPPS_ID,p);
        }
        this->show();
        break;
    case eViewStatus_Inactive:
        break;
    default:
        break;
    }
}

void CallingView::InitCallingView()
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
    m_pContacts->setStyleSheet("QPushButton{border:none;color:#008AFF;font-size:24px;background:transparent;}");
    m_pContacts->setText("Contacts");
    m_pContacts->show();

    m_pCRecents = new CPushButton(this);
    m_pCRecents->setGeometry(QRect(417,58,160,33));
    m_pCRecents->setFocusPolicy(Qt::NoFocus);
    m_pCRecents->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
    m_pCRecents->setText("Recents");
    m_pCRecents->show();

    m_pBTSetting = new CPushButton(this);
    m_pBTSetting->setGeometry(QRect(611,58,160,33));
    m_pBTSetting->setFocusPolicy(Qt::NoFocus);
    m_pBTSetting->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
    m_pBTSetting->setText("Bt setting");
    m_pBTSetting->show();


    m_pBlueLineLabel = new  QLabel(this);
    m_pBlueLineLabel->setGeometry(QRect(267,107,76,3));
    m_pBlueLineLabel->setStyleSheet("QLabel{border-image:url(:/Phone/Source/images/underline_of_the_title.png);background:transparent;}");
    m_pBlueLineLabel->show();

    m_pWhiteLineLabel = new  QLabel(this);
    m_pWhiteLineLabel->setGeometry(QRect(54,110,692,3));
    m_pWhiteLineLabel->setStyleSheet("QLabel{border-image:url(:/Phone/Source/images/dotted_line.png);background:transparent;}");
    m_pWhiteLineLabel->show();

    m_pContactsList = new CVListWidget(this);
    m_pContactsList->setGeometry(QRect(54,114,724,350));
    m_pContactsList->SetLeftMargin(0);
    m_pContactsList->SetSplitLine(":/Phone/Source/images/thins_line.png",":/Phone/Source/images/thins_line.png");
    m_pContactsList->SetScrollBarStyle(4);
    m_pContactsList->AutoSetSelected(false);
   // m_pContactsList->SetItemBackgroundInfo("",":/Phone/Source/images/phone_list_push.png","");
    m_pContactsList->show();


    m_pHangUpBtn = new CPushButton(this);
    m_pHangUpBtn->setGeometry(QRect(96,402,140,50));
    m_pHangUpBtn->setFocusPolicy(Qt::NoFocus);
    m_pHangUpBtn->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/hang_up_normal.png);color:#FFFFFF;font-size:24px;background:transparent;}");
    m_pHangUpBtn->show();

    m_pCallBtn = new CPushButton(this);
    m_pCallBtn->setGeometry(QRect(256,402,140,50));
    m_pCallBtn->setFocusPolicy(Qt::NoFocus);
    m_pCallBtn->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/box_normal.png);color:#FFFFFF;font-size:24px;background:transparent;}");
    m_pCallBtn->setText(tr("Call"));
    m_pCallBtn->SetEnabled(false);
    m_pCallBtn->show();

    m_pMuteBtn = new CPushButton(this);
    m_pMuteBtn->setGeometry(QRect(416,402,140,50));
    m_pMuteBtn->setFocusPolicy(Qt::NoFocus);
    m_pMuteBtn->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/box_normal.png);color:#FFFFFF;font-size:24px;background:transparent;}");
    m_pMuteBtn->setText(tr("Mute"));
    m_pMuteBtn->SetEffect(0.5);
    m_pMuteBtn->SetStatus(CPushButton::eStatus_Normal);
    m_pMuteBtn->show();

    m_pReceiverBtn = new CPushButton(this);
    m_pReceiverBtn->setGeometry(QRect(576,402,140,50));
    m_pReceiverBtn->setFocusPolicy(Qt::NoFocus);
    m_pReceiverBtn->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/box_normal.png);color:#FFFFFF;font-size:24px;background:transparent;}");
    m_pReceiverBtn->setText(tr("Receiver"));
    m_pReceiverBtn->SetEffect(0.5);
    m_pReceiverBtn->SetStatus(CPushButton::eStatus_Normal);
    m_pReceiverBtn->show();

    m_callTimer1.setInterval(1000);

}



void CallingView::InitConnect()
{
    connect(m_pKeyboard,SIGNAL(clicked()),this,SLOT(OnKeyBoard()),Qt::UniqueConnection);
    connect(m_pCRecents,SIGNAL(clicked()),this,SLOT(OnRecents()),Qt::UniqueConnection);
    connect(m_pBTSetting,SIGNAL(clicked()),this,SLOT(OnBTSetting()),Qt::UniqueConnection);
    connect(m_pHangUpBtn,SIGNAL(clicked()),this,SLOT(OnHangUp()),Qt::UniqueConnection);
    connect(m_pMuteBtn,SIGNAL(clicked()),this,SLOT(OnMute()),Qt::UniqueConnection);
    connect(m_pReceiverBtn,SIGNAL(clicked()),this,SLOT(OnReceiver()),Qt::UniqueConnection);
    connect(&m_callTimer1,SIGNAL(timeout()),this,SLOT(OnCallTimer()),Qt::UniqueConnection);
}

void CallingView::AddCall()
{
    if(m_pContactsList->count()==0)
    {
        //add data
        QString name = PhoneData::Inst()->GetCallName();
        QString number = PhoneData::Inst()->GetCallNumber();
        QString time = PhoneData::Inst()->GetCallTIme();
        QString status = PhoneData::Inst()->GetCallStatus();
        CListWidgetItem item(QSize(692,94));
        item.AddIcon(QRect(0,0,75,74),QPixmap(":/Phone/Source/images/head_portrait_normal.png"));
        item.AddText(QRect(87,9,300,41),name,Qt::AlignLeft|Qt::AlignVCenter,30);
        item.AddText(QRect(87,51,180,33),number,Qt::AlignLeft|Qt::AlignVCenter,24);
        item.AddText(QRect(400,15,292,33),time,Qt::AlignRight|Qt::AlignVCenter,24);
        item.AddText(QRect(400,51,292,33),status,Qt::AlignRight|Qt::AlignVCenter,30,QColor(0,174,4));
        m_pContactsList->InsertItem(0,item);
        m_iCallTime1 = PhoneData::Inst()->GetCallTimeToInt();
        m_callTimer1.start();

        SPhoneInfo &info = PhoneData::Inst()->CurCall();
        PhoneData::Inst()->addNewRecentsInfo(info);


    }else if(1 == m_pContactsList->count())
    {
        //add data
        QString name = PhoneData::Inst()->GetCallName();
        QString number = PhoneData::Inst()->GetCallNumber();
        QString time = PhoneData::Inst()->GetCallTIme();
        QString status = PhoneData::Inst()->GetCallStatus();
        CListWidgetItem item(QSize(692,94));
        item.AddIcon(QRect(0,0,75,74),QPixmap(":/Phone/Source/images/head_portrait_normal.png"));
        item.AddText(QRect(87,9,300,41),name,Qt::AlignLeft|Qt::AlignVCenter,30);
        item.AddText(QRect(87,51,180,33),number,Qt::AlignLeft|Qt::AlignVCenter,24);
        item.AddText(QRect(400,15,292,33),time,Qt::AlignRight|Qt::AlignVCenter,24);
        item.AddText(QRect(400,51,292,33),status,Qt::AlignRight|Qt::AlignVCenter,30,QColor(0,174,4));
        m_pContactsList->InsertItem(0,item);
        m_iCallTime2 = PhoneData::Inst()->GetCallTimeToInt();
    }

}

void CallingView::UpdateData()
{
    int Id = PhoneData::Inst()->GetViewId();
    switch (Id) {
    case Phone::eViewId_KeyBoard:
    {
        m_pKeyboard->setGeometry(QRect(29,58,160,33));
        m_pKeyboard->setFocusPolicy(Qt::NoFocus);
        m_pKeyboard->setStyleSheet("QPushButton{border:none;color:#008AFF;font-size:24px;background:transparent;}");
        m_pKeyboard->setText("Keyboard");
        m_pKeyboard->show();

        m_pContacts->setGeometry(QRect(223,58,160,33));
        m_pContacts->setFocusPolicy(Qt::NoFocus);
        m_pContacts->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
        m_pContacts->setText("Contacts");
        m_pContacts->show();

        m_pCRecents->setGeometry(QRect(417,58,160,33));
        m_pCRecents->setFocusPolicy(Qt::NoFocus);
        m_pCRecents->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
        m_pCRecents->setText("Recents");
        m_pCRecents->show();

        m_pBTSetting->setGeometry(QRect(611,58,160,33));
        m_pBTSetting->setFocusPolicy(Qt::NoFocus);
        m_pBTSetting->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
        m_pBTSetting->setText("Bt setting");
        m_pBTSetting->show();


        m_pBlueLineLabel->setGeometry(QRect(75,107,76,3));
        m_pBlueLineLabel->setStyleSheet("QLabel{border-image:url(:/Phone/Source/images/underline_of_the_title.png);background:transparent;}");
        m_pBlueLineLabel->show();
    }
        break;
    case Phone::eViewId_Contacts:
    case Phone::eViewId_ContactsDetails:
    {
        m_pKeyboard->setGeometry(QRect(29,58,160,33));
        m_pKeyboard->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
        m_pKeyboard->setText("Keyboard");
        m_pKeyboard->show();

        m_pContacts->setGeometry(QRect(223,58,160,33));
        m_pContacts->setFocusPolicy(Qt::NoFocus);
        m_pContacts->setStyleSheet("QPushButton{border:none;color:#008AFF;font-size:24px;background:transparent;}");
        m_pContacts->setText("Contacts");
        m_pContacts->show();

        m_pCRecents->setGeometry(QRect(417,58,160,33));
        m_pCRecents->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
        m_pCRecents->setText("Recents");
        m_pCRecents->show();

        m_pBTSetting->setGeometry(QRect(611,58,160,33));
        m_pBTSetting->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
        m_pBTSetting->setText("Bt setting");
        m_pBTSetting->show();

        m_pBlueLineLabel->setGeometry(QRect(267,107,76,3));
        m_pBlueLineLabel->setStyleSheet("QLabel{border-image:url(:/Phone/Source/images/underline_of_the_title.png);background:transparent;}");
        m_pBlueLineLabel->show();
    }
        break;
    case Phone::eViewId_Recents:
    {
        m_pKeyboard->setGeometry(QRect(29,58,160,33));
        m_pKeyboard->setFocusPolicy(Qt::NoFocus);
        m_pKeyboard->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
        m_pKeyboard->setText("Keyboard");
        m_pKeyboard->show();

        m_pContacts->setGeometry(QRect(223,58,160,33));
        m_pContacts->setFocusPolicy(Qt::NoFocus);
        m_pContacts->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
        m_pContacts->setText("Contacts");
        m_pContacts->show();

        m_pCRecents->setGeometry(QRect(417,58,160,33));
        m_pCRecents->setFocusPolicy(Qt::NoFocus);
        m_pCRecents->setStyleSheet("QPushButton{border:none;color:#008AFF;font-size:24px;background:transparent;}");
        m_pCRecents->setText("Recents");
        m_pCRecents->show();

        m_pBTSetting->setGeometry(QRect(611,58,160,33));
        m_pBTSetting->setFocusPolicy(Qt::NoFocus);
        m_pBTSetting->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
        m_pBTSetting->setText("Bt setting");
        m_pBTSetting->show();

        m_pBlueLineLabel->setGeometry(QRect(459,107,76,3));
        m_pBlueLineLabel->setStyleSheet("QLabel{border-image:url(:/Phone/Source/images/underline_of_the_title.png);background:transparent;}");
        m_pBlueLineLabel->show();
    }
        break;
    case Phone::eViewId_BTSetting:
    {
        m_pKeyboard->setGeometry(QRect(29,58,160,33));
        m_pKeyboard->setFocusPolicy(Qt::NoFocus);
        m_pKeyboard->setStyleSheet("QPushButton{border:none;color:#008AFF;font-size:24px;background:transparent;}");
        m_pKeyboard->setText("Keyboard");
        m_pKeyboard->show();

        m_pContacts->setGeometry(QRect(223,58,160,33));
        m_pContacts->setFocusPolicy(Qt::NoFocus);
        m_pContacts->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
        m_pContacts->setText("Contacts");
        m_pContacts->show();

        m_pCRecents->setGeometry(QRect(417,58,160,33));
        m_pCRecents->setFocusPolicy(Qt::NoFocus);
        m_pCRecents->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
        m_pCRecents->setText("Recents");
        m_pCRecents->show();

        m_pBTSetting->setGeometry(QRect(611,58,160,33));
        m_pBTSetting->setFocusPolicy(Qt::NoFocus);
        m_pBTSetting->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
        m_pBTSetting->setText("Bt setting");
        m_pBTSetting->show();


        m_pBlueLineLabel->setGeometry(QRect(653,107,76,3));
        m_pBlueLineLabel->setStyleSheet("QLabel{border-image:url(:/Phone/Source/images/underline_of_the_title.png);background:transparent;}");
        m_pBlueLineLabel->show();
    }
        break;
    default:
        break;
    }
    m_pKeyboard->SetEnabled(false);
    m_pContacts->SetEnabled(false);
    m_pCRecents->SetEnabled(false);
    m_pBTSetting->SetEnabled(false);
}

void CallingView::OnKeyBoard()
{

}

void CallingView::OnRecents()
{

}

void CallingView::OnBTSetting()
{

}

void CallingView::OnHangUp()
{
    m_callTimer1.stop();
    PhoneData::Inst()->SetCallingStatus(false);

    map<string,string> p;
    p.insert(make_pair("PhoneCallStatus","false"));
    HMIFrameWork::Inst()->Notify(SDLAPPS_ID,p);

    if(Phone::Inst()->IsOutAppCall())
    {
        HMIFrameWork::Inst()->AppBack();
    }
    Phone::Inst()->ViewBack();
    m_pContactsList->RemoveAllItems();
}

void CallingView::OnMute()
{
    if(CPushButton::eStatus_Normal == m_pMuteBtn->GetStatus())
    {
        m_pMuteBtn->SetEffect(1.0);
        m_pMuteBtn->SetStatus(CPushButton::eStatus_Select);
    }else if(CPushButton::eStatus_Select == m_pMuteBtn->GetStatus())
    {
        m_pMuteBtn->SetEffect(0.5);
        m_pMuteBtn->SetStatus(CPushButton::eStatus_Normal);
    }
}

void CallingView::OnReceiver()
{
    if(CPushButton::eStatus_Normal == m_pReceiverBtn->GetStatus())
    {
        m_pReceiverBtn->SetEffect(1.0);
        m_pReceiverBtn->SetStatus(CPushButton::eStatus_Select);
    }else if(CPushButton::eStatus_Select == m_pReceiverBtn->GetStatus())
    {
        m_pReceiverBtn->SetEffect(0.5);
        m_pReceiverBtn->SetStatus(CPushButton::eStatus_Normal);
    }
}

void CallingView::OnCallTimer()
{
  m_iCallTime1+=1;
  QString time = PhoneData::Inst()->ToTime(m_iCallTime1);
  m_pContactsList->UpdateItemText(0,time,2);
}

