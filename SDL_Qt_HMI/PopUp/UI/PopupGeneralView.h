#ifndef POPUPGENERALVIEW_H
#define POPUPGENERALVIEW_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "HMIFrameWork/CView.h"
#include <QTimer>
#include "PopUpBase.h"
//131 32
//189 32
//800
//800 -131  670 /2 335
#define BTN_B


class PopupGeneralView : public PopUpBase
{
    Q_OBJECT
public:
    enum ePopupStyle{
        PopupStyle_Default,
        PopupStyle_Title
    };

    enum eButtonStyle{
        ButtonStyle_None,
        ButtonStyle_BtnA,
        ButtonStyle_BtnB,
        ButtonStyle_BtnAS,
        ButtonStyle_BtnBS,
        ButtonStyle_BtnABS
    };
    explicit PopupGeneralView(QWidget *parent = 0);
    void AddTitle(const QString& title);
    void AddContextA(const QString& text);
    void AddContextALight(const QString& text);
    void AddContextB(const QString& text);
    void AddContextBLight(const QString& text);
    void AddBtnA(const QString& text);
    void AddBtnB(const QString& text);
    void AddTimer(int time);
    void AddHandle(const QString& text);

    void Show();
    virtual void Finish();
    void DrawContextA(QString context, QString light);
    void DrawContextB(QString context, QString light);
    void HighLightText(QString light);
signals:
    void SigTimerOut(const QString& Id);
    void SigButtonClick(const QString& Id,const QString& replayInfo);
public slots:
    void OnTimer();
    void OnButtonA();
    void OnButtonB();
private:
    QLabel *m_pBackgroundLabel;
    QLabel *m_pLineTop;
    QLabel *m_pLineBottom;
    QLabel *m_TitleLabel;
    QVBoxLayout *m_pVDisplayAreaLayout;
    QHBoxLayout *m_pHDisplayAreaLayout;
    QWidget *m_pVDisplayArea;
    QWidget *m_pHDisplayArea;

    QTextEdit *m_pText;
//    QLabel *m_pMsg;
    QPushButton *m_pBtnA;
    QPushButton *m_pBtnB;
    eButtonStyle m_buttonStyle;
    ePopupStyle m_popupStyle;
    int m_itime;
    QTimer m_timer;
};

#endif // POPUPGENERALVIEW_H
