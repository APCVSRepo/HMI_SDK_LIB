#ifndef ALERTVIEW_H
#define ALERTVIEW_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include "SDLApps/Templates/Common/AppBase.h"
#include "SDLApps/Templates/Common/Button.h"

#define MAX_BTN_NUM 4

class AlertView : public QWidget {
    Q_OBJECT

public:
    explicit AlertView(AppListInterface *pList, QWidget *parent = 0);
    ~AlertView();

protected:
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *);

signals:

public slots:
    void OnSoftBtnClicked(int iSoftBtnID);
    void OnTimeOut();

private:
    void setSoftButtons(std::vector<SSoftButton> vec_softButtons);

private:
    QLabel *m_pAppNameLab;
    QLabel m_aAlertLab[3];
    CButton m_aSoftBtn[MAX_BTN_NUM];
    std::vector <SSoftButton> m_vSoftButtons;

    AppListInterface *m_pList;

    QTimer m_Timer;

    QLabel *m_pBackground;
    QLabel *m_pLineTop;
    QLabel *m_pLineBottom;
    QWidget *m_pPopUpArea;
};

#endif // ALERTVIEW_H
