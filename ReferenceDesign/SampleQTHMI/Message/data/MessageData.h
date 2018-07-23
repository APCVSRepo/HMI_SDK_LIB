#ifndef MESSAGEDATA_H
#define MESSAGEDATA_H

#include <iostream>
#include <QObject>
#include <QList>
#include <map>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <QDate>
#include <QTime>
using namespace std;

struct TLastMessageInfo{
    QString textContent;
    QDate date;
    QTime time;
    bool isIn;
    bool isSuccess; // send message
};

struct TText{
    int sessionId;
    int contactId;
    QString content;
    QString number;
    QString picture;
    QTime time;
    QDate date;
    bool isIn;
    QString telNumTo;
    QString telNumFrom;
};

struct TSessionList{
    int sessionId;
    int contactId;
    QString lastName;
    QString firstName;
    QString number;
    QString picture;
    QString telNumFrom;
    TLastMessageInfo lastInfo;
};

class MessageData : public QObject
{
    Q_OBJECT
    explicit MessageData();

public:

    static MessageData*Inst();
    void InitNameMap();
    void InitTestMessageData();
    void InitTestMessageListData();
    QList<TText *> &GetMessageData();
    QList<TSessionList *> &GetMessageListData();

    void SetSessionId(int id);
    int GetSessionId();


    void SetViewId(int id);
    int GetViewId();
signals:

public slots:

private:
    static MessageData* m_pInst;
    QList<TText*> m_messageData;
    QList<TSessionList*> m_messageListData;


    QString m_callName;
    QString m_callNumber;
    int     m_callTime;
    QString m_callStatus;
    int m_iViewId;
    int m_iSessionId;
    QString m_telNum;

};

#endif // MESSAGEDATA_H
