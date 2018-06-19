#include "CPushButton.h"
#include <QPainter>
#include <QPixmap>
#include <QFont>
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
{
    m_pEffect = new QGraphicsOpacityEffect();
    m_pEffect->setOpacity(1);
    this->setGraphicsEffect(m_pEffect);
    m_LongPressTotalTimer.setInterval(1000);
    m_LongPressTotalTimer.setSingleShot(true);
    connect(&m_LongPressTotalTimer,SIGNAL(timeout()),this,SLOT(OnLongPressTotal()),Qt::UniqueConnection);

    m_LongPressTimer.setInterval(50);
    m_LongPressTimer.setSingleShot(true);
    connect(&m_LongPressTimer,SIGNAL(timeout()),this,SLOT(OnLongPress()),Qt::UniqueConnection);

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
}

void CPushButton::SetId(int id)
{
    m_iId = id;
}

void CPushButton::SetData(const QString &data)
{
    m_data = data;
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


void CPushButton::MouseEvent(QEvent *e)
{
    if(!m_bIsEnabled)
    {
        return;
    }
    switch (e->type()) {
    case QEvent::MouseButtonPress:
    {
        m_pEffect->setOpacity(0.4*m_dEffect);
        this->setGraphicsEffect(m_pEffect);
        m_LongPressTotalTimer.start();
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
        m_LongPressTotalTimer.stop();
        m_LongPressTimer.stop();

        m_pEffect->setOpacity(1*m_dEffect);
        this->setGraphicsEffect(m_pEffect);
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
