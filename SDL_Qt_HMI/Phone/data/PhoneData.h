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
    char  convertText(wchar_t  n);
    bool  In(wchar_t  start,  wchar_t  end,  wchar_t  code);
    wchar_t toWchar(string text);
signals:

public slots:

private:
    static PhoneData* m_pInst;
    QList<SPhoneInfo*> m_ContactsInfo;
    QList<SPhoneInfo*> m_RecentsInfo;
    map<string,char> m_NamesMap;
};

#endif // PHONEDATA_H
