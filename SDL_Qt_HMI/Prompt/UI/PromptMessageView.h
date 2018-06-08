#ifndef PROMPTMESSAGEVIEW_H
#define PROMPTMESSAGEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "HMIFrameWork/CView.h"
#include <QTimer>
#include "PromptBase.h"
#include "HMIWidgets/CPushButton.h"
//131 32
//189 32
//800
//800 -131  670 /2 335
#define BTN_B


class PromptMessageView : public PromptBase
{
    Q_OBJECT
public:
    enum ePromptStyle{
        PromptStyle_Default,
        PromptStyle_Title
    };

    enum eButtonStyle{
        ButtonStyle_None,
        ButtonStyle_BtnA,
        ButtonStyle_BtnB,
        ButtonStyle_BtnAS,
        ButtonStyle_BtnBS,
        ButtonStyle_BtnABS
    };
    explicit PromptMessageView(QWidget *parent = 0);
    ~PromptMessageView();
    void AddTitle(const QString& title);
    void AddContextA(const QString& text);
    void AddContextALight(const QString& text);
    void AddContextB(const QString& text);
    void AddContextBLight(const QString& text);
    void AddBtnA(const QString& text);
    void AddBtnB(const QString& text);
    void AddTimer(int time);
    void AddHandle(const QString& text);
    void AddMessageName(const QString& text);
    void AddMessageTime(const QString& text);
    void AddMessageContent(const QString& text);
    void UpdatePosion(const QPoint& point );


    void Show();
    virtual void Finish();
    void DrawContextA(QString context, QString light);
    void DrawContextB(QString context, QString light);
    void HighLightText(QString light);
    QString geteElidedText(QFont font, const QString& text, int MaxWidth);

signals:
    void SigTimerOut(const QString& Id);
    void SigButtonClick(const QString& Id,const QString& replayInfo);
public slots:
    void OnTimer();
    void OnButtonA();
    void OnButtonB();
private:
    QLabel *m_pNameLabel;
    QLabel *m_pContentLabel;
    QLabel *m_pTimeLabel;
    QLabel *m_pIconLabel;


    CPushButton *m_pVoiceBtn;
    QPushButton *m_pBtnA;
    CPushButton *m_pBtnB;
    int m_itime;
    QTimer m_timer;
};

#endif // PROMPTMESSAGEVIEW_H
