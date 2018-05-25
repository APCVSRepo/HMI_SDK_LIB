#ifndef HOMEVIEW_H
#define HOMEVIEW_H
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
#include "QuickLanuch/UI/QuickLanuchView.h"
#include "HMIFrameWork/AppConfig.h"
#include "HMIFrameWork/App.h"
#include "HMIFrameWork/CView.h"

class HomeView:public QWidget, public CView
{
    Q_OBJECT
    Q_PROPERTY(QPoint position READ getPosition WRITE setPosition)

public:
    enum ePressStatus
    {
       PressUnknow,
       PressShort,
       PressLong
    };
    enum eAnimationMode
    {
        eAnimationModeKnown,
        eAnimationModeReplace,
        eAnimationModeSort
    };
    enum eAFlipMode
    {
        eAFlipModeKnown,
        eAFlipModeToNext,
        eAFlipModeTopre
    };
    enum eEditMode
    {
        eEdit_SINGLE,
        eEdit_ALL
    };
    explicit HomeView(QWidget *parent = 0);
    ~HomeView();

    virtual void viewAction(int state);

    void InitHomeView();

    void SetPageSize(QSize size);
    QSize GetPageSize();
    void InsertApp(int index,CCButton*app);
    void InsertAppFinish();
    void SetIsEditStatus(bool isEdit);
    bool GetIsEditStatus();
    void GoToEditStatus();
    void ExitEditStatus();
    void RemoveAll();
    void RemoveSelect(int index);
    void RemoveSelect(QString name);
    void SortByIndex(int index);
    void SortByIndex(int PressIndex,int SelectIndex);
    void SortByIndexNoMove(int PressIndex, int SelectIndex);
    void SortMove();
    void SetViewGeometry(QRect rect);
    void SetCurrentPageNum(int page);

    int GetCurrentPageNum();
    int Index(int x,int y);

    CCButton *GetApp();
    void SetApp(CCButton *app);
    CCButton * SelectedApp(int index);
    CCButton * SelectedApp(int x,int y);
    void SetAnimationMode(eAnimationMode mode);
    eAnimationMode getAnimationMode();
    void AppBtnShadow(CCButton *btn);
    void AppBtnZoom(CCButton *btn);

    void ToNextOrPre(QRect rect);
    void ToNextPage();
    void ToPrePage();
    void ToSelectPage(int page);
    void ToNoAnimationSelectPage(int page);

    void MoveAnimation(const QPoint startPos, const QPoint endPos,int time);

    void UpdateTextByIndex(int index,QString text);
    QList<CCButton*> GetAppList();

    void StartUpTriggerDomain(bool isStartUpTriggerDomain);
    void SetTriggerDomain(QRect r);
    bool IsTriggerDomain(int x,int y);

protected:
    bool MouseEvent(QObject *, QEvent*);
    bool TouchEvent(QObject *, QEvent*);
    bool GestureEvent(QObject *, QEvent*);
    bool eventFilter(QObject *, QEvent *);
private:
    QPoint getPosition();
    void setPosition(QPoint position);
public  slots:
   void PressTimeout();
   void FlipTimeout();
   void OnSortByIndex(int PressIndex,int SelectIndex);
   void OnMoving();
   void OnMoveParentFinish(int index);
   void OnMoveAppFinish(int index);
   void OnQuickMove(QString type);
   void OnEnterTriggerDomainStatus(bool,QString type);

signals:
    void SigRelease(int,QString,QString);
    void SigPageNum(int);
    void SigIsEnterEdit(bool);
    void SigSortByIndex(int PressIndex,int SelectIndex);
    void SigPress(int,QString,QString);
    void SigMovingPos(int x ,int y,QString Type);
    void SigReleasePos(int x,int y,QString Type);
    void SigTriggerDomain(int x,int y,CCButton::CCBtnInfo);
    void SigEnterTriggerDomain(bool,QString type);

public slots:
    void OnAppClick(int,QString,QString);

private:
    CCButton            *m_pAppBtn;
    CCButton            *m_pAppBtnShadow;
    CCButton            *m_pAppBtnZoom;
    QPropertyAnimation  *m_pMoveAnimation;
    QRect                m_viewRect;
    bool                 m_bIsStartUpTriggerDomain;
    QRect                m_triggerDomain;
    bool                 m_bEnterTriggerDomain;
    QTimer               m_pressTimer;
    QTimer               m_flipTimer;
    QTimer               m_movingTimer;
    bool                 m_bIsEditStatus;
    QSize                m_pageSize;
    int                  m_iPageTotalNum;
    int                  m_iCurrentPageNum;
    int                  m_iPressIndex;
    int                  m_iPosX;
    int                  m_iPosY;
    QPoint               m_stayPos;
    int                  m_iGlobalX;
    int                  m_iPosDiffX;
    int                  m_iPosDiffY;
    eAnimationMode       m_animationMode;
    bool                 m_bIsStartShadow;
    bool                 m_bIsStartZoom;
    eAFlipMode           m_flip;
    eEditMode            m_editMode;
    int                  m_iMovingIndex;
    bool                 m_bIsMoving;
    bool                 m_bIsPageMoving;
    int                  m_iFlipAppIndex;
    int                  m_iFlipStep;
    QList<CCButton*>     m_ListBtn;
    QMap<int,QRect>      m_MapRect;
};

#endif // HOMEVIEW_H
