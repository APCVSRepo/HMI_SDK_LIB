#ifndef PHONEDATA_H
#define PHONEDATA_H

#include <iostream>
#include <QObject>
#include <QList>
#include <map>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <QDate>
using namespace std;
struct SPhoneInfo{
    QString LastName;
    QString FirstName;
    QString MobileNumber;
    QString WorkNumber;
    QString HomeNumber;
    QString OthersNumber;
    QString picture;
    QString pictureContact;
    int     status;

    QDate date;
};

struct SMatchContact{
    QString LastName;
    QString FirstName;
    QString number;
};

enum eRecentsStatus
{
   eIncomingCall_Answer,
   eIncomingCall_NotAnswer,
   eDialCall

};
class PhoneData : public QObject
{
    Q_OBJECT
    explicit PhoneData();

public:

    static PhoneData*Inst();
    void InitNameMap();
    void InitTestContactsData();
    void InitTestRecentsData();
    QList<SPhoneInfo *> GetContactsInfo();
    QList<SPhoneInfo *> GetRecentsInfo();
    void SetContactsIndex(int index);
    char  convertText(wchar_t  n);
    bool  In(wchar_t  start,  wchar_t  end,  wchar_t  code);
    wchar_t toWchar(string text);
    SPhoneInfo *GetContactsDetailInfo();

    void SetCallNumber(const QString & number);
    void SetCallName(const QString& name);
    void SetCallStatus(const QString& status);
    void SetCallTime(int time);
    QString GetCallNumber();
    QString GetCallName();
    QString GetCallStatus();
    QString GetCallTIme();
    QString ToTime(int time);

    void SetViewId(int id);
    int GetViewId();

    QList<SMatchContact*>& GetMatchContacts(const QString& number );
    void ReleaseMatchContacts();
signals:

public slots:

private:
    static PhoneData* m_pInst;
    QList<SPhoneInfo*> m_ContactsInfo;
    QList<SMatchContact*> m_MatchContactsInfo;
    QList<SPhoneInfo*> m_RecentsInfo;

    map<string,char> m_NamesMap;
    int m_ContactsInfoIndex;

    QString m_callName;
    QString m_callNumber;
    int     m_callTime;
    QString m_callStatus;
    int m_iViewId;

};

#endif // PHONEDATA_H
