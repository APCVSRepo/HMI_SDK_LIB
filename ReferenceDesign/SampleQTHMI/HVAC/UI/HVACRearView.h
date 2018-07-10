#ifndef HVACREARVIEW_H
#define HVACREARVIEW_H
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
#include "HMIWidgets/CSlider.h"
#include <QButtonGroup>
class HVACRearView:public QWidget, public CView
{
    Q_OBJECT

public:
    explicit HVACRearView(QWidget *parent = 0);
    ~HVACRearView();

    virtual void viewAction(int state);

    void InitHVACRearView();

    void InitConnect();
    void FrontHairModeSelect(bool isSelect);
    void FrontBelowHairModeSelect(bool isSelect);
    void BelowHairModeSelect(bool isSelect);
public slots:

    void OnLeftAddTemperature();
    void OnLeftSubTemperature();
    void OnTitleFront();
    void OnTitleReart();
    void OnHairModeSelect(int);


    void OnSubAirVolume();
    void OnAddAirVolume();
    void OnAirVolumeDataSlider(int);

    void OnAuto();
private:

    int m_iLeftTemperature;
    int m_iTemperatureMin;
    int m_iTemperatureMax;
    int m_iAirVolume;
    CPushButton* m_pLeftAddTemperatureBtn;
    CPushButton* m_pLeftSubTemperatureBtn;
    QLabel *m_LeftTemperatureDataLabel;


    QLabel *m_pTitleBlueLineLabel;
    QLabel *m_pTitleWhiteLineLabel;
    CPushButton* m_pTitleFrontBtn;
    CPushButton* m_pTitleReartBtn;

    QButtonGroup *m_pHairModeGroup;
    CPushButton* m_pFrontHairModeBtn;
    CPushButton* m_pFrontBelowHairModeBtn;
    CPushButton* m_pBelowHairModeBtn;

    CPushButton* m_pSubAirVolumeBtn;
    CPushButton* m_pAddAirVolumeBtn;
    CSlider *m_pAirVolumeDataSlider;

    CPushButton* m_pAutoBtn;



};

#endif // HVACREARVIEW_H
