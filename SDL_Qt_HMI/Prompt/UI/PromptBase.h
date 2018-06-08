#ifndef PROMPTBASE_H
#define PROMPTBASE_H

#include <QWidget>
#include <map>
#include <iostream>
using namespace std;
class PromptBase : public QWidget
{
    Q_OBJECT
public:
    explicit PromptBase(QWidget *parent = 0);
    void Parse(map<string, string> parameter);
    QString GetPromptId();
    QString GetPromptType();
    QString GetPromptShow();
    QString GetPromptTitle();
    QString GetPromptContextA();
    QString GetPromptContextB();
    QString GetPromptContextALight();
    QString GetPromptContextBLight();
    QString GetPromptButtonA();
    QString GetPromptButtonB();
    QString GetPromptReplyButtonA();
    QString GetPromptReplyButtonB();
    QString GetPromptHandle();
    int GetPromptTime();
    //message
    QString GetPromptMessageName();
    QString GetPromptMessageTime();
    QString GetPromptMessageContent();

    //Nav
    QString GetPromptNavDirection();
    QString GetPromptNavDistance();
    QString GetPromptNavSceneDescription();
    QString GetPromptNavDestination();

    QString GetFromeAppId();

    bool IsExistPromptId();
    bool IsExistPromptType();
    bool IsExistPromptShow();
    bool IsExistPromptTitle();
    bool IsExistPromptContextA();
    bool IsExistPromptContextB();
    bool IsExistPromptContextALight();
    bool IsExistPromptContextBLight();
    bool IsExistPromptButtonA();
    bool IsExistPromptButtonB();
    bool IsExistPromptReplyButtonA();
    bool IsExistPromptReplyButtonB();
    bool IsExistPromptHandle();
    bool IsExistPromptTime();
    bool IsExistFromAppId();
    //message
    bool IsExistPromptMessageName();
    bool IsExistPromptMessageTime();
    bool IsExistPromptMessageContent();

    //Nav
    bool IsExistPromptNavDirection();
    bool IsExistPromptNavDistance();
    bool IsExistPromptNavSceneDescription();
    bool IsExistPromptNavDestination();

    void Release();

    virtual void Finish();
signals:

public slots:

private:
    QString m_PromptId;
    QString m_PromptType;
    QString m_PromptShow;
    QString m_PromptTitle;
    QString m_PromptContextA;
    QString m_PromptContextB;
    QString m_PromptContextALight;
    QString m_PromptContextBLight;
    QString m_PromptButtonA;
    QString m_PromptButtonB;
    QString m_PromptReplyButtonA;
    QString m_PromptReplyButtonB;
    QString m_PromptHandle;
    QString m_PromptTime;
    //message
    QString m_PromptMessageName;
    QString m_PromptMessageTime;
    QString m_PromptMessageContent;

    //Nav
    QString m_PromptNavDirectionIcon;
    QString m_PromptNavDistance;
    QString m_PromptNavSceneDescription;
    QString m_PromptNavDestination;

    QString m_fromAppId;

    bool m_bPromptId;
    bool m_bPromptType;
    bool m_bPromptShow;
    bool m_bPromptTitle;
    bool m_bPromptContextA;
    bool m_bPromptContextB;
    bool m_bPromptContextALight;
    bool m_bPromptContextBLight;
    bool m_bPromptButtonA;
    bool m_bPromptButtonB;
    bool m_bPromptReplyButtonA;
    bool m_bPromptReplyButtonB;
    bool m_bPromptHandle;
    bool m_bPromptTime;
    bool m_bFromAppId;

    //message
    bool m_bPromptMessageName;
    bool m_bPromptMessageTime;
    bool m_bPromptMessageContent;


    //Nav
    bool m_bPromptNavDirectionIcon;
    bool m_bPromptNavDistance;
    bool m_bPromptNavSceneDescription;
    bool m_bPromptNavDestination;


};

#endif // PROMPTBASE_H
