#include "Phone/UI/ContactsView.h"
#include "HMIFrameWork/log_interface.h"
#include<unistd.h>
#include <QFont>
#include "AppLayer.h"
#include "HVAC/app/HVAC.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HVAC/data/HVACData.h"
#include "Phone/app/Phone.h"
#include "Phone/data/PhoneData.h"
ContactsView::ContactsView(QWidget *parent)
    :QWidget(parent)
    ,CView(Phone::eViewId_Contacts)
    ,m_InputText("")
{
    this->setGeometry(QRect(0,0,800,480));
    this->show();
    InitContactsView();


    InitConnect();
}

ContactsView::~ContactsView()
{

}

void ContactsView::viewAction(int state)
{
    INFO()<<" ContactsView  viewAction state = " << state;
    switch (state) {
    case eviewStatus_Init:
    {
        UpdateData();
    }
        break;
    case eViewStatus_Active:
        PhoneData::Inst()->SetViewId(Phone::eViewId_Contacts);

        this->show();
        break;
    default:
        break;
    }
}

void ContactsView::InitContactsView()
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
    m_pContactsList->SetItemBackgroundInfo("",":/Phone/Source/images/phone_list_push.png","");
    m_pContactsList->show();

    m_pPhonePickerSelect = new PhonePicker(this);
    m_pPhonePickerSelect->setGeometry(QRect(746,114,32,351));
    m_pPhonePickerSelect->SetItemCountPerPage(27);
    m_pPhonePickerSelect->raise();
    m_pPhonePickerSelect->show();

    QStringList textList;
    textList<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H"<<"I"<<"J"<<"K"\
           <<"L"<<"M"<<"N"<<"O"<<"P"<<"Q"<<"R"<<"S"<<"T"<<"U"<<"V" \
          <<"W"<<"X"<<"Y"<<"Z"<<"#";
    for(int i = 0; i<textList.size();++i)
    {
        m_pPhonePickerSelect->InsertItem(i,textList.at(i),QSize(32,13),10);
    }

    m_pPhonePickerSelectLabel = new QLabel(this);
    m_pPhonePickerSelectLabel->setGeometry(QRect(703,238,50,50));
    m_pPhonePickerSelectLabel->setStyleSheet("QLabel{border-image:url(:/Phone/Source/images/bubble.png);color:rgb(0,138,255);font-size:24px;background:transparent;}");
    m_pPhonePickerSelectLabel->setAlignment(Qt::AlignCenter);
    m_pPhonePickerSelectLabel->setText("A");
    m_pPhonePickerSelectLabel->hide();
}



void ContactsView::InitConnect()
{
    connect(m_pKeyboard,SIGNAL(clicked()),this,SLOT(OnKeyBoard()),Qt::UniqueConnection);
    connect(m_pCRecents,SIGNAL(clicked()),this,SLOT(OnRecents()),Qt::UniqueConnection);
    connect(m_pBTSetting,SIGNAL(clicked()),this,SLOT(OnBTSetting()),Qt::UniqueConnection);
    connect(m_pContactsList,SIGNAL(listItemReleased(int)),this,SLOT(OnListClick(int)),Qt::UniqueConnection);
    connect(m_pPhonePickerSelect,SIGNAL(CurrentText(int,QString)),this,SLOT(OnPhonePickerClick(int,QString)),Qt::UniqueConnection);
}

void ContactsView::UpdateData()
{
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
        QString contacts = "Contacts " + PhoneData::Inst()->GetRecentsInfo().at(i)->FirstName +"  "+ PhoneData::Inst()->GetRecentsInfo().at(i)->LastName;
        item.AddText(QRect(47,18,300,52),contacts,Qt::AlignLeft|Qt::AlignTop,24,QColor(255,255,255));

        m_pContactsList->InsertItem(i,item);
    }
}

void ContactsView::OnKeyBoard()
{
    Phone::Inst()->ViewForwardById(Phone::eViewId_KeyBoard);

}

void ContactsView::OnRecents()
{
    Phone::Inst()->ViewForwardById(Phone::eViewId_Recents);

}

void ContactsView::OnBTSetting()
{
    PhoneData::Inst()->SetViewId(Phone::eViewId_BTSetting);
    map<string,string> p;
    p.insert(make_pair("BTSetting","Show"));
    p.insert(make_pair("FromAppId",PHONE_ID));
    HMIFrameWork::Inst()->Notify(HOME_ID,p);

}

void ContactsView::OnListClick(int index)
{
    PhoneData::Inst()->SetContactsIndex(index);
    Phone::Inst()->ViewForwardById(Phone::eViewId_ContactsDetails);
}

void ContactsView::OnPhonePickerClick(int index, QString text)
{
    if(index>=0)
    {
        m_pPhonePickerSelectLabel->move(703,114+(index+1)*13-6-25);
        m_pPhonePickerSelectLabel->setText(text);
        m_pPhonePickerSelectLabel->show();
    }else
    {
        m_pPhonePickerSelectLabel->hide();
    }
    INFO() <<"OnPhonePickerClick = " <<index<<" " <<text;
}





