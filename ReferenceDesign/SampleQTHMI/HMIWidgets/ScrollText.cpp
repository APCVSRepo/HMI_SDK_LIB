
#include <QPainter>
#include <QPropertyAnimation>
#include "ScrollText.h"

ScrollText::ScrollText( QWidget *parent)
    : QObject(NULL)
    , m_sizeWholeText(0, 0)
    , m_nScrollPos(0)
    , m_nScrollStep(10)
    , m_nTextIntervalDis(50)
    , m_nCycleCount(3)
    , m_nCycleIndex(0)
    , m_nStartTimeMsec(10000)
    , m_bScrollEnabled(false)
    , m_bScrllLeftAnimation(false)
    , m_bSingleShot(false)
    , m_nWidth(0)
    , m_nHeight(0)
{
    m_pWidget = parent;
    m_qsStaticText.setTextFormat(Qt::PlainText);
    connect(&m_StartScrollTimer, SIGNAL(timeout()), this, SLOT(onStartTimerOut()));

    m_pScrollAnimation = new QPropertyAnimation(this, "textPos");
    connect(m_pScrollAnimation, SIGNAL(finished()), this, SLOT(animFinished()));
}

ScrollText::~ScrollText()
{

}

int ScrollText::textPos()
{
    return m_nScrollPos;
}

void ScrollText::setTextPos(int textPos)
{
    m_nScrollPos = textPos;
    m_pWidget->update();
}

void ScrollText::animFinished()
{
    if (m_nCycleIndex < m_nCycleCount -1)
    {
        m_nCycleIndex++;
        if (m_pScrollAnimation)
        {
            m_pScrollAnimation->setStartValue(0);
            int endValue = m_sizeWholeText.width() + m_nTextIntervalDis;
            m_pScrollAnimation->setEndValue(endValue);
            m_pScrollAnimation->setEasingCurve(QEasingCurve::Linear);
            m_pScrollAnimation->setLoopCount(1);
            m_pScrollAnimation->setDuration(m_nScrollStep * endValue);
            m_pScrollAnimation->start();
            m_bScrllLeftAnimation = true;
        }
    }
    else
    {
        if (!m_bSingleShot)
        {
            m_StartScrollTimer.start(m_nStartTimeMsec);
        }
        m_bScrollEnabled = false;
        m_nCycleIndex = 0;
    }
}

void ScrollText::onStartTimerOut()
{
    m_StartScrollTimer.stop();
    if (m_pScrollAnimation)
    {
        m_bScrollEnabled = true;
        m_pScrollAnimation->setStartValue(0);
        int endValue = m_sizeWholeText.width() + m_nTextIntervalDis;
        m_pScrollAnimation->setEndValue(endValue);
        m_pScrollAnimation->setEasingCurve(QEasingCurve::Linear);
        m_pScrollAnimation->setLoopCount(1);
        m_pScrollAnimation->setDuration(m_nScrollStep * endValue);
        m_pScrollAnimation->start();
        m_bScrllLeftAnimation = true;
    }
}

void ScrollText::setText(QString text, int width, int height, QFont& font)
{
    m_nWidth = width;
    m_nHeight = height;
    m_nCycleIndex = 0;
    m_nScrollPos = 0;
    m_bScrollEnabled = false;
    if (m_pScrollAnimation && QPropertyAnimation::Running == m_pScrollAnimation->state())
    {
        m_pScrollAnimation->stop();
    }
    if (m_StartScrollTimer.isActive())
    {
        m_StartScrollTimer.stop();
    }
    QFontMetrics fontMetrics(font);
    m_qsText = fontMetrics.elidedText(text, Qt::ElideRight, width);
    if (m_pWidget->isVisible())
    {
        startScrollText();
    }
    m_StartScrollTimer.start(m_nStartTimeMsec);

    //width or height may be different from the last
    //if (m_TextImage.isNull())
    {
        m_TextImage = QImage(width, height, QImage::Format_ARGB32_Premultiplied);
    }
    m_qsStaticText.setText(text);
    m_qsStaticText.prepare(QTransform(), font);
    m_sizeWholeText = QSize(fontMetrics.width(m_qsStaticText.text()), fontMetrics.height());
}

void ScrollText::setSingleShot(bool bSingleShot)
{
    m_bSingleShot = bSingleShot;
}

void ScrollText::setCycleCount(int count)
{
    m_nCycleCount = count;
}

void ScrollText::setTextIntervalDis(int dis)
{
    m_nTextIntervalDis = dis;
}

void ScrollText::startScrollText()
{
    m_nCycleIndex = 0;
    m_nScrollPos = 0;
    m_bScrollEnabled = false;
    if (m_pScrollAnimation && QPropertyAnimation::Running == m_pScrollAnimation->state())
    {
        m_pScrollAnimation->stop();
    }
    if (m_StartScrollTimer.isActive())
    {
        m_StartScrollTimer.stop();
    }
    m_StartScrollTimer.start(m_nStartTimeMsec);
}

void ScrollText::stopScrollText()
{
    if (m_pScrollAnimation && QPropertyAnimation::Running == m_pScrollAnimation->state())
    {
        m_pScrollAnimation->stop();
    }
    if (m_StartScrollTimer.isActive())
    {
        m_StartScrollTimer.stop();
    }
}

void ScrollText::paintTextImage(QPainter *painter, int x, int y)
{
    if (m_qsText.isNull())
    {
        return;
    }
    int posX = 0, posY = 0;
    if (m_bScrollEnabled)
    {
        m_TextImage.fill(qRgba(0, 0, 0, 0));
        QPainter pb(&m_TextImage);
        pb.setPen(painter->pen());
        pb.setFont(painter->font());
        posX = -m_nScrollPos;
        posY = (m_nHeight - m_sizeWholeText.height()) / 2;
        pb.drawStaticText(posX, posY, m_qsStaticText);
        painter->drawImage(x, y, m_TextImage);
        if (m_nScrollPos > m_sizeWholeText.width() - m_nWidth + m_nTextIntervalDis)
        {
            posX = m_sizeWholeText.width() - m_nScrollPos + m_nTextIntervalDis;
            posY = (m_nHeight - m_sizeWholeText.height()) / 2;
            pb.drawStaticText(posX, posY, m_qsStaticText);
            painter->drawImage(x, y, m_TextImage);
        }
    }
    else
    {
        m_TextImage.fill(qRgba(0, 0, 0, 0));
        QPainter pb(&m_TextImage);
        pb.setPen(painter->pen());
        pb.setFont(painter->font());
        posX = 0;
        posY = (m_nHeight - m_sizeWholeText.height()) / 2;
        pb.drawStaticText(posX, posY, m_qsText);
        painter->drawImage(x, y, m_TextImage);
    }
}

void ScrollText::setScrollStep(int nStep)
{
    m_nScrollStep = nStep;
}

void ScrollText::setStartTimeMsec(int msec)
{
    m_nStartTimeMsec = msec;
}
