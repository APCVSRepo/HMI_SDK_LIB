#ifndef MESSAGESVIEW_H
#define MESSAGESVIEW_H
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
class MessagesView:public QWidget, public CView
{
    Q_OBJECT

public:


    explicit MessagesView(QWidget *parent = 0);
    ~MessagesView();

    virtual void viewAction(int state);

    void InitMessagesView();

    void InitConnect();

    void UpdataData();

    QString toWeek(int week);
public slots:

    void OnBack();
    void OnListClick(int);
private:
    CPushButton *m_pBackBtn;


    CVListWidget*   m_pMessagesList;

};

#endif // MESSAGESVIEW_H
