#include "Message/UI/MessagesNoNewInfoView.h"
#include "HMIFrameWork/log_interface.h"
#include<unistd.h>
#include <QFont>
#include "HVAC/app/HVAC.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HVAC/data/HVACData.h"
#include "Message/app/Message.h"
#include "Message/data/MessageData.h"
MessagesNoNewInfoView::MessagesNoNewInfoView(QWidget *parent)
    :QWidget(parent)
    ,CView(Message::eViewId_MessagesNoNewInfo)
{
    this->setGeometry(QRect(0,0,800,480));
    this->show();
    InitMessagesNoNewInfoView();


    InitConnect();
}

MessagesNoNewInfoView::~MessagesNoNewInfoView()
{

}

void MessagesNoNewInfoView::viewAction(int state)
{
    INFO()<<" MessagesNoNewInfoView  viewAction state = " << state;
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

void MessagesNoNewInfoView::InitMessagesNoNewInfoView()
{

    m_pBackBtn = new CPushButton(this);
    m_pBackBtn->setStyleSheet("QPushButton{border:none;background:transparent;}");
    m_pBackBtn->setGeometry(QRect(16,61,198,29));
    m_pBackBtn->SetText(QRect(38,0,160,29),tr("Message"),22,Qt::AlignLeft|Qt::AlignVCenter,QColor(75,169,255));
    m_pBackBtn->SetIcon(QRect(0,0,29,29),":/Message/Source/images/button_back.png");
    m_pBackBtn->setFocusPolicy(Qt::NoFocus);
    m_pBackBtn->hide();

    m_pTitleLabel = new QLabel(this);
    m_pTitleLabel->setGeometry(QRect(144,69,512,32));
    m_pTitleLabel->setStyleSheet("QLabel{border:none;background:transparent;color:#4BA9FF;font-size:30px;}");
    m_pTitleLabel->setAlignment(Qt::AlignLeft| Qt::AlignVCenter);
    m_pTitleLabel->setText("NO NEW MESSAGES");
    m_pTitleLabel->show();


    m_pLineLabel = new QLabel(this);
    m_pLineLabel->setGeometry(QRect(54,138,692,1));
    m_pLineLabel->setStyleSheet("QLabel{border-image:url(:/Message/Source/images/line.png);background:transparent;color:rgb(128,128,128);font-size:18;}");
    m_pLineLabel->show();


    m_pContextLabel1 = new QLabel(this);
    m_pContextLabel1->setGeometry(QRect(0,238,800,32));
    m_pContextLabel1->setStyleSheet("QLabel{border:none;background:transparent;color:#FFFFFF;font-size:24px;}");
    m_pContextLabel1->setAlignment(Qt::AlignTop| Qt::AlignHCenter);
    m_pContextLabel1->setText("This application does not display historical SMS.");
    m_pContextLabel1->show();

    m_pContextLabel2 = new QLabel(this);
    m_pContextLabel2->setGeometry(QRect(188,275,424,200));
    m_pContextLabel2->setStyleSheet("QLabel{border:none;background:transparent;color:#BDBDBD;font-size:18px;}");
    m_pContextLabel2->setAlignment(Qt::AlignTop| Qt::AlignHCenter);
    m_pContextLabel2->setWordWrap(true);
    m_pContextLabel2->setText("When your phone is connected,the newly received SMS will be displayed in this application.");
    m_pContextLabel2->show();


}



void MessagesNoNewInfoView::InitConnect()
{
    connect(m_pBackBtn,SIGNAL(clicked()),this,SLOT(OnBack()),Qt::UniqueConnection);

}

void MessagesNoNewInfoView::UpdataData()
{

}


void MessagesNoNewInfoView::OnBack()
{
    HMIFrameWork::Inst()->AppBack();
}






