#ifndef MESSAGELISTVIEW_H
#define MESSAGELISTVIEW_H
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
class MessageListView:public QWidget, public CView
{
    Q_OBJECT

public:


    explicit MessageListView(QWidget *parent = 0);
    ~MessageListView();

    virtual void viewAction(int state);

    void InitMessageListView();

    void InitConnect();

    void UpdataData();

    void AddOneMessage();
public slots:
    void OnBack();

    void OnListClick(int);
    void OnPhoneNumberClick(QString);
private:
    CPushButton     *m_pBackBtn;
    QLabel          *m_pTitleLabel;
    QLabel          *m_pLineLabel;

    CVListWidget    *m_pMessagesList;


};

#endif // MESSAGELISTVIEW_H
