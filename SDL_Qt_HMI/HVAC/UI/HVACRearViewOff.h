#ifndef HVACREARVIEWOFF_H
#define HVACREARVIEWOFF_H
#include <QWidget>
#include <QMouseEvent>
#include <QTouchEvent>
#include <QTimer>
#include <QList>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QPainter>
#include <QCoreApplication>
#include "HMIFrameWork/log_interface.h"
#include "HMIWidgets/CCButton.h"
#include "QuickLanuch/UI/QuickLanuchView.h"
#include "HMIFrameWork/AppConfig.h"
#include "HMIFrameWork/App.h"
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CPushButton.h"
#include <QSlider>

class HVACRearViewOff:public QWidget, public CView
{
    Q_OBJECT

public:
    explicit HVACRearViewOff(QWidget *parent = 0);
    ~HVACRearViewOff();

    virtual void viewAction(int state);

    void InitHVACRearViewOff();
    void InitConnect();
public slots:

    void OnTitleFront();
private:

    QLabel *m_pOffLabel;

    QLabel *m_pTitleBlueLineLabel;
    QLabel *m_pTitleWhiteLineLabel;
    CPushButton* m_pTitleFrontBtn;
    CPushButton* m_pTitleReartBtn;



};

#endif // HVACREARVIEWOFF_H
