#ifndef CALLINGVIEW_H
#define CALLINGVIEW_H

#include <QWidget>
#include <QMouseEvent>
#include <QTouchEvent>
#include <QTimer>
#include <QList>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QPainter>
#include <QCoreApplication>
#include "HMIFrameWork/log_interface.h"
#include "HMIWidgets/CCButton.h"
#include "HMIFrameWork/AppConfig.h"
#include "HMIFrameWork/App.h"
#include "HMIFrameWork/CView.h"
#include "HMIWidgets/CPushButton.h"
#include "Phone/app/Phone.h"
#include "HMIWidgets/CPushButton.h"
#include <QLabel>
#include <QButtonGroup>
#include <QLineEdit>
#include "HMIWidgets/CVListWidget.h"

class CallingView:public QWidget, public CView
{
    Q_OBJECT

public:


    explicit CallingView(QWidget *parent = 0);
    ~CallingView();

    virtual void viewAction(int state);

    void InitCallingView();

    void InitConnect();
    void AddCall();
    void UpdateData();
public slots:
    void OnKeyBoard();
    void OnRecents();
    void OnBTSetting();

    void OnHangUp();
    void OnMute();
    void OnReceiver();
private:
    QString m_InputText;
    CPushButton*    m_pKeyboard;
    CPushButton*    m_pContacts;
    CPushButton*    m_pCRecents;
    CPushButton*    m_pBTSetting;

    QLabel*         m_pWhiteLineLabel;
    QLabel*         m_pBlueLineLabel;

    CVListWidget*   m_pContactsList;

    CPushButton*    m_pHangUpBtn;
    CPushButton*    m_pCallBtn;
    CPushButton*    m_pMuteBtn;
    CPushButton*    m_pReceiverBtn;

};

#endif // CALLINGVIEW_H
