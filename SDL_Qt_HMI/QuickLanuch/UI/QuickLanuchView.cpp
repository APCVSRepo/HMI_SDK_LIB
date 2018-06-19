#include "QuickLanuchView.h"
#include <QStylePainter>
#include <QStyleOption>
#include "QuickLanuch/app/QuickLanuch.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "QuickLanuchWindow.h"
QuickLanuchView::QuickLanuchView(QWidget *parent)
    :QWidget(parent)
    ,CView(QuickLanuch::eViewId_Main)
    ,m_pMoveAnimation(NULL)
    ,m_pAppBtn(NULL)
    ,m_pPullBackBtn(NULL)
    ,m_pPullBackAnimation(NULL)
    ,m_pVoiceBtn(NULL)
    ,m_bEditStatus(false)
{
    this->setGeometry(0,0,160,440);
    this->resize(160,440);
    this->setStyleSheet("QWidget{background:transparent;}");
    this->raise();
    this->show();

    installEventFilter(this);
    setAttribute(Qt::WA_AcceptTouchEvents);

    m_pMoveAnimation = new QPropertyAnimation(this);
    m_pMoveAnimation->setTargetObject(this);
    m_pMoveAnimation->setPropertyName("position");

    m_pPullBackAnimation = new QPropertyAnimation(this);
    m_pPullBackAnimation->setTargetObject(this);
    m_pPullBackAnimation->setPropertyName("position");

    InitQuickLanuchData();
    InitQuickLanuchView();

    connect(QuickLanuch::Inst(),SIGNAL(SigAppInfo(int,int,string)),this,SLOT(OnReplaceInfo(int,int,string)),Qt::UniqueConnection);
    connect(this,SIGNAL(SigRelease(int,QString,QString)),this,SLOT(OnAppClick(int,QString,QString)),Qt::UniqueConnection);
    connect(QuickLanuch::Inst(),SIGNAL(SigEnterQuick(QString,QString)),this,SLOT(OnEnterQuickStatus(QString,QString)),Qt::UniqueConnection);

    m_pressTimer.setInterval(1000);
    m_pressTimer.setSingleShot(true);
    connect(&m_pressTimer,SIGNAL(timeout()),this,SLOT(OnEnterEditStatus()));

    this->show();
    this->raise();
    this->SetViewGeometry(QRect(0,0,160,440));


}

QuickLanuchView::~QuickLanuchView()
{

}

void QuickLanuchView::viewAction(int state)
{

}

bool QuickLanuchView::MouseEvent(QObject *obj, QEvent *event)
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
        globalPos2 = GetApp()->GetGlobalPos(QPoint(mouseEvent->pos().x(),mouseEvent->pos().y()));
        globalPos.setX(GetApp()->geometry().x()+mouseEvent->pos().x());
        globalPos.setY(GetApp()->geometry().y()+mouseEvent->pos().y());
    }

    switch (event->type()) {
    case QEvent::MouseButtonPress:
    {
        INFO("quicklaunch press.");
        m_iPosX = globalPos.x();
        m_iPosY = globalPos.y();
        if(GetEditStatus())
        {
            if(GetApp())
            {
               m_iPosDiffX = m_iPosX-GetApp()->geometry().x();
               m_iPosDiffY = m_iPosY-GetApp()->geometry().y();
               GetApp()->raise();
               GetApp()->show();
               GetApp()->SetIsPress(true);
               GetApp()->UpdateText("",true);
               GetApp()->SetViewStatus(CCButton::ViewStatusPushed);

            }
        }else
        {
            if(GetApp())
            {
               m_iPosDiffX = m_iPosX-GetApp()->geometry().x();
               m_iPosDiffY = m_iPosY-GetApp()->geometry().y();
               GetApp()->raise();
               GetApp()->show();
               GetApp()->UpdateText("",true);
               GetApp()->SetViewStatus(CCButton::ViewStatusPushed);
               GetApp()->SetIsPress(true);
               if("Voice" != GetApp()->GetInfo().Type && "PullBack" != GetApp()->GetInfo().Type)
               {
                    m_pressTimer.start();
               }
            }
        }


    }
        break;
    case QEvent::MouseMove:
    {
        if(GetEditStatus())
        {
            if(GetApp())
            {
                GetApp()->move(globalPos.x()-m_iPosDiffX,globalPos.y()-m_iPosDiffY);
                m_stayPos.setX((globalPos2.x())%this->geometry().width());
                m_stayPos.setY(globalPos2.y());
                CCButton* btn = Index(globalPos.x(),globalPos.y());
                if(btn)
                {
                    SortByIndex(GetApp()->GetIndex(),btn->GetIndex());
                }
            }
        }
    }
        break;
    case QEvent::MouseButtonRelease:
    {
        m_pressTimer.stop();
        if(GetApp())
        {
            GetApp()->SetViewStatus(CCButton::ViewStatusNormal);
        }
        if(GetEditStatus()){

        }
        else {
            if(GetApp())
            {
               if("PullBack" == GetApp()->GetInfo().Type)
               {
                   if(this->parent())
                   {
                       QuickLanuchWindow *Parent = dynamic_cast<QuickLanuchWindow*>(this->parent());
                       connect(Parent,SIGNAL(PullBackFinish()),this,SLOT(OnPullBackFinish()),Qt::UniqueConnection);
                       if(Parent->geometry().x() == 0)
                       {
                            emit SigPllBack("BACK");
                            GetApp()->InsertNormalStyle(":/QuickLanuch/Source/images/popup_normal.png");
                            GetApp()->InsertPushStyle(":/QuickLanuch/Source/images/popup_push.png");
                            QRect r(Parent->geometry());
                            Parent->PullBackAnimation(QPoint(r.x(),r.y()),QPoint(GetApp()->width()-r.width()+1,r.y()),300);

                       }else if(Parent->geometry().x() + Parent->geometry().width() - GetApp()->width() -1 == 0)
                       {
                            emit SigPllBack("PULL");
                            Parent->setGeometry(QRect(Parent->geometry().x(),40,161,440));
                            m_pPullBackBtn->SetAppGeometry(QRect(121,173,39,66));
                            GetApp()->InsertNormalStyle(":/QuickLanuch/Source/images/anastole_normal.png");
                            GetApp()->InsertPushStyle(":/QuickLanuch/Source/images/anastole_push.png");
                            QRect r(Parent->geometry());
                            Parent->PullBackAnimation(QPoint(r.x(),r.y()),QPoint(0,r.y()),300);
                       }
                    }
               }
               else if("Voice" == GetApp()->GetInfo().Type){
                   emit SigVoiceClick();
               }
               else{
                   emit SigRelease(GetApp()->GetIndex(),GetApp()->GetType(),GetApp()->GetName());
                   GetApp()->UpdateText(GetApp()->GetText());
                   GetApp()->SetIsPress(false);
               }
            }
        }
        if(GetEditStatus())
        {
            ExitEditStatus();
        }
        SetApp(NULL);
    }
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj,event);
}

bool QuickLanuchView::eventFilter(QObject *obj, QEvent *event)
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
            }
        }
        break;
    }
    default:
        break;
    }
    return QWidget::eventFilter(obj,event);
}

void QuickLanuchView::paintEvent(QPaintEvent *event)
{

    QStylePainter painter(this);
    QStyleOption opt;
    opt.initFrom(this);
    opt.rect=rect();
    painter.drawPrimitive(QStyle::PE_Widget, opt);

    QWidget::paintEvent(event);
}

void QuickLanuchView::InitQuickLanuchView()
{
    QList<AppInfo>  listApps;

    {
        AppInfo appInfo1;
        appInfo1.AppBgPathNormal = ":/QuickLanuch/Source/images/phone_left.png";
        appInfo1.AppBgPathPush = ":/QuickLanuch/Source/images/phone_left_push.png";
        appInfo1.AppEditPath = "";
        appInfo1.AppIconPath = ":/QuickLanuch/Source/images/phone_left_hover.png";
        appInfo1.AppName =QObject::tr(PHONE_NAME);
        appInfo1.AppType = PHONE_ID;
        listApps.append(appInfo1);
    }
    {
        AppInfo appInfo2;
        appInfo2.AppBgPathNormal = ":/QuickLanuch/Source/images/Media_left.png";
        appInfo2.AppBgPathPush = ":/QuickLanuch/Source/images/media_left_push.png";
        appInfo2.AppEditPath = "";
        appInfo2.AppIconPath = ":/QuickLanuch/Source/images/media_left_hover.png";
        appInfo2.AppName =QObject::tr(MEDIA_NAME);
        appInfo2.AppType =MEDIA_ID;
        listApps.append(appInfo2);
    }
    {
        AppInfo appInfo3;
        appInfo3.AppBgPathNormal = ":/QuickLanuch/Source/images/nav_left.png";
        appInfo3.AppBgPathPush = ":/QuickLanuch/Source/images/nav_left_push.png";
        appInfo3.AppEditPath = "";
        appInfo3.AppIconPath = ":/QuickLanuch/Source/images/nav_left_hover";
        appInfo3.AppName =QObject::tr(NAV_NAME);
        appInfo3.AppType =NAV_ID;
        listApps.append(appInfo3);
    }
    for(int i = 0;i<listApps.size();++i)
    {
        CCButton * app = new CCButton(this);
        app->SetViewStatusStyle(CCButton::ViewStatusStyle_Change);
        app->SetTextSize(14);
        app->SetAppGeometry(QRect(QUICK_OFFSET_POS_X,i*(QUICK_APP_BT_H+QUICK_ROW_SPACE)+QUICK_OFFSET_POS_Y,QUICK_APP_BT_W,QUICK_APP_BT_H));
        app->InsertEditStyle(QRect(35,1,16,16),listApps.at(i).AppEditPath);
        app->InsertNormalStyle(QRect(38,10,QUICK_APP_ICON_W,QUICK_APP_ICON_H),listApps.at(i).AppBgPathNormal);
        app->InsertPushStyle(QRect(28,0,QUICK_APP_BT_PUSH_W,QUICK_APP_BT_PUSH_W),listApps.at(i).AppBgPathPush);
        app->InsertIconStyle(QRect(38,10,QUICK_APP_ICON_W,QUICK_APP_ICON_H),listApps.at(i).AppIconPath);
        app->InsertText(QRect(0,QUICK_APP_ICON_H+1,QUICK_APP_BT_W,16),listApps.at(i).AppName,true);
        app->InsertType(listApps.at(i).AppType);
        app->InsertName(listApps.at(i).AppName);
        app->SetIndex(i);
        this->InsertQucikLanuch(i,app);

        CCButton *appSplite = new CCButton(this);
        appSplite->SetAppGeometry(QRect(QUICK_OFFSET_POS_X,i*(QUICK_APP_BT_H+QUICK_ROW_SPACE)+QUICK_OFFSET_POS_Y+QUICK_APP_BT_H,QUICK_APP_BT_W,14));

        appSplite->SetViewStatusStyle(CCButton::ViewStatusStyle_Change);
        appSplite->InsertNormalStyle(QRect(38,0,44,14),":/QuickLanuch/Source/images/line_left.png");
        appSplite->InsertPushStyle(QRect(38,0,44,14),":/QuickLanuch/Source/images/line_left.png");
        appSplite->SetIndex(i+listApps.size());
        appSplite->raise();
        appSplite->show();


        INFO("apps index = %d",i);
    }
    CCButton* pullBackBtn = new CCButton(this);
    pullBackBtn->SetViewStatusStyle(CCButton::ViewStatusStyle_Change);
    pullBackBtn->SetAppGeometry(QRect(121,0,39,66));
    pullBackBtn->InsertNormalStyle(QRect(0,0,39,66),":/QuickLanuch/Source/images/popup_normal.png");
    pullBackBtn->InsertPushStyle(QRect(0,0,39,66),":/QuickLanuch/Source/images/popup_push.png");
    pullBackBtn->InsertType("PullBack");
    pullBackBtn->show();

    CreatePullBack(pullBackBtn);
    CCButton* voiceBtn = new CCButton(this);
    voiceBtn->SetViewStatusStyle(CCButton::ViewStatusStyle_Change);
    voiceBtn->SetAppGeometry(QRect(58,387,44,44));
    voiceBtn->InsertNormalStyle(QRect(0,0,44,44),":/QuickLanuch/Source/images/volume_normal.png");
    voiceBtn->InsertPushStyle(QRect(0,0,44,44),":/QuickLanuch/Source/images/volume_push.png");
    voiceBtn->InsertType("Voice");
    voiceBtn->raise();
    voiceBtn->show();
    CreateVoice(voiceBtn);

    connect(this,SIGNAL(SigPllBack(QString)),this,SLOT(OnPllBack(QString)),Qt::UniqueConnection);

}

void QuickLanuchView::InitQuickLanuchData()
{
    {
        AppInfo appInfo1;
        appInfo1.AppBgPathNormal = ":/QuickLanuch/Source/images/phone_left.png";
        appInfo1.AppBgPathPush = ":/QuickLanuch/Source/images/phone_left_push.png";
        appInfo1.AppEditPath = "";
        appInfo1.AppIconPath = ":/QuickLanuch/Source/images/phone_left_hover.png";
        appInfo1.AppName =QObject::tr(PHONE_NAME);
        appInfo1.AppType = PHONE_ID;
        m_ListData.append(appInfo1);
    }
    {
        AppInfo appInfo2;
        appInfo2.AppBgPathNormal = ":/QuickLanuch/Source/images/Media_left.png";
        appInfo2.AppBgPathPush = ":/QuickLanuch/Source/images/media_left_push.png";
        appInfo2.AppEditPath = "";
        appInfo2.AppIconPath = ":/QuickLanuch/Source/images/media_left_hover.png";
        appInfo2.AppName =QObject::tr(MEDIA_NAME);
        appInfo2.AppType =MEDIA_ID;
        m_ListData.append(appInfo2);
    }
    {
        AppInfo appInfo3;
        appInfo3.AppBgPathNormal = ":/QuickLanuch/Source/images/nav_left.png";
        appInfo3.AppBgPathPush = ":/QuickLanuch/Source/images/nav_left_push.png";
        appInfo3.AppEditPath = "";
        appInfo3.AppIconPath = ":/QuickLanuch/Source/images/nav_left_hover.png";
        appInfo3.AppName =QObject::tr(NAV_NAME);
        appInfo3.AppType =NAV_ID;
        m_ListData.append(appInfo3);
    }
    {
        AppInfo appInfo4;
        appInfo4.AppBgPathNormal = ":/QuickLanuch/Source/images/Application_left.png";
        appInfo4.AppBgPathPush = ":/QuickLanuch/Source/images/Application_left_push.png";
        appInfo4.AppEditPath = "";
        appInfo4.AppIconPath = ":/QuickLanuch/Source/images/Application_left_hover.png";
        appInfo4.AppName =QObject::tr(SDLAPPS_NAME);
        appInfo4.AppType =SDLAPPS_ID;
        m_ListData.append(appInfo4);
    }
    {
        AppInfo appInfo5;
        appInfo5.AppBgPathNormal = ":/QuickLanuch/Source/images/setting_left.png";
        appInfo5.AppBgPathPush = ":/QuickLanuch/Source/images/setting_left_push.png";
        appInfo5.AppEditPath = "";
        appInfo5.AppIconPath = ":/QuickLanuch/Source/images/setting_left_hover.png";
        appInfo5.AppName =QObject::tr(SETTINGS_NAME);
        appInfo5.AppType =SETTINGS_ID;
        m_ListData.append(appInfo5);
    }
    {
        AppInfo appInfo6;
        appInfo6.AppBgPathNormal = ":/QuickLanuch/Source/images/HVAC_left.png";
        appInfo6.AppBgPathPush = ":/QuickLanuch/Source/images/HVAC_left_push.png";
        appInfo6.AppEditPath = "";
        appInfo6.AppIconPath = ":/QuickLanuch/Source/images/HVAC_left_hover.png";
        appInfo6.AppName =QObject::tr(HVAC_NAME);
        appInfo6.AppType =HVAC_ID;
        m_ListData.append(appInfo6);
    }
    {
        AppInfo appInfo7;
        appInfo7.AppBgPathNormal = ":/QuickLanuch/Source/images/Message_left.png";
        appInfo7.AppBgPathPush = ":/QuickLanuch/Source/images/Message_left_push.png";
        appInfo7.AppEditPath = "";
        appInfo7.AppIconPath = ":/QuickLanuch/Source/images/Message_left_hover.png";
        appInfo7.AppName =QObject::tr(MESSAGE_NAME);
        appInfo7.AppType =MESSAGE_ID;
        m_ListData.append(appInfo7);
    }

    {
        AppInfo appInfo8;
        appInfo8.AppBgPathNormal = ":/QuickLanuch/Source/images/Weather_left.png";
        appInfo8.AppBgPathPush = ":/QuickLanuch/Source/images/Weather_left_push.png";
        appInfo8.AppEditPath = "";
        appInfo8.AppIconPath = ":/QuickLanuch/Source/images/Weather_left_hover.png";
        appInfo8.AppName =QObject::tr(WEATHER_NAME);
        appInfo8.AppType =WEATHER_ID;
        m_ListData.append(appInfo8);
    }
}

void QuickLanuchView::SetViewGeometry(QRect rect)
{
    m_viewRect = rect;
    this->setGeometry(rect);
}

void QuickLanuchView::InsertQucikLanuch(int index, CCButton *app)
{
    if(app)
    {
        app->installEventFilter(this);
        m_ListBtn.insert(index,app);
        m_MapRect.insert(index,app->GetViewRect());
    }
}

void QuickLanuchView::ReplaceQucikLanuch(int x,int y, QString type)
{
    if(!containsType(type))
    {
        int index = findAppInfo(type);
        if(index != -1)
        {
            CCButton* app_ = Index(x,y);
            if(app_)
            {
                app_->UpdateType(m_ListData.at(index).AppType);
                app_->UpdateIconStyle(m_ListData.at(index).AppIconPath);
                app_->UpdateName(m_ListData.at(index).AppName);
                app_->UpdateBgStyle(m_ListData.at(index).AppBgPathPush);
                app_->UpdateEditStyle(m_ListData.at(index).AppEditPath);
                app_->UpdateNormalStyle(m_ListData.at(index).AppBgPathNormal);
                app_->UpdatePushStyle(m_ListData.at(index).AppBgPathPush);
                app_->UpdateText(m_ListData.at(index).AppName);
            }
        }
    }
}

bool QuickLanuchView::containsType(QString type)
{
    QList<CCButton*>::iterator it = m_ListBtn.begin();
    for(;it != m_ListBtn.end();++it)
    {
        if((*it)->GetInfo().Type.compare(type) == 0)
        {
            return true;
        }
    }
    return false;
}

void QuickLanuchView::EnterEditStatus()
{
    m_bEditStatus = true;
    if(m_ListBtn.size())
    {
       QList<CCButton*>::iterator it = m_ListBtn.begin();
       for(;it != m_ListBtn.end();++it)
       {
           (*it)->SetEditStatus(true);
           (*it)->UpdateText("",true);
           (*it)->JitterAnimation(500);
       }
    }
}

void QuickLanuchView::ExitEditStatus()
{
    m_bEditStatus = false;
    if(m_ListBtn.size())
    {
       QList<CCButton*>::iterator it = m_ListBtn.begin();
       for(;it != m_ListBtn.end();++it)
       {
           (*it)->SetEditStatus(false);
           if(GetApp())
           {
               if(GetApp()->GetType() != (*it)->GetType())
               {
                  (*it)->UpdateText((*it)->GetText(),true);
               }
           }
           else
           {
                (*it)->UpdateText((*it)->GetText(),true);
           }
       }
    }
    if(GetApp())
    {
        GetApp()->MoveAnimation(QPoint(GetApp()->geometry().x(),GetApp()->geometry().y()),QPoint(GetApp()->GetViewRect().x(),GetApp()->GetViewRect().y()),500);
    }
}

bool QuickLanuchView::GetEditStatus()
{
    return m_bEditStatus;
}

void QuickLanuchView::CreatePullBack(CCButton *btn)
{
    if(btn)
    {
        m_pPullBackBtn = btn;
        m_pPullBackBtn->InsertType( "PullBack");
        btn->installEventFilter(this);
    }
}

void QuickLanuchView::CreateVoice(CCButton *btn)
{
    if(btn)
    {
        m_pVoiceBtn = btn;
        m_pVoiceBtn->InsertType( "Voice");
        btn->installEventFilter(this);
    }
}

void QuickLanuchView::SortByIndex(int PressIndex, int SelectIndex)
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
                    //m_iFlipAppIndex = (*it)->GetIndex();
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
                    //m_iFlipAppIndex = (*it)->GetIndex();
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



CCButton* QuickLanuchView::Index(int x, int y)
{
    y -= 40;
    if(m_viewRect.contains(x,y))
    {
        QList<CCButton*>::iterator it = m_ListBtn.begin();
        for(;it != m_ListBtn.end();++it)
        {
            QRect rect((*it)->GetViewRect().x(),(*it)->GetViewRect().y(),\
                       (*it)->GetViewRect().width(),(*it)->GetViewRect().height());
            if(rect.contains(x,y))
            {
                return (*it);
            }
        }
    }
    return NULL;
}

int QuickLanuchView::findAppInfo(QString type)
{
    for(int i = 0 ;i < m_ListData.size();i++)
    {
        if(m_ListData.at(i).AppType == type)
        {
            return i;
        }
    }

    return -1;
}

CCButton *QuickLanuchView::GetApp()
{
    return m_pAppBtn;
}

void QuickLanuchView::SetApp(CCButton *app)
{
    m_pAppBtn = app;
}

QPoint QuickLanuchView::getPosition()
{

}

void QuickLanuchView::setPosition(QPoint position)
{
    this->move(position);
    if(GetApp())
    {
        GetApp()->update();
    }
    update() ;
}

void QuickLanuchView::MoveAnimation(const QPoint startPos, const QPoint endPos, int time)
{
    if(m_pMoveAnimation)
    {

        m_pMoveAnimation->setDuration(time);
        m_pMoveAnimation->setStartValue(startPos);
        m_pMoveAnimation->setEndValue(endPos);
        m_pMoveAnimation->start();
    }
}

void QuickLanuchView::PullBackAnimation(const QPoint startPos, const QPoint endPos, int time)
{
    if(m_pPullBackAnimation)
    {

        m_pPullBackAnimation->setDuration(time);
        m_pPullBackAnimation->setStartValue(startPos);
        m_pPullBackAnimation->setEndValue(endPos);
        m_pPullBackAnimation->start();
    }
}

void QuickLanuchView::OnReplaceInfo(int x ,int y ,string type)
{
    ReplaceQucikLanuch(x,y,QString::fromStdString( type));
}

void QuickLanuchView::OnAppClick(int index, QString type, QString name)
{
    map<string,string> p ;
    p.insert(make_pair("AppClick",type.toStdString()));
    HMIFrameWork::Inst()->Notify(HOME_ID,p);
}

void QuickLanuchView::OnPllBack(QString type)
{
    map<string,string> p ;
    p.insert(make_pair("QuickMove",type.toStdString()));
    HMIFrameWork::Inst()->Notify(HOME_ID,p);
}

void QuickLanuchView::OnEnterQuickStatus(QString status,QString type)
{
    if("True" == status)
    {
        if(containsType(type))
        {
            QList<CCButton*>::iterator it = m_ListBtn.begin();

            for(;it != m_ListBtn.end();++it)
            {
                if((*it)->GetInfo().Type.compare(type) == 0)
                {
                    (*it)->SetExist(true);
                }
            }
        }
    }else if("False" == status)
    {
        QList<CCButton*>::iterator it = m_ListBtn.begin();

        for(;it != m_ListBtn.end();++it)
        {

            (*it)->SetExist(false);
        }
    }
}

void QuickLanuchView::OnEnterEditStatus()
{
    EnterEditStatus();
}

void QuickLanuchView::OnPullBackFinish()
{
    if(this->parent())
    {
        QuickLanuchWindow *Parent = dynamic_cast<QuickLanuchWindow*>(this->parent());
        if(Parent->geometry().x()<0)
        {
            Parent->setGeometry(QRect(Parent->geometry().x(),213,161,66));
            m_pPullBackBtn->SetAppGeometry(QRect(121,0,39,66));
        }
    }
}
