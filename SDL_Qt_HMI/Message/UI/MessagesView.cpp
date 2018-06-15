#include "Message/UI/MessagesView.h"
#include "HMIFrameWork/log_interface.h"
#include<unistd.h>
#include <QFont>
#include "HVAC/app/HVAC.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HVAC/data/HVACData.h"
#include "Message/app/Message.h"
#include "Message/data/MessageData.h"
MessagesView::MessagesView(QWidget *parent)
    :QWidget(parent)
    ,CView(Message::eViewId_Messages)
{
    this->setGeometry(QRect(0,0,800,480));
    this->show();
    InitMessagesView();


    InitConnect();
}

MessagesView::~MessagesView()
{

}

void MessagesView::viewAction(int state)
{
    INFO()<<" MessagesView  viewAction state = " << state;
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

void MessagesView::InitMessagesView()
{

    m_pBackBtn = new CPushButton(this);
    m_pBackBtn->setStyleSheet("QPushButton{border:none;background:transparent;}");
    m_pBackBtn->setGeometry(QRect(16,61,198,29));
    m_pBackBtn->SetText(QRect(38,0,160,29),tr("Message"),22,Qt::AlignLeft|Qt::AlignVCenter,QColor(75,169,255));
    m_pBackBtn->SetIcon(QRect(0,0,29,29),":/Message/Source/images/button_back.png");
    m_pBackBtn->setFocusPolicy(Qt::NoFocus);
    m_pBackBtn->show();

    m_pMessagesList = new CVListWidget(this);
    m_pMessagesList->setGeometry(QRect(54,111,724,353));
    m_pMessagesList->SetLeftMargin(0);
    m_pMessagesList->SetSplitLine(":/Message/Source/images/line.png",":/Message/Source/images/line.png");
    m_pMessagesList->SetScrollBarStyle(4);
    m_pMessagesList->SetItemBackgroundInfo("",":/Message/Source/images/message_list_push.png","");
    m_pMessagesList->show();
}



void MessagesView::InitConnect()
{
    connect(m_pBackBtn,SIGNAL(clicked()),this,SLOT(OnBack()),Qt::UniqueConnection);

    connect(m_pMessagesList,SIGNAL(listItemReleased(int)),this,SLOT(OnListClick(int)),Qt::UniqueConnection);

}

void MessagesView::UpdataData()
{
  m_pMessagesList->RemoveAllItems();
  QList<TSessionList *> &data =   MessageData::Inst()->GetMessageListData();
  for(int i = 0; i< data.size();i++)
  {

      CListWidgetItem item(QSize (692,78));
      item.AddIcon(QRect(0,0,40,78),QPixmap(data.at(i)->picture));
      item.AddText(QRect(65,12,443,24),data.at(i)->telNumFrom,Qt::AlignLeft|Qt::AlignVCenter,24);
      QDate date(data.at(i)->lastInfo.date);
      QTime time(data.at(i)->lastInfo.time.hour(),data.at(i)->lastInfo.time.minute(),0);
      QTime curTime(QTime::currentTime().hour(),QTime::currentTime().minute(),0);
      QString strTime;
      if(date == QDate::currentDate() && time == curTime)
      {
          strTime = "NOW";
      }else if(date == QDate::currentDate() && time < curTime)
      {
          strTime = time.toString("hh:mm");
      }else if(date.year() == QDate::currentDate().year() && date.month() == QDate::currentDate().month())
      {
          if(QDate::currentDate().day() -date.day() == 1)
          {
              strTime = "Yesterday";
          }else if(QDate::currentDate().day() -date.day()>1 && QDate::currentDate().day() -date.day()<=7){
              int week = date.dayOfWeek();
              int curWeek = QDate::currentDate().dayOfWeek();

              INFO()<<" week = " << week << " cur = " << curWeek;
              if(week < curWeek)
              {
                 strTime = toWeek(week);
              }
              else
              {
                  strTime = date.toString("MM-dd");
              }
          }else {
              strTime = date.toString("MM-dd");
          }

      }else if(date.year() == QDate::currentDate().year() && date.month() < QDate::currentDate().month())
      {
          strTime = date.toString("MM-dd");
      }
      else if(date.year()<QDate::currentDate().year())
      {
          strTime = date.toString("yyyy-MM-dd");
      }
      item.AddText(QRect(502,12,190,24),strTime,Qt::AlignRight|Qt::AlignVCenter,18,QColor(189,189,189));
      item.AddText(QRect(65,46,627,24),data.at(i)->lastInfo.textContent,Qt::AlignLeft|Qt::AlignVCenter,18,QColor(128,128,128));
      m_pMessagesList->InsertItem(i,item);
      m_pMessagesList->SetSpecifiedID(i,data.at(i)->sessionId);
  }
}

QString MessagesView::toWeek(int week)
{
    QString strWeek = "";
    switch (week) {
    case 1:
       strWeek = "Monday";
        break;
    case 2:
       strWeek = "Tuesday";
        break;
    case 3:
       strWeek = "Wednesday";
        break;
    case 4:
       strWeek = "Thursday";
        break;
    case 5:
       strWeek = "Friday";
        break;
    case 6:
       strWeek = "Saturday";
        break;
    case 7:
       strWeek = "Sunday";
        break;
    default:
        break;
    }

    return strWeek;
}

void MessagesView::OnBack()
{
    HMIFrameWork::Inst()->AppBack();
}




void MessagesView::OnListClick(int index)
{
    MessageData::Inst()->SetSessionId(m_pMessagesList->GetSpecifiedID(index));
    Message::Inst()->ViewForwardById(Message::eViewId_MessageList);
}





