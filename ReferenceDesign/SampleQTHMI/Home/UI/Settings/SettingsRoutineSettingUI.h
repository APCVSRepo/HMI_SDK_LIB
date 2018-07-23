#ifndef SETTINGSROUTINESETTINGUI_H
#define SETTINGSROUTINESETTINGUI_H

#include <QWidget>
#include "HMIWidgets/CVListWidget.h"
#include <QLabel>
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CPushButton.h"
class SettingsRoutineSettingUI : public QWidget,public CView
{
    Q_OBJECT

public:
    explicit SettingsRoutineSettingUI(QWidget *parent = 0);
    ~SettingsRoutineSettingUI();
    virtual void viewAction(int state);

    void InitConnect();
public slots:
    void OnBack();
    void OnListBtnClick(int,int);
    void OnListClick(int);

    void OnComboBoxActive(int index,int itemIndex);
private:
    CPushButton *m_pBackBtn;
    QLabel* m_pTitleLabel;
    CVListWidget* m_pVList;
    QLabel *m_pBackgroundLabel;
};

#endif // SETTINGSROUTINESETTINGUI_H
