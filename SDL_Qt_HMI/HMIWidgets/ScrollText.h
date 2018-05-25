#ifndef SCROLLTEXT_H
#define SCROLLTEXT_H

#include <QWidget>
#include <QTimer>
#include <QStaticText>
#include <QImage>

class QPropertyAnimation;

class ScrollText : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int textPos READ textPos WRITE setTextPos)
public:
    explicit ScrollText(QWidget *parent);
    virtual ~ScrollText();
    void setScrollStep(int nStep);
    void setStartTimeMsec(int msec);
    void setText(QString text, int width, int height, QFont& font);
    void setSingleShot(bool bSingleShot);
    void setCycleCount(int count);
    void setTextIntervalDis(int dis);
    void startScrollText();
    void stopScrollText();
    void paintTextImage(QPainter *painter, int x = 0, int y = 0);

protected:
    int textPos();
    void setTextPos(int textPos);

signals:

public slots:
    void animFinished();
    void onStartTimerOut();

private:
    QTimer                 m_StartScrollTimer;
    QPropertyAnimation*    m_pScrollAnimation;
    QWidget*               m_pWidget;
    QString                m_qsText;
    QString                m_qsSeparator;
    QStaticText            m_qsStaticText;
    QSize                  m_sizeWholeText;
    QImage                 m_TextImage;
    int                    m_nScrollPos;
    int                    m_nScrollStep;
    int                    m_nTextIntervalDis;
    int                    m_nCycleCount;
    int                    m_nCycleIndex;
    int                    m_nStartTimeMsec;
    bool                   m_bScrollEnabled;
    bool                   m_bScrllLeftAnimation;
    bool                   m_bSingleShot;
    int                    m_nWidth;
    int                    m_nHeight;
};

#endif // SCROLLTEXT_H
