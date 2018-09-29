#include "CPushButton.h"
#include <QPainter>
#include <QPixmap>
#include <QFont>
#include <QMouseEvent>
CPushButton::CPushButton(QWidget *parent)
    :QPushButton(parent)
    ,m_type("")
    ,m_status(eStatus_Normal)
    ,m_iId(-1)
    ,m_data("")
    ,m_icon("")
    ,m_iconRect(QRect(0,0,0,0))
    ,m_iconAlign(Qt::AlignCenter)
    ,m_text("")
    ,m_textRect(QRect(0,0,0,0))
    ,m_textColor(QColor(255,255,255))
    ,m_textAlign(Qt::AlignCenter)
    ,m_bIsEnabled(true)
    ,m_dEffect(1.0)
    ,m_bEnableEffect(true)
    ,m_eBtnStatus(eStatus_Normal)
    ,m_btnNormalStyle("")
    ,m_btnPushStyle("")
    ,m_btnSelectStyle("")
    ,m_btnStatusRect(QRect(0,0,0,0))
{
    setStyleSheet("QPushButton{border:none;background:transparent;}");
    m_pEffect = new QGraphicsOpacityEffect();
    m_pEffect->setOpacity(1);
    this->setGraphicsEffect(m_pEffect);
    m_LongPressTotalTimer.setInterval(1000);
    m_LongPressTotalTimer.setSingleShot(true);
    connect(&m_LongPressTotalTimer,SIGNAL(timeout()),this,SLOT(OnLongPressTotal()),Qt::UniqueConnection);

    m_LongPressTimer.setInterval(50);
    m_LongPressTimer.setSingleShot(true);
    connect(&m_LongPressTimer,SIGNAL(timeout()),this,SLOT(OnLongPress()),Qt::UniqueConnection);

    connect(this,SIGNAL(clicked()),this,SLOT(OnClicked()),Qt::UniqueConnection);
}

void CPushButton::SetStyle(const QString &style)
{
    setStyleSheet(style);
}

bool CPushButton::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease:
    {
       MouseEvent(e);
    }
        break;
    default:
        break;
    }
    return QPushButton::event(e);
}

void CPushButton::SetType(const QString &type)
{
    m_type = type;
}

void CPushButton::SetStatus(CPushButton::eStatus status)
{
    m_status = status;
    update();
}

void CPushButton::SetId(int id)
{
    m_iId = id;
}

void CPushButton::SetData(const QString &data)
{
    m_data = data;
}

void CPushButton::SetStatusStyle(const QRect &rect, const QString &normal, const QString &push, const QString &select)
{
    m_btnStatusRect = rect;
    m_btnNormalStyle = normal;
    m_btnPushStyle = push;
    m_btnSelectStyle = select;
    update();
}

void CPushButton::SetEnabled(bool isEnabeled)
{
    this->setEnabled(isEnabeled);
    m_bIsEnabled = isEnabeled;
    update();
}

QString CPushButton::GetType()
{
    return m_type;
}

CPushButton::eStatus CPushButton::GetStatus()
{
    return m_status;
}

QString CPushButton::GetData()
{
    return m_data;
}

int CPushButton::GetId()
{
    return m_iId;
}

void CPushButton::SetIcon(const QRect& rect,const QString &icon)
{
     m_icon = icon;
     m_iconRect = rect;
}

void CPushButton::SetText(const QRect &rect, const QString &text, int fontsize, Qt::Alignment align, const QColor &color)
{
    m_text = text;
    m_textRect = rect;
    m_textFontSize = fontsize;
    m_textColor = color;
    m_textAlign = align;
}

void CPushButton::SetEffect(double effect)
{
    m_dEffect = effect;
    m_pEffect->setOpacity(m_dEffect);
    this->setGraphicsEffect(m_pEffect);
}

void CPushButton::SetEnableEffect(bool isEnable)
{
    m_bEnableEffect = isEnable;
}


void CPushButton::MouseEvent(QEvent *e)
{
    if(!m_bIsEnabled)
    {
        return;
    }

    switch (e->type()) {
    case QEvent::MouseButtonPress:
    {
        m_eBtnStatus = eStatus_Push;
        update();
        if(m_bEnableEffect)
        {
            m_pEffect->setOpacity(0.4*m_dEffect);
            this->setGraphicsEffect(m_pEffect);
            m_LongPressTotalTimer.start();
        }
    }
        break;
    case QEvent::MouseButtonDblClick:
    {

    }
        break;
    case QEvent::MouseMove:
    {

    }
        break;
    case QEvent::MouseButtonRelease:
    {
        m_eBtnStatus = eStatus_Normal;
        update();
        m_LongPressTotalTimer.stop();
        m_LongPressTimer.stop();

        if(m_bEnableEffect)
        {
            m_pEffect->setOpacity(1*m_dEffect);
            this->setGraphicsEffect(m_pEffect);
        }
    }
        break;
    default:
        break;

    }

}
#include "HMIFrameWork/log_interface.h"
void CPushButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);
    QPainter p(this);


    if(!m_bEnableEffect)
    {
        if("" != m_btnNormalStyle && eStatus_Normal == m_eBtnStatus)
        {
            QPixmap icon(m_btnNormalStyle);
            p.drawPixmap(m_btnStatusRect,icon);
        }else if("" != m_btnPushStyle && eStatus_Push == m_eBtnStatus)
        {
            QPixmap icon(m_btnPushStyle);
            p.drawPixmap(m_btnStatusRect,icon);
        }else if("" != m_btnSelectStyle && eStatus_Select == m_eBtnStatus)
        {
            QPixmap icon(m_btnSelectStyle);
            p.drawPixmap(m_btnStatusRect,icon);
        }
    }

    if(m_icon != "")
    {
       QPixmap icon(m_icon);
       p.drawPixmap(m_iconRect,icon);
    }
    if(m_text != "")
    {
        QFont f;
        f.setPixelSize(m_textFontSize);
        if(m_bIsEnabled)
        {
           p.setPen(m_textColor);
        }
        else
        {
            int r = m_textColor.red()*0.4;
            int g = m_textColor.green()*0.4;
            int b = m_textColor.blue()*0.4;

            p.setPen(QColor(r,g,b));
        }
        p.setFont(f);
        p.drawText(m_textRect,m_textAlign,m_text);
    }
}

void CPushButton::OnLongPressTotal()
{
    m_LongPressTimer.start();
}

void CPushButton::OnLongPress()
{
    emit LongPress();
    if(!m_LongPressTimer.isActive())
        m_LongPressTimer.start();
}

void CPushButton::OnClicked()
{
    emit clicked(m_iId);
}
