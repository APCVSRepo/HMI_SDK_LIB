#ifndef SETTINGSEMERGENCYUI_H
#define SETTINGSEMERGENCYUI_H

#include <QWidget>
#include "HMIWidgets/CVListWidget.h"
#include <QLabel>
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CPushButton.h"
class SettingsEmergencyUI : public QWidget,public CView
{
    Q_OBJECT

public:
    explicit SettingsEmergencyUI(QWidget *parent = 0);
    ~SettingsEmergencyUI();
    virtual void viewAction(int state);

    void InitConnect();
public slots:
    void OnBack();
    void OnListBtnClick(int,int);
    void OnListClick(int);
private:
    CPushButton *m_pBackBtn;
    QLabel* m_pTitleLabel;
    CVListWidget* m_pVList;
    QLabel *m_pBackgroundLabel;
};

#endif // SETTINGSEMERGENCYUI_H
