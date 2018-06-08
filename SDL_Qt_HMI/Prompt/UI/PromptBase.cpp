#include "PromptBase.h"

PromptBase::PromptBase(QWidget *parent)
    :QWidget(parent)
    ,m_PromptId("")
    ,m_PromptType("")
    ,m_PromptShow("")
    ,m_PromptTitle("")
    ,m_PromptContextA("")
    ,m_PromptContextB("")
    ,m_PromptContextALight("")
    ,m_PromptContextBLight("")
    ,m_PromptButtonA("")
    ,m_PromptButtonB("")
    ,m_PromptReplyButtonA("")
    ,m_PromptReplyButtonB("")
    ,m_PromptHandle("")
    ,m_PromptTime("")
    ,m_fromAppId("")
    ,m_PromptMessageName("")
    ,m_PromptMessageTime("")
    ,m_PromptMessageContent("")
    ,m_PromptNavDirectionIcon("")
    ,m_PromptNavDistance("")
    ,m_PromptNavSceneDescription("")
    ,m_PromptNavDestination("")
    ,m_bPromptId(false)
    ,m_bPromptType(false)
    ,m_bPromptShow(false)
    ,m_bPromptTitle(false)
    ,m_bPromptContextA(false)
    ,m_bPromptContextB(false)
    ,m_bPromptContextALight(false)
    ,m_bPromptContextBLight(false)
    ,m_bPromptButtonA(false)
    ,m_bPromptButtonB(false)
    ,m_bPromptReplyButtonA(false)
    ,m_bPromptReplyButtonB(false)
    ,m_bPromptHandle(false)
    ,m_bPromptTime(false)
    ,m_bFromAppId(false)
    ,m_bPromptMessageName(false)
    ,m_bPromptMessageTime(false)
    ,m_bPromptMessageContent(false)
    ,m_bPromptNavDirectionIcon(false)
    ,m_bPromptNavDistance(false)
    ,m_bPromptNavSceneDescription(false)
    ,m_bPromptNavDestination(false)
{
}

void PromptBase::Parse(map<string, string> parameter)
{
    map<string,string>::const_iterator it = parameter.find("PromptType");
    //PromptId ,PromptType ,Show ,Title,ContextA,ContextB,ContextALight,ContextBLight,
    //ButtonA,ButtonB,ReplyButtonA,ReplyButtonB,Time ,Handle

    if(it!=parameter.end())
    {
        Release();
        m_PromptType = QString::fromStdString(it->second);
        m_bPromptType = true;
        it = parameter.find("PromptId");
        if(it != parameter.end())
        {
            m_PromptId = QString::fromStdString(it->second);
            m_bPromptId = true;
            it = parameter.find("Show");
            if(it != parameter.end())
            {
                m_PromptShow = QString::fromStdString(it->second);
                m_bPromptShow = true;

                it = parameter.find("FromAppId");
                if(it != parameter.end())
                {
                    m_fromAppId = QString::fromStdString(it->second);
                }

                it = parameter.find("Title");
                if(it != parameter.end())
                {
                    m_PromptTitle = QString::fromStdString(it->second);
                    m_bPromptTitle = true;
                }
                it = parameter.find("ContextA");
                if(it != parameter.end())
                {
                    m_PromptContextA = QString::fromStdString(it->second);
                    m_bPromptContextA = true;
                }
                it = parameter.find("ContextB");
                if(it != parameter.end())
                {
                    m_PromptContextB = QString::fromStdString(it->second);
                    m_bPromptContextB  = true;
                }
                it = parameter.find("ContextALight");
                if(it != parameter.end())
                {
                    m_PromptContextALight = QString::fromStdString(it->second);
                    m_bPromptContextALight = true;
                }
                it = parameter.find("ContextBLight");
                if(it != parameter.end())
                {
                    m_PromptContextBLight = QString::fromStdString(it->second);
                    m_bPromptContextBLight = true;
                }
                it = parameter.find("ButtonA");
                if(it != parameter.end())
                {
                    m_PromptButtonA = QString::fromStdString(it->second);
                    m_bPromptButtonA  = true;
                }
                it = parameter.find("ButtonB");
                if(it != parameter.end())
                {
                    m_PromptButtonB = QString::fromStdString(it->second);
                    m_bPromptButtonB = true;
                }
                it = parameter.find("ReplyButtonA");
                if(it != parameter.end())
                {
                    m_PromptReplyButtonA = QString::fromStdString(it->second);
                    m_bPromptReplyButtonA = true;
                }
                it = parameter.find("ReplyButtonB");
                if(it != parameter.end())
                {
                    m_PromptReplyButtonB = QString::fromStdString(it->second);
                    m_bPromptReplyButtonB = true;
                }
                it = parameter.find("Handle");
                if(it != parameter.end())
                {
                    m_PromptHandle = QString::fromStdString(it->second);
                    m_bPromptHandle = true;
                }
                it = parameter.find("Time");
                if(it != parameter.end())
                {
                    m_PromptTime = QString::fromStdString(it->second);
                    m_bPromptTime = true;
                }

                //message

                it = parameter.find("MessageName");
                if(it != parameter.end())
                {
                    m_PromptMessageName = QString::fromStdString(it->second);
                    m_bPromptMessageName = true;
                }

                it = parameter.find("MessageTime");
                if(it != parameter.end())
                {
                    m_PromptMessageTime = QString::fromStdString(it->second);
                    m_bPromptMessageTime = true;
                }

                it = parameter.find("MessageContent");
                if(it != parameter.end())
                {
                    m_PromptMessageContent = QString::fromStdString(it->second);
                    m_bPromptMessageContent = true;
                }

                //Nav
                it = parameter.find("NavDirection");
                if(it != parameter.end())
                {
                    m_PromptNavDirectionIcon = QString::fromStdString(it->second);
                    m_bPromptNavDirectionIcon = true;
                }

                it = parameter.find("NavDistance");
                if(it != parameter.end())
                {
                    m_PromptNavDistance = QString::fromStdString(it->second);
                    m_bPromptNavDistance = true;
                }

                it = parameter.find("NavSceneDescription");
                if(it != parameter.end())
                {
                    m_PromptNavSceneDescription = QString::fromStdString(it->second);
                    m_bPromptNavSceneDescription = true;
                }

                it = parameter.find("NavDestination");
                if(it != parameter.end())
                {
                    m_PromptNavDestination = QString::fromStdString(it->second);
                    m_bPromptNavDestination = true;
                }
            }
        }

    }
}

QString PromptBase::GetPromptId()
{
    return m_PromptId;
}

QString PromptBase::GetPromptType()
{
    return m_PromptType;
}

QString PromptBase::GetPromptShow()
{
    return m_PromptShow;
}

QString PromptBase::GetPromptTitle()
{
    return m_PromptTitle;
}

QString PromptBase::GetPromptContextA()
{
    return m_PromptContextA;
}

QString PromptBase::GetPromptContextB()
{
    return m_PromptContextB;
}

QString PromptBase::GetPromptContextALight()
{
    return m_PromptContextALight;
}

QString PromptBase::GetPromptContextBLight()
{
    return m_PromptContextBLight;
}

QString PromptBase::GetPromptButtonA()
{
    return m_PromptButtonA;
}

QString PromptBase::GetPromptButtonB()
{
    return m_PromptButtonB;
}

QString PromptBase::GetPromptReplyButtonA()
{
    return m_PromptReplyButtonA;
}

QString PromptBase::GetPromptReplyButtonB()
{
    return m_PromptReplyButtonB;
}

QString PromptBase::GetPromptHandle()
{
    return m_PromptHandle;
}

int PromptBase::GetPromptTime()
{
    return  m_PromptTime.toInt();
}

QString PromptBase::GetPromptMessageName()
{
    return m_PromptMessageName;
}

QString PromptBase::GetPromptMessageTime()
{
    return m_PromptMessageTime;
}

QString PromptBase::GetPromptMessageContent()
{
    return m_PromptMessageContent;
}

QString PromptBase::GetPromptNavDirection()
{
    return m_PromptNavDirectionIcon;
}

QString PromptBase::GetPromptNavDistance()
{
    return m_PromptNavDistance;
}

QString PromptBase::GetPromptNavSceneDescription()
{
    return m_PromptNavSceneDescription;
}

QString PromptBase::GetPromptNavDestination()
{
    return m_PromptNavDestination;
}

QString PromptBase::GetFromeAppId()
{
    return m_fromAppId;
}

bool PromptBase::IsExistPromptId()
{
    return m_bPromptId;
}

bool PromptBase::IsExistPromptType()
{
    return m_bPromptType;
}

bool PromptBase::IsExistPromptShow()
{
    return m_bPromptShow;
}

bool PromptBase::IsExistPromptTitle()
{
    return m_bPromptTitle;
}

bool PromptBase::IsExistPromptContextA()
{
    return m_bPromptContextA;
}

bool PromptBase::IsExistPromptContextB()
{
    return m_bPromptContextB;
}

bool PromptBase::IsExistPromptContextALight()
{
    return m_bPromptContextALight;
}

bool PromptBase::IsExistPromptContextBLight()
{
    return m_bPromptContextBLight;
}

bool PromptBase::IsExistPromptButtonA()
{
    return m_bPromptButtonA;
}

bool PromptBase::IsExistPromptButtonB()
{
    return m_bPromptButtonB;
}

bool PromptBase::IsExistPromptReplyButtonA()
{
    return m_bPromptReplyButtonA;
}

bool PromptBase::IsExistPromptReplyButtonB()
{
    return m_bPromptReplyButtonB;
}

bool PromptBase::IsExistPromptHandle()
{
    return m_bPromptHandle;
}

bool PromptBase::IsExistPromptTime()
{
    return m_bPromptTime;
}

bool PromptBase::IsExistFromAppId()
{
    return m_bFromAppId;
}

bool PromptBase::IsExistPromptMessageName()
{
    return m_bPromptMessageName;
}

bool PromptBase::IsExistPromptMessageTime()
{
    return m_bPromptMessageTime;
}

bool PromptBase::IsExistPromptMessageContent()
{
    return m_bPromptMessageContent;
}

bool PromptBase::IsExistPromptNavDirection()
{
    return m_bPromptNavDirectionIcon;
}

bool PromptBase::IsExistPromptNavDistance()
{
    return m_bPromptNavDistance;
}

bool PromptBase::IsExistPromptNavSceneDescription()
{
    return m_bPromptNavSceneDescription;
}

bool PromptBase::IsExistPromptNavDestination()
{
    return m_bPromptNavDestination;
}


void PromptBase::Release()
{
     m_PromptId = "";
     m_PromptType = "";
     m_PromptShow = "";
     m_PromptTitle = "";
     m_PromptContextA = "";
     m_PromptContextB = "";
     m_PromptContextALight = "";
     m_PromptContextBLight = "";
     m_PromptButtonA = "";
     m_PromptButtonB = "";
     m_PromptReplyButtonA = "";
     m_PromptReplyButtonB = "";
     m_PromptHandle = "";
     m_PromptTime = "";
}

void PromptBase::Finish()
{

}

