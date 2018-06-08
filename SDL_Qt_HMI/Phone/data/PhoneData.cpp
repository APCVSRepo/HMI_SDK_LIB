#include "PhoneData.h"
#include "Phone/app/Phone.h"
#include "HMIFrameWork/log_interface.h"
#include <QtCore/QTextStream>
PhoneData* PhoneData::m_pInst = NULL;
PhoneData::PhoneData()
    :m_ContactsInfoIndex(-1)
    ,m_callName("")
    ,m_callNumber("")
    ,m_callTime(0)
    ,m_callStatus("")
    ,m_iViewId(-1)
{

    InitTestContactsData();
    InitTestRecentsData();
}



PhoneData *PhoneData::Inst()
{
    if(NULL == m_pInst)
    {
        m_pInst = new PhoneData();
    }
    return m_pInst;
}

void PhoneData::InitNameMap()
{
    int i;
     wchar_t wc = L'a';
     char *pmbnull = NULL;
     char *pmb = (char *)malloc( sizeof( char ) );

     qDebug( "convertText a wide character:\n" );
     i = wctomb( pmb, wc );
     qDebug( "\tCharacters convertTexted: %u\n", i );
     qDebug( "\tMultibyte character: %.1s\n\n", pmb );

     qDebug( "Attempt to convertText when target is NULL:\n" );
     i = wctomb( pmbnull, wc );
     qDebug( "\tCharacters convertTexted: %u\n", i );
     qDebug( "\tMultibyte character: %.1s\n", pmbnull );;
}

void PhoneData::InitTestRecentsData()
{
    SPhoneInfo *info  = new SPhoneInfo;
    info->FirstName = "Allen";
    info->LastName = "";
    info->MobileNumber = "13000000000";
    info->WorkNumber = "79999999";
    info->HomeNumber = "23333333";
    info->OthersNumber = "6444444";
    info->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info->status = eIncomingCall_Answer;
    info->date.setDate(QDate::currentDate().year(),QDate::currentDate().month(),QDate::currentDate().day());
    m_RecentsInfo.append(info);

    SPhoneInfo *info1  = new SPhoneInfo;
    info1->FirstName = "Allen";
    info1->LastName = "";
    info1->MobileNumber = "13000000000";
    info1->WorkNumber = "79999999";
    info1->HomeNumber = "23333333";
    info1->OthersNumber = "6444444";
    info1->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info1->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info1->status = eIncomingCall_Answer;
    info1->date.setDate(2018,5,31);

    m_RecentsInfo.append(info1);

    SPhoneInfo *info2  = new SPhoneInfo;
    info2->FirstName = "Allen";
    info2->LastName = "";
    info2->MobileNumber = "13000000000";
    info2->WorkNumber = "79999999";
    info2->HomeNumber = "23333333";
    info2->OthersNumber = "6444444";
    info2->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info2->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info2->status = eIncomingCall_Answer;
    info2->date.setDate(2018,5,30);

    m_RecentsInfo.append(info2);

    SPhoneInfo *info3  = new SPhoneInfo;
    info3->FirstName = "Allen2";
    info3->LastName = "";
    info3->MobileNumber = "13000000002";
    info3->WorkNumber = "79999999";
    info3->HomeNumber = "23333333";
    info3->OthersNumber = "6444444";
    info3->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info3->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info3->status = eDialCall;
    info3->date.setDate(2018,5,30);
    m_RecentsInfo.append(info3);


    SPhoneInfo *info4  = new SPhoneInfo;
    info4->FirstName = "Allen3";
    info4->LastName = "";
    info4->MobileNumber = "13000000003";
    info4->WorkNumber = "79999999";
    info4->HomeNumber = "23333333";
    info4->OthersNumber = "6444444";
    info4->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info4->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info4->status = eIncomingCall_NotAnswer;
    info4->date.setDate(2018,5,30);
    m_RecentsInfo.append(info4);


    SPhoneInfo *info5  = new SPhoneInfo;
    info5->FirstName = "Allen";
    info5->LastName = "";
    info5->MobileNumber = "13000000000";
    info5->WorkNumber = "79999999";
    info5->HomeNumber = "23333333";
    info5->OthersNumber = "6444444";
    info5->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info5->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info5->status = eIncomingCall_NotAnswer;
    info5->date.setDate(2018,5,28);
    m_RecentsInfo.append(info5);


    SPhoneInfo *info6  = new SPhoneInfo;
    info6->FirstName = "Allen4";
    info6->LastName = "";
    info6->MobileNumber = "13000000004";
    info6->WorkNumber = "79999999";
    info6->HomeNumber = "23333333";
    info6->OthersNumber = "6444444";
    info6->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info6->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info6->status = eDialCall;
    info6->date.setDate(2018,5,28);
    m_RecentsInfo.append(info6);


    SPhoneInfo *info7  = new SPhoneInfo;
    info7->FirstName = "Allen";
    info7->LastName = "";
    info7->MobileNumber = "13000000000";
    info7->WorkNumber = "79999999";
    info7->HomeNumber = "23333333";
    info7->OthersNumber = "6444444";
    info7->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info7->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info7->status = eIncomingCall_Answer;
    info7->date.setDate(2018,5,27);
    m_RecentsInfo.append(info7);


    SPhoneInfo *info8  = new SPhoneInfo;
    info8->FirstName = "Allen";
    info8->LastName = "";
    info8->MobileNumber = "13000000000";
    info8->WorkNumber = "79999999";
    info8->HomeNumber = "23333333";
    info8->OthersNumber = "6444444";
    info8->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info8->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info8->status = eIncomingCall_Answer;
    info8->date.setDate(2018,5,27);
    m_RecentsInfo.append(info8);


    SPhoneInfo *info9  = new SPhoneInfo;
    info9->FirstName = "Allen";
    info9->LastName = "";
    info9->MobileNumber = "13000000000";
    info9->WorkNumber = "79999999";
    info9->HomeNumber = "23333333";
    info9->OthersNumber = "6444444";
    info9->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info9->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info9->status = eIncomingCall_NotAnswer;
    info9->date.setDate(2018,5,22);
    m_RecentsInfo.append(info9);


    SPhoneInfo *info10  = new SPhoneInfo;
    info10->FirstName = "Allen55";
    info10->LastName = "";
    info10->MobileNumber = "13000000066";
    info10->WorkNumber = "79999999";
    info10->HomeNumber = "23333333";
    info10->OthersNumber = "6444444";
    info10->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info10->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info10->status = eIncomingCall_NotAnswer;
    info10->date.setDate(2018,5,21);
    m_RecentsInfo.append(info10);


    SPhoneInfo *info11  = new SPhoneInfo;
    info11->FirstName = "Allen";
    info11->LastName = "";
    info11->MobileNumber = "13000000000";
    info11->WorkNumber = "79999999";
    info11->HomeNumber = "23333333";
    info11->OthersNumber = "6444444";
    info11->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info11->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info11->status = eIncomingCall_Answer;
    info11->date.setDate(2018,5,11);
    m_RecentsInfo.append(info11);


    SPhoneInfo *info12  = new SPhoneInfo;
    info12->FirstName = "Allen";
    info12->LastName = "";
    info12->MobileNumber = "13000000000";
    info12->WorkNumber = "79999999";
    info12->HomeNumber = "23333333";
    info12->OthersNumber = "6444444";
    info12->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info12->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info12->status = eIncomingCall_Answer;
    info12->date.setDate(2018,5,7);
    m_RecentsInfo.append(info12);


    SPhoneInfo *info13  = new SPhoneInfo;
    info13->FirstName = "Allen";
    info13->LastName = "";
    info13->MobileNumber = "13000000000";
    info13->WorkNumber = "79999999";
    info13->HomeNumber = "23333333";
    info13->OthersNumber = "6444444";
    info13->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info13->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info13->status = eDialCall;
    info13->date.setDate(2018,5,1);
    m_RecentsInfo.append(info13);

    SPhoneInfo *info14  = new SPhoneInfo;
    info14->FirstName = "Allen";
    info14->LastName = "";
    info14->MobileNumber = "13000000000";
    info14->WorkNumber = "79999999";
    info14->HomeNumber = "23333333";
    info14->OthersNumber = "6444444";
    info14->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info14->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info14->status = eDialCall;
    info14->date.setDate(2018,4,28);
    m_RecentsInfo.append(info14);
}

void PhoneData::InitTestContactsData()
{
    SPhoneInfo *info  = new SPhoneInfo;
    info->FirstName = "Allen";
    info->LastName = "";
    info->MobileNumber = "13000000000";
    info->WorkNumber = "79999999";
    info->HomeNumber = "23333333";
    info->OthersNumber = "6444444";
    info->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info->status = -1;

    m_ContactsInfo.append(info);

    SPhoneInfo *info1  = new SPhoneInfo;
    info1->FirstName = "Allen1";
    info1->LastName = "";
    info1->MobileNumber = "13100000001";
    info1->WorkNumber = "79999999";
    info1->HomeNumber = "23333333";
    info1->OthersNumber = "6444444";
    info1->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info1->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info1->status = -1;

    m_ContactsInfo.append(info1);

    SPhoneInfo *info2  = new SPhoneInfo;
    info2->FirstName = "Allen2";
    info2->LastName = "";
    info2->MobileNumber = "13230000002";
    info2->WorkNumber = "79999999";
    info2->HomeNumber = "23333333";
    info2->OthersNumber = "6444444";
    info2->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info2->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info2->status = -1;

    m_ContactsInfo.append(info2);

    SPhoneInfo *info3  = new SPhoneInfo;
    info3->FirstName = "Allen3";
    info3->LastName = "";
    info3->MobileNumber = "13003600003";
    info3->WorkNumber = "79999999";
    info3->HomeNumber = "23333333";
    info3->OthersNumber = "6444444";
    info3->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info3->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info3->status = -1;

    m_ContactsInfo.append(info3);


    SPhoneInfo *info4  = new SPhoneInfo;
    info4->FirstName = "Allen4";
    info4->LastName = "";
    info4->MobileNumber = "13045000004";
    info4->WorkNumber = "79999999";
    info4->HomeNumber = "23333333";
    info4->OthersNumber = "6444444";
    info4->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info4->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info4->status = -1;

    m_ContactsInfo.append(info4);


    SPhoneInfo *info5  = new SPhoneInfo;
    info5->FirstName = "Allen5";
    info5->LastName = "";
    info5->MobileNumber = "13567000005";
    info5->WorkNumber = "79999999";
    info5->HomeNumber = "23333333";
    info5->OthersNumber = "6444444";
    info5->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info5->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info5->status = -1;

    m_ContactsInfo.append(info5);


    SPhoneInfo *info6  = new SPhoneInfo;
    info6->FirstName = "Allen6";
    info6->LastName = "";
    info6->MobileNumber = "13023456006";
    info6->WorkNumber = "79999999";
    info6->HomeNumber = "23333333";
    info6->OthersNumber = "6444444";
    info6->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info6->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info6->status = -1;

    m_ContactsInfo.append(info6);


    SPhoneInfo *info7  = new SPhoneInfo;
    info7->FirstName = "Allen7";
    info7->LastName = "";
    info7->MobileNumber = "13033300007";
    info7->WorkNumber = "79999999";
    info7->HomeNumber = "23333333";
    info7->OthersNumber = "6444444";
    info7->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info7->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info7->status = -1;

    m_ContactsInfo.append(info7);


    SPhoneInfo *info8  = new SPhoneInfo;
    info8->FirstName = "Allen8";
    info8->LastName = "";
    info8->MobileNumber = "15100000008";
    info8->WorkNumber = "79999999";
    info8->HomeNumber = "23333333";
    info8->OthersNumber = "6444444";
    info8->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info8->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info8->status = -1;

    m_ContactsInfo.append(info8);


    SPhoneInfo *info9  = new SPhoneInfo;
    info9->FirstName = "Allen9";
    info9->LastName = "";
    info9->MobileNumber = "16780000009";
    info9->WorkNumber = "79999999";
    info9->HomeNumber = "23333333";
    info9->OthersNumber = "6444444";
    info9->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info9->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info9->status = -1;

    m_ContactsInfo.append(info9);


    SPhoneInfo *info10  = new SPhoneInfo;
    info10->FirstName = "Allen10";
    info10->LastName = "";
    info10->MobileNumber = "16600000100";
    info10->WorkNumber = "79999999";
    info10->HomeNumber = "23333333";
    info10->OthersNumber = "6444444";
    info10->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info10->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info10->status = -1;

    m_ContactsInfo.append(info10);


    SPhoneInfo *info11  = new SPhoneInfo;
    info11->FirstName = "Allen11";
    info11->LastName = "";
    info11->MobileNumber = "13000000011";
    info11->WorkNumber = "79999999";
    info11->HomeNumber = "23333333";
    info11->OthersNumber = "6444444";
    info11->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info11->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info11->status = -1;

    m_ContactsInfo.append(info11);


    SPhoneInfo *info12  = new SPhoneInfo;
    info12->FirstName = "Allen12";
    info12->LastName = "";
    info12->MobileNumber = "13000000012";
    info12->WorkNumber = "79999999";
    info12->HomeNumber = "23333333";
    info12->OthersNumber = "6444444";
    info12->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info12->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info12->status = -1;

    m_ContactsInfo.append(info12);


    SPhoneInfo *info13  = new SPhoneInfo;
    info13->FirstName = "Allen13";
    info13->LastName = "";
    info13->MobileNumber = "13000000013";
    info13->WorkNumber = "79999999";
    info13->HomeNumber = "23333333";
    info13->OthersNumber = "6444444";
    info13->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info13->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info13->status = -1;

    m_ContactsInfo.append(info13);

    SPhoneInfo *info14  = new SPhoneInfo;
    info14->FirstName = "Allen14";
    info14->LastName = "";
    info14->MobileNumber = "13100000014";
    info14->WorkNumber = "79999999";
    info14->HomeNumber = "23333333";
    info14->OthersNumber = "6444444";
    info14->pictureContact = ":/Phone/Source/images/head_portrait.png";
    info14->picture = ":/Phone/Source/images/head_portrait_normal.png";
    info14->status = -1;

    m_ContactsInfo.append(info14);
}

QList<SPhoneInfo *> PhoneData::GetContactsInfo()
{
    return m_ContactsInfo;
}

QList<SPhoneInfo *> PhoneData::GetRecentsInfo()
{
    return m_RecentsInfo;
}

void PhoneData::SetContactsIndex(int index)
{
    m_ContactsInfoIndex = index;
}

char  PhoneData::convertText(wchar_t  n)

  {

  if  (In(0xB0A1,0xB0C4,n))  return  'a';

  if  (In(0XB0C5,0XB2C0,n))  return  'b';

  if  (In(0xB2C1,0xB4ED,n))  return  'c';

  if  (In(0xB4EE,0xB6E9,n))  return  'd';

  if  (In(0xB6EA,0xB7A1,n))  return  'e';

  if  (In(0xB7A2,0xB8c0,n))  return  'f';

  if  (In(0xB8C1,0xB9FD,n))  return  'g';

  if  (In(0xB9FE,0xBBF6,n))  return  'h';

  if  (In(0xBBF7,0xBFA5,n))  return  'j';

  if  (In(0xBFA6,0xC0AB,n))  return  'k';

  if  (In(0xC0AC,0xC2E7,n))  return  'l';

  if  (In(0xC2E8,0xC4C2,n))  return  'm';

  if  (In(0xC4C3,0xC5B5,n))  return  'n';

  if  (In(0xC5B6,0xC5BD,n))  return  'o';

  if  (In(0xC5BE,0xC6D9,n))  return  'p';

  if  (In(0xC6DA,0xC8BA,n))  return  'q';

  if  (In(0xC8BB,0xC8F5,n))  return  'r';

  if  (In(0xC8F6,0xCBF0,n))  return  's';

  if  (In(0xCBFA,0xCDD9,n))  return  't';

  if  (In(0xCDDA,0xCEF3,n))  return  'w';

  if  (In(0xCEF4,0xD188,n))  return  'x';

  if  (In(0xD1B9,0xD4D0,n))  return  'y';

  if  (In(0xD4D1,0xD7F9,n))  return  'z';

  return  '\0';

  }
bool  PhoneData::In(wchar_t  start,  wchar_t  end,  wchar_t  code)

 {

 if  (code  >=  start  &&  code  <=  end)

 {

 return  true;

 }

 return  false;

}

wchar_t PhoneData::toWchar(string sChinese)
{
    sChinese = "我";

      char  chr[3];

      wchar_t  wchr  =  0;
      char  bbbb;
      char*  buff  =  new  char[sChinese.length()/2];

      memset(buff,  0x00,  sizeof(char)*sChinese.length()/2+1);

      for  (int  i  =  0,  j  =  0;  i  <  (sChinese.length()/2);  ++i)

      {

      memset(chr,  0x00,  sizeof(chr));

      chr[0]  =  sChinese[j++];

      chr[1]  =  sChinese[j++];

      chr[2]  =  '\0';

      //  单个字符的编码  如：'我'  =  0xced2

      wchr  =  0;

      wchr  =  (chr[0]  &  0xff)  <<  8;

      wchr  |=  (chr[1]  &  0xff);

      INFO() <<" wchr = "<< wchr <<"  " << (int)chr[0] << "  " << (int)chr[1];
       bbbb =  convertText(wchr);

      }

      cout  <<  "pin  yin  =  ["  <<  bbbb  <<  "]"  <<  endl;
}

SPhoneInfo *PhoneData::GetContactsDetailInfo()
{
    if(m_ContactsInfoIndex >= 0 && m_ContactsInfoIndex < m_ContactsInfo.size())
    {
        return m_ContactsInfo.at(m_ContactsInfoIndex);
    }
    m_ContactsInfoIndex = -1;
    return NULL;
}

void PhoneData::SetCallNumber(const QString &number)
{
       m_callNumber = number;
}

void PhoneData::SetCallName(const QString &name)
{
    m_callName = name;
}

void PhoneData::SetCallStatus(const QString &status)
{
    m_callStatus = status;
}

void PhoneData::SetCallTime(int time)
{
    m_callTime = time;
}

QString PhoneData::GetCallNumber()
{
    return m_callNumber;
}

QString PhoneData::GetCallName()
{
    return m_callName;
}

QString PhoneData::GetCallStatus()
{
    return m_callStatus;
}

QString PhoneData::GetCallTIme()
{
    return ToTime(m_callTime);
}

QString PhoneData::ToTime(int time)
{
    int hour = (time / 3600) % 24;
    int min = (time / 60) % 60;
    int sec = time % 60;
    QString strHour ;
    QString strMin ;
    QString strSec ;
    if(0 == hour)
    {
        if(0 <= min && 10 > min)
        {
            if(0<=sec && 10 > sec )
            {
                strMin = "0" + QString::number(min);
                strSec = "0" + QString::number(sec);
            }else if(10 <= sec)
            {
                strMin = "0" + QString::number(min);
                strSec = QString::number(sec);
            }
        }else if(10 <= min )
        {
            if(0 <= sec  && 10 > sec )
            {
                strMin = QString::number(min);
                strSec = "0" + QString::number(sec);
            }else if(sec >=10)
            {
                strMin = QString::number(min);
                strSec = QString::number(sec);
            }
        }
        return strMin+":"+strSec;
    }
    else if(0 < hour  && 9 > hour )
    {
        if(0 <= min  && 10 > min )
        {
            if(0 <= sec &&  10 > sec )
            {
                strMin = "0" + QString::number(min);
                strSec = "0" + QString::number(sec);
            }else if(10 <= sec)
            {
                strMin = "0" + QString::number(min);
                strSec = QString::number(sec);
            }
        }else if(10 <= min )
        {
            if(0 <= sec && 10 > sec )
            {
                strMin = QString::number(min);
                strSec = "0" + QString::number(sec);
            }else if(10 <= sec)
            {
                strMin = QString::number(min);
                strSec = QString::number(sec);
            }
        }
        strHour = "0" + QString::number(hour);
        return strHour +":"+strMin+":"+strSec;
    }else if(9 < hour  && 23 > hour )
    {
        if(0 <= min  && 10 > min)
        {
            if(0 <= sec && 10 > sec)
            {
                strMin = "0" + QString::number(min);
                strSec = "0" + QString::number(sec);
            }else if(10 <= sec)
            {
                strMin = "0" + QString::number(min);
                strSec = QString::number(sec);
            }
        }else if(10 <= min )
        {
            if(0 <= sec && 10 > sec)
            {
                strMin = QString::number(min);
                strSec = "0" + QString::number(sec);
            }else if(10 <= sec)
            {
                strMin = QString::number(min);
                strSec = QString::number(sec);
            }
        }
        strHour = QString::number(hour);
        return strHour +":"+strMin+":"+strSec;
    }
    return "";
}

void PhoneData::SetViewId(int id)
{
    m_iViewId = id;
}

int PhoneData::GetViewId()
{
    return m_iViewId;
}

QList<SMatchContact *>& PhoneData::GetMatchContacts(const QString &number)
{
    ReleaseMatchContacts();
    QList<SPhoneInfo*>::iterator it = m_ContactsInfo.begin();
    for(;it != m_ContactsInfo.end();++it)
    {
       if((*it)->HomeNumber.indexOf(number)>=0)
       {

            SMatchContact *temp = new SMatchContact;
            temp->FirstName = (*it)->FirstName;
            temp->LastName = (*it)->LastName;
            temp->number = (*it)->HomeNumber;
            m_MatchContactsInfo.append(temp);
       }
       else if((*it)->MobileNumber.indexOf(number)>=0)
       {
           INFO() <<"GetMatchContacts MobileNumber";
            SMatchContact *temp = new SMatchContact;
            temp->FirstName = (*it)->FirstName;
            temp->LastName = (*it)->LastName;
            temp->number = (*it)->MobileNumber;
            m_MatchContactsInfo.append(temp);
       }
       else if((*it)->OthersNumber.indexOf(number)>=0 )
       {
            SMatchContact *temp = new SMatchContact;
            temp->FirstName = (*it)->FirstName;
            temp->LastName = (*it)->LastName;
            temp->number = (*it)->OthersNumber;
            m_MatchContactsInfo.append(temp);

       }else if((*it)->WorkNumber.indexOf(number)>=0 ){

            SMatchContact *temp = new SMatchContact;
            temp->FirstName = (*it)->FirstName;
            temp->LastName = (*it)->LastName;
            temp->number = (*it)->WorkNumber;
            m_MatchContactsInfo.append(temp);
       }
    }
    return m_MatchContactsInfo;
}

void PhoneData::ReleaseMatchContacts()
{
    if(m_MatchContactsInfo.size() > 0)
    {
        QList<SMatchContact*>::iterator it = m_MatchContactsInfo.begin();
        for(;it != m_MatchContactsInfo.end();++it)
        {
            SMatchContact* temp = (*it);
            m_MatchContactsInfo.erase(it);
            delete temp;
            temp = NULL;
        }
    }
}


