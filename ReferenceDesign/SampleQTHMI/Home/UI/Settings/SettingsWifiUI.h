#ifndef SETTINGSWIFIUI_H
#define SETTINGSWIFIUI_H

#include <QWidget>
#include <QLabel>
#include "HMIWidgets/CVListWidget.h"
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CPushButton.h"
class SettingsWifiUI : public QWidget ,public CView
{
    Q_OBJECT

    enum eWifiStatus{
        WIFI_OFF = 0,
        WIFI_ON = 1
    };
public:
    explicit SettingsWifiUI(QWidget *parent = 0);
    ~SettingsWifiUI();
    virtual void viewAction(int state);
signals:
    void SigWifiStatusChanged(int status);  //OFF:0, ON:1

public slots:
    void OnBack();
    void OnListButtonReleased(int index, int btnIndex);
    void OnListButtonReleased(int index, int btnIndex, int specifiedID);
    void OnListItemClicked(int index, int specifiedID);
    void OnWifiStatusChanged(int status);
    void OnWifiListUpdate();

private:
    void SetWifiStatus(int status, bool init = false);
    void StartWifi();
    void UpdateWifiList();

private:
    CPushButton *m_pBackBtn;
    QLabel* m_pTitleLabel;

    CVListWidget* m_pVlist;
    int m_iWifiStatus;
};

#endif // SETTINGSWIFIUI_H
