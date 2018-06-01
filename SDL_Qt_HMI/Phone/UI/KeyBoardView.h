#ifndef KEYBOARDVIEW_H
#define KEYBOARDVIEW_H
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
class KeyBoardView:public QWidget, public CView
{
    Q_OBJECT

public:


    explicit KeyBoardView(QWidget *parent = 0);
    ~KeyBoardView();

    virtual void viewAction(int state);

    void InitKeyBoardView();

    void InitConnect();

public slots:
    void OnKeyBoard(int Id);
    void OnDeleteLongPress();
    void OnTextChange(QString text);

    void OnContacts();
    void OnRecents();
    void OnBTSetting();
private:
    QString m_InputText;
    CPushButton*    m_pKeyboard;
    CPushButton*    m_pContacts;
    CPushButton*    m_pCRecents;
    CPushButton*    m_pBTSetting;

    QLabel*         m_pWhiteLineLabel;
    QLabel*         m_pBlueLineLabel;
    QLabel*         m_pNumberInputLabel;
    QLineEdit*      m_pNumberInput;


    QButtonGroup*   m_pBtttonGroup;
    CPushButton*    m_pNumber0;
    CPushButton*    m_pNumber1;
    CPushButton*    m_pNumber2;
    CPushButton*    m_pNumber3;
    CPushButton*    m_pNumber4;
    CPushButton*    m_pNumber5;
    CPushButton*    m_pNumber6;
    CPushButton*    m_pNumber7;
    CPushButton*    m_pNumber8;
    CPushButton*    m_pNumber9;

    CPushButton*    m_pNumberDelete;
    CPushButton*    m_pNumberDial;
    CPushButton*    m_pNumbercStarSymbol;
    CPushButton*    m_pNumberdWellSymbol;
    CVListWidget*   m_pMatchContactsList;

};

#endif // KEYBOARDVIEW_H
