#ifndef HVACFRONTVIEW_H
#define HVACFRONTVIEW_H
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
#include "HVAC/app/HVAC.h"

class HVACFrontView:public QWidget, public CView
{
    Q_OBJECT

public:


    explicit HVACFrontView(QWidget *parent = 0);
    ~HVACFrontView();

    virtual void viewAction(int state);

    void InitHVACFrontView();

    void InitHvacIndication();

    void InitConnect();


    void FrontHairModeSelect(bool isSelect);
    void FrontBelowHairModeSelect(bool isSelect);
    void BelowHairModeSelect(bool isSelect);
    void DefrostingModeSelect(bool isSelect);

public slots:
    void OnLeftAddTemperature();
    void OnLeftSubTemperature();
    void OnRightAddTemperature();
    void OnRightSubTemperature();
    void OnTitleFront();
    void OnTitleReart();

    void OnHairModeSelect(int);
    void OnSubAirVolume();
    void OnAddAirVolume();
    void OnAirVolumeDataSlider(int);
    void OnHvacModeSelect(int);

private:
    int m_iHvacZone;
    int m_iLeftTemperature;
    int m_iRightTemperature;
    int m_iTemperatureMin;
    int m_iTemperatureMax;
    int m_iAirVolume;
    int m_HvacMode;
    CPushButton* m_pLeftAddTemperatureBtn;
    CPushButton* m_pLeftSubTemperatureBtn;
    QLabel *m_LeftTemperatureDataLabel;

    CPushButton* m_pRightAddTemperatureBtn;
    CPushButton* m_pRightSubTemperatureBtn;
    QLabel *m_RightTemperatureDataLabel;

    QLabel *m_pTitleBlueLineLabel;
    QLabel *m_pTitleWhiteLineLabel;
    CPushButton* m_pTitleFrontBtn;
    CPushButton* m_pTitleReartBtn;


    QButtonGroup *m_pHairModeGroup;
    CPushButton* m_pFrontHairModeBtn;
    CPushButton* m_pFrontBelowHairModeBtn;
    CPushButton* m_pBelowHairModeBtn;
    CPushButton* m_pDefrostingModeBtn;

    CPushButton* m_pSubAirVolumeBtn;
    CPushButton* m_pAddAirVolumeBtn;
    CSlider *m_pAirVolumeDataSlider;


    QButtonGroup *m_pHVACModeGroup;
    CPushButton* m_pPowerBtn;
    CPushButton* m_pSyncingBtn;
    CPushButton* m_pAutoBtn;
    CPushButton* m_pACBtn;
    CPushButton* m_pCycleModeBtn;



};

#endif // HVACFRONTVIEW_H
