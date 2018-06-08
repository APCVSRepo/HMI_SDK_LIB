#include "PopUpBase.h"

PopUpBase::PopUpBase(QWidget *parent)
    :QWidget(parent)
    ,m_PopUpId("")
    ,m_PopupType("")
    ,m_PopUpShow("")
    ,m_PopUpTitle("")
    ,m_PopUpContextA("")
    ,m_PopUpContextB("")
    ,m_PopUpContextALight("")
    ,m_PopUpContextBLight("")
    ,m_PopUpButtonA("")
    ,m_PopUpButtonB("")
    ,m_PopUpReplyButtonA("")
    ,m_PopUpReplyButtonB("")
    ,m_PopUpHandle("")
    ,m_PopUpTime("")
    ,m_fromAppId("")
    ,m_Password("")
    ,m_bPopUpId(false)
    ,m_bPopUpType(false)
    ,m_bPopUpShow(false)
    ,m_bPopUpTitle(false)
    ,m_bPopUpContextA(false)
    ,m_bPopUpContextB(false)
    ,m_bPopUpContextALight(false)
    ,m_bPopUpContextBLight(false)
    ,m_bPopUpButtonA(false)
    ,m_bPopUpButtonB(false)
    ,m_bPopUpReplyButtonA(false)
    ,m_bPopUpReplyButtonB(false)
    ,m_bPopUpHandle(false)
    ,m_bPopUpTime(false)
    ,m_bFromAppId(false)
    ,m_bPassword(false)
{
}

PopUpBase::~PopUpBase()
{

}

void PopUpBase::Parse(map<string, string> parameter)
{
    map<string,string>::const_iterator it = parameter.find("PopUpType");
    //PopUpId ,PopupType ,Show ,Title,ContextA,ContextB,ContextALight,ContextBLight,
    //ButtonA,ButtonB,ReplyButtonA,ReplyButtonB,Time ,Handle

    if(it!=parameter.end())
    {
        Release();
        m_PopupType = QString::fromStdString(it->second);
        m_bPopUpType = true;
        it = parameter.find("PopUpId");
        if(it != parameter.end())
        {
            m_PopUpId = QString::fromStdString(it->second);
            m_bPopUpId = true;
            it = parameter.find("Show");
            if(it != parameter.end())
            {
                m_PopUpShow = QString::fromStdString(it->second);
                m_bPopUpShow = true;

                it = parameter.find("FromAppId");
                if(it != parameter.end())
                {
                    m_fromAppId = QString::fromStdString(it->second);
                }

                it = parameter.find("Title");
                if(it != parameter.end())
                {
                    m_PopUpTitle = QString::fromStdString(it->second);
                    m_bPopUpTitle = true;
                }
                it = parameter.find("ContextA");
                if(it != parameter.end())
                {
                    m_PopUpContextA = QString::fromStdString(it->second);
                    m_bPopUpContextA = true;
                }
                it = parameter.find("ContextB");
                if(it != parameter.end())
                {
                    m_PopUpContextB = QString::fromStdString(it->second);
                    m_bPopUpContextB  = true;
                }
                it = parameter.find("ContextALight");
                if(it != parameter.end())
                {
                    m_PopUpContextALight = QString::fromStdString(it->second);
                    m_bPopUpContextALight = true;
                }
                it = parameter.find("ContextBLight");
                if(it != parameter.end())
                {
                    m_PopUpContextBLight = QString::fromStdString(it->second);
                    m_bPopUpContextBLight = true;
                }
                it = parameter.find("ButtonA");
                if(it != parameter.end())
                {
                    m_PopUpButtonA = QString::fromStdString(it->second);
                    m_bPopUpButtonA  = true;
                }
                it = parameter.find("ButtonB");
                if(it != parameter.end())
                {
                    m_PopUpButtonB = QString::fromStdString(it->second);
                    m_bPopUpButtonB = true;
                }
                it = parameter.find("ReplyButtonA");
                if(it != parameter.end())
                {
                    m_PopUpReplyButtonA = QString::fromStdString(it->second);
                    m_bPopUpReplyButtonA = true;
                }
                it = parameter.find("ReplyButtonB");
                if(it != parameter.end())
                {
                    m_PopUpReplyButtonB = QString::fromStdString(it->second);
                    m_bPopUpReplyButtonB = true;
                }
                it = parameter.find("Handle");
                if(it != parameter.end())
                {
                    m_PopUpHandle = QString::fromStdString(it->second);
                    m_bPopUpHandle = true;
                }
                it = parameter.find("Time");
                if(it != parameter.end())
                {
                    m_PopUpTime = QString::fromStdString(it->second);
                    m_bPopUpTime = true;
                }

                it = parameter.find("Password");
                if(it != parameter.end())
                {
                    m_Password = QString::fromStdString(it->second);
                    m_bPassword = true;
                }
            }
        }

    }
}

QString PopUpBase::GetPopUpId()
{
    return m_PopUpId;
}

QString PopUpBase::GetPopupType()
{
    return m_PopupType;
}

QString PopUpBase::GetPopUpShow()
{
    return m_PopUpShow;
}

QString PopUpBase::GetPopUpTitle()
{
    return m_PopUpTitle;
}

QString PopUpBase::GetPopUpContextA()
{
    return m_PopUpContextA;
}

QString PopUpBase::GetPopUpContextB()
{
    return m_PopUpContextB;
}

QString PopUpBase::GetPopUpContextALight()
{
    return m_PopUpContextALight;
}

QString PopUpBase::GetPopUpContextBLight()
{
    return m_PopUpContextBLight;
}

QString PopUpBase::GetPopUpButtonA()
{
    return m_PopUpReplyButtonA;
}

QString PopUpBase::GetPopUpButtonB()
{
    return m_PopUpReplyButtonB;
}

QString PopUpBase::GetPopUpReplyButtonA()
{
    return m_PopUpReplyButtonA;
}

QString PopUpBase::GetPopUpReplyButtonB()
{
    return m_PopUpReplyButtonB;
}

QString PopUpBase::GetPopUpHandle()
{
    return m_PopUpHandle;
}

int PopUpBase::GetPopUpTime()
{
    return  m_PopUpTime.toInt();
}

QString PopUpBase::GetFromeAppId()
{
    return m_fromAppId;
}

QString PopUpBase::GetPassword()
{
    return m_Password;
}

bool PopUpBase::IsExistPopUpId()
{
    return m_bPopUpId;
}

bool PopUpBase::IsExistPopupType()
{
    return m_bPopUpType;
}

bool PopUpBase::IsExistPopUpShow()
{
    return m_bPopUpShow;
}

bool PopUpBase::IsExistPopUpTitle()
{
    return m_bPopUpTitle;
}

bool PopUpBase::IsExistPopUpContextA()
{
    return m_bPopUpContextA;
}

bool PopUpBase::IsExistPopUpContextB()
{
    return m_bPopUpContextB;
}

bool PopUpBase::IsExistPopUpContextALight()
{
    return m_bPopUpContextALight;
}

bool PopUpBase::IsExistPopUpContextBLight()
{
    return m_bPopUpContextBLight;
}

bool PopUpBase::IsExistPopUpButtonA()
{
    return m_bPopUpButtonA;
}

bool PopUpBase::IsExistPopUpButtonB()
{
    return m_bPopUpButtonB;
}

bool PopUpBase::IsExistPopUpReplyButtonA()
{
    return m_bPopUpReplyButtonA;
}

bool PopUpBase::IsExistPopUpReplyButtonB()
{
    return m_bPopUpReplyButtonB;
}

bool PopUpBase::IsExistPopUpHandle()
{
    return m_bPopUpHandle;
}

bool PopUpBase::IsExistPopUpTime()
{
    return m_bPopUpTime;
}

bool PopUpBase::IsExistFromAppId()
{
    return m_bFromAppId;
}

bool PopUpBase::IsExistPassword()
{
    return m_bPassword;
}


void PopUpBase::Release()
{
     m_PopUpId = "";
     m_PopupType = "";
     m_PopUpShow = "";
     m_PopUpTitle = "";
     m_PopUpContextA = "";
     m_PopUpContextB = "";
     m_PopUpContextALight = "";
     m_PopUpContextBLight = "";
     m_PopUpButtonA = "";
     m_PopUpButtonB = "";
     m_PopUpReplyButtonA = "";
     m_PopUpReplyButtonB = "";
     m_PopUpHandle = "";
     m_PopUpTime = "";
     m_Password = "";

     m_bPopUpId = false ;
     m_bPopUpType = false ;
     m_bPopUpShow = false ;
     m_bPopUpTitle = false ;
     m_bPopUpContextA = false ;
     m_bPopUpContextB = false ;
     m_bPopUpContextALight = false ;
     m_bPopUpContextBLight = false ;
     m_bPopUpButtonA = false ;
     m_bPopUpButtonB = false ;
     m_bPopUpReplyButtonA = false ;
     m_bPopUpReplyButtonB = false ;
     m_bPopUpHandle = false ;
     m_bPopUpTime = false ;
     m_bFromAppId = false ;
     m_bPassword = false ;
}

void PopUpBase::Finish()
{

}

