#ifndef CROTATIONWIDGET_H
#define CROTATIONWIDGET_H

#include <QLabel>
#include <QTimer>
#include <QPainter>

class CRotationWidget: public QLabel
{
    Q_OBJECT
public:
    enum eRotateDirection{
        ROTATE_CLOCKWISE = 0,
        ROTATE_ANTICLOCKWISE = 1,

        DEFAULT_DIRECTION = ROTATE_CLOCKWISE
    };
    explicit CRotationWidget(QWidget *parent=0);
    ~CRotationWidget();

    void setPixmap(const QString &path);
    void setPixmap(const QPixmap &pixmap);

    void start();
    void stop();

    void setRotateDirection(eRotateDirection direction = DEFAULT_DIRECTION);

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
    eRotateDirection m_eDirection;
};

#endif // CROTATIONWIDGET_H
