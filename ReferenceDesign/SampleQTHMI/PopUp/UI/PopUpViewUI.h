#ifndef PopUpViewUI_H
#define PopUpViewUI_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include "HMIFrameWork/CView.h"
#include "PopupGeneralView.h"
#include "PopUpBase.h"
#include <QList>
class PopUpViewUI : public QWidget, public CView
{
    Q_OBJECT
public:
    explicit PopUpViewUI(QWidget *parent = 0);
    ~PopUpViewUI();

    //CView interface
    virtual void viewAction(int state);



private:
    void CreatePopUp(QString& type,map<string, string> parameter);
    PopUpBase* GetPopUp(QString& Id );
    void Parse(map<string, string> parameter);

    void ReleasePopup(const QString& Id);

    void PopUpHide();
    void Replay(const QString& PopUpId,const QString& info);
   // string
signals:

public slots:
    void OnTimerOut(const QString& Id);
    void OnButtonClick(const QString& Id,const QString& replayInfo);
    void OnPopUpNotify(string appId,map<string, string> parameter);
private:
    PopupGeneralView *m_pPopupGeneralView;
    QList <PopUpBase*> PopupList;

    //PopUpId ,PopupType ,Show ,Title,ContextA,ContextB,ContextALight,ContextBLight,
    //ButtonA,ButtonB,ReplyButtonA,ReplyButtonB ,Time ,Handle

};

#endif // PopUpViewUI_H
