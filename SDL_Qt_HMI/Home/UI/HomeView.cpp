#include "HomeView.h"
#include <QDebug>
#include<unistd.h>
#include <QFont>
#include "AppLayer.h"
#include "Home/app/Home.h"
#include "HMIFrameWork/HMIFrameWork.h"
HomeView::HomeView(QWidget *parent)
    :QWidget(parent)
    ,CView(Home::eViewId_Main)
    ,m_pAppBtn(NULL)
    ,m_pAppBtnShadow(NULL)
    ,m_pAppBtnZoom(NULL)
    ,m_pMoveAnimation(NULL)
    ,m_viewRect(QRect(0,0,0,0))
    ,m_bIsStartUpTriggerDomain(false)
    ,m_triggerDomain(QRect(0,0,0,0))
    ,m_bEnterTriggerDomain(false)
    ,m_bIsEditStatus(false)
    ,m_pageSize(QSize(0,0))
    ,m_iPageTotalNum(0)
    ,m_iCurrentPageNum(1)
    ,m_iPressIndex(-1)
    ,m_iPosX(-1)
    ,m_iPosY(-1)
    ,m_stayPos(QPoint(-1,-1))
    ,m_iGlobalX(0)
    ,m_iPosDiffX(-1000)
    ,m_iPosDiffY(-1000)
    ,m_animationMode(eAnimationModeKnown)
    ,m_bIsStartShadow(false)
    ,m_bIsStartZoom(false)
    ,m_flip(eAFlipModeKnown)
    ,m_editMode(eEdit_ALL)
    ,m_iMovingIndex(-1)
    ,m_bIsMoving(false)
    ,m_bIsPageMoving(false)
    ,m_iFlipAppIndex(-1)
    ,m_iFlipStep(0)
{
    m_ListBtn.clear();
    m_MapRect.clear();
    installEventFilter(this);
    setAttribute(Qt::WA_AcceptTouchEvents);
    m_pressTimer.setInterval(1000);
    m_pressTimer.setSingleShot(true);
    connect(&m_pressTimer,SIGNAL(timeout()),this,SLOT(PressTimeout()));

    m_flipTimer.setInterval(1000);
    connect(&m_flipTimer,SIGNAL(timeout()),this,SLOT(FlipTimeout()));

    m_movingTimer.setInterval(1000);
    connect(&m_movingTimer,SIGNAL(timeout()),this,SLOT(OnMoving()));

    connect(this,SIGNAL(SigSortByIndex(int,int)),this,SLOT(OnSortByIndex(int,int)));

    m_pAppBtnShadow = new CCButton(this);
    //m_pAppBtnShadow->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_pAppBtnShadow->hide();

    m_pAppBtnZoom = new CCButton(this);
    //m_pAppBtnZoom->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_pAppBtnZoom->hide();
    m_pMoveAnimation = new QPropertyAnimation(this);
    m_pMoveAnimation->setTargetObject(this);
    m_pMoveAnimation->setPropertyName("position");

    SetPageSize(QSize(800,480));
    InitHomeView();
    StartUpTriggerDomain(true);
    SetTriggerDomain(QRect(0,40,160,440));


    connect(Home::Inst(),SIGNAL(SigQuickMove(QString)),this,SLOT(OnQuickMove(QString)),Qt::UniqueConnection);
   // this->show();
}

HomeView::~HomeView()
{

}

void HomeView::viewAction(int state)
{
    INFO()<<" Homeview  viewAction state = " << state;
}

void HomeView::InitHomeView()
{
    connect(this,SIGNAL(SigRelease(int,QString,QString)),this,SLOT(OnAppClick(int,QString,QString)),Qt::UniqueConnection);

    QList<AppInfo> listApps;
    {
        AppInfo appInfo3;
        appInfo3.AppBgPathNormal = ":/Home/Source/images/phone.png";
        appInfo3.AppBgPathPush = ":/Home/Source/images/phone_push.png";
        appInfo3.AppEditPath = "";
        appInfo3.AppIconPath = "";
        appInfo3.AppName =QObject::tr(PHONE_NAME);
        appInfo3.AppType =PHONE_ID;
        listApps.append(appInfo3);
    }
    {
        AppInfo appInfo1;
        appInfo1.AppBgPathNormal = ":/Home/Source/images/Media.png";
        appInfo1.AppBgPathPush = ":/Home/Source/images/Media_push.png";
        appInfo1.AppEditPath = "";
        appInfo1.AppIconPath = "";
        appInfo1.AppName =QObject::tr(MEDIA_NAME);
        appInfo1.AppType = MEDIA_ID;
        listApps.append(appInfo1);
    }
    {
        AppInfo appInfo2;
        appInfo2.AppBgPathNormal = ":/Home/Source/images/nav.png";
        appInfo2.AppBgPathPush = ":/Home/Source/images/nav_push.png";
        appInfo2.AppEditPath = "";
        appInfo2.AppIconPath = "";
        appInfo2.AppName =QObject::tr(NAV_NAME);
        appInfo2.AppType =NAV_ID;
        listApps.append(appInfo2);
    }
    {
        AppInfo appInfo5;
        appInfo5.AppBgPathNormal = ":/Home/Source/images/Setting.png";
        appInfo5.AppBgPathPush = ":/Home/Source/images/Setting_push.png";
        appInfo5.AppEditPath = "";
        appInfo5.AppIconPath = "";
        appInfo5.AppName =QObject::tr(SETTINGS_NAME);
        appInfo5.AppType =SETTINGS_ID;
        listApps.append(appInfo5);
    }
    {
        AppInfo appInfo6;
        appInfo6.AppBgPathNormal = ":/Home/Source/images/HVAC.png";
        appInfo6.AppBgPathPush = ":/Home/Source/images/HVAC_push.png";
        appInfo6.AppEditPath = "";
        appInfo6.AppIconPath = "";
        appInfo6.AppName =QObject::tr(HVAC_NAME);
        appInfo6.AppType =HVAC_ID;
        listApps.append(appInfo6);
    }
    {
        AppInfo appInfo7;
        appInfo7.AppBgPathNormal = ":/Home/Source/images/message.png";
        appInfo7.AppBgPathPush = ":/Home/Source/images/message_push.png";
        appInfo7.AppEditPath = "";
        appInfo7.AppIconPath = "";
        appInfo7.AppName =QObject::tr(MESSAGE_NAME);
        appInfo7.AppType =MESSAGE_ID;
        listApps.append(appInfo7);
    }

    {
        AppInfo appInfo8;
        appInfo8.AppBgPathNormal = ":/Home/Source/images/weather.png";
        appInfo8.AppBgPathPush = ":/Home/Source/images/weather_push.png";
        appInfo8.AppEditPath = "";
        appInfo8.AppIconPath = "";
        appInfo8.AppName =QObject::tr(WEATHER_NAME);
        appInfo8.AppType =WEATHER_ID;
        listApps.append(appInfo8);
    }
    {
        AppInfo appInfo4;
        appInfo4.AppBgPathNormal = ":/Home/Source/images/application.png";
        appInfo4.AppBgPathPush = ":/Home/Source/images/application_push.png";
        appInfo4.AppEditPath = "";
        appInfo4.AppIconPath = "";
        appInfo4.AppName =QObject::tr(SDLAPPS_NAME);
        appInfo4.AppType =SDLAPPS_ID;
        listApps.append(appInfo4);
    }

    for(int i = 0;i<listApps.size();++i)
    {
        int nRow = i / 4;
        int nClomn = i % 4;
        int nPage = (nRow + 1) / 2 + (nRow + 1) % 2;
        INFO()<<"ncol = "<<nClomn;
        CCButton * app = new CCButton(this);
        app->SetAppGeometry(QRect(OFFSET_POS_X +HOME_PAGE_OFFSET_POS_X + (nPage -1)*800 + (APP_BT_W + COLUMN_SPACE)*nClomn,OFFSET_POS_Y + (APP_BT_H + ROW_SPACE)*nRow,APP_BT_W,APP_BT_H));
        app->SetViewStatusStyle(CCButton::ViewStatusStyle_Change);
        app->InsertEditStyle(QRect(76,6,30,30),listApps.at(i).AppEditPath);
        app->InsertNormalStyle(QRect(0,0,APP_ICON_W,APP_ICON_H),listApps.at(i).AppBgPathNormal);
        app->InsertPushStyle(QRect(0,0,APP_ICON_W,APP_ICON_H),listApps.at(i).AppBgPathPush);
        app->InsertIconStyle(QRect(0,0,APP_ICON_W,APP_ICON_H),listApps.at(i).AppIconPath);
        app->InsertText(QRect(0,APP_ICON_H,APP_BT_W,31),listApps.at(i).AppName,true);
        app->InsertType(listApps.at(i).AppType);
        app->InsertName(listApps.at(i).AppName);
        if(listApps.at(i).AppType == WEATHER_ID)
        {
           app->AddExtendedText(QRect(0,71,120,20),"19℃",18);
        }
        InsertApp(i,app);
    }

    InsertAppFinish();
}

void HomeView::SetPageSize(QSize size)
{
    m_pageSize = size;
}

QSize HomeView::GetPageSize()
{
    return m_pageSize;
}

void HomeView::InsertApp(int index, CCButton *app)
{
    if(app)
    {
      int nPage = (index+1) / 8;
      int rpage = (index+1) % 8;
      if(0 == rpage)
      {
          m_iPageTotalNum = nPage;
      }
      else
      {
          m_iPageTotalNum = nPage + 1;
      }
      app->installEventFilter(this);
      app->SetEditStatus(false);
      app->SetIndex(index);
      connect(app,SIGNAL(MoveParentFinish(int)),this,SLOT(OnMoveParentFinish(int)));
      connect(app,SIGNAL(MoveAppFinish(int)),this,SLOT(OnMoveAppFinish(int)));
      app->show();
      m_ListBtn.insert(index,app);
      m_MapRect.insert(index,app->GetViewRect());
    }
}

void HomeView::InsertAppFinish()
{
    INFO("page width size = %d, height size = %d ,page num =%d.",m_pageSize.width(),m_pageSize.height(),m_iPageTotalNum);
    this->resize(QSize(m_pageSize.width()*m_iPageTotalNum+HOME_PAGE_OFFSET_POS_X,m_pageSize.height()));
    this->move(-HOME_PAGE_OFFSET_POS_X,0);
    m_viewRect.setRect(m_viewRect.x()+HOME_PAGE_OFFSET_POS_X,m_viewRect.y(),m_pageSize.width()*m_iPageTotalNum,m_pageSize.height());
    update();
    INFO("create home view  finish. ");
}


void HomeView::SetIsEditStatus(bool isEdit)
{
    m_bIsEditStatus = isEdit;
    m_movingTimer.stop();
    m_iMovingIndex = -1;
    map<string,string> p;
    if(isEdit)
        p.insert(make_pair("AppEditStatus","true"));
    else
        p.insert(make_pair("AppEditStatus","false"));
    HMIFrameWork::Inst()->Notify(QUICKLANUCH_ID,p);
    emit SigIsEnterEdit(isEdit);
}

bool HomeView::GetIsEditStatus()
{
    return m_bIsEditStatus;
}

void HomeView::GoToEditStatus()
{
    if(m_editMode == eEdit_ALL)
    {
        SetIsEditStatus(true);
        if(m_ListBtn.size())
        {
           QList<CCButton*>::iterator it = m_ListBtn.begin();
           for(;it != m_ListBtn.end();++it)
           {
               (*it)->SetEditStatus(true);
               (*it)->JitterAnimation(500);
           }
        }
    }
    else if(m_editMode == eEdit_SINGLE)
    {
        if(GetApp())
        {
            SetIsEditStatus(true);
            GetApp()->SetEditStatus(true);
        }
    }
}

void HomeView::ExitEditStatus()
{
    SetIsEditStatus(false);
    if(m_ListBtn.size())
    {
       QList<CCButton*>::iterator it = m_ListBtn.begin();
       for(;it != m_ListBtn.end();++it)
       {
           (*it)->SetEditStatus(false);
       }
    }
    if(GetApp())
    {
        GetApp()->OpacityAnimation(0.5,1,500);
       // GetApp()->UpdateText(GetApp()->GetText());
        GetApp()->MoveAnimation(QPoint(GetApp()->geometry().x(),GetApp()->geometry().y()),QPoint(GetApp()->GetViewRect().x(),GetApp()->GetViewRect().y()),500);
        GetApp()->SizeAnimation(QSize(APP_BT_W+10, APP_BT_H+10), QSize(APP_BT_W, APP_BT_H),300,false);
    }
}

void HomeView::RemoveAll()
{
    if(m_ListBtn.size())
    {
       QList<CCButton*>::iterator it = m_ListBtn.begin();
       for(;it != m_ListBtn.end();++it)
       {
           if(*it)
           {
               (*it)->hide();
               delete *it;
           }
       }
       m_ListBtn.clear();
    }
}

void HomeView::RemoveSelect(int index)
{

    if(m_ListBtn.size())
    {
       QList<CCButton*>::iterator it = m_ListBtn.begin();
       for(;it != m_ListBtn.end();++it)
       {
           if((NULL != (*it)) && ((*it)->GetIndex() == index))
           {
               CCButton * appBtn = (*it);
               appBtn->hide();
               it = m_ListBtn.erase(it);
               delete appBtn;
               appBtn = NULL;
               if(m_MapRect.size())
               {
                   m_MapRect.erase(m_MapRect.end() - 1);
               }
           }
           if((NULL != (*it)) && (it != m_ListBtn.end())&& ((*it)->GetIndex()>index))
           {
               (*it)->SetIndex((*it)->GetIndex()-1);
               if(m_MapRect.find((*it)->GetIndex())!= m_MapRect.end())
               {
                (*it)->SetViewRect(m_MapRect.find((*it)->GetIndex()).value());
                (*it)->MoveAnimation(QPoint((*it)->geometry().x(),(*it)->geometry().y()),\
                                     QPoint(m_MapRect.find((*it)->GetIndex()).value().x(),m_MapRect.find((*it)->GetIndex()).value().y()),500);
               }
           }
       }
    }
}

void HomeView::RemoveSelect(QString name)
{
    if(m_ListBtn.size())
    {
       QList<CCButton*>::iterator it = m_ListBtn.begin();
       for(;it != m_ListBtn.end();++it)
       {
           if((*it)->GetName() == name)
           {
               RemoveSelect((*it)->GetIndex());
               break;
           }
       }
    }
}

void HomeView::SortByIndex(int index)
{
    if(m_ListBtn.size())
    {
        CCButton* Pressmodel = NULL;
        QList<CCButton*>::iterator pressit = m_ListBtn.begin();
        for(;pressit != m_ListBtn.end();++pressit)
        {
            if((NULL != (*pressit)) &&((*pressit)->GetIndex() == m_iPressIndex))
            {
                Pressmodel = (*pressit);
                m_ListBtn.erase(pressit);
                break;
            }
        }
        QList<CCButton*>::iterator it = m_ListBtn.begin();
        for(;it != m_ListBtn.end();++it)
        {
            if((NULL != (*it)) && ((*it)->GetIndex() >= index))
            {
                if((*it)->GetIndex() == index)
                {
                    Pressmodel->SetIndex(index);
                    m_ListBtn.insert(index,Pressmodel);
                }
                (*it)->SetIndex((*it)->GetIndex()+1);
            }
        }
    }
}

void HomeView::SortByIndex(int PressIndex, int SelectIndex)
{
    QList<CCButton*>::iterator it = m_ListBtn.begin();
    for(;it != m_ListBtn.end();++it)
    {
        if((*it)->GetIndex() == PressIndex)
        {
            (*it)->SetIndex(SelectIndex);
            if(m_MapRect.find(SelectIndex)!=m_MapRect.end())
            {
                (*it)->SetViewRect(m_MapRect.find(SelectIndex).value());
                (*it)->MoveAnimation(QPoint((*it)->geometry().x(),(*it)->geometry().y()),\
                                     QPoint((*it)->GetViewRect().x(),(*it)->GetViewRect().y()),
                                     500);
            }
        }
        else if(PressIndex>SelectIndex)
        {

            if((*it)->GetIndex()>=SelectIndex && (*it)->GetIndex()<PressIndex)
            {

                (*it)->SetIndex((*it)->GetIndex()+1);
                if(m_MapRect.find((*it)->GetIndex())!=m_MapRect.end())
                {
                    (*it)->SetViewRect(m_MapRect.find((*it)->GetIndex()).value());
                    (*it)->MoveAnimation(QPoint((*it)->geometry().x(),(*it)->geometry().y()),\
                                         QPoint((*it)->GetViewRect().x(),(*it)->GetViewRect().y()),
                                         500);
                }
            }
        }
        else if(PressIndex<SelectIndex)
        {

            if((*it)->GetIndex()>PressIndex && (*it)->GetIndex()<=SelectIndex)
            {

                (*it)->SetIndex((*it)->GetIndex()-1);
                if(m_MapRect.find((*it)->GetIndex())!=m_MapRect.end())
                {
                    (*it)->SetViewRect(m_MapRect.find((*it)->GetIndex()).value());
                    (*it)->MoveAnimation(QPoint((*it)->geometry().x(),(*it)->geometry().y()),\
                                         QPoint((*it)->GetViewRect().x(),(*it)->GetViewRect().y()),
                                         500);
                }
            }
        }
    }
}

void HomeView::SortByIndexNoMove(int PressIndex, int SelectIndex)
{
    QList<CCButton*>::iterator it = m_ListBtn.begin();
    for(;it != m_ListBtn.end();++it)
    {
        if((*it)->GetIndex() == PressIndex)
        {
            (*it)->SetIndex(SelectIndex);
            if(m_MapRect.find(SelectIndex)!=m_MapRect.end())
            {
                (*it)->SetViewRect(m_MapRect.find(SelectIndex).value());
            }
            continue;
        }
        else if(PressIndex>SelectIndex)
        {

            if((*it)->GetIndex()>=SelectIndex && (*it)->GetIndex()<PressIndex)
            {

                (*it)->SetIndex((*it)->GetIndex()+1);
                if((*it)->GetIndex() == PressIndex)
                {
                    m_iFlipAppIndex = (*it)->GetIndex();
                }
                if(m_MapRect.find((*it)->GetIndex())!=m_MapRect.end())
                {
                    (*it)->SetViewRect(m_MapRect.find((*it)->GetIndex()).value());
                    (*it)->MoveAnimation(QPoint((*it)->geometry().x(),(*it)->geometry().y()),\
                                         QPoint((*it)->GetViewRect().x(),(*it)->GetViewRect().y()),
                                         500);
                }
            }
        }
        else if(PressIndex<SelectIndex)
        {

            if((*it)->GetIndex()>PressIndex && (*it)->GetIndex()<=SelectIndex)
            {
                (*it)->SetIndex((*it)->GetIndex()-1);
                if((*it)->GetIndex() == SelectIndex-1)
                {
                    m_iFlipAppIndex = (*it)->GetIndex();
                }
                if(m_MapRect.find((*it)->GetIndex())!=m_MapRect.end())
                {
                    (*it)->SetViewRect(m_MapRect.find((*it)->GetIndex()).value());
                    (*it)->MoveAnimation(QPoint((*it)->geometry().x(),(*it)->geometry().y()),\
                                         QPoint((*it)->GetViewRect().x(),(*it)->GetViewRect().y()),
                                         500);
                }
            }
        }
    }
}

void HomeView::SortMove()
{
    QList<CCButton*>::iterator it = m_ListBtn.begin();
    for(;it != m_ListBtn.end();++it)
    {

    }
}

void HomeView::SetViewGeometry(QRect rect)
{
    m_viewRect = rect;
    this->setGeometry(rect);
}

void HomeView::SetCurrentPageNum(int page)
{
    m_iCurrentPageNum = page;
}

int HomeView::GetCurrentPageNum()
{
    return m_iCurrentPageNum;
}

int HomeView::Index(int x, int y)
{
    if(m_viewRect.contains(x,y))
    {
        QList<CCButton*>::iterator it = m_ListBtn.begin();
        for(;it != m_ListBtn.end();++it)
        {
            QRect rect((*it)->GetViewRect().x()+(*it)->GetNormalStyleRect().x(),(*it)->GetViewRect().y()+(*it)->GetNormalStyleRect().y(),\
                       (*it)->GetNormalStyleRect().width(),(*it)->GetNormalStyleRect().height());
            if(rect.contains(x,y))
            {
                return (*it)->GetIndex();
            }
        }
    }
    return -1;
}

CCButton *HomeView::GetApp()
{
    return m_pAppBtn;
}

void HomeView::SetApp(CCButton *app)
{
    m_pAppBtn = app;
}

CCButton * HomeView::SelectedApp(int index)
{
    if(m_ListBtn.size())
    {
        QList<CCButton*>::iterator it = m_ListBtn.begin();
        for(;it != m_ListBtn.end();++it)
        {
            if((*it)->GetIndex() == index)
            {
                return (*it);
            }
        }
    }
    return NULL;
}

CCButton *HomeView::SelectedApp(int x, int y)
{
    if(m_viewRect.contains(x,y))
    {
        QList<CCButton*>::iterator it = m_ListBtn.begin();
        for(;it != m_ListBtn.end();++it)
        {
            QRect rect((*it)->geometry().x()+(*it)->GetNormalStyleRect().x(),(*it)->geometry().y()+(*it)->GetNormalStyleRect().y(),\
                       (*it)->GetNormalStyleRect().width(),(*it)->GetNormalStyleRect().height());
            if(rect.contains(x,y))
            {
                return (*it);
            }
        }
    }
    return NULL;
}

void HomeView::SetAnimationMode(HomeView::eAnimationMode mode)
{
    m_animationMode = mode;
}

HomeView::eAnimationMode HomeView::getAnimationMode()
{
    return m_animationMode;
}

void HomeView::AppBtnShadow(CCButton *btn)
{
    if(!m_bIsStartShadow)
    {
        m_bIsStartShadow = true;
        if(btn && m_pAppBtnShadow)
        {
           m_pAppBtnShadow->SetAppGeometry(btn->geometry());
           m_pAppBtnShadow->SetEditStatus(true);
           m_pAppBtnShadow->InsertEditStyle(btn->GetEditStyleRect(),btn->GetEditStyle());
           m_pAppBtnShadow->InsertNormalStyle(btn->GetNormalStyleRect(),btn->GetNormalStyle());
           m_pAppBtnShadow->InsertPushStyle(btn->GetPushStyleRect(),btn->GetPushStyle());
           m_pAppBtnShadow->InsertIconStyle(btn->GetIconStyleRect(),btn->GetIconStyle());
           m_pAppBtnShadow->InsertText(btn->GetTextRect(),btn->GetText(),true);
           m_pAppBtnShadow->InsertName(btn->GetName());
           m_pAppBtnShadow->OpacityAnimation(0.5,0,500,true);
        }
    }
}

void HomeView::AppBtnZoom(CCButton *btn)
{   if(!m_bIsStartZoom)
    {
         m_bIsStartZoom = true;
        if(btn && m_pAppBtnZoom)
        {
           m_pAppBtnZoom->SetAppGeometry(btn->geometry());
           m_pAppBtnZoom->InsertIconStyle(btn->GetIconStyleRect(),btn->GetIconStyle());
           m_pAppBtnZoom->SizeAnimation(QSize(btn->GetIconStyleRect().width(),btn->GetIconStyleRect().height()),QSize(0,0),300,true);
        }
    }
}

void HomeView::ToNextOrPre(QRect rect)
{
    if(rect.x() <=(m_iCurrentPageNum-1)*m_pageSize.width() )
    {
        if(m_iCurrentPageNum>1)
        {
            m_flip = eAFlipModeTopre;
            if(!m_flipTimer.isActive())
            {
                m_flipTimer.start();
            }
        }
        else
        {
          m_flipTimer.stop();
        }
    }
    else if(rect.x() + rect.width() >= m_iCurrentPageNum*m_pageSize.width())
    {
        if(m_iCurrentPageNum < m_iPageTotalNum)
        {
            m_flip = eAFlipModeToNext;
            if(!m_flipTimer.isActive())
            {
                m_flipTimer.start();
            }
        }
        else
        {
            m_flipTimer.stop();
        }
    }
    else
    {
        if(m_flipTimer.isActive())
        {
            m_flipTimer.stop();
        }
        m_flip = eAFlipModeKnown;
    }
}

void HomeView::ToNextPage()
{
    if(m_iCurrentPageNum < m_iPageTotalNum)
    {
        m_bIsPageMoving = true;
        ++m_iCurrentPageNum;
        if(GetApp())
        {
            GetApp()->MoveParentAnimation(QPoint((-(m_iCurrentPageNum-2)*m_pageSize.width()),0),QPoint((-(m_iCurrentPageNum-1)*m_pageSize.width()),0),500);
        }
        else
        {
            this->MoveAnimation(QPoint((-(m_iCurrentPageNum-2)*m_pageSize.width()),0),QPoint((-(m_iCurrentPageNum-1)*m_pageSize.width()),0),500);
        }
        emit SigPageNum(m_iCurrentPageNum);
    }
    else
    {
        m_flipTimer.stop();
    }
}

void HomeView::ToPrePage()
{
    if(m_iCurrentPageNum > 1)
    {
        m_bIsPageMoving = true;
        --m_iCurrentPageNum;
        if(GetApp())
        {
            GetApp()->MoveParentAnimation(QPoint((-(m_iCurrentPageNum)*m_pageSize.width()),0),QPoint((-(m_iCurrentPageNum-1)*m_pageSize.width()),0),500);
        }
        else
        {
            this->MoveAnimation(QPoint((-(m_iCurrentPageNum)*m_pageSize.width()),0),QPoint((-(m_iCurrentPageNum-1)*m_pageSize.width()),0),500);
        }
        emit SigPageNum(m_iCurrentPageNum);
    }
    else
    {
      m_flipTimer.stop();
    }
}

void HomeView::ToSelectPage(int page)
{
    if(1 <= page && m_iPageTotalNum >= page)
    {
        this->MoveAnimation(QPoint((-(m_iCurrentPageNum-1)*m_pageSize.width()),0),QPoint((-(page-1)*m_pageSize.width()),0),500);
        m_iCurrentPageNum = page;
    }
}

void HomeView::ToNoAnimationSelectPage(int page)
{
    if(1 <= page && m_iPageTotalNum >= page)
    {
        this->move(QPoint((-(page-1)*m_pageSize.width()),0));
        m_iCurrentPageNum = page;
    }
}

void HomeView::MoveAnimation(const QPoint startPos, const QPoint endPos, int time)
{
    if(m_pMoveAnimation)
    {

        m_bIsPageMoving = false;
        m_pMoveAnimation->setDuration(time);
        m_pMoveAnimation->setStartValue(startPos);
        m_pMoveAnimation->setEndValue(endPos);
        m_pMoveAnimation->start();
    }
}

void HomeView::UpdateTextByIndex(int index, QString text)
{
    QList<CCButton*>::iterator it = m_ListBtn.begin();
    for(;it != m_ListBtn.end();++it)
    {
        if((*it)->GetIndex() == index)
        {
            (*it)->UpdateText(text,false);
        }
    }
}

QList<CCButton *> HomeView::GetAppList()
{
    return m_ListBtn;
}

void HomeView::StartUpTriggerDomain(bool isStartUpTriggerDomain)
{
    if(m_bIsStartUpTriggerDomain)
    {
        disconnect(this,SIGNAL(SigEnterTriggerDomain(bool,QString)),this,SLOT(OnEnterTriggerDomainStatus(bool,QString)));
    }
    m_bIsStartUpTriggerDomain = isStartUpTriggerDomain;
    if(m_bIsStartUpTriggerDomain)
    {
        connect(this,SIGNAL(SigEnterTriggerDomain(bool,QString)),this,SLOT(OnEnterTriggerDomainStatus(bool,QString)),Qt::UniqueConnection);
    }
}

void HomeView::SetTriggerDomain(QRect r)
{
    m_triggerDomain = r;
}

bool HomeView::IsTriggerDomain(int x, int y)
{

    if(!m_bIsStartUpTriggerDomain)
    {
        return false;
    }

    if(m_triggerDomain.contains(x,y))
    {
        INFO("contain ok !");
        return true;
    }
    INFO("contain none !");
    return false;
}

bool HomeView::MouseEvent(QObject *obj, QEvent *event)
{
    if(NULL == obj || NULL == event)
    {
        return QWidget::eventFilter(obj,event);
    }
    if(NULL == GetApp())
    {
        SetApp(static_cast<CCButton*>(obj));
    }
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    QPoint globalPos(0,0);
    QPoint globalPos2(0,0);
    if(GetApp())
    {
        GetApp()->raise();
        globalPos2 = GetApp()->GetGlobalPos(QPoint(mouseEvent->pos().x(),mouseEvent->pos().y()));
        globalPos.setX(GetApp()->geometry().x()+mouseEvent->pos().x());
        globalPos.setY(GetApp()->geometry().y()+mouseEvent->pos().y());
    }

    switch (event->type()) {
    case QEvent::MouseButtonPress:
    {
        m_iPosX = globalPos.x();
        m_iPosY = globalPos.y();
        m_bIsStartShadow = false;
        m_bIsStartZoom = false;
        m_iGlobalX = 0;
        m_bIsMoving = false;
        if(GetApp())
        {
            GetApp()->SetViewStatus(CCButton::ViewStatusPushed);
        }
        if(GetIsEditStatus())
        {
            m_movingTimer.stop();
            m_iMovingIndex = -1;
            if(GetApp())
            {
               GetApp()->raise();
               emit SigPress(GetApp()->GetIndex(),GetApp()->GetType(),GetApp()->GetName());
               m_iPosDiffX = m_iPosX-GetApp()->geometry().x();
               m_iPosDiffY = m_iPosY-GetApp()->geometry().y();
               GetApp()->SetIsPress(true);
               GetApp()->UpdateText("",true);

            }
        }
        else
        {
            if(GetApp())
            {
               emit SigPress(GetApp()->GetIndex(),GetApp()->GetType(),GetApp()->GetName());
               m_iPosDiffX = m_iPosX-GetApp()->geometry().x();
               m_iPosDiffY = m_iPosY-GetApp()->geometry().y();
               GetApp()->SetIsPress(true);
               m_pressTimer.start();
            }

         }
    }
        break;
    case QEvent::MouseMove:
    {
        if(GetIsEditStatus())
        {
            if(GetApp())
            {
                GetApp()->move(globalPos.x()-m_iPosDiffX,globalPos.y()-m_iPosDiffY);
                //AppBtnShadow(GetApp());
                m_stayPos.setX((globalPos2.x())%m_pageSize.width());
                m_stayPos.setY(globalPos2.y());
               if(IsTriggerDomain(GetApp()->x()+20,GetApp()->y()+20)&&!m_bIsPageMoving&&((this->geometry().x()+ m_pageSize.width()*(m_iCurrentPageNum - 1)) >=0)) {
                  if(!m_bEnterTriggerDomain)
                  {
                    m_bEnterTriggerDomain = true;
                    emit SigEnterTriggerDomain(true,GetApp()->GetType());
                  }

                }else
                {
                   if(m_bEnterTriggerDomain)
                   {
                       m_bEnterTriggerDomain = false;
                       emit SigEnterTriggerDomain(false,"");
                   }

                }

            }
        }
    }
        break;
    case QEvent::MouseButtonRelease:
    {
        m_pressTimer.stop();
        m_flipTimer.stop();
        if(GetApp())
        {
           GetApp()->SetViewStatus(CCButton::ViewStatusNormal);
           GetApp()->SetIsPress(false);
        }
        qDebug() << "x = " << m_stayPos.x() << " y = " << m_stayPos.y();
        if(GetIsEditStatus())
        {
            if(GetApp())
            {

               if(IsTriggerDomain(m_stayPos.x(),m_stayPos.y())&&!m_bIsPageMoving&&((this->geometry().x()+ m_pageSize.width()*(m_iCurrentPageNum - 1)) >=0)) {

                   INFO()<<"replace start .";
                   map<string,string> p;
                   p.insert(make_pair("QuickLanuchAppType",GetApp()->GetType().toStdString()));
                   p.insert(make_pair("QuickLanuchX",QString::number(m_stayPos.x()).toStdString()));
                   p.insert(make_pair("QuickLanuchY",QString::number(m_stayPos.y()).toStdString()));
                   HMIFrameWork::Inst()->Notify(QUICKLANUCH_ID,p);
                   emit SigTriggerDomain(m_stayPos.x(),m_stayPos.y(),GetApp()->GetInfo());
                }

            }
            if(m_bEnterTriggerDomain)
            {
                m_bEnterTriggerDomain = false;
                emit SigEnterTriggerDomain(false,"");
            }
        }
        if(GetApp()&&!GetIsEditStatus())
        {
           if(!m_bIsMoving)
           {
              INFO("mouse HomeView SigRelease");
              emit SigRelease(GetApp()->GetIndex(),GetApp()->GetType(),GetApp()->GetName());
           }
        }
        if(GetIsEditStatus())
        {
            ExitEditStatus();
        }
        m_bIsPageMoving = false;
        m_bIsMoving = false;
        SetApp(NULL);
    }
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj,event);
}

bool HomeView::TouchEvent(QObject *obj, QEvent *event)
{
    if(NULL == obj || NULL == event)
    {
        return QWidget::eventFilter(obj,event);
    }
    if(NULL == GetApp())
    {
        SetApp(static_cast<CCButton*>(obj));
    }
    QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
    QPoint globalPos(0,0);
    QPoint globalPos2(0,0);
    if(GetApp())
    {
        globalPos2 = GetApp()->GetGlobalPos(QPoint(touchEvent->touchPoints().at(0).pos().x(),touchEvent->touchPoints().at(0).pos().y()));
        globalPos.setX(GetApp()->geometry().x()+touchEvent->touchPoints().at(0).pos().x());
        globalPos.setY(GetApp()->geometry().y()+touchEvent->touchPoints().at(0).pos().y());
    }
    switch (event->type()) {
    case QEvent::TouchBegin:
    {
        m_iPosX = globalPos.x();
        m_iPosY = globalPos.y();
        m_bIsStartShadow = false;
        m_bIsStartZoom = false;
        m_iGlobalX = 0;
        m_bIsMoving = false;
        if(GetIsEditStatus())
        {
            m_movingTimer.stop();
            m_iMovingIndex = -1;
            if(GetApp())
            {
               GetApp()->raise();
               emit SigPress(GetApp()->GetIndex(),GetApp()->GetType(),GetApp()->GetName());
               m_iPosDiffX = m_iPosX-GetApp()->geometry().x();
               m_iPosDiffY = m_iPosY-GetApp()->geometry().y();
               GetApp()->OpacityAnimation(1,0.5,500);
               GetApp()->SizeAnimation(QSize(APP_BT_W, APP_BT_H), QSize(APP_BT_W+10, APP_BT_H+10),300,false);
               GetApp()->SetViewStatus(CCButton::ViewStatusPushed);
               GetApp()->SetIsPress(true);
               GetApp()->UpdateText("",true);

            }
        }
        else
        {
            if(GetApp())
            {
               emit SigPress(GetApp()->GetIndex(),GetApp()->GetType(),GetApp()->GetName());
               m_iPosDiffX = m_iPosX-GetApp()->geometry().x();
               m_iPosDiffY = m_iPosY-GetApp()->geometry().y();
               GetApp()->SetViewStatus(CCButton::ViewStatusPushed);
               GetApp()->SetIsPress(true);
               m_pressTimer.start();
            }

         }
    }
        break;
    case QEvent::TouchUpdate:
    {
        if(GetIsEditStatus())
        {
            if(GetApp())
            {
                GetApp()->move(globalPos.x()-m_iPosDiffX,globalPos.y()-m_iPosDiffY);
                emit SigMovingPos(globalPos2.x()%m_pageSize.width(),globalPos2.y(),GetApp()->GetType());
                AppBtnShadow(GetApp());
                ToNextOrPre(GetApp()->geometry());
                m_stayPos.setX((globalPos2.x())%m_pageSize.width());
                m_stayPos.setY(globalPos2.y());
                if(Index(globalPos.x(),globalPos.y())>=0)
                {
                    if(Index(globalPos.x(),globalPos.y()) != m_iMovingIndex)
                    {
                        m_movingTimer.start();
                    }
                    else
                    {
                        if(!m_movingTimer.isActive())
                        {
                           m_movingTimer.start();
                        }
                    }
                    m_iMovingIndex = Index(globalPos.x(),globalPos.y());
                }
                else if(Index(GetApp()->geometry().x()+GetApp()->geometry().width(),GetApp()->geometry().y()+GetApp()->geometry().height()/2)>=0)
                {
                    if(Index(GetApp()->geometry().x()+GetApp()->geometry().width(),GetApp()->geometry().y()+GetApp()->geometry().height()/2)!= m_iMovingIndex)
                    {
                        m_movingTimer.start();
                    }
                    else
                    {
                        if(!m_movingTimer.isActive())
                        {
                           m_movingTimer.start();
                        }
                    }
                    m_iMovingIndex = Index(GetApp()->geometry().x()+GetApp()->geometry().width(),GetApp()->geometry().y()+GetApp()->geometry().height()/2);
                }
                else
                {
                    m_movingTimer.stop();
                    m_iMovingIndex = -1;
                }
            }
        }
    }
        break;
    case QEvent::TouchEnd:
    {
        m_pressTimer.stop();
        m_flipTimer.stop();
        if(GetIsEditStatus())
        {
            if(GetApp())
            {
               emit SigReleasePos(globalPos2.x()%m_pageSize.width(),globalPos2.y(),GetApp()->GetType());
                if(!m_bIsStartUpTriggerDomain || !IsTriggerDomain(m_stayPos.x(),m_stayPos.y()))
                {
                   GetApp()->OpacityAnimation(0.5,1,500);
                   GetApp()->UpdateText(GetApp()->GetText());
                   GetApp()->MoveAnimation(QPoint(globalPos.x()-m_iPosDiffX,globalPos.y()-m_iPosDiffY),QPoint(GetApp()->GetViewRect().x(),GetApp()->GetViewRect().y()),500);
                   GetApp()->SizeAnimation(QSize(APP_BT_W+10, APP_BT_H+10), QSize(APP_BT_W, APP_BT_H),300,false);
                   GetApp()->update();
                }
                else
                {
                  GetApp()->SizeAnimation(QSize(APP_BT_W+10, APP_BT_H+10), QSize(APP_BT_W, APP_BT_H),300,false);
                  GetApp()->UpdateText(GetApp()->GetText());
                  GetApp()->move(QPoint(GetApp()->GetViewRect().x(),GetApp()->GetViewRect().y()));
                  GetApp()->OpacityAnimation(0,1,500);
                  GetApp()->update();
                }
               if(Index(globalPos.x(),globalPos.y())>=0)
               {
                   if(!m_bIsStartUpTriggerDomain || !IsTriggerDomain(m_stayPos.x(),m_stayPos.y()))
                    {
                     SortByIndex(GetApp()->GetIndex(),Index(globalPos.x(),globalPos.y()));
                     m_stayPos.setX(-1);
                     m_stayPos.setY(-1);
                   }
               }
            }
        }
        if(GetApp())
        {
           if(!m_bIsMoving)
           {
              INFO("touch HomeView SigRelease");
              emit SigRelease(GetApp()->GetIndex(),GetApp()->GetType(),GetApp()->GetName());
           }
        }
        if(GetApp())
        {
           GetApp()->SetViewStatus(CCButton::ViewStatusNormal);
           GetApp()->SetIsPress(false);
        }
        m_bIsMoving = false;
        SetApp(NULL);
    }
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj,event);
}

bool HomeView::GestureEvent(QObject *obj, QEvent *event)
{
    if(NULL == obj || NULL == event)
    {
        return true;
    }

   return false;
}


bool HomeView::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonDblClick:
        return true;
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease:
    {
        if("CCButton" ==  (QString)(obj->metaObject()->className()))
        {
            if(NULL == GetApp() || obj == GetApp())
            {

                return MouseEvent(obj,event);
            }
        }
       break;
    }
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        if("CCButton" ==  (QString)(obj->metaObject()->className()))
        {
            if(NULL == GetApp() || obj == GetApp())
            {
               // return TouchEvent(obj, event);
            }
        }
        break;
    }
    case QEvent::Gesture:
    {
        return false;
        if(GetIsEditStatus() && GetApp())
        {
            break;
        }
        else
        {
            return GestureEvent(obj,event);
        }
    }
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj,event);
}

QPoint HomeView::getPosition()
{

}

void HomeView::setPosition(QPoint position)
{
    this->move(position);
    if(GetApp())
    {
        GetApp()->update();
    }
    update();
}

void HomeView::PressTimeout()
{
    GoToEditStatus();
    if(GetApp())
    {
        GetApp()->UpdateText("",true);
//        GetApp()->SizeAnimation(QSize(APP_BT_W, APP_BT_H), QSize(APP_BT_W+10, APP_BT_H+10),300,false);
//        GetApp()->OpacityAnimation(1,0.5,500);
    }
}

void HomeView::FlipTimeout()
{
    switch (m_flip) {
    case eAFlipModeToNext:
    {
        if(m_iCurrentPageNum < m_iPageTotalNum)
        {
            if(GetApp()&&GetIsEditStatus())
            {
                int curPage = m_iCurrentPageNum;
                int curindex = 8 * curPage;
                if(curindex > m_ListBtn.size())
                {
                    curindex = m_ListBtn.size();
                }
                if(curindex <= m_ListBtn.size())
                {
                    if((curindex-1) != GetApp()->GetIndex())
                    {
                        m_iFlipStep = 1;
                        SortByIndexNoMove(GetApp()->GetIndex(),curindex-1);
                    }
                    else
                    {
                        m_iFlipAppIndex = -1;
                        m_iFlipStep = 2;
                        this->ToNextPage();
                    }
                }
            }
        }
    }
        break;
    case eAFlipModeTopre:
    {
       m_iFlipStep = 0;
       this->ToPrePage();
    }
        break;
    default:
    {
        m_iFlipStep = 0;
    }
        break;
    }
}

void HomeView::OnSortByIndex(int PressIndex, int SelectIndex)
{
    SortByIndex(PressIndex,SelectIndex);
}

void HomeView::OnMoving()
{
    m_movingTimer.stop();
    if(GetApp() &&GetIsEditStatus()&& m_iMovingIndex >=0)
    {
       // if(!HQuickPart::getInstance().inQuickScale(m_stayPos))
        {
            SortByIndexNoMove(GetApp()->GetIndex(),m_iMovingIndex);
        }
    }
}

void HomeView::OnMoveParentFinish(int index)
{
    m_bIsPageMoving = false;
    if(m_iFlipStep != 2)
    {
        return;
    }
    else
    {
       m_iFlipStep  = 0;
       if(GetApp()&&GetIsEditStatus())
       {
           int indexbyPage = m_iCurrentPageNum * 8;
           if(m_iCurrentPageNum <= m_iPageTotalNum )
           {
              if(indexbyPage > m_ListBtn.size())
              {
                  indexbyPage = m_ListBtn.size();
              }
               if(indexbyPage <= m_ListBtn.size())
              {
                  SortByIndexNoMove(GetApp()->GetIndex(),indexbyPage-1);
              }
           }
       }
    }
    Q_UNUSED(index);
}

void HomeView::OnMoveAppFinish(int index)
{
    if(1 != m_iFlipStep)
    {
        return ;
    }
    else
    {
       if(index >=0 && m_iFlipAppIndex >=0)
       {
               m_iFlipAppIndex = -1;
               m_iFlipStep = 2;
               this->ToNextPage();
       }
    }
}

void HomeView::OnQuickMove(QString type)
{
    if("PULL" == type)
    {
        this->MoveAnimation(QPoint(this->geometry().x(),0),QPoint((-(m_iCurrentPageNum-1)*m_pageSize.width()),0),300);

    }else if("BACK" == type)
    {
        this->MoveAnimation(QPoint(this->geometry().x(),0),QPoint((-(m_iCurrentPageNum-1)*m_pageSize.width())-80,0),300);
    }
}

void HomeView::OnEnterTriggerDomainStatus(bool status,QString type)
{
    map<string,string> p ;
    p.insert(make_pair("QuickTriggerDomainStatus",status?"True":"False"));
    p.insert(make_pair("Type",type.toStdString()));
    HMIFrameWork::Inst()->Notify(QUICKLANUCH_ID,p);
}

void HomeView::OnAppClick(int index, QString type, QString name)
{
    INFO()<<" index = " << index << " type = " << type << " name = " << name;
    map<string,string> p ;
    p.insert(make_pair("AppClick",type.toStdString()));
    HMIFrameWork::Inst()->Notify(HOME_ID,p);
}




