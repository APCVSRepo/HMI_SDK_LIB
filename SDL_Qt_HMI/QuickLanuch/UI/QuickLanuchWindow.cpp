#include "QuickLanuchWindow.h"
#include <QDebug>
QuickLanuchWindow::QuickLanuchWindow(QWidget *parent)
    :QWidget(parent)
{
    this->setStyleSheet("QWidget{background:transparent;}");
    setGeometry(QRect(0,40,161,440));
    m_pBackgroundLabel = new QLabel(this);
    m_pBackgroundLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_pBackgroundLabel->setGeometry(QRect(0,0,160,440));
    m_pBackgroundLabel->setStyleSheet("QLabel{border-image:url(:/QuickLanuch/Source/images/quicklunch_bg_transparent.png);background:transparent;}");
    m_pBackgroundLabel->show();

    m_pLine = new QLabel(this);
    m_pLine->setGeometry(QRect(160,0,161,440));
    m_pLine->setStyleSheet("QLabel{border-image:url(:/QuickLanuch/Source/images/quicklunch_line.png);background:transparent;}");
    m_pLine->hide();

    m_pPullBackAnimation = new QPropertyAnimation(this);
    m_pPullBackAnimation->setTargetObject(this);
    m_pPullBackAnimation->setPropertyName("position");

    connect(m_pPullBackAnimation,SIGNAL(finished()),this,SLOT(PullBackAnimationFinish()),Qt::UniqueConnection);
    this->setGeometry(QRect(-121,213,161,66));
    this->hide();
}

QPoint QuickLanuchWindow::getPosition()
{

}

void QuickLanuchWindow::setPosition(QPoint position)
{
    this->move(position);
}

void QuickLanuchWindow::PullBackAnimation(const QPoint startPos, const QPoint endPos, int time)
{
    qDebug() <<" QuickLanuchWindow PullBackAnimation";
    if(m_pPullBackAnimation)
    {
        if(this->geometry().x() < 0)
        {
            m_pLine->show();
            m_pBackgroundLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
            m_pBackgroundLabel->setGeometry(QRect(0,0,160,440));
            m_pBackgroundLabel->setStyleSheet("QLabel{border-image:url(:/QuickLanuch/Source/images/quicklunch_bg.png);background:transparent;}");
            m_pBackgroundLabel->lower();
            m_pBackgroundLabel->show();
        }
        m_pPullBackAnimation->setDuration(time);
        m_pPullBackAnimation->setStartValue(startPos);
        m_pPullBackAnimation->setEndValue(endPos);
        m_pPullBackAnimation->start();
    }
}

void QuickLanuchWindow::PullBackAnimationFinish()
{
    emit PullBackFinish();
    qDebug()<< " finisj +++" << this->geometry();
    if(this->geometry().x() < 0)
    {
        m_pLine->hide();
        m_pBackgroundLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
        m_pBackgroundLabel->setGeometry(QRect(0,0,160,440));
        m_pBackgroundLabel->setStyleSheet("QLabel{border-image:url(:/QuickLanuch/Source/images/quicklunch_bg_transparent.png);background:transparent;}");
        m_pBackgroundLabel->lower();
        m_pBackgroundLabel->show();
    }
}
