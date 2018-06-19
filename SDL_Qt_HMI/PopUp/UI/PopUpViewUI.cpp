#include "PopUpViewUI.h"
#include "PopUp/app/PopUp.h"
#include "HMIFrameWork/log_interface.h"
#include "PopUp/app/PopUp.h"
#include "HMIFrameWork/HMIFrameWork.h"

PopUpViewUI::PopUpViewUI(QWidget *parent)
    :QWidget(parent)
    ,CView(PopUp::eViewId_Main)

{
    this->setGeometry(0,0,800,480);

    connect(PopUp::Inst(),SIGNAL(SigPopUpNotify(string,map<string,string>)),this,SLOT(OnPopUpNotify(string,map<string,string>)),Qt::UniqueConnection);
}

PopUpViewUI::~PopUpViewUI()
{

}

void PopUpViewUI::viewAction(int state)
{
    INFO("PopUpViewUI  viewAction state = %d", state);

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

void PopUpViewUI::CreatePopUp(QString &type,map<string, string> parameter)
{
    if("General" == type )
    {
       PopupGeneralView*  general=  new PopupGeneralView(this);
       PopupList.append(dynamic_cast<PopUpBase*>(general));
       connect(general,SIGNAL(SigTimerOut(QString)),this,SLOT(OnTimerOut(QString)));
       connect(general,SIGNAL(SigButtonClick(QString,QString)),this,SLOT(OnButtonClick(QString,QString)));
       general->Parse(parameter);
       general->Finish();

    }else if("Prompt" == type)
    {

    }
}

PopUpBase *PopUpViewUI::GetPopUp(QString& Id )
{
    QList <PopUpBase*>::iterator it = PopupList.begin();
    for(;it != PopupList.end();++it)
    {
        if((*it)->GetPopUpId() == Id)
        {
            return (*it);
        }
    }
    return NULL;
}

void PopUpViewUI::Parse(map<string, string> parameter)
{
    map<string,string>::const_iterator it = parameter.find("PopUpType");
    string type_,id_,show_;
    if(it!=parameter.end())
    {

        type_ = it->second;
        it = parameter.find("PopUpId");
        if(it != parameter.end())
        {
            id_= it->second;
            it = parameter.find("Show");
            if(it != parameter.end())
            {
                show_ = it->second;
                if(show_ == "True")
                {
                    HMIFrameWork::Inst()->AppShow(POPUP_ID);
                }
                QString qId = QString::fromStdString( id_);
                PopUpBase * pv = GetPopUp(qId);

                if(pv!=NULL)
                {
                    pv->Parse(parameter);
                    pv->Finish();

                }else
                {
                    QString qType = QString::fromStdString( type_);
                    CreatePopUp(qType,parameter);
                }
            }
        }

    }
}

void PopUpViewUI::ReleasePopup(const QString &Id)
{
    QList <PopUpBase*>::iterator it = PopupList.begin();
    for(;it != PopupList.end();++it)
    {
        if((*it)->GetPopUpId() == Id)
        {
            PopUpBase* temp= *it;
            PopupList.erase(it);

            delete temp;
            temp = NULL;
            return;
        }
    }
}

void PopUpViewUI::PopUpHide()
{
    if(PopupList.size() <= 0)
    {
        PopUp::Inst()->onAppHide();
    }
}

void PopUpViewUI::Replay(const QString& PopUpId,const QString& info)
{
    INFO("[Popup] Replay PopUpId = %s ,info =%s .",PopUpId.toStdString().c_str(),info.toStdString().c_str());
    QList <PopUpBase*>::iterator it = PopupList.begin();
    for(;it != PopupList.end();++it)
    {
        if((*it)->GetPopUpId() == PopUpId)
        {
            QString fromAppId = (*it)->GetFromeAppId();
            map<string,string> p;
            p.insert(make_pair("Button",info.toStdString()));
            HMIFrameWork::Inst()->Reply(fromAppId.toStdString(),p);
        }
    }
}

void PopUpViewUI::OnTimerOut(const QString& Id)
{
    ReleasePopup(Id);
    PopUpHide();
}

void PopUpViewUI::OnButtonClick(const QString& Id,const QString& replayInfo)
{

    Replay(Id,replayInfo);
    ReleasePopup(Id);
    PopUpHide();
}


void PopUpViewUI::OnPopUpNotify(string appId, map<string, string> parameter)
{
    Parse(parameter);
}

