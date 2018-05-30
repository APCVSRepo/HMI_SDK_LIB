#ifndef SETTINGSDATETIMEUI_H
#define SETTINGSDATETIMEUI_H

#include <QWidget>
#include "HMIWidgets/DateTimePicker.h"
#include "HMIWidgets/CPushButton.h"
#include <QLabel>
#include <QDate>
#include <QTime>
#include "HMIWidgets/CVListWidget.h"
#include <QTimer>
#include "HMIFrameWork/CView.h"
class SettingsDateTimeUI : public QWidget , public CView
{
    Q_OBJECT
public:
    explicit SettingsDateTimeUI(QWidget *parent = 0);
    ~SettingsDateTimeUI();
    virtual void viewAction(int state);

    bool GetAmOrPm(int hour);
    int TimeTo12HourClock(int hour);
    void InitConnect();
signals:

public slots:
    void OnBack();
    void OnListBtnRelease(int index,int btnIndex);
    void OnTimer();
private:
    CPushButton *m_pBackBtn;
    QLabel* m_pTitleLabel;

    DateTimePicker *m_pDateTime;

    QLabel* m_pYearLabel;
    QLabel* m_pMonLabel;
    QLabel* m_pDayLabel;
    QLabel* m_pColonLabel;

    CVListWidget* m_pVList;

    QTimer        m_timer;
};

#endif // SETTINGSDATETIMEUI_H
