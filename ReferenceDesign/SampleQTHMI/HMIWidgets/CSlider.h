#ifndef CSLIDER_H
#define CSLIDER_H
#include <QSlider>
#include <QMoveEvent>
class CSlider : public QSlider
{
    Q_OBJECT
public:
    explicit CSlider(QWidget *parent = 0);
    explicit CSlider(Qt::Orientation orientation, QWidget *parent = 0);
    ~CSlider();
protected:
    void mousePressEvent(QMouseEvent *ev);
};

#endif // CSLIDER_H
