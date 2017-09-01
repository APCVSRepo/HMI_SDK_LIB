#ifndef ALERTVIEW_H
#define ALERTVIEW_H

#include <QWidget>
#include <QLabel>
#include <Common/CustomButton.h>
#include "Common/AppBase.h"

class AlertView : public QWidget
{
    Q_OBJECT
public:
    explicit AlertView(AppListInterface *pList,QWidget *parent = 0);
    ~AlertView();

protected:
    void showEvent(QShowEvent * e);
signals:

public slots:
    void OnSoftBtnClicked(int iSoftBtnID);
    void OnTimeOut();
private:
    QLabel *m_pAppNameLab;
    QLabel m_aAlertLab[3];
    CCustomButton m_aSoftBtn[6];

    AppListInterface *m_pList;

    QTimer m_Timer;
};

#endif // ALERTVIEW_H
