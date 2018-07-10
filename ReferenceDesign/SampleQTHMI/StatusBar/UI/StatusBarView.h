#ifndef STATUSBARVIEW_H
#define STATUSBARVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTime>
#include <QTimer>
#include <QHBoxLayout>
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CPushButton.h"
#include "HMIWidgets/CRotationWidget.h"

class StatusBarView : public QWidget, public CView
{
    Q_OBJECT
public:
    explicit StatusBarView(QWidget *parent = 0);
    ~StatusBarView();

    void SetBTStatus(bool visible);
    void SetMessageStatus(bool visible, int count = 0);
    void SetWifiStatus(bool visible);
    void SetUSBStatus(bool visible);
    //CView interface
    virtual void viewAction(int state);
signals:

public slots:
    void OnHomeBtnClicked();
    void OnVRClicked();
    void OnTimeUpdate();

    //data change
    void OnLoadingStatusChanged(bool status);
    void OnTemperatureChanged(int temperature);
    void OnTemperatureUnitChanged(bool isCelsius);
    void OnIconStatusChanged(int type, bool active, int count);

private:
    void UpdateTemperature();

private:
    QLabel *m_pBackgroundLabel;
    CPushButton *m_pHomeBtn;
    CPushButton *m_pVRBtn;

    QLabel *m_pBTIcon;
    QLabel *m_pMsgIcon;
    QLabel *m_pMsgCount;
    QLabel *m_pWifiIcon;
    QLabel *m_pUSBIcon;
    QHBoxLayout *m_pStatusLayout;
    QWidget *m_pStatusWidget;

    QLabel *m_pSlash1;
    CRotationWidget *m_pLoadingIcon;
    QWidget *m_pLoadingWidget;
    QLabel *m_pSlash2;
    QLabel *m_pTemperatureIcon;
    QLabel *m_pTemperature;
    QLabel *m_pSlash3;

    QLabel *m_pTimeLabel;
    QTimer *m_pTimer;

    int m_iCurrentTemperature;  //in Celsius
    bool m_bUnitCelsius;
    bool m_bIsLoading;
};

#endif // STATUSBARVIEW_H
