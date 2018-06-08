#ifndef RECENTSVIEW_H
#define RECENTSVIEW_H
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
#include <QDate>
#include <QDateTime>
class RecentsView:public QWidget, public CView
{
    Q_OBJECT

public:


    explicit RecentsView(QWidget *parent = 0);
    ~RecentsView();

    virtual void viewAction(int state);

    void InitRecentsView();

    void InitConnect();

    void UpdataData();

    int DiddDays(QDate  destDate, QDate CompareDate);
public slots:
    void OnKeyBoard();
    void OnContants();
    void OnBTSetting();

    void OnListClick(int);
private:
    QString m_InputText;
    CPushButton*    m_pKeyboard;
    CPushButton*    m_pContacts;
    CPushButton*    m_pCRecents;
    CPushButton*    m_pBTSetting;

    QLabel*         m_pWhiteLineLabel;
    QLabel*         m_pBlueLineLabel;

    CVListWidget*   m_pRecentsList;

};

#endif // RECENTSVIEW_H
