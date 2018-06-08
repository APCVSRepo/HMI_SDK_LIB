#include "Phone/UI/KeyBoardView.h"
#include "HMIFrameWork/log_interface.h"
#include<unistd.h>
#include <QFont>
#include "AppLayer.h"
#include "HVAC/app/HVAC.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HVAC/data/HVACData.h"
#include "Phone/app/Phone.h"
#include "Phone/data/PhoneData.h"
KeyBoardView::KeyBoardView(QWidget *parent)
    :QWidget(parent)
    ,CView(Phone::eViewId_KeyBoard)
    ,m_InputText("")
{
    this->setGeometry(QRect(0,0,800,480));
    this->show();
    InitKeyBoardView();


    InitConnect();
}

KeyBoardView::~KeyBoardView()
{

}

void KeyBoardView::viewAction(int state)
{
    INFO()<<" KeyBoardView  viewAction state = " << state;
    switch (state) {
    case eviewStatus_Init:
    {
    }
        break;
    case eViewStatus_Active:
        PhoneData::Inst()->SetViewId(Phone::eViewId_KeyBoard);

        this->show();
        break;
    default:
        break;
    }
}

void KeyBoardView::InitKeyBoardView()
{
    m_pKeyboard = new CPushButton(this);
    m_pKeyboard->setGeometry(QRect(29,58,160,33));
    m_pKeyboard->setFocusPolicy(Qt::NoFocus);
    m_pKeyboard->setStyleSheet("QPushButton{border:none;color:#008AFF;font-size:24px;background:transparent;}");
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
    m_pBlueLineLabel->setGeometry(QRect(75,107,76,3));
    m_pBlueLineLabel->setStyleSheet("QLabel{border-image:url(:/Phone/Source/images/underline_of_the_title.png);background:transparent;}");
    m_pBlueLineLabel->show();

    m_pWhiteLineLabel = new  QLabel(this);
    m_pWhiteLineLabel->setGeometry(QRect(54,110,692,3));
    m_pWhiteLineLabel->setStyleSheet("QLabel{border-image:url(:/Phone/Source/images/dotted_line.png);background:transparent;}");
    m_pWhiteLineLabel->show();

    m_pNumberInputLabel = new  QLabel(this);
    m_pNumberInputLabel->setGeometry(QRect(54,129,350,50));
    m_pNumberInputLabel->setStyleSheet("QLabel{border-image:url(:/Phone/Source/images/dial_up_box.png);background:transparent;}");
    m_pNumberInputLabel->show();

    m_pNumberInput = new QLineEdit(this);
    m_pNumberInput->setGeometry(QRect(79,133,300,41));
    m_pNumberInput->setStyleSheet("QLineEdit{border:none;color:#FFB121;font-size:30px;background:transparent;}");
    m_pNumberInput->setAlignment(Qt::AlignCenter);
    m_pNumberInput->show();


    m_pNumber1 = new CPushButton(this);
    m_pNumber1->setGeometry(QRect(54,194,80,60));
    m_pNumber1->setFocusPolicy(Qt::NoFocus);
    m_pNumber1->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/1_normal.png);background:transparent;}");
    m_pNumber1->show();

    m_pNumber2 = new CPushButton(this);
    m_pNumber2->setGeometry(QRect(144,194,80,60));
    m_pNumber2->setFocusPolicy(Qt::NoFocus);
    m_pNumber2->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/2_normal.png);background:transparent;}");
    m_pNumber2->show();

    m_pNumber3 = new CPushButton(this);
    m_pNumber3->setGeometry(QRect(234,194,80,60));
    m_pNumber3->setFocusPolicy(Qt::NoFocus);
    m_pNumber3->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/3_normal.png);background:transparent;}");
    m_pNumber3->show();



    m_pNumberDelete = new CPushButton(this);
    m_pNumberDelete->setGeometry(QRect(324,194,80,60));
    m_pNumberDelete->setFocusPolicy(Qt::NoFocus);
    m_pNumberDelete->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/delete_normal.png);background:transparent;}");
    m_pNumberDelete->show();

    m_pNumber4 = new CPushButton(this);
    m_pNumber4->setGeometry(QRect(54,264,80,60));
    m_pNumber4->setFocusPolicy(Qt::NoFocus);
    m_pNumber4->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/4_normal.png);background:transparent;}");
    m_pNumber4->show();

    m_pNumber5 = new CPushButton(this);
    m_pNumber5->setGeometry(QRect(144,264,80,60));
    m_pNumber5->setFocusPolicy(Qt::NoFocus);
    m_pNumber5->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/5_normal.png);background:transparent;}");
    m_pNumber5->show();

    m_pNumber6 = new CPushButton(this);
    m_pNumber6->setGeometry(QRect(234,264,80,60));
    m_pNumber6->setFocusPolicy(Qt::NoFocus);
    m_pNumber6->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/6_normal.png);background:transparent;}");
    m_pNumber6->show();


    m_pNumberDial = new CPushButton(this);
    m_pNumberDial->setGeometry(QRect(324,264,80,200));
    m_pNumberDial->setFocusPolicy(Qt::NoFocus);
    m_pNumberDial->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/phone_normal.png);background:transparent;}");
    m_pNumberDial->show();

    m_pNumber7 = new CPushButton(this);
    m_pNumber7->setGeometry(QRect(54,334,80,60));
    m_pNumber7->setFocusPolicy(Qt::NoFocus);
    m_pNumber7->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/7_normal.png);background:transparent;}");
    m_pNumber7->show();

    m_pNumber8 = new CPushButton(this);
    m_pNumber8->setGeometry(QRect(144,334,80,60));
    m_pNumber8->setFocusPolicy(Qt::NoFocus);
    m_pNumber8->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/8_normal.png);background:transparent;}");
    m_pNumber8->show();

    m_pNumber9 = new CPushButton(this);
    m_pNumber9->setGeometry(QRect(234,334,80,60));
    m_pNumber9->setFocusPolicy(Qt::NoFocus);
    m_pNumber9->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/9_normal.png);background:transparent;}");
    m_pNumber9->show();


    m_pNumbercStarSymbol = new CPushButton(this);
    m_pNumbercStarSymbol->setGeometry(QRect(54,404,80,60));
    m_pNumbercStarSymbol->setFocusPolicy(Qt::NoFocus);
    m_pNumbercStarSymbol->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/10_normal.png);background:transparent;}");
    m_pNumbercStarSymbol->show();

    m_pNumber0 = new CPushButton(this);
    m_pNumber0->setGeometry(QRect(144,404,80,60));
    m_pNumber0->setFocusPolicy(Qt::NoFocus);
    m_pNumber0->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/0_normal.png);background:transparent;}");
    m_pNumber0->show();

    m_pNumberdWellSymbol = new CPushButton(this);
    m_pNumberdWellSymbol->setGeometry(QRect(234,404,80,60));
    m_pNumberdWellSymbol->setFocusPolicy(Qt::NoFocus);
    m_pNumberdWellSymbol->setStyleSheet("QPushButton{border-image:url(:/Phone/Source/images/#_normal.png);background:transparent;}");
    m_pNumberdWellSymbol->show();

    m_pBtttonGroup = new QButtonGroup;
    m_pBtttonGroup->addButton(m_pNumber0,eNumber_0);
    m_pBtttonGroup->addButton(m_pNumber1,eNumber_1);
    m_pBtttonGroup->addButton(m_pNumber2,eNumber_2);
    m_pBtttonGroup->addButton(m_pNumber3,eNumber_3);
    m_pBtttonGroup->addButton(m_pNumber4,eNumber_4);
    m_pBtttonGroup->addButton(m_pNumber5,eNumber_5);
    m_pBtttonGroup->addButton(m_pNumber6,eNumber_6);
    m_pBtttonGroup->addButton(m_pNumber7,eNumber_7);
    m_pBtttonGroup->addButton(m_pNumber8,eNumber_8);
    m_pBtttonGroup->addButton(m_pNumber9,eNumber_9);
    m_pBtttonGroup->addButton(m_pNumberDelete,eNumber_Delete);
    m_pBtttonGroup->addButton(m_pNumberDial,eNumber_Dial);
    m_pBtttonGroup->addButton(m_pNumbercStarSymbol,eNumber_Star);
    m_pBtttonGroup->addButton(m_pNumberdWellSymbol,eNumber_Well);


    m_pMatchContactsList = new CVListWidget(this);
    m_pMatchContactsList->setGeometry(QRect(420,158,354,296));
    m_pMatchContactsList->SetLeftMargin(0);
    m_pMatchContactsList->SetSplitLine(":/Phone/Source/images/thins_line.png",":/Phone/Source/images/thins_line.png");
    m_pMatchContactsList->SetScrollBarStyle(4);
    m_pMatchContactsList->SetItemBackgroundInfo("",":/Phone/Source/images/phone_list_push.png","");
    m_pMatchContactsList->show();
}



void KeyBoardView::InitConnect()
{
    connect(m_pBtttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(OnKeyBoard(int)),Qt::UniqueConnection);
    connect(m_pNumberDelete,SIGNAL(LongPress()),this,SLOT(OnDeleteLongPress()),Qt::UniqueConnection);
    connect(m_pNumberInput,SIGNAL(textChanged(QString)),this,SLOT(OnTextChange(QString)),Qt::UniqueConnection);
    connect(m_pContacts,SIGNAL(clicked()),this,SLOT(OnContacts()),Qt::UniqueConnection);
    connect(m_pCRecents,SIGNAL(clicked()),this,SLOT(OnRecents()),Qt::UniqueConnection);
    connect(m_pBTSetting,SIGNAL(clicked()),this,SLOT(OnBTSetting()),Qt::UniqueConnection);
    connect(m_pMatchContactsList,SIGNAL(listItemReleased(int)),this,SLOT(OnListClick(int)),Qt::UniqueConnection);


}

void KeyBoardView::MachContacts(const QString &number)
{
    m_pMatchContactsList->RemoveAllItems(false);
    QList<SMatchContact*>& slist = PhoneData::Inst()->GetMatchContacts(number);
    for(int i = 0 ; i < slist.size();i++)
    {
        CListWidgetItem item(QSize(326,59));
        QString name ;
        if("" ==  slist.at(i)->LastName)
        {
            name = slist.at(i)->FirstName;
        }
        else
        {
            name = slist.at(i)->FirstName+ " " + slist.at(i)->LastName;
        }
        item.AddText(QRect(32,0,304,59),tr("Contacts ")+name,Qt::AlignLeft|Qt::AlignVCenter,24);
        m_pMatchContactsList->InsertItem(i,item);
        m_pMatchContactsList->SetSpecifiedText(i,name);
        m_pMatchContactsList->SetSpecifiedText2(i,slist.at(i)->number);
    }
}

void KeyBoardView::OnKeyBoard(int Id)
{
    switch (Id) {
    case eNumber_0:
    {
        m_InputText.append("0");
        m_pNumberInput->setText(m_InputText);
    }
        break;
    case eNumber_1:
    {
        m_InputText.append("1");
        m_pNumberInput->setText(m_InputText);
    }
        break;
    case eNumber_2:
    {
        m_InputText.append("2");
        m_pNumberInput->setText(m_InputText);
    }
        break;
    case eNumber_3:
    {
        m_InputText.append("3");
        m_pNumberInput->setText(m_InputText);
    }
        break;
    case eNumber_4:
    {
        m_InputText.append("4");
        m_pNumberInput->setText(m_InputText);
    }
        break;
    case eNumber_5:
    {
        m_InputText.append("5");
        m_pNumberInput->setText(m_InputText);
    }
        break;
    case eNumber_6:
    {
        m_InputText.append("6");
        m_pNumberInput->setText(m_InputText);
    }
        break;
    case eNumber_7:
    {
        m_InputText.append("7");
        m_pNumberInput->setText(m_InputText);
    }
        break;
    case eNumber_8:
    {
        m_InputText.append("8");
        m_pNumberInput->setText(m_InputText);
    }
        break;
    case eNumber_9:
    {
        m_InputText.append("9");
        m_pNumberInput->setText(m_InputText);
    }
        break;
    case eNumber_Delete:
    {
        if(m_InputText.length()>0)
        {
            m_InputText = m_InputText.left(m_InputText.length()-1);
            m_pNumberInput->setText(m_InputText);
        }
    }
        break;
    case eNumber_Dial:
    {
        if(m_pNumberInput->text().length() > 0)
        {
            PhoneData::Inst()->SetCallNumber(m_pNumberInput->text());
            PhoneData::Inst()->SetCallName(m_pNumberInput->text());
            PhoneData::Inst()->SetCallTime(0);
            PhoneData::Inst()->SetCallStatus("Call");

            Phone::Inst()->ViewForwardById(Phone::eViewId_Calling);
            PhoneData::Inst()->SetViewId(Phone::eViewId_KeyBoard);
        }
    }
        break;
    case eNumber_Star:
    {
        m_InputText.append("*");
        m_pNumberInput->setText(m_InputText);
    }
        break;
    case eNumber_Well:
    {
        m_InputText.append("#");
        m_pNumberInput->setText(m_InputText);
    }
        break;
    default:
        break;
    }
}

void KeyBoardView::OnDeleteLongPress()
{
    if(m_InputText.length()>0)
    {
        m_InputText = m_InputText.left(m_InputText.length()-1);
        m_pNumberInput->setText(m_InputText);
    }
}

void KeyBoardView::OnTextChange(QString text)
{
    if(text.length()>2)
    {
        INFO() <<" aaaaaaaaaaa";
        MachContacts(m_pNumberInput->text());
    }else if(m_pNumberInput->text().length()<=2)
    {
        INFO() <<" bbbbbbbbbb";
        if(m_pMatchContactsList->count()>0)
            m_pMatchContactsList->RemoveAllItems();
    }
    INFO() << "  OnTextChange " <<text;
}

void KeyBoardView::OnContacts()
{
   Phone::Inst()->ViewForwardById(Phone::eViewId_Contacts);
}

void KeyBoardView::OnRecents()
{
   Phone::Inst()->ViewForwardById(Phone::eViewId_Recents);
}

void KeyBoardView::OnBTSetting()
{
    PhoneData::Inst()->SetViewId(Phone::eViewId_BTSetting);
    map<string,string> p;
    p.insert(make_pair("BTSetting","Show"));
    p.insert(make_pair("FromAppId",PHONE_ID));
    HMIFrameWork::Inst()->Notify(HOME_ID,p);
}

void KeyBoardView::OnListClick(int index)
{
    QString name = m_pMatchContactsList->GetSpecifiedText(index);
    QString number = m_pMatchContactsList->GetSpecifiedText2(index);

    PhoneData::Inst()->SetCallName(name);
    PhoneData::Inst()->SetCallNumber(number);
    PhoneData::Inst()->SetCallTime(0);
    PhoneData::Inst()->SetCallStatus("Call");

    Phone::Inst()->ViewForwardById(Phone::eViewId_Calling);
    PhoneData::Inst()->SetViewId(Phone::eViewId_KeyBoard);
    INFO() << index<<" "<<name <<"  " << number;
}






