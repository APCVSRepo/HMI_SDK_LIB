#include "Phone/UI/ContactsDetailsView.h"
#include "HMIFrameWork/log_interface.h"
#include<unistd.h>
#include <QFont>
#include "HVAC/app/HVAC.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HVAC/data/HVACData.h"
#include "Phone/app/Phone.h"
#include "Phone/data/PhoneData.h"
ContactsDetailsView::ContactsDetailsView(QWidget *parent)
    :QWidget(parent)
    ,CView(Phone::eViewId_ContactsDetails)
{
    this->setGeometry(QRect(0,0,800,480));
    this->hide();
    InitContactsDetailsView();


    InitConnect();
}

ContactsDetailsView::~ContactsDetailsView()
{

}

void ContactsDetailsView::viewAction(int state)
{
    INFO("[Phone] ContactsDetailsView  viewAction state = %d ",state);
    switch (state) {
    case eviewStatus_Init:
    {
    }
        break;
    case eViewStatus_Active:
        PhoneData::Inst()->SetViewId(Phone::eViewId_ContactsDetails);
        UpdateData();
        this->show();
        break;
    default:
        break;
    }
}

void ContactsDetailsView::InitContactsDetailsView()
{
    m_pBackBtn = new CPushButton(this);
    m_pBackBtn->setGeometry(QRect(23,61,160,33));
    m_pBackBtn->setFocusPolicy(Qt::NoFocus);
    m_pBackBtn->setStyleSheet("QPushButton{border:none;color:#838382;font-size:24px;background:transparent;}");
    m_pBackBtn->SetIcon(QRect(0,0,15,27),":/Phone/Source/images/back.png");
    m_pBackBtn->SetText(QRect(31,0,130,33),tr("Contacts"),24,Qt::AlignLeft|Qt::AlignVCenter,QColor(0,138,255));
    m_pBackBtn->show();

    m_pPortraitLabel = new QLabel(this);
    m_pPortraitLabel->setGeometry(QRect(89,147,180,180));
    m_pPortraitLabel->setStyleSheet("QLabel{border-image:url(:/Phone/Source/images/head_portrait.png);background:transparent;}");
    m_pPortraitLabel->show();

    m_pNameLabel = new QLabel(this);
    m_pNameLabel->setGeometry(QRect(89,354,180,41));
    m_pNameLabel->setStyleSheet("QLabel{border:none;color:rgb(255,255,255);font-size:30px;background:transparent;}");
    m_pNameLabel->setAlignment(Qt::AlignCenter);
    m_pNameLabel->setText("Allen");
    m_pNameLabel->show();

    m_pContactsList = new CVListWidget(this);
    m_pContactsList->setGeometry(QRect(293,134,481,346));
    m_pContactsList->SetLeftMargin(0);
    m_pContactsList->SetSplitLine(":/Phone/Source/images/thins_line.png",":/Phone/Source/images/thins_line.png");
    m_pContactsList->SetItemBackgroundInfo("",":/Phone/Source/images/phone_list_push.png","");
    m_pContactsList->SetScrollBarStyle(4);
    m_pContactsList->show();

}



void ContactsDetailsView::InitConnect()
{
    connect(m_pBackBtn,SIGNAL(clicked()),this,SLOT(OnBack()),Qt::UniqueConnection);
    connect(m_pContactsList,SIGNAL(listItemReleased(int)),this,SLOT(OnListClick(int)),Qt::UniqueConnection);
}

void ContactsDetailsView::UpdateData()
{
    m_pContactsList->RemoveAllItems();
    if(NULL!=PhoneData::Inst()->GetContactsDetailInfo())
    {
        QString pic = PhoneData::Inst()->GetContactsDetailInfo()->pictureContact;

        QString name = "";
        if("" == PhoneData::Inst()->GetContactsDetailInfo()->LastName)
        {
            name =PhoneData::Inst()->GetContactsDetailInfo()->FirstName;
        }
        else
        {
            name =PhoneData::Inst()->GetContactsDetailInfo()->FirstName+" "+PhoneData::Inst()->GetContactsDetailInfo()->LastName;
        }
        m_pPortraitLabel->setStyleSheet("QLabel{border-image:url("+pic+");background:transparent;}");
        m_pNameLabel->setText(name);

        CListWidgetItem item1(QSize(481,68));
        item1.AddIcon(QRect(0,0,22,68),QPixmap(":/Phone/Source/images/mobile_phone.png"));
        QString mobile  = tr("Mobile Phone:") + PhoneData::Inst()->GetContactsDetailInfo()->MobileNumber;
        item1.AddText(QRect(47,0,437,68),mobile,Qt::AlignLeft|Qt::AlignVCenter,30);
        m_pContactsList->InsertItem(0,item1);
        m_pContactsList->SetSpecifiedText(0,PhoneData::Inst()->GetContactsDetailInfo()->MobileNumber);
        m_pContactsList->SetSpecifiedText2(0,name);


        CListWidgetItem item2(QSize(481,68));
        item2.AddIcon(QRect(0,0,22,68),QPixmap(":/Phone/Source/images/mobile_phone.png"));
        QString workPhone  = tr("Work Phone:") + PhoneData::Inst()->GetContactsDetailInfo()->WorkNumber;
        item2.AddText(QRect(47,0,437,68),workPhone,Qt::AlignLeft|Qt::AlignVCenter,30);
        m_pContactsList->InsertItem(1,item2);
        m_pContactsList->SetSpecifiedText(1,PhoneData::Inst()->GetContactsDetailInfo()->WorkNumber);
        m_pContactsList->SetSpecifiedText2(1,name);


        CListWidgetItem item3(QSize(481,68));
        item3.AddIcon(QRect(0,0,22,68),QPixmap(":/Phone/Source/images/mobile_phone.png"));
        QString homePhone = tr("Home Phone:") + PhoneData::Inst()->GetContactsDetailInfo()->HomeNumber;
        item3.AddText(QRect(47,0,437,68),homePhone,Qt::AlignLeft|Qt::AlignVCenter,30);
        m_pContactsList->InsertItem(2,item3);
        m_pContactsList->SetSpecifiedText(2,PhoneData::Inst()->GetContactsDetailInfo()->HomeNumber);
        m_pContactsList->SetSpecifiedText2(2,name);

        CListWidgetItem item4(QSize(481,68));
        item4.AddIcon(QRect(0,0,22,68),QPixmap(":/Phone/Source/images/mobile_phone.png"));
        QString others = tr("Others:") + PhoneData::Inst()->GetContactsDetailInfo()->OthersNumber;
        item4.AddText(QRect(47,0,437,68),others,Qt::AlignLeft|Qt::AlignVCenter,30);
        m_pContactsList->InsertItem(3,item4);
        m_pContactsList->SetSpecifiedText(3,PhoneData::Inst()->GetContactsDetailInfo()->OthersNumber);
        m_pContactsList->SetSpecifiedText2(3,name);

    }
}

void ContactsDetailsView::OnBack()
{
    Phone::Inst()->ViewBack();

}

void ContactsDetailsView::OnListClick(int index)
{
    PhoneData::Inst()->SetCallName(m_pContactsList->GetSpecifiedText2(index));
    PhoneData::Inst()->SetCallNumber(m_pContactsList->GetSpecifiedText(index));
    PhoneData::Inst()->SetCallStatus("Call");
    PhoneData::Inst()->SetCallTime(0);

    SPhoneInfo* info = PhoneData::Inst()->findContactsByNumber(m_pContactsList->GetSpecifiedText(0));

    if(NULL != info)
    {
        info->date = QDate::currentDate();
        info->time = QTime::currentTime();
        info->status = eDialCall;
        info->number = m_pContactsList->GetSpecifiedText(index);
        PhoneData::Inst()->SetCallInfo(*info);
    }else{
        SPhoneInfo info;
        info.date = QDate::currentDate();
        info.time = QTime::currentTime();
        info.status = eDialCall;
        info.number = m_pContactsList->GetSpecifiedText(index);
        info.FirstName = m_pContactsList->GetSpecifiedText(index);;
        PhoneData::Inst()->SetCallInfo(info);
    }
    PhoneData::Inst()->SetAddNewCall(true);
    Phone::Inst()->ViewForwardById(Phone::eViewId_Calling);
}







