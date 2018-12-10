#include "MenuButton.h"
#include <QPainter>
#include <QRectF>
#include <QTextOption>
#include <QUrl>

MenuButton::MenuButton(QWidget *parent): QPushButton(parent) {
    m_isActive = false;
}

MenuButton::~MenuButton() {

}

void MenuButton::setText(const QString &text) {
    m_text = text;
    update();
}

void MenuButton::setActive(bool active) {
    m_isActive = active;
    update();
}

void MenuButton::setIcon(const QString on, const QString off) {
    if (!m_pOnImage.load(on)) {
        QUrl qurl(on);
        m_pOnImage.load(qurl.path());
    }

    if (!m_pOffImage.load(off)) {
        QUrl qurl(off);
        m_pOffImage.load(qurl.path());
    }
}

void MenuButton::setIcon(QImage on, QImage off) {
    m_pOnImage = on;
    m_pOffImage = off;
}

void MenuButton::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);
    QPainter painter(this);
    QColor   wordColor;

    if (m_isActive) {
        QRect orect = QRect((width()-m_pOnImage.width())/2,0,m_pOnImage.width(),m_pOnImage.height());
        painter.drawImage(orect, m_pOnImage);
        wordColor = Qt::white;
    } else {
        QRect orect = QRect((width()-m_pOffImage.width())/2,0,m_pOffImage.width(),m_pOffImage.height());
        painter.drawImage(orect, m_pOffImage);
        wordColor = Qt::black;
    }

    QPen pen(wordColor);
    pen.setWidthF(2);
    painter.setPen(pen);
    QFont font;
    font.setPixelSize(18);
    painter.setFont(font);
    QRectF rect = QRectF(0, 125, width(), 21);
    //hide text which is out of range
    QFontMetrics qfm(font);
    QString strShow = qfm.elidedText(m_text, Qt::ElideRight, width());
    painter.drawText(rect, strShow, QTextOption(Qt::AlignCenter));
}

std::string MenuButton::Text() {
#if defined(WINCE)
    return m_text.toLocal8Bit().data();
#else
    return m_text.toStdString();
#endif
}
