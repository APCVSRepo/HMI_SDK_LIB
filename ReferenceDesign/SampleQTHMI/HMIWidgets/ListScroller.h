#ifndef LISTSCROLLER_H
#define LISTSCROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QPoint>


class Scroller;
class QAbstractScrollArea;
class QPropertyAnimation;

class ListScroller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue);
public:
    enum eGestureDirection
    {
        eNoDirection = 0,
        eDragLeft,
        eDragRight,
        eDragUp,
        eDragDown,
        eFlickLeft,
        eFlickRight,
        eFlickUp,
        eFlickDown
    };
    enum eListType
    {
        eNoList = 0,
        eHListWidget,
        eCVListWidget,
        eReminderDailyList,
        eCCalendarWidget
    };
    explicit ListScroller(QObject *parent = 0);
    ~ListScroller();

    void enableScroller(QAbstractScrollArea* scrollArea, const eListType elistType);
    void setOrientation(const Qt::Orientation orientation);
    QObject* getScrollerView();

    void scrollToPreviousPage();
    void scrollToNextPage();
    void setScrollModePerPage(bool mode);
    void setPageCount(int count);
    void setDisabled(bool mode);
    void setCurrentPage(int page);
    int  getCurrentPage();
    int value() const;
    void setValue(const int value);

protected:
    bool eventFilter(QObject* object, QEvent* event);
    bool mouseEventProcess(QObject* object, QEvent* event);

    int minimum() const;
    void setMinimum(const int value);
    int maximum() const;
    void setMaximum(const int value);
    //
    void setMoveAnimation(int startValue, int endValue, int msecs);

    void DragStartedAction(const QPoint& pos);
    void DragUpdatedAction(const QPoint& pos);
    void DragEndAction(const QPoint& pos);

    void ListPressedProcess(const QPoint& pos);
    void ListMovedProcess();
    void ListReleasedProcess(const QPoint& pos);

    void setFlickAnimation(int startValue, int endValue, int msecs);

signals:
    void flick(int direction);
    void dragPos(int x);
    void dragDirection(int x);

public slots:
    void animFinished();
    void flickAnimFinished();
    void onVScrollBarValueChanged(int value);
    void onSliderPressed();
    void onSliderReleased();

private:
    QScopedPointer<Scroller> d;
    //
    QPropertyAnimation*    m_pAnimation;
    QPropertyAnimation*    m_pFlickAnimation;
    QAbstractScrollArea*   m_pScrollArea;
    //
    eGestureDirection      m_eGestureDirection;
    eListType              m_eListType;
    Qt::Orientation        m_eListOrientation;
    //
//    QPoint                 m_pointTouchBeginScreenPos;
//    QPoint                 m_pointTouchUpdateScreenPos;
    QPoint                 m_pointMousePressPos;
    QPoint                 m_pointMouseMovePos;
    //
    int                    m_nPageCount;
    int                    m_nCurrentPageCount;
    int                    m_nScrollBarMaximum;
    //
    bool                   m_bIsAnimating;
    bool                   m_bScrollModePerPage;
    bool                   m_bLongPressed;
    bool                   m_bDisabled;
    bool                   m_bDoReboundAction;
    bool                   m_bSliderPressed;
};

#endif // LISTSCROLLER_H
