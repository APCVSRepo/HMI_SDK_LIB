#include "SliderSelect.h"
#include <QPalette>

SliderSelect::SliderSelect(QWidget *parent):
    QWidget(parent)
    ,m_normalStyle("")
    ,m_pushStyle("")
    ,m_selectStyle("")
    ,m_text("")
    ,m_iIndex(-1)
    ,m_iPosionId(-1)
    ,m_size(QSize(0,0))
    ,m_status(eNormal)
{
    m_rect.setRect(0,0,0,0);
    this->show();
}

SliderSelect::~SliderSelect()
{

}

void SliderSelect::SetGeometry(QRect rect)
{
    this->setGeometry(rect);
    update();
}

void SliderSelect::setIndex(int index)
{
    m_iIndex = index;
}

void SliderSelect::SetNormalStyle(QString style)
{
    m_normalStyle = style;
    update();
}

void SliderSelect::SetPushStyle(QString style)
{
    m_pushStyle = style;
}

void SliderSelect::SetSelectStyle(QString style)
{
    m_selectStyle = style;
}

void SliderSelect::SetPosionID(int id)
{
    m_iPosionId = id;
}

int SliderSelect::GetPosionID()
{
   return m_iPosionId;
}

void SliderSelect::Insert(int index)
{
    m_iIndex = index;
}


void SliderSelect::setRect(QRect rect)
{
    m_rect = rect;
    this->setGeometry(rect);
    update();
}

QRect SliderSelect::getRect()
{
    return m_rect;
}

int SliderSelect::getIndex()
{
    return m_iIndex;
}

void SliderSelect::setSize(QSize size)
{
    m_size = size;
}

QSize SliderSelect::getSize()
{
    return m_size;
}

void SliderSelect::setText(QString &text)
{
    m_text = text;
}

void SliderSelect::setStatus(eViewStatus status)
{
    m_status = status;
    update();
}

void SliderSelect::UpdateStatus(SliderSelect::eViewStatus status)
{
    m_status = status;
    update();
}

SliderSelect::eViewStatus SliderSelect::getStatus()
{
    return m_status;
}
void SliderSelect::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    switch (m_status) {
    case eNormal:
        painter.drawPixmap(QRect(0,0,m_rect.width(),m_rect.height()),QPixmap(m_normalStyle));
        break;
    case ePushed:
        painter.drawPixmap(QRect(0,0,m_rect.width(),m_rect.height()),QPixmap(m_pushStyle));
        break;
    case eSelect:
        painter.drawPixmap(QRect(0,0,m_rect.width(),m_rect.height()),QPixmap(m_selectStyle));
        break;
    default:
        break;
    }
}
