#ifndef SETTINGSBTUI_H
#define SETTINGSBTUI_H

#include <QWidget>
#include <QLabel>
#include "HMIWidgets/CVListWidget.h"
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CPushButton.h"

class SettingsBTUI : public QWidget , public CView
{
    Q_OBJECT

    enum eBTStatus{
        BT_OFF = 0,
        BT_ON = 1
    };
public:
    explicit SettingsBTUI(QWidget *parent = 0);
    ~SettingsBTUI();
    virtual void viewAction(int state);
signals:
    void SigBTStatusChanged(int status);  //OFF:0, ON:1

public slots:
    void OnBack();
    void OnListButtonReleased(int index, int btnIndex);
    void OnListButtonReleased(int index, int btnIndex, int specifiedID);
    void OnListItemClicked(int index, int specifiedID);
    void OnBTStatusChanged(int status);

    void OnDeviceListUpdate();

private:
    void SetBTStatus(int status, bool init = false);
    void StartBT();
    void UpdateBTList();

    void ShowPopUpPair();
    void ShowPopUpDisConnect();
    void ShowPopUpRemoveFromPairdList();

private:
    CPushButton *m_pBackBtn;
    QLabel* m_pTitleLabel;
    CVListWidget* m_pVlist;
    int m_iBTStatus;

};

#endif // SETTINGSBTUI_H
