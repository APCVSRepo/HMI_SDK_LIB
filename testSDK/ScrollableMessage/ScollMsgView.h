#ifndef SCOLLMSGVIEW_H
#define SCOLLMSGVIEW_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include "Common/CustomButton.h"
#include "Common/AppBase.h"

class CScollMsgView : public QWidget
{
    Q_OBJECT
public:
    explicit CScollMsgView(AppListInterface *pList,QWidget *parent = 0);
    ~CScollMsgView();
protected:
    void showEvent(QShowEvent * e);
signals:

public slots:
    void OnTimeOutSlot();
    void OnReturnBtnClicked();
    void OnSoftBtnClicked(int iBtnId);
private:
    void SetTimeOut(int iDuration);

    AppListInterface *m_pList;

    QTimer *m_pTimer;
    CCustomButton *m_pReturnBtn;
    QLabel *m_pAppNameLab;
    CCustomButton *m_pSoftBtn;
    QTextEdit *m_pText;
};

#endif // SCOLLMSGVIEW_H
