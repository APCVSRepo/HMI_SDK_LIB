#include "CSlider.h"
#include <math.h>
CSlider::CSlider(QWidget *parent)
    :QSlider(parent)
{

}

CSlider::CSlider(Qt::Orientation orientation, QWidget *parent)
    :QSlider(orientation,parent)
{

}

CSlider::~CSlider()
{

}

void CSlider::mousePressEvent(QMouseEvent *ev)
{
    QSlider::mousePressEvent(ev);

    double pos = ev->pos().x() / (double)width();
    double _value = pos * (maximum() - minimum()) + minimum();
    int _vv =ceil( _value);
    setValue(_vv);
}
