#ifndef CCBUTTON_H
#define CCBUTTON_H
#include <QWidget>
#include <QMouseEvent>
#include <QTouchEvent>
#include <QTimer>
#include <QList>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QPainter>
#include <HMIFrameWork/log_interface.h>
#include <QCoreApplication>

class CCButton:public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double opacity READ getOpacity WRITE setOpacity)
    Q_PROPERTY(QPoint position READ getPosition WRITE setPosition)
    Q_PROPERTY(QPoint ParentPosition READ getParentPosition WRITE setParentPosition)
    Q_PROPERTY(QSize size READ getSize WRITE setSize)
public:
    struct CCBtnInfo
    {
        QString Type;
        QString IconPath;
        QString Name;
        QString BgPath;
        QString EditPath;
        QString NormalPath;
        QString PushedPath;
        QString Text;
        int     Index;
    };
    enum ViewStatus
    {
        ViewStatusUnknow,
        ViewStatusNormal,
        ViewStatusPushed,
        ViewStatusInactive
    };
    CCButton(QWidget *parent = NULL);
    ~CCButton();
    void SetAppGeometry(QRect rect);
    void SetViewRect(QRect rect);
    void InsertEditStyle(QRect rect,QString EditStyle);
    void InsertNormalStyle(QRect rect,QString NormalStyle);
    void InsertPushStyle(QRect rect,QString PushStyle);
    void InsertIconStyle(QRect rect,QString IconStyle);
    void InsertEditStyle(QString EditStyle);
    void InsertNormalStyle(QString NormalStyle);
    void InsertPushStyle(QString PushStyle);
    void InsertIconStyle(QString IconStyle);
    void InsertText(QRect rect,QString text,bool midFlag = false,Qt::Orientation eOrientation = Qt::Horizontal);
    void InsertName(QString Name);
    void InsertType(QString Type);
    void SetIndex(int index);

    QRect GetViewRect();

    QString GetEditStyle();
    QString GetNormalStyle();
    QString GetPushStyle();
    QString GetIconStyle();
    QRect GetEditStyleRect();
    QRect GetNormalStyleRect();
    QRect GetPushStyleRect();
    QRect GetIconStyleRect();

    void UpdateText(QString text,bool IsUpdate=false);
    void UpdateInfo(CCBtnInfo btnInfo);
    void UpdateType(QString type);
    void UpdateIconStyle(QString style);
    void UpdateName(QString name);
    void UpdateBgStyle(QString style);
    void UpdateEditStyle(QString style);
    void UpdateNormalStyle(QString style);
    void UpdatePushStyle(QString style);

    QString GetText();
    QString GetName();
    QString GetType();
    int     GetIndex();
    QRect GetTextRect();

    void SetEditStatus(bool isEditStatus);
    void SetViewStatus(ViewStatus status);
    void SetIsPress(bool IsPress);

    void OpacityAnimation(double start, double end,int time,bool IsHide=false);
    void MoveAnimation(const QPoint startPos, const QPoint endPos,int time,bool IsHide = false);
    void MoveParentAnimation(const QPoint startPos, const QPoint endPos,int time,bool IsHide = false);
    void SizeAnimation(const QSize start, const QSize end,int time,bool IsHide=false);
    bool GetIsEndAnimation();

    QPoint GetGlobalPos(const QPoint currPos);

    CCBtnInfo GetInfo();
public slots:
    void OnOpacityAnimationFinished();
    void AnimationFinished();
    void MoveAnimationFinished();
    void MoveParentAnimationFinished();
public:signals:
    void MoveParentFinish(int index);
    void MoveAppFinish(int index);
protected:
    void paintEvent(QPaintEvent* event);
    bool eventFilter(QObject *, QEvent *);
private:
    double getOpacity();
    void setOpacity(double opacity);
    QSize getSize();
    void setSize(QSize size);
    QPoint getPosition();
    void setPosition(QPoint position);

    QPoint getParentPosition();
    void setParentPosition(QPoint ParentPosition);
 private:
    QPropertyAnimation* m_pOpacityAnimation;
    QGraphicsOpacityEffect* m_pEffect;
    QPropertyAnimation* m_pMoveAnimation;
    QPropertyAnimation* m_pMoveParentAnimation;
    QPropertyAnimation* m_pSizeAnimation;
    QRect m_viewRect;
    QString m_editStyle;
    QString m_normalStyle;
    QString m_pushStyle;
    QString m_iconStyle;
    QString m_text;
    QString m_updateText;
    bool    m_bmidFlag;
    bool    m_bIsUpdateText;
    Qt::Orientation m_eTextOrientation;
    QRect m_EditStyleRect;
    QRect m_NormalStyleRect;
    QRect m_PushStyleRect;
    QRect m_IconStyleRect;
    QRect m_textRect;
    QString m_name;
    QString m_type;
    int m_iIndex;
    bool m_bIsEditStatus;
    bool m_IsPress;
    ViewStatus m_ViewStatus;
    bool m_AppIsHide;
    bool m_IsEndAnimation;
    int m_iPosX;
    int m_iPosY;
    QSize m_DiffSize;
    CCBtnInfo m_Info;
};

#endif // CCBUTTON_H
