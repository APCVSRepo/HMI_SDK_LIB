#include "Message/UI/MessageListView.h"
#include "HMIFrameWork/log_interface.h"
#include<unistd.h>
#include <QFont>
#include "HVAC/app/HVAC.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HVAC/data/HVACData.h"
#include "Message/app/Message.h"
#include "Message/data/MessageData.h"
MessageListView::MessageListView(QWidget *parent)
    :QWidget(parent)
    ,CView(Message::eViewId_MessageList)
{
    this->setGeometry(QRect(0,0,800,480));
    this->show();
    InitMessageListView();


    InitConnect();
}

MessageListView::~MessageListView()
{

}

void MessageListView::viewAction(int state)
{
    INFO("[Message] MessageListView  viewAction state = %d" ,state);
    switch (state) {
    case eviewStatus_Init:
    {
        UpdataData();
    }
        break;
    case eViewStatus_Active:
        MessageData::Inst()->SetViewId(Message::eViewId_Messages);

        this->show();
        break;
    default:
        break;
    }
}
void MessageListView::InitMessageListView()
{
    m_pBackBtn = new CPushButton(this);
    m_pBackBtn->setStyleSheet("QPushButton{border:none;background:transparent;}");
    m_pBackBtn->setGeometry(QRect(16,61,198,29));
    m_pBackBtn->SetText(QRect(38,0,160,29),tr("Message list"),22,Qt::AlignLeft|Qt::AlignVCenter,QColor(75,169,255));
    m_pBackBtn->SetIcon(QRect(0,0,29,29),":/Message/Source/images/button_back.png");
    m_pBackBtn->setFocusPolicy(Qt::NoFocus);
    m_pBackBtn->show();


    m_pTitleLabel = new QLabel(this);
    m_pTitleLabel->setGeometry(QRect(0,108,800,20));
    m_pTitleLabel->setStyleSheet("QLabel{border:none;background:transparent;color:rgb(128,128,128);font-size:18;}");
    m_pTitleLabel->setAlignment(Qt::AlignCenter);
    m_pTitleLabel->setText("Today 5:00PM");
    m_pTitleLabel->show();


    m_pLineLabel = new QLabel(this);
    m_pLineLabel->setGeometry(QRect(54,138,692,1));
    m_pLineLabel->setStyleSheet("QLabel{border-image:url(:/Message/Source/images/line.png);background:transparent;color:rgb(128,128,128);font-size:18;}");
    m_pLineLabel->show();

    m_pMessagesList = new CVListWidget(this);
    m_pMessagesList->setGeometry(QRect(54,139,724,353));
    m_pMessagesList->SetLeftMargin(0);
    m_pMessagesList->SetSplitLine("","");
    m_pMessagesList->SetScrollBarStyle(4);
    m_pMessagesList->SetItemBackgroundInfo("","","");
    m_pMessagesList->AutoSetSelected(false);
    m_pMessagesList->show();
}



void MessageListView::InitConnect()
{
    connect(m_pBackBtn,SIGNAL(clicked()),this,SLOT(OnBack()),Qt::UniqueConnection);
    connect(m_pMessagesList,SIGNAL(listItemReleased(int)),this,SLOT(OnListClick(int)),Qt::UniqueConnection);
    connect(m_pMessagesList,SIGNAL(phoneNumberReleased(QString)),this,SLOT(OnPhoneNumberClick(QString)),Qt::UniqueConnection);

}

void MessageListView::UpdataData()
{
    QList<TText*> &data = MessageData::Inst()->GetMessageData();
    for(int i = 0 ; i< data.size();i++)
    {
        CListWidgetItem item(QSize(692,40));
        if(!data.at(i)->isIn)
        {
            item.AddIcon(QRect(652,30,40,40),QPixmap(":/Message/Source/images/default_profile.png"));
            item.AddSpecialText(QRect(194,40,418,40),data.at(i)->content,Qt::AlignRight|Qt::TextWrapAnywhere,18,QColor(255,255,255),true,QColor(46,108,161));
            item.AddIcon(QRect(622,40,9,7),QPixmap(":/Message/Source/images/dialog_right.png"));

        }else
        {
            item.AddText(QRect(66,0,200,20),data.at(i)->number,Qt::AlignLeft|Qt::AlignVCenter,18,QColor(189,189,189));
            item.AddSpecialText(QRect(79,47,418,40),data.at(i)->content,Qt::AlignLeft|Qt::TextWrapAnywhere,18,QColor(255,255,255),true,QColor(46,46,46));
            item.AddIcon(QRect(0,16,40,40),QPixmap(":/Message/Source/images/default_profile.png"));
            item.AddIcon(QRect(60,47,9,7),QPixmap(":/Message/Source/images/dialog_left.png"));
        }
        m_pMessagesList->InsertItem(i,item);
    }
}

void MessageListView::OnBack()
{
    Message::Inst()->ViewBack();
}


void MessageListView::OnListClick(int index)
{

}

void MessageListView::OnPhoneNumberClick(QString number)
{
    INFO("[Message] : OnPhoneNumberClick , %s .",number.toStdString().c_str());
    map<string,string> p;
    p.insert(make_pair("MessageDialNumber",number.toStdString()));
    HMIFrameWork::Inst()->Notify(PHONE_ID,p);
}





