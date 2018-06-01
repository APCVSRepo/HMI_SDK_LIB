#include "Phone/UI/ContactsDetailsView.h"
#include <QDebug>
#include<unistd.h>
#include <QFont>
#include "AppLayer.h"
#include "HVAC/app/HVAC.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HVAC/data/HVACData.h"
#include "Phone/app/Phone.h"
#include "Phone/data/PhoneData.h"
ContactsDetailsView::ContactsDetailsView(QWidget *parent)
    :QWidget(parent)
    ,CView(Phone::eViewId_ContactsDetails)
    ,m_InputText("")
{
    this->setGeometry(QRect(0,0,800,480));
    this->show();
    InitContactsDetailsView();


    InitConnect();
}

ContactsDetailsView::~ContactsDetailsView()
{

}

void ContactsDetailsView::viewAction(int state)
{
    INFO()<<" ContactsDetailsView  viewAction state = " << state;
    switch (state) {
    case eviewStatus_Init:
    {
    }
        break;
    case eViewStatus_Active:
        PhoneData::Inst()->toWchar("我");

        this->show();
        break;
    default:
        break;
    }
}

void ContactsDetailsView::InitContactsDetailsView()
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


}



void ContactsDetailsView::InitConnect()
{
    connect(m_pKeyboard,SIGNAL(clicked()),this,SLOT(OnKeyBoard()),Qt::UniqueConnection);
    connect(m_pCRecents,SIGNAL(clicked()),this,SLOT(OnRecents()),Qt::UniqueConnection);
    connect(m_pBTSetting,SIGNAL(clicked()),this,SLOT(OnBTSetting()),Qt::UniqueConnection);

}

void ContactsDetailsView::OnKeyBoard()
{
    Phone::Inst()->ViewForwardById(Phone::eViewId_KeyBoard);

}

void ContactsDetailsView::OnRecents()
{
    Phone::Inst()->ViewForwardById(Phone::eViewId_Recents);

}

void ContactsDetailsView::OnBTSetting()
{
    map<string,string> p;
    p.insert(make_pair("BTSetting","Show"));
    p.insert(make_pair("FromAppId",PHONE_ID));
    HMIFrameWork::Inst()->Notify(HOME_ID,p);

}





