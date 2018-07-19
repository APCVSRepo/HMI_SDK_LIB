#include "BootAnimationUI.h"
#include "Home/app/Home.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HMIFrameWork/log_interface.h"

BootAnimationUI::BootAnimationUI(QWidget *parent)
    :QWidget(parent)
    ,CView(Home::eViewId_BootAnimation)
{
    this->setGeometry(QRect(0,0,800,480));
    this->setStyleSheet("QWidget{background:transparent;}");
    m_pAnimation = new BootAnimation(this);
    m_pAnimation->setGeometry(QRect(0,0,800,480));
    m_pAnimation->show();
    this->hide();

    connect(m_pAnimation,SIGNAL(PlayFinish()),this,SLOT(OnPlayFinish()),Qt::UniqueConnection);
}

void BootAnimationUI::viewAction(int state)
{
    INFO("[Home] BootAnimationUI viewAction %d .",state);
    switch (state) {
    case eViewStatus_Active:
    {
        m_pAnimation->PlayAnimation();
    }
        break;
    case eViewStatus_Inactive:
    {
        m_pAnimation->Stop();
    }
    case eviewStatus_Init:
    {
        m_pAnimation->Stop();
        this->hide();
    }
        break;
    default:
        break;
    }
}

void BootAnimationUI::OnPlayFinish()
{
   map<string,string> p;
   p.insert(make_pair("action","BootAnimationFinish"));
   HMIFrameWork::Inst()->Notify(HOME_ID,p);
}
