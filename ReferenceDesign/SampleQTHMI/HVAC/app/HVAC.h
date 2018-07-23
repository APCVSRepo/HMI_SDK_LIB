#ifndef HVAC_H
#define HVAC_H

#include "HMIFrameWork/App.h"
#include "HVAC/UI/HVACFrontView.h"
#include <QWidget>
#include "HMIFrameWork/AppConfig.h"
#include "HVAC/Factory/HVACVFactory.h"
#include <QObject>

#define HVAC_FRONT_SIGLE_ZONE 1
#define HVAC_FRONT_LEFT_RIGHT_ZONE 2
#define HVAC_FRONT_REAR_ZONE 3
#define HVAC_FRONT_LEFT_RIGRT_AND_REAR_ZONE 4


enum eHairMode{
    eFrontHairMode,
    eFrontBelowHairMode,
    eBelowHairMode,
    eDefrostingMode
};

enum eHVACMode
{
    eHVACModePower,
    eHVACModeSYNC,
    eHVACModeAuto,
    eHVACModeAC,
    eHVACModeCycle
};

enum eHVACCirculationMode
{
    eInernalCirculation,
    eExternalCirculation,
    eAutoCirculation
};

class HVAC:public QObject,public App
{
    Q_OBJECT
private:
        HVAC();
public:
    enum eViewId{
        eViewId_Front_On,
        eViewId_Front_Off,
        eViewId_Rear_On,
        eViewId_Rear_Off
    };

    static HVAC* Inst();

    void onAppShow(string appId,string viewId) ;
    void onAppHide();
    void onNotify(string appId, map<string, string> parameter);
    void onReply(string appId, map<string, string> parameter);

public slots:
    void OnAppShow(string appId,string viewId);
    void OnAppHide();
    void OnNotify(string appId, map<string, string> parameter);
    void OnReply(string appId, map<string, string> parameter);

public:signals:
    void SigAppShow(string appId,string viewId);
    void SigAppHide();
    void SigNotify(string appId, map<string, string> parameter);
    void SigReply(string appId, map<string, string> parameter);

    void SigQuickMove(QString type);
private:
    static HVAC *m_pInst;
};

#endif // HVAC_H
