#include "MessageData.h"
#include "Message/app/Message.h"
#include "HMIFrameWork/log_interface.h"
#include <QtCore/QTextStream>
MessageData* MessageData::m_pInst = NULL;
MessageData::MessageData()

{
    m_iSessionId = -1;
    InitTestMessageData();
    InitTestMessageListData();
}



MessageData *MessageData::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new MessageData();
    }
    return m_pInst;
}


void MessageData::InitTestMessageData()
{

    TText *data = new TText;
    data->contactId = 0;
    data->content = "FLow";
    data->date.setDate(QDate::currentDate().year(),QDate::currentDate().month(),QDate::currentDate().day());
    data->isIn = false;
    int num = 1008600;
    data->number = QString::number(num);
    data->picture = ":/Message/Source/images/default_profile.png";
    data->sessionId = 0;
    data->telNumFrom = "10086";
    data->telNumTo ="me";
    data->time = QTime::currentTime();

     m_messageData.append(data);

    TText *data2 = new TText;
    data2->contactId = 1;
    data2->content = "[Traffic alert] at 14:20 on August 30,2016 ,you hava 845.33MB of domestic traffic this mounth,and the remaining traffic is 422.66MB.Pay attention ,please.Traffic usage can be clicked on http://123456.cn/iNYyise.If you need to cancel the reminding,please replay to 1008611.China Mobile";
    data2->date.setDate(QDate::currentDate().year(),QDate::currentDate().month(),QDate::currentDate().day());
    data2->isIn = true;
     num = 10086111;
    data2->number = QString::number(num);
    data2->picture = ":/Message/Source/images/default_profile.png";
    data2->sessionId = 1;
    data2->telNumFrom = "10086";
    data2->telNumTo ="me";
    data2->time =QTime(QTime::currentTime().hour(),QTime::currentTime().minute()-1,1);

    m_messageData.append(data2);
}

void MessageData::InitTestMessageListData()
{


    TSessionList *data = new TSessionList;
    data->contactId = 0;
    data->lastInfo.textContent = "[Traffic alert] at 14:20 on August 30,2016 ,you hava 845.33MB of domestic traffic this mounth,and the remaining traffic is 422.66MB.Pay attention ,please. \n \
                     Traffic usage can be clicked on http://123456.cn/iNYyise.If you need to cancel the reminding,please replay to 1008611.China Mobile";
    data->lastInfo.date.setDate(QDate::currentDate().year(),QDate::currentDate().month(),QDate::currentDate().day());
    data->lastInfo.isIn = true;
    int num = 1008600;
    data->number = QString::number(num);
    data->picture = ":/Message/Source/images/default_profile.png";
    data->sessionId = 0;
    data->telNumFrom = "10086";
    data->lastInfo.time = QTime::currentTime();

     m_messageListData.append(data);

    TSessionList *data2 = new TSessionList;
    data2->contactId = 1;
    data2->lastInfo.textContent = "[Traffic alert] at 14:20 on August 30,2016 ,you hava 845.33MB of domestic traffic this mounth,and the remaining traffic is 422.66MB.Pay attention ,please. \n \
                     Traffic usage can be clicked on http://123456.cn/iNYyise.If you need to cancel the reminding,please replay to 1008611.China Mobile";
    data2->lastInfo.date.setDate(QDate::currentDate().year(),QDate::currentDate().month(),QDate::currentDate().day());
    data2->lastInfo.isIn = true;
     num = 1008611;
    data2->number = QString::number(num);
    data2->picture = ":/Message/Source/images/default_profile.png";
    data2->sessionId = 1;
    data2->telNumFrom = "10086111";
    data2->lastInfo.time =QTime(QTime::currentTime().hour(),QTime::currentTime().minute()-1,1);

    m_messageListData.append(data2);

    TSessionList *data3 = new TSessionList;
    data3->contactId = 2;
    data3->lastInfo.textContent = "[Traffic alert] at 14:20 on August 30,2016 ,you hava 845.33MB of domestic traffic this mounth,and the remaining traffic is 422.66MB.Pay attention ,please. \n \
                     Traffic usage can be clicked on http://123456.cn/iNYyise.If you need to cancel the reminding,please replay to 1008611.China Mobile";
    data3->lastInfo.date.setDate(QDate::currentDate().year(),QDate::currentDate().month(),QDate::currentDate().day()-1);
    data3->lastInfo.isIn = true;
     num = 1008612;
    data3->number = QString::number(num);
    data3->picture = ":/Message/Source/images/default_profile.png";
    data3->sessionId = 2;
    data3->telNumFrom = "10086111";
    data3->lastInfo.time = QTime::currentTime();

    m_messageListData.append(data3);


    TSessionList *data4 = new TSessionList;
    data4->contactId = 3;
    data4->lastInfo.textContent = "[Traffic alert] at 14:20 on August 30,2016 ,you hava 845.33MB of domestic traffic this mounth,and the remaining traffic is 422.66MB.Pay attention ,please. \n \
                     Traffic usage can be clicked on http://123456.cn/iNYyise.If you need to cancel the reminding,please replay to 1008611.China Mobile";
    data4->lastInfo.date.setDate(QDate::currentDate().year(),QDate::currentDate().month(),QDate::currentDate().day()-2);
    data4->lastInfo.isIn = true;
     num = 1008613;
    data4->number = QString::number(num);
    data4->picture = ":/Message/Source/images/default_profile.png";
    data4->sessionId = 3;
    data4->telNumFrom = "10086112";
    data4->lastInfo.time = QTime::currentTime();

    m_messageListData.append(data4);


    for(int i = 0; i < 10;i++)
    {
        TSessionList *data1 = new TSessionList;
        data1->contactId = 1+i;
        data1->lastInfo.textContent = "[Traffic alert] at 14:20 on August 30,2016 ,you hava 845.33MB of domestic traffic this mounth,and the remaining traffic is 422.66MB.Pay attention ,please.Traffic usage can be clicked on http://123456.cn/iNYyise.If you need to cancel the reminding,please replay to 1008611.China Mobile";
        data1->lastInfo.date.setDate(QDate::currentDate().year(),QDate::currentDate().month()-1,QDate::currentDate().day());
        data1->lastInfo.isIn = true;
        int num = 10087+i;
        data1->number = QString::number(num);
        data1->picture = ":/Message/Source/images/default_profile.png";
        data1->sessionId = 4+i;
        data1->telNumFrom = QString::number(num);
        data1->lastInfo.time = QTime::currentTime();
        m_messageListData.append(data1);
    }

    TSessionList *data5 = new TSessionList;
    data5->contactId = 14;
    data5->lastInfo.textContent = "[Traffic alert] at 14:20 on August 30,2016 ,you hava 845.33MB of domestic traffic this mounth,and the remaining traffic is 422.66MB.Pay attention ,please. \n \
                     Traffic usage can be clicked on http://123456.cn/iNYyise.If you need to cancel the reminding,please replay to 1008611.China Mobile";
    data5->lastInfo.date.setDate(QDate::currentDate().year()-1,QDate::currentDate().month(),QDate::currentDate().day()-2);
    data5->lastInfo.isIn = true;
     num = 10086112;
    data5->number = QString::number(num);
    data5->picture = ":/Message/Source/images/default_profile.png";
    data5->sessionId = 14;
    data5->telNumFrom = "1008611";
    data5->lastInfo.time = QTime::currentTime();

    m_messageListData.append(data5);
}

QList<TText *> &MessageData::GetMessageData()
{
    for(int i = 0;i < m_messageData.size();++i)
    {
        m_messageData.at(i)->number  = m_telNum;
    }

    return  m_messageData;
}

QList<TSessionList *> &MessageData::GetMessageListData()
{

    return m_messageListData;
}

void MessageData::SetSessionId(int id)
{
    INFO()<<" id = " << id;
    m_iSessionId = id;

    for(int i = 0; i < m_messageListData.size();i++)
    {
        if(m_messageListData.at(i)->sessionId == id)
        {
            m_telNum = m_messageListData.at(i)->telNumFrom;
            INFO()<<" id = " << id <<"  " << m_telNum;
            return;
        }
    }

}

int MessageData::GetSessionId()
{
    return m_iSessionId;
}

void MessageData::SetViewId(int id)
{
    m_iViewId = id;
}

int MessageData::GetViewId()
{
    return m_iViewId;
}



