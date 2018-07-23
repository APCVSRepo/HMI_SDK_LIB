#ifndef SETTINGSMAINUI_H
#define SETTINGSMAINUI_H

#include <QWidget>
#include "HMIWidgets/CVListWidget.h"
#include <QLabel>
#include "HMIFrameWork/CView.h"
namespace Ui {
class SettingsMainUI;
}

class SettingsMainUI : public QWidget,public CView
{
    Q_OBJECT

public:
    explicit SettingsMainUI(QWidget *parent = 0);
    ~SettingsMainUI();
    virtual void viewAction(int state);

    void InitConnect();
public slots:
    void OnListBtnClick(int,int);
    void OnListClick(int);

    void OnHour12Or24(bool bHour12Or24);
    void OnLanguageChange(QString language);
    void OnPatternChange(QString pattern);
    void OnMobileApplicationsStatus(QString status);
    void OnEmergencRescueStatus(QString status);
    void OnBTStatusChanged(QString status);
    void OnWifiStatusChanged(QString status);

private:
    CVListWidget* m_pVlist;
    QLabel *m_pBackgroundLabel;
};

#endif // SETTINGSMAINUI_H
