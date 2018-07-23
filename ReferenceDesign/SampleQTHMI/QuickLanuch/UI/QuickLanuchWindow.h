#ifndef QUICKLANUCHWINDOW_H
#define QUICKLANUCHWINDOW_H
#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
class QuickLanuchWindow:public QWidget
{
    Q_PROPERTY(QPoint position READ getPosition WRITE setPosition)
    Q_OBJECT
public:
    explicit QuickLanuchWindow(QWidget *parent = 0);

public:
    QPoint getPosition();
    void setPosition(QPoint position);
    void PullBackAnimation(const QPoint startPos, const QPoint endPos,int time);
public slots:
    void PullBackAnimationFinish();
public:signals:
    void PullBackFinish();
private:
    QLabel *m_pBackgroundLabel;
    QLabel *m_pLine;
    QPropertyAnimation      *m_pPullBackAnimation;

};

#endif // QUICKLANUCHWINDOW_H
