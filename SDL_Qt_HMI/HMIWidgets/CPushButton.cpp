#include "CPushButton.h"

CPushButton::CPushButton(QWidget *parent)
    :QPushButton(parent)
{
    m_pEffect = new QGraphicsOpacityEffect();
    m_pEffect->setOpacity(1);
    this->setGraphicsEffect(m_pEffect);
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

void CPushButton::MouseEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::MouseButtonPress:
    {
        m_pEffect->setOpacity(0.4);
        this->setGraphicsEffect(m_pEffect);
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
        m_pEffect->setOpacity(1);
        this->setGraphicsEffect(m_pEffect);
    }
        break;
    default:
        break;

    }

}
