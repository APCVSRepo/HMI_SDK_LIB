#include "CCButton.h"
#include "Home/UI/HomeView.h"
CCButton::CCButton(QWidget *parent)
  : QWidget(parent)
  , m_pOpacityAnimation(NULL)
  , m_pEffect(NULL)
  , m_pMoveAnimation(NULL)
  , m_pSizeAnimation(NULL)
  , m_viewRect(QRect(0,0,0,0))
  , m_editStyle("")
  , m_normalStyle("")
  , m_pushStyle("")
  , m_iconStyle("")
  , m_text("")
  , m_updateText("")
  , m_bmidFlag(false)
  , m_bIsUpdateText(false)
  , m_EditStyleRect(QRect(0,0,0,0))
  , m_NormalStyleRect(QRect(0,0,0,0))
  , m_PushStyleRect(QRect(0,0,0,0))
  , m_IconStyleRect(QRect(0,0,0,0))
  , m_textRect(QRect(0,0,0,0))
  , m_name("")
  , m_type("")
  , m_iIndex(-1)
  , m_bIsEditStatus(false)
  , m_IsPress(false)
  , m_ViewStatus(ViewStatusNormal)
  , m_AppIsHide(false)
  , m_IsEndAnimation(true)
  , m_DiffSize(QSize(0,0))
{

   qRegisterMetaType<CCBtnInfo>("CCBtnInfo");
   this->show();
   m_Info.BgPath = "";
   m_Info.IconPath = "";
   m_Info.Name = "";
   m_Info.Type = "";
   m_Info.EditPath = "";
   m_Info.Index = -1;
   m_Info.NormalPath = "";
   m_Info.PushedPath = "";
   m_Info.Text = "";
   this->installEventFilter(this);
   this->setAttribute(Qt::WA_AcceptTouchEvents);
   m_pEffect = new QGraphicsOpacityEffect(this);
   m_pEffect->setOpacity(1);
   this->setGraphicsEffect(m_pEffect);

   m_pOpacityAnimation = new QPropertyAnimation(this);
   m_pOpacityAnimation->setTargetObject(this);
   m_pOpacityAnimation->setPropertyName("opacity");

   connect(m_pOpacityAnimation, SIGNAL(finished()), this, SLOT(OnOpacityAnimationFinished()));

   m_pMoveAnimation = new QPropertyAnimation(this);
   m_pMoveAnimation->setTargetObject(this);
   m_pMoveAnimation->setPropertyName("position");

   m_pMoveParentAnimation = new QPropertyAnimation(this);
   m_pMoveParentAnimation->setTargetObject(this);
   m_pMoveParentAnimation->setPropertyName("ParentPosition");

   m_pSizeAnimation = new QPropertyAnimation(this);
   m_pSizeAnimation->setTargetObject(this);
   m_pSizeAnimation->setPropertyName("size");

   connect(m_pOpacityAnimation, SIGNAL(finished()), this, SLOT(AnimationFinished()));
   connect(m_pMoveAnimation, SIGNAL(finished()), this, SLOT(MoveAnimationFinished()));
   connect(m_pSizeAnimation, SIGNAL(finished()), this, SLOT(AnimationFinished()));
   connect(m_pMoveParentAnimation, SIGNAL(finished()), this, SLOT(MoveParentAnimationFinished()));

}

CCButton::~CCButton()
{
  if(m_pOpacityAnimation)
  {
      delete m_pOpacityAnimation;
  }
  if(m_pEffect)
  {
      delete m_pEffect;
  }
  if(m_pMoveAnimation)
  {
      delete m_pMoveAnimation;
  }
}

void CCButton::SetAppGeometry(QRect rect)
{
    m_viewRect = rect;
    this->setGeometry(rect);
}

void CCButton::SetViewRect(QRect rect)
{
   m_viewRect = rect;
}

void CCButton::InsertEditStyle(QRect rect, QString EditStyle)
{
    m_EditStyleRect = rect;
    m_editStyle = EditStyle;
    m_Info.EditPath = EditStyle;
    update();
}

void CCButton::InsertNormalStyle(QRect rect, QString NormalStyle)
{
    m_NormalStyleRect = rect;
    m_normalStyle = NormalStyle;
    m_Info.NormalPath = NormalStyle;
    update();
}

void CCButton::InsertPushStyle(QRect rect, QString PushStyle)
{
    m_PushStyleRect = rect;
    m_pushStyle = PushStyle;
    m_Info.PushedPath = PushStyle;
    update();
}

void CCButton::InsertIconStyle(QRect rect, QString IconStyle)
{
    m_IconStyleRect = rect;
    m_iconStyle = IconStyle;
    m_Info.IconPath = IconStyle;
    update();
}

void CCButton::InsertEditStyle(QString EditStyle)
{
    m_editStyle = EditStyle;
    m_Info.EditPath = EditStyle;
    update();
}

void CCButton::InsertNormalStyle(QString NormalStyle)
{
    m_normalStyle = NormalStyle;
    m_Info.NormalPath = NormalStyle;
    update();
}

void CCButton::InsertPushStyle(QString PushStyle)
{
    m_pushStyle = PushStyle;
    m_Info.PushedPath = PushStyle;
    update();
}

void CCButton::InsertIconStyle(QString IconStyle)
{
    m_iconStyle = IconStyle;
    m_Info.IconPath = IconStyle;
    update();
}

void CCButton::InsertText(QRect rect, QString text,bool midFlag,Qt::Orientation eOrientation)
{

    m_textRect = rect;
    m_bIsUpdateText = false;
    m_text = text;
    m_Info.Text = text;
    m_bmidFlag = midFlag;
    m_eTextOrientation = eOrientation;
    update();
}

void CCButton::InsertName(QString Name)
{
    m_Info.Name = Name;
    m_name = Name;
}

void CCButton::InsertType(QString Type)
{
    m_Info.Type = Type;
    m_type = Type;
}

void CCButton::SetIndex(int index)
{
    m_Info.Index = index;
    m_iIndex = index;
}

QRect CCButton::GetViewRect()
{
    return m_viewRect;
}

QString CCButton::GetEditStyle()
{
    return m_editStyle;
}

QString CCButton::GetNormalStyle()
{
    return m_normalStyle;
}

QString CCButton::GetPushStyle()
{
    return m_pushStyle;
}

QString CCButton::GetIconStyle()
{
    return m_iconStyle;
}

QRect CCButton::GetEditStyleRect()
{
    return m_EditStyleRect;
}

QRect CCButton::GetNormalStyleRect()
{
    return m_NormalStyleRect;
}

QRect CCButton::GetPushStyleRect()
{
    return m_PushStyleRect;
}

QRect CCButton::GetIconStyleRect()
{
    return m_IconStyleRect;
}

void CCButton::UpdateInfo(CCButton::CCBtnInfo btnInfo)
{
    m_editStyle = btnInfo.EditPath;
    m_normalStyle = btnInfo.NormalPath;
    m_pushStyle = btnInfo.PushedPath;
    m_iconStyle = btnInfo.IconPath;
    m_text = btnInfo.Text;
    m_type = btnInfo.Type;
    m_name = btnInfo.Name;
    m_Info.BgPath = btnInfo.BgPath;
    m_Info.EditPath = btnInfo.EditPath;
    m_Info.IconPath = btnInfo.IconPath;
    m_Info.Name = btnInfo.Name;
    m_Info.NormalPath = btnInfo.NormalPath;
    m_Info.PushedPath = btnInfo.PushedPath;
    m_Info.Text = btnInfo.Text;
    m_Info.Type = btnInfo.Type;
    update();
}

void CCButton::UpdateType(QString type)
{

    m_type = type;
    m_Info.Type = type;
    update();
}

void CCButton::UpdateIconStyle(QString style)
{
    m_iconStyle = style;
    m_Info.IconPath = style;
    update();
}

void CCButton::UpdateName(QString name)
{
    m_name = name;
    m_Info.Name = name;
    update();
}

void CCButton::UpdateBgStyle(QString style)
{
    m_Info.BgPath = style;
    update();
}

void CCButton::UpdateEditStyle(QString style)
{
    m_editStyle = style;
    m_Info.EditPath = style;
    update();
}

void CCButton::UpdateNormalStyle(QString style)
{
    m_normalStyle = style;
    m_Info.NormalPath = style;
    update();
}

void CCButton::UpdatePushStyle(QString style)
{

    m_pushStyle = style;
    m_Info.PushedPath = style;
    update();
}

QString CCButton::GetText()
{
    return m_text;
}

QString CCButton::GetName()
{
    return m_name;
}

QString CCButton::GetType()
{
    return m_type;
}

int CCButton::GetIndex()
{
    return m_iIndex;
}

QRect CCButton::GetTextRect()
{
    return m_textRect;
}

void CCButton::SetEditStatus(bool isEditStatus)
{
    m_bIsEditStatus = isEditStatus;
    update();
}

void CCButton::SetViewStatus(CCButton::ViewStatus status)
{
    m_ViewStatus = status;
    update();
}

void CCButton::SetIsPress(bool IsPress)
{
    m_IsPress = IsPress;
    update();
}

void CCButton::UpdateText(QString text, bool IsUpdate)
{
    m_bIsUpdateText = IsUpdate;
    if(!IsUpdate)
    {
        m_text = text;
        m_Info.Text = text;
    }
    else
    {
       m_updateText = text;
    }
    update();
}

void CCButton::OpacityAnimation(double start, double end,int time,bool IsHide)
{
    if(m_pOpacityAnimation)
    {
        m_pOpacityAnimation->stop();
        m_IsEndAnimation = false;
        this->show();
        m_AppIsHide = IsHide;
        m_pOpacityAnimation->setDuration(time);
        m_pOpacityAnimation->setStartValue(start);
        m_pOpacityAnimation->setEndValue(end);
        m_pOpacityAnimation->start();
    }
}

void CCButton::MoveAnimation(const QPoint startPos, const QPoint endPos, int time, bool IsHide)
{
    if(m_pMoveAnimation)
    {
        this->show();
        m_AppIsHide = IsHide;
        m_pMoveAnimation->stop();
        m_pMoveAnimation->setDuration(time);
        m_pMoveAnimation->setStartValue(startPos);
        m_pMoveAnimation->setEndValue(endPos);
        m_pMoveAnimation->start();
    }
}

void CCButton::MoveParentAnimation(const QPoint startPos, const QPoint endPos, int time, bool IsHide)
{
    if(m_pMoveParentAnimation)
    {
        m_pMoveParentAnimation->stop();
        m_pMoveParentAnimation->setDuration(time);
        m_pMoveParentAnimation->setStartValue(startPos);
        m_pMoveParentAnimation->setEndValue(endPos);
        m_pMoveParentAnimation->start();
    }
    Q_UNUSED(IsHide);
}


void CCButton::SizeAnimation(const QSize start, const QSize end, int time, bool IsHide)
{
    if(m_pSizeAnimation)
    {
        m_DiffSize = end - start;
        this->show();
        m_AppIsHide = IsHide;
        m_pSizeAnimation->setDuration(time);
        m_pSizeAnimation->setStartValue(start);
        m_pSizeAnimation->setEndValue(end);
        m_pSizeAnimation->start();
    }
}

bool CCButton::GetIsEndAnimation()
{
    return m_IsEndAnimation;
}
QPoint CCButton::GetGlobalPos(const QPoint currPos)
{
    HomeView *pBtnParent = dynamic_cast<HomeView*>(this->parent());
    if (NULL == pBtnParent)
    {
        return QPoint();
    }

    return (pBtnParent->mapToParent(this->mapToParent(currPos)));
}

CCButton::CCBtnInfo CCButton::GetInfo()
{
    return m_Info;
}
void CCButton::OnOpacityAnimationFinished()
{
    if(m_AppIsHide)
    {
        m_AppIsHide = false;
        this->hide();
    }
}

void CCButton::AnimationFinished()
{
    m_IsEndAnimation = true;
    if(m_AppIsHide)
    {
        m_AppIsHide = false;
        this->hide();
    }
}

void CCButton::MoveAnimationFinished()
{
    m_IsEndAnimation = true;
    if(m_AppIsHide)
    {
        m_AppIsHide = false;
        this->hide();
    }
    emit MoveAppFinish(GetIndex());
}

void CCButton::MoveParentAnimationFinished()
{
    if(m_pMoveParentAnimation)
    {
        INFO("MoveParentAnimationFinished index=%d",GetIndex());
        emit MoveParentFinish(GetIndex());
    }
}

void CCButton::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);


    QPixmap Normal;
    QPixmap push;
    QPixmap Icon;
    if(m_normalStyle != "")
    {
        Normal = QPixmap(m_normalStyle).scaled(m_NormalStyleRect.size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    }
    painter.drawPixmap(m_NormalStyleRect,Normal);
    if(ViewStatusPushed == m_ViewStatus)
    {
        if(m_pushStyle!="")
        {
            push = QPixmap(m_pushStyle).scaled(m_PushStyleRect.size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        }
        painter.drawPixmap(m_PushStyleRect,push);
    }
    if(m_bIsEditStatus && !m_IsPress)
    {
       painter.drawPixmap(m_EditStyleRect,QPixmap(m_editStyle));
    }
    if(m_iconStyle != "")
    {
        Icon = QPixmap(m_iconStyle).scaled(m_IconStyleRect.size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    }
    painter.drawPixmap(m_IconStyleRect,Icon);

    painter.setPen(QColor(255,255,255));
    QFont font;
    font.setPixelSize(20);
    painter.setFont(font);
    if (Qt::Horizontal == m_eTextOrientation)
    {
        if (!m_bmidFlag)
        {

            if(m_bIsUpdateText)
            {
              painter.drawText(m_textRect, m_updateText);
            }
            else
            {
              painter.drawText(m_textRect, m_text);
            }
        }
        else
        {
            if(m_bIsUpdateText)
            {
                painter.drawText(m_textRect, Qt::AlignCenter, m_updateText);
            }
            else
            {
                painter.drawText(m_textRect, Qt::AlignCenter, m_text);
            }
        }
    }
}

bool CCButton::eventFilter(QObject *obj, QEvent *e)
{
    switch (e->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease:
        break;
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        return true;
    }
    default:
        break;
    }
   return QObject::eventFilter(obj,e);
}

double CCButton::getOpacity()
{

}

void CCButton::setOpacity(double opacity)
{
    m_pEffect->setOpacity(opacity);
    update();
}

QSize CCButton::getSize()
{
}

void CCButton::setSize(QSize size)
{
    int sizex = this->geometry().width() - size.width();
    int sizey = this->geometry().height() - size.height();
    m_NormalStyleRect.setSize(QSize(m_NormalStyleRect.width() - sizex,m_NormalStyleRect.height()-sizey));
    m_PushStyleRect.setSize(QSize(m_PushStyleRect.width() - sizex,m_PushStyleRect.height()-sizey));
    m_IconStyleRect.setSize(QSize(m_IconStyleRect.width() - sizex,m_IconStyleRect.height()-sizey));
    this->resize(size);
    this->update();
}

QPoint CCButton::getPosition()
{

}

void CCButton::setPosition(QPoint position)
{
    this->move(position);
    this->update();
}

QPoint CCButton::getParentPosition()
{

}

void CCButton::setParentPosition(QPoint ParentPosition)
{
    reinterpret_cast<HomeView*>(this->parent())->move(ParentPosition);
    update();
}
