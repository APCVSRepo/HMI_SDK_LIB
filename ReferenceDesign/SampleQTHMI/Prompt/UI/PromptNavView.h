#ifndef PROMPTNAVVIEW_H
#define PROMPTNAVVIEW_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "HMIFrameWork/CView.h"
#include <QTimer>
#include "PromptBase.h"
//131 32
//189 32
//800
//800 -131  670 /2 335
#define BTN_B

class PromptNavView : public PromptBase
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
    explicit PromptNavView(QWidget *parent = 0);
    ~PromptNavView();
    void AddTitle(const QString& title);
    void AddContextA(const QString& text);
    void AddContextALight(const QString& text);
    void AddContextB(const QString& text);
    void AddContextBLight(const QString& text);
    void AddBtnA(const QString& text);
    void AddBtnB(const QString& text);
    void AddTimer(int time);
    void AddHandle(const QString& text);
    void AddNavDirection(const QString& text);
    void AddNavDistance(const QString& text);
    void AddNavSceneDescription(const QString& text);
    void AddNavDestination(const QString& text);
    void UpdatePosition();


    void Show();
    virtual void Finish();
    void DrawContextA(QString context, QString light);
    void DrawContextB(QString context, QString light);
    void HighLightText(QString light);
    QString geteElidedText(QFont font, const QString& text, int MaxWidth);
    int getTextWidth(QFont font, const QString& text);

signals:
    void SigTimerOut(const QString& Id);
    void SigButtonClick(const QString& Id,const QString& replayInfo);
public slots:
    void OnTimer();
    void OnButtonA();
private:
    QLabel *m_pNavDirectionIconLabel;
    QLabel *m_pNavDistanceLabel;
    QLabel *m_pNavSceneDescriptionLabel;
    QLabel *m_pNavDestinationLabel;

    QPushButton *m_pBtnA;
    int m_itime;
    QTimer m_timer;
};


#endif // PROMPTNAVVIEW_H
