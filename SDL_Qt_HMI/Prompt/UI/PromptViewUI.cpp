#include "PromptViewUI.h"
#include "Prompt/app/Prompt.h"
#include "HMIFrameWork/log_interface.h"
#include "Prompt/app/Prompt.h"
#include "HMIFrameWork/HMIFrameWork.h"

PromptViewUI::PromptViewUI(QWidget *parent)
    :QWidget(parent)
    ,CView(Prompt::eViewId_Main)

{
    this->setGeometry(0,0,800,480);

    connect(Prompt::Inst(),SIGNAL(SigPromptNotify(string,map<string,string>)),this,SLOT(OnPromptNotify(string,map<string,string>)),Qt::UniqueConnection);
}

PromptViewUI::~PromptViewUI()
{

}

void PromptViewUI::viewAction(int state)
{
    INFO("PromptViewUI  viewAction state = %d", state);

    switch (state) {
    case eviewStatus_Init:

        break;
    case eViewStatus_Active:

        break;
    case eViewStatus_Inactive:

        break;
    default:
        break;
    }
}

void PromptViewUI::CreatePrompt(QString &type,map<string, string> parameter)
{
    if("PromptMessage" == type)
    {
        PromptBase * pv = IsExistPromptMessage();
        if(NULL != pv)
        {
            pv->Parse(parameter);
            pv->Finish();
        }
        else
        {
           PromptMessageView*  Message=  new PromptMessageView(this);
           PromptList.append(dynamic_cast<PromptBase*>(Message));
           connect(Message,SIGNAL(SigTimerOut(QString)),this,SLOT(OnTimerOut(QString)));
           connect(Message,SIGNAL(SigButtonClick(QString,QString)),this,SLOT(OnButtonClick(QString,QString)));
           Message->Parse(parameter);
           Message->Finish();
        }

    }else if(type == "PromptNav")
    {
        PromptBase * pv = IsExistPromptNav();
        if(NULL != pv)
        {
            pv->Parse(parameter);
            pv->Finish();
        }
        else
        {
            PromptNavView*  Nav=  new PromptNavView(this);
            PromptList.append(dynamic_cast<PromptBase*>(Nav));
            connect(Nav,SIGNAL(SigTimerOut(QString)),this,SLOT(OnTimerOut(QString)));
            connect(Nav,SIGNAL(SigButtonClick(QString,QString)),this,SLOT(OnButtonClick(QString,QString)));
            Nav->Parse(parameter);
            Nav->Finish();
        }
    }
    UpdateWindowSize();
}

PromptBase *PromptViewUI::GetPrompt(QString& Id )
{
    QList <PromptBase*>::iterator it = PromptList.begin();
    for(;it != PromptList.end();++it)
    {
        if((*it)->GetPromptId() == Id)
        {
            return (*it);
        }
    }
    return NULL;
}

void PromptViewUI::Parse(map<string, string> parameter)
{
    map<string,string>::const_iterator it = parameter.find("PromptType");
    string type_,id_,show_;
    if(it!=parameter.end())
    {

        type_ = it->second;
        it = parameter.find("PromptId");
        if(it != parameter.end())
        {
            id_= it->second;
            it = parameter.find("Show");
            if(it != parameter.end())
            {
                show_ = it->second;
                if("True" == show_)
                {
                    HMIFrameWork::Inst()->AppShow(PROMPT_ID);
                }
                QString qId = QString::fromStdString( id_);
                PromptBase * pv = GetPrompt(qId);

                if(pv!=NULL)
                {
                    pv->Parse(parameter);
                    pv->Finish();

                }else
                {
                    QString qType = QString::fromStdString( type_);
                    CreatePrompt(qType,parameter);
                }
            }
        }

    }
}

PromptBase* PromptViewUI::IsExistPromptMessage()
{
    QList <PromptBase*>::iterator it = PromptList.begin();
    for(;it != PromptList.end();++it)
    {
        if("PromptMessage" == (*it)->GetPromptType())
        {
            return (*it);
        }
    }
    return NULL;
}

PromptBase* PromptViewUI::IsExistPromptNav()
{
    QList <PromptBase*>::iterator it = PromptList.begin();
    for(;it != PromptList.end();++it)
    {
        if("PromptNav" == (*it)->GetPromptType())
        {
            return (*it);
        }
    }
    return NULL;
}

void PromptViewUI::UpdateWindowSize()
{
    PromptBase * pvMessage = IsExistPromptMessage();
    if(PromptList.size()> 1)
    {
        Prompt::Inst()->UpdateWIndSize(QSize(800,102+77));
        if(NULL != pvMessage)
        {
            pvMessage->setGeometry(QRect(0,102,pvMessage->width(),pvMessage->height()));
        }
    }else
    {
        Prompt::Inst()->UpdateWIndSize(QSize(800,102));
        if(NULL != pvMessage)
        {
            pvMessage->setGeometry(QRect(0,0,pvMessage->width(),pvMessage->height()));

        }
    }
}

void PromptViewUI::ReleasePrompt(const QString &Id)
{
    QList <PromptBase*>::iterator it = PromptList.begin();
    for(;it != PromptList.end();++it)
    {
        INFO()<<PromptList.size();
        if((*it) != NULL && (*it)->GetPromptId() == Id)
        {
            PromptBase* temp= *it;
            PromptList.erase(it);

            if(temp != NULL)
            {
                delete temp;
                temp = NULL;
                UpdateWindowSize();
                return;
            }
        }
    }
    INFO() <<"ReleasePrompt";
}

void PromptViewUI::PromptHide()
{
    INFO()<<"PromptHide " << PromptList.size();
    if(PromptList.size() <= 0)
    {
        Prompt::Inst()->onAppHide();
    }
}

void PromptViewUI::Replay(const QString& PromptId,const QString& info)
{
    INFO() << " ++++++++ " << PromptId << "     " << info;
    QList <PromptBase*>::iterator it = PromptList.begin();
    for(;it != PromptList.end();++it)
    {
        if((*it)->GetPromptId() == PromptId)
        {
            INFO() << " ++++++++ " << PromptId << "     " << info;
            QString fromAppId = (*it)->GetFromeAppId();
            INFO() << " ++++++++ " << PromptId << "     " << info << "  " << fromAppId;
            map<string,string> p;
            p.insert(make_pair("Button",info.toStdString()));
            HMIFrameWork::Inst()->Reply(fromAppId.toStdString(),p);
        }
    }
}

void PromptViewUI::OnTimerOut(const QString& Id)
{
    ReleasePrompt(Id);
    PromptHide();
}

void PromptViewUI::OnButtonClick(const QString& Id,const QString& replayInfo)
{

    Replay(Id,replayInfo);
    INFO() <<" aaaaaaa" ;

    ReleasePrompt(Id);
    INFO() <<" aaaaaaa" ;

    PromptHide();

    INFO() <<" aaaaaaa" ;
}


void PromptViewUI::OnPromptNotify(string appId, map<string, string> parameter)
{
    Parse(parameter);
}

