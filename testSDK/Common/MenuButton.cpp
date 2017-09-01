#include "MenuButton.h"
#include <QPainter>
#include <QRectF>
#include <QTextOption>
#include <QUrl>
MenuButton::MenuButton(QWidget *pParent):QPushButton(pParent)
{
    m_isActive = false;
}

MenuButton::~MenuButton()
{

}

void MenuButton::setText(const QString &text)
{
    m_text = text;
    update();
}

void MenuButton::setActive(bool active)
{
    m_isActive = active;
    update();
}

void MenuButton::setIcon(const QString on,const QString off)
{

    if (!m_pOnImage.load(on)) {
        QUrl qurl(on);
        m_pOnImage.load(qurl.path());
    }

    if (!m_pOffImage.load(off)) {
        QUrl qurl(off);
        m_pOffImage.load(qurl.path());
    }
}

void MenuButton::setIcon(QImage on, QImage off)
{
    m_pOnImage = on;
    m_pOffImage = off;
}

void MenuButton::paintEvent(QPaintEvent *e)
{
    //QPushButton::paintEvent(e);
    QPainter painter(this);
    QColor   wordColor;

    if (m_isActive) {
        QRect irect = m_pOnImage.rect();
        QRect orect = rect();
        int sx = (irect.width()-orect.width())/2;
        int sy = (irect.height()-orect.height())/2;
        m_pOnImage = m_pOnImage.scaled(width(),height());
       //painter.drawImage(0,0,orect.width(),orect.height(),m_pOnImage,sx,sy);
        painter.drawImage(orect,m_pOnImage);
       wordColor = Qt::white;
    } else {
        QRect irect = m_pOffImage.rect();
        QRect orect = rect();
        int sx = (irect.width()-orect.width())/2;
        int sy = (irect.height()-orect.height())/2;
        m_pOffImage = m_pOffImage.scaled(width(),height());
       //painter.drawImage(0,0,orect.width(),orect.height(),m_pOffImage,sx,sy);
        painter.drawImage(orect,m_pOffImage);
       wordColor = Qt::black;
    }

    QPen pen(wordColor);
    pen.setWidthF(2);
    painter.setPen(pen);
    QFont font;
    font.setFamily("Liberation Serif");
    font.setPixelSize(22);
    //font.setBold(true);
    painter.setFont(font);
    QRectF rect = QRectF(0,1.0*height()*15/24,width(),height()/3);
    painter.drawText(rect,m_text,QTextOption(Qt::AlignCenter));
}

std::string MenuButton::Text()
{
#if defined(WINCE)
    return m_text.toLocal8Bit().data();
#else
    return m_text.toStdString();
#endif
}
