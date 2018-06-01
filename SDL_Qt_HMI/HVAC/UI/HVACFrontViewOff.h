#ifndef HVACFRONTVIEWOFF_H
#define HVACFRONTVIEWOFF_H
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

class HVACFrontViewOff:public QWidget, public CView
{
    Q_OBJECT

public:
    explicit HVACFrontViewOff(QWidget *parent = 0);
    ~HVACFrontViewOff();

    virtual void viewAction(int state);

    void InitHVACFrontViewOff();
    void InitConnect();
public slots:
    void OnTitleReart();
    void OnPower();
    void OnZone(int zone);
private:
    int m_iHvacZone;
    QLabel *m_pOffLabel;

    QLabel *m_pTitleBlueLineLabel;
    QLabel *m_pTitleWhiteLineLabel;
    CPushButton* m_pTitleFrontBtn;
    CPushButton* m_pTitleReartBtn;
    CPushButton* m_pPowerBtn;


};

#endif // HVACFRONTVIEWOFF_H
