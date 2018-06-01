#ifndef POPUPBASE_H
#define POPUPBASE_H

#include <QWidget>
#include <map>
#include <iostream>
using namespace std;
class PopUpBase : public QWidget
{
    Q_OBJECT
public:
    explicit PopUpBase(QWidget *parent = 0);
    void Parse(map<string, string> parameter);
    QString GetPopUpId();
    QString GetPopupType();
    QString GetPopUpShow();
    QString GetPopUpTitle();
    QString GetPopUpContextA();
    QString GetPopUpContextB();
    QString GetPopUpContextALight();
    QString GetPopUpContextBLight();
    QString GetPopUpButtonA();
    QString GetPopUpButtonB();
    QString GetPopUpReplyButtonA();
    QString GetPopUpReplyButtonB();
    QString GetPopUpHandle();
    int GetPopUpTime();
    QString GetFromeAppId();

    bool IsExistPopUpId();
    bool IsExistPopupType();
    bool IsExistPopUpShow();
    bool IsExistPopUpTitle();
    bool IsExistPopUpContextA();
    bool IsExistPopUpContextB();
    bool IsExistPopUpContextALight();
    bool IsExistPopUpContextBLight();
    bool IsExistPopUpButtonA();
    bool IsExistPopUpButtonB();
    bool IsExistPopUpReplyButtonA();
    bool IsExistPopUpReplyButtonB();
    bool IsExistPopUpHandle();
    bool IsExistPopUpTime();
    bool IsExistFromAppId();

    void Release();

    virtual void Finish();
signals:

public slots:

private:
    QString m_PopUpId;
    QString m_PopupType;
    QString m_PopUpShow;
    QString m_PopUpTitle;
    QString m_PopUpContextA;
    QString m_PopUpContextB;
    QString m_PopUpContextALight;
    QString m_PopUpContextBLight;
    QString m_PopUpButtonA;
    QString m_PopUpButtonB;
    QString m_PopUpReplyButtonA;
    QString m_PopUpReplyButtonB;
    QString m_PopUpHandle;
    QString m_PopUpTime;

    QString m_fromAppId;

    bool m_bPopUpId;
    bool m_bPopUpType;
    bool m_bPopUpShow;
    bool m_bPopUpTitle;
    bool m_bPopUpContextA;
    bool m_bPopUpContextB;
    bool m_bPopUpContextALight;
    bool m_bPopUpContextBLight;
    bool m_bPopUpButtonA;
    bool m_bPopUpButtonB;
    bool m_bPopUpReplyButtonA;
    bool m_bPopUpReplyButtonB;
    bool m_bPopUpHandle;
    bool m_bPopUpTime;
    bool m_bFromAppId;

};

#endif // POPUPBASE_H
