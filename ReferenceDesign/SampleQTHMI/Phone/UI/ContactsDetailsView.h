#ifndef CONTACTSDETAILSVIEW_H
#define CONTACTSDETAILSVIEW_H
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
class ContactsDetailsView:public QWidget, public CView
{
    Q_OBJECT

public:


    explicit ContactsDetailsView(QWidget *parent = 0);
    ~ContactsDetailsView();

    virtual void viewAction(int state);

    void InitContactsDetailsView();

    void InitConnect();
    void UpdateData();

public slots:
    void OnBack();
    void OnListClick(int);
private:
    CPushButton*    m_pBackBtn;

    QLabel*         m_pPortraitLabel;
    QLabel*         m_pNameLabel;
    CVListWidget*   m_pContactsList;

};

#endif // CONTACTSDETAILSVIEW_H
