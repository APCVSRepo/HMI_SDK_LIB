#ifndef CROTATIONWIDGET_H
#define CROTATIONWIDGET_H

#include <QLabel>
#include <QTimer>
#include <QPainter>

class CRotationWidget: public QLabel
{
    Q_OBJECT
public:
    explicit  CRotationWidget(QWidget *parent=0);
    ~CRotationWidget();

    void setPixmap(const QString &path);
    void start();
    void stop();

protected:
    void paintEvent(QPaintEvent *event);

public slots:
    void onRatateTimeout();

private:
    QTimer *m_timer;
    bool m_bRotationStarted;
    int  m_nRotationDegree;
    int  m_nRotationAngle;
    QPixmap m_image;
};

#endif // CROTATIONWIDGET_H
