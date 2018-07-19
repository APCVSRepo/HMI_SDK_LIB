#ifndef SETTINGSDISPLAYUI_H
#define SETTINGSDISPLAYUI_H

#include <QWidget>
#include "HMIWidgets/CVListWidget.h"
#include <QLabel>
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CPushButton.h"
#include <QSlider>
class SettingsDisplayUI : public QWidget,public CView
{
    Q_OBJECT

public:
    explicit SettingsDisplayUI(QWidget *parent = 0);
    ~SettingsDisplayUI();
    virtual void viewAction(int state);

    void InitConnect();
public slots:
    void OnBack();
    void OnListBtnClick(int,int);
    void OnListClick(int);
    void OnLuminanceRegulationValue(int);

    void OnAddLuminanceRegulationValue();
    void OnSubLuminanceRegulationValue();
    void OnComboBoxActive(int index,const QString& data);

private:
    CPushButton *m_pBackBtn;
    QLabel* m_pTitleLabel;
    CVListWidget* m_pVlist;
    QLabel *m_pBackgroundLabel;
    QLabel *m_pLuminanceRegulationLabel;

    CPushButton *m_pLeftBtn;
    CPushButton *m_pRightBtn;
    QSlider *m_pLuminanceRegulationSlider;
};

#endif // SETTINGSDISPLAYUI_H
