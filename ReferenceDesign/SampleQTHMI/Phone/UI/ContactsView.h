#ifndef CONTACTSVIEW_H
#define CONTACTSVIEW_H
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
#include "HMIWidgets/PhonePicker.h"


class ContactsView:public QWidget, public CView
{
    Q_OBJECT

public:


    explicit ContactsView(QWidget *parent = 0);
    ~ContactsView();

    virtual void viewAction(int state);

    void InitContactsView();

    void InitConnect();

    void UpdateData();

public slots:
    void OnKeyBoard();
    void OnRecents();
    void OnBTSetting();
    void OnListClick(int index);

    void OnPhonePickerClick(int index,QString text);
private:
    QString         m_InputText;
    CPushButton*    m_pKeyboard;
    CPushButton*    m_pContacts;
    CPushButton*    m_pCRecents;
    CPushButton*    m_pBTSetting;

    QLabel*         m_pWhiteLineLabel;
    QLabel*         m_pBlueLineLabel;

    CVListWidget*   m_pContactsList;
    PhonePicker*    m_pPhonePickerSelect;
    QLabel*         m_pPhonePickerSelectLabel;

};

#endif // CONTACTSVIEW_H
