#include "QuickLanuchView.h"
#include <QStylePainter>
#include <QStyleOption>
#include "QuickLanuch/app/QuickLanuch.h"
#include "HMIFrameWork/HMIFrameWork.h"
QuickLanuchView::QuickLanuchView(QWidget *parent)
    :QWidget(parent)
    ,CView(QuickLanuch::eViewId_Main)
    ,m_pMoveAnimation(NULL)
    ,m_pAppBtn(NULL)
    ,m_pPullBackBtn(NULL)
    ,m_pPullBackAnimation(NULL)
    ,m_pVoiceBtn(NULL)
{
    this->resize(170,480);
    this->setStyleSheet("QWidget{background-color:black;background:red;}");

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
    this->show();

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

            if(GetApp())
            {
               emit SigPress(GetApp()->GetIndex(),GetApp()->GetType(),GetApp()->GetName());
               GetApp()->SetViewStatus(CCButton::ViewStatusPushed);
               GetApp()->SetIsPress(true);
            }

    }
        break;
    case QEvent::MouseMove:
    {

    }
        break;
    case QEvent::MouseButtonRelease:
    {
        if(GetApp())
        {
           if("PullBack" == GetApp()->GetInfo().Type)
           {
               if(this->geometry().x() == 0)
               {
                    QRect r(this->geometry());
                    PullBackAnimation(QPoint(r.x(),r.y()),QPoint(GetApp()->width()-r.width(),r.y()),300);
               }else if(this->geometry().x() + this->geometry().width() - GetApp()->width() == 0)
               {
                    QRect r(this->geometry());
                    PullBackAnimation(QPoint(r.x(),r.y()),QPoint(0,r.y()),300);
               }
           }
           else if("Voice" == GetApp()->GetInfo().Type){
               emit SigVoiceClick();
           }
           else{
               emit SigRelease(GetApp()->GetIndex(),GetApp()->GetType(),GetApp()->GetName());
               GetApp()->SetViewStatus(CCButton::ViewStatusNormal);
               GetApp()->SetIsPress(false);
           }
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
        appInfo1.AppBgPathNormal = ":/QuickLanuch/Source/images/Home_ButtonAppMedia.png";
        appInfo1.AppBgPathPush = ":/QuickLanuch/Source/images/Home_ButtonAppMedia.png";
        appInfo1.AppEditPath = ":/QuickLanuch/Source/images/Home_ButtonAppMedia.png";
        appInfo1.AppIconPath = ":/QuickLanuch/Source/images/Home_ButtonAppMedia.png";
        appInfo1.AppName =QObject::tr(MEDIA_NAME);
        appInfo1.AppType = MEDIA_ID;
        listApps.append(appInfo1);
    }
    {
        AppInfo appInfo2;
        appInfo2.AppBgPathNormal = ":/QuickLanuch/Source/images/Home_ButtonAppNavi.png";
        appInfo2.AppBgPathPush = ":/QuickLanuch/Source/images/Home_ButtonAppNavi.png";
        appInfo2.AppEditPath = ":/QuickLanuch/Source/images/Home_ButtonAppNavi.png";
        appInfo2.AppIconPath = ":/QuickLanuch/Source/images/Home_ButtonAppNavi.png";
        appInfo2.AppName =QObject::tr(NAV_NAME);
        appInfo2.AppType =NAV_ID;
        listApps.append(appInfo2);
    }
    {
        AppInfo appInfo3;
        appInfo3.AppBgPathNormal = ":/QuickLanuch/Source/images/Home_ButtonAppPhone.png";
        appInfo3.AppBgPathPush = ":/QuickLanuch/Source/images/Home_ButtonAppPhone.png";
        appInfo3.AppEditPath = ":/QuickLanuch/Source/images/Home_ButtonAppPhone.png";
        appInfo3.AppIconPath = ":/QuickLanuch/Source/images/Home_ButtonAppPhone.png";
        appInfo3.AppName =QObject::tr(PHONE_NAME);
        appInfo3.AppType =PHONE_ID;
        listApps.append(appInfo3);
    }
    for(int i = 0;i<listApps.size();++i)
    {
        CCButton * app = new CCButton(this);
        app->SetAppGeometry(QRect(5,i*(142+10),142,142));
        app->InsertEditStyle(QRect(0,0,142,142),listApps.at(i).AppEditPath);
        app->InsertNormalStyle(QRect(12,14,117,114),listApps.at(i).AppBgPathNormal);
        app->InsertPushStyle(QRect(12,14,117,114),listApps.at(i).AppBgPathPush);
        app->InsertIconStyle(QRect(12,14,117,114),listApps.at(i).AppIconPath);
        app->InsertText(QRect(0,113,142,20),listApps.at(i).AppName,true);
        app->InsertType(listApps.at(i).AppType);
        app->InsertName(listApps.at(i).AppName);
        app->SetIndex(i);
        this->InsertQucikLanuch(i,app);

        INFO("apps index = %d",i);
    }

    this->SetViewGeometry(QRect(0,0,160,480));
    this->raise();
    this->show();

}

void QuickLanuchView::InitQuickLanuchData()
{
    {
        AppInfo appInfo1;
        appInfo1.AppBgPathNormal = ":/QuickLanuch/Source/images/Home_ButtonAppMedia.png";
        appInfo1.AppBgPathPush = ":/QuickLanuch/Source/images/Home_ButtonAppMedia.png";
        appInfo1.AppEditPath = ":/QuickLanuch/Source/images/Home_ButtonAppMedia.png";
        appInfo1.AppIconPath = ":/QuickLanuch/Source/images/Home_ButtonAppMedia.png";
        appInfo1.AppName =QObject::tr(MEDIA_NAME);
        appInfo1.AppType = MEDIA_ID;
        m_ListData.append(appInfo1);
    }
    {
        AppInfo appInfo2;
        appInfo2.AppBgPathNormal = ":/QuickLanuch/Source/images/Home_ButtonAppNavi.png";
        appInfo2.AppBgPathPush = ":/QuickLanuch/Source/images/Home_ButtonAppNavi.png";
        appInfo2.AppEditPath = ":/QuickLanuch/Source/images/Home_ButtonAppNavi.png";
        appInfo2.AppIconPath = ":/QuickLanuch/Source/images/Home_ButtonAppNavi.png";
        appInfo2.AppName =QObject::tr(NAV_NAME);
        appInfo2.AppType =NAV_ID;
        m_ListData.append(appInfo2);
    }
    {
        AppInfo appInfo3;
        appInfo3.AppBgPathNormal = ":/QuickLanuch/Source/images/Home_ButtonAppPhone.png";
        appInfo3.AppBgPathPush = ":/QuickLanuch/Source/images/Home_ButtonAppPhone.png";
        appInfo3.AppEditPath = ":/QuickLanuch/Source/images/Home_ButtonAppPhone.png";
        appInfo3.AppIconPath = ":/QuickLanuch/Source/images/Home_ButtonAppPhone.png";
        appInfo3.AppName =QObject::tr(PHONE_NAME);
        appInfo3.AppType =PHONE_ID;
        m_ListData.append(appInfo3);
    }
    {
        AppInfo appInfo4;
        appInfo4.AppBgPathNormal = ":/QuickLanuch/Source/images/Home_ButtonAppGallery.png";
        appInfo4.AppBgPathPush = ":/QuickLanuch/Source/images/Home_ButtonAppGallery.png";
        appInfo4.AppEditPath = ":/QuickLanuch/Source/images/Home_ButtonAppGallery.png";
        appInfo4.AppIconPath = ":/QuickLanuch/Source/images/Home_ButtonAppGallery.png";
        appInfo4.AppName =QObject::tr(SDLAPPS_NAME);
        appInfo4.AppType =SDLAPPS_ID;
        m_ListData.append(appInfo4);
    }
    {
        AppInfo appInfo5;
        appInfo5.AppBgPathNormal = ":/QuickLanuch/Source/images/Home_ButtonAppSettings.png";
        appInfo5.AppBgPathPush = ":/QuickLanuch/Source/images/Home_ButtonAppSettings.png";
        appInfo5.AppEditPath = ":/QuickLanuch/Source/images/Home_ButtonAppSettings.png";
        appInfo5.AppIconPath = ":/QuickLanuch/Source/images/Home_ButtonAppSettings.png";
        appInfo5.AppName =QObject::tr(SETTINGS_NAME);
        appInfo5.AppType =SETTINGS_ID;
        m_ListData.append(appInfo5);
    }
    {
        AppInfo appInfo6;
        appInfo6.AppBgPathNormal = ":/QuickLanuch/Source/images/Home_ButtonAppClimate.png";
        appInfo6.AppBgPathPush = ":/QuickLanuch/Source/images/Home_ButtonAppClimate.png";
        appInfo6.AppEditPath = ":/QuickLanuch/Source/images/Home_ButtonAppClimate.png";
        appInfo6.AppIconPath = ":/QuickLanuch/Source/images/Home_ButtonAppClimate.png";
        appInfo6.AppName =QObject::tr(HVAC_NAME);
        appInfo6.AppType =HVAC_ID;
        m_ListData.append(appInfo6);
    }
    {
        AppInfo appInfo7;
        appInfo7.AppBgPathNormal = ":/QuickLanuch/Source/images/Home_ButtonAppText.png";
        appInfo7.AppBgPathPush = ":/QuickLanuch/Source/images/Home_ButtonAppText.png";
        appInfo7.AppEditPath = ":/QuickLanuch/Source/images/Home_ButtonAppText.png";
        appInfo7.AppIconPath = ":/QuickLanuch/Source/images/Home_ButtonAppText.png";
        appInfo7.AppName =QObject::tr(MESSAGE_NAME);
        appInfo7.AppType =MESSAGE_ID;
        m_ListData.append(appInfo7);
    }

    {
        AppInfo appInfo8;
        appInfo8.AppBgPathNormal = ":/QuickLanuch/Source/images/Home_Weather.png";
        appInfo8.AppBgPathPush = ":/QuickLanuch/Source/images/Home_Weather.png";
        appInfo8.AppEditPath = ":/QuickLanuch/Source/images/Home_Weather.png";
        appInfo8.AppIconPath = ":/QuickLanuch/Source/images/Home_Weather.png";
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

void QuickLanuchView::CreatePullBackBtn(CCButton *btn)
{
    if(btn)
    {
        m_pPullBackBtn = btn;
        m_pPullBackBtn->InsertType( "PullBack");
        btn->installEventFilter(this);
    }
}

void QuickLanuchView::CreatePullVoiceBtn(CCButton *btn)
{
    if(btn)
    {
        m_pVoiceBtn = btn;
        m_pVoiceBtn->InsertType( "Voice");
        btn->installEventFilter(this);
    }
}



CCButton* QuickLanuchView::Index(int x, int y)
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
