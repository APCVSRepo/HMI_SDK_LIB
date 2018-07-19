#ifndef PROMPTViewUI_H
#define PROMPTViewUI_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include "HMIFrameWork/CView.h"
#include "PromptMessageView.h"
#include "PromptNavView.h"
#include "PromptBase.h"
#include <QList>
class PromptViewUI : public QWidget, public CView
{
    Q_OBJECT
public:
    explicit PromptViewUI(QWidget *parent = 0);
    ~PromptViewUI();

    //CView interface
    virtual void viewAction(int state);



private:
    void CreatePrompt(QString& type,map<string, string> parameter);
    PromptBase* GetPrompt(QString& Id );
    void Parse(map<string, string> parameter);

    PromptBase* IsExistPromptMessage();
    PromptBase* IsExistPromptNav();
    void UpdateWindowSize();
    void ReleasePrompt(const QString& Id);

    void PromptHide();
    void Replay(const QString& PromptId,const QString& info);
   // string
signals:

public slots:
    void OnTimerOut(const QString& Id);
    void OnButtonClick(const QString& Id,const QString& replayInfo);
    void OnPromptNotify(string appId,map<string, string> parameter);
private:
    QList <PromptBase*> PromptList;

    //PromptId ,PromptType ,Show ,Title,ContextA,ContextB,ContextALight,ContextBLight,
    //ButtonA,ButtonB,ReplyButtonA,ReplyButtonB ,Time ,Handle

};

#endif // PROMPTViewUI_H
