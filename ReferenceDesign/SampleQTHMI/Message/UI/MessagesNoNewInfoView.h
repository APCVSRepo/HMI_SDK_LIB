#ifndef MESSAGESNONEWINFOVIEW_H
#define MESSAGESNONEWINFOVIEW_H
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
#include "Message/app/Message.h"
#include "HMIWidgets/CPushButton.h"
#include <QLabel>
#include <QButtonGroup>
#include <QLineEdit>
#include "HMIWidgets/CVListWidget.h"
#include <QDate>
#include <QDateTime>
class MessagesNoNewInfoView:public QWidget, public CView
{
    Q_OBJECT

public:


    explicit MessagesNoNewInfoView(QWidget *parent = 0);
    ~MessagesNoNewInfoView();

    virtual void viewAction(int state);

    void InitMessagesNoNewInfoView();

    void InitConnect();

    void UpdataData();

public slots:

    void OnBack();
private:
    CPushButton *m_pBackBtn;

    QLabel          *m_pTitleLabel;
    QLabel          *m_pLineLabel;
    QLabel          *m_pContextLabel1;
    QLabel          *m_pContextLabel2;

};

#endif // MESSAGESNONEWINFOVIEW_H
