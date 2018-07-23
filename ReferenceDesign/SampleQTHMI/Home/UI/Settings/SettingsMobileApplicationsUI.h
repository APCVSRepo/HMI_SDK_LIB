#ifndef SETTINGSMOBILEAPPLICATIONSUI_H
#define SETTINGSMOBILEAPPLICATIONSUI_H

#include <QWidget>
#include "HMIWidgets/CVListWidget.h"
#include <QLabel>
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CPushButton.h"
class SettingsMobileApplicationsUI : public QWidget,public CView
{
    Q_OBJECT

public:
    explicit SettingsMobileApplicationsUI(QWidget *parent = 0);
    ~SettingsMobileApplicationsUI();
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

#endif // SETTINGSMOBILEAPPLICATIONSUI_H
