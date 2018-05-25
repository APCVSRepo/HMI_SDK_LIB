
#include <QApplication>
#include <QScrollBar>
#include <QAbstractScrollArea>
#include <QMouseEvent>
#include <QTouchEvent>
#include <QEvent>
#include <QTimer>
#include <QPropertyAnimation>
#include "ListScroller.h"
#include "CVListWidget.h"
#include "WidgetsCommon.h"

class Scroller
{
public:
    Scroller()
        : scrollArea(NULL)
        , lastScrollBarValue(0)
        , isMoving(false)
    {
        ;
    }

    QAbstractScrollArea* scrollArea;
    QPoint lastPressedPoint;
    int lastScrollBarValue;
    bool isMoving;
};

ListScroller::ListScroller(QObject *parent)
    : QObject(parent)
    , d(new Scroller)
    , m_pAnimation(NULL)
    , m_pFlickAnimation(NULL)
    , m_pScrollArea(NULL)
    , m_eGestureDirection(eNoDirection)
    , m_eListType(eNoList)
    , m_eListOrientation(Qt::Vertical)
    , m_nPageCount(0)
    , m_nCurrentPageCount(1)
    , m_nScrollBarMaximum(0)
    , m_bIsAnimating(false)
    , m_bScrollModePerPage(false)
    , m_bLongPressed(false)
    , m_bDisabled(false)
    , m_bDoReboundAction(false)
    , m_bSliderPressed(false)
{

}

ListScroller::~ListScroller()
{
    if (m_pAnimation)
    {
        delete m_pAnimation;
        m_pAnimation = NULL;
    }
    if (m_pFlickAnimation)
    {
        delete m_pFlickAnimation;
        m_pFlickAnimation = NULL;
    }
}

void ListScroller::enableScroller(QAbstractScrollArea *scrollArea, const eListType elistType)
{
    if (!scrollArea)
    {
        return;
    }
    // remove existing association
    if (d->scrollArea)
    {
        d->scrollArea->viewport()->removeEventFilter(this);
        d->scrollArea->removeEventFilter(this);
        d->scrollArea = NULL;
    }
    // associate
    scrollArea->installEventFilter(this);
    scrollArea->viewport()->installEventFilter(this);
    d->scrollArea = scrollArea;
    d->scrollArea->ungrabGesture(Qt::PanGesture);
    m_eListType = elistType;
    if (eHListWidget == m_eListType)
    {
        m_bDoReboundAction = true;
    }
    m_pScrollArea = scrollArea;

    m_pAnimation = new QPropertyAnimation(this, "value");
    connect(m_pAnimation, SIGNAL(finished()), this, SLOT(animFinished()));

    m_pFlickAnimation = new QPropertyAnimation(this, "value");
    connect(m_pFlickAnimation, SIGNAL(finished()), this, SLOT(flickAnimFinished()));

    connect(d->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onVScrollBarValueChanged(int)));
    connect(d->scrollArea->verticalScrollBar(), SIGNAL(sliderPressed()), this, SLOT(onSliderPressed()));
    connect(d->scrollArea->verticalScrollBar(), SIGNAL(sliderReleased()), this, SLOT(onSliderReleased()));
}

void ListScroller::setOrientation(const Qt::Orientation orientation)
{
    m_eListOrientation = orientation;
}

QObject *ListScroller::getScrollerView()
{
    return d->scrollArea->viewport();
}

void ListScroller::scrollToPreviousPage()
{
    if (m_nPageCount <= 1)
    {
        return;
    }
    int nowValue = value();
    if (nowValue > 0)
    {
        int endValue = m_pScrollArea->width() * (m_nCurrentPageCount-2);
        if (endValue < 0)
        {
            endValue = 0;
        }
        setMoveAnimation(nowValue, endValue, 600);
    }
}

void ListScroller::scrollToNextPage()
{
    if (m_nPageCount <= 1)
    {
        return;
    }
    int nowValue = value();
    if (nowValue < maximum())
    {
        int endValue = m_pScrollArea->width() * (m_nCurrentPageCount);
        if (endValue > maximum())
        {
            endValue = maximum();
        }
        setMoveAnimation(nowValue, endValue, 600);
    }
}

void ListScroller::setScrollModePerPage(bool mode)
{
    m_bScrollModePerPage = mode;
    if (m_bScrollModePerPage)
    {
        m_bDoReboundAction = false;
    }
}

void ListScroller::setPageCount(int count)
{
    Log("[ListScroller::setPageCount]: count = %d", count);
    m_nPageCount = count;
}

void ListScroller::setDisabled(bool mode)
{
    m_bDisabled = mode;
}

void ListScroller::setCurrentPage(int page)
{
    Log("[ListScroller::setCurrentPage]: page = %d", page);
    if (page > 0)
    {
        m_nCurrentPageCount = page;
        setValue((page-1)*m_pScrollArea->width());
    }
}

int ListScroller::getCurrentPage()
{
    return m_nCurrentPageCount;
}

bool ListScroller::eventFilter(QObject *object, QEvent *event)
{
    const QEvent::Type eventType = event->type();
    switch (eventType)
    {
    case QEvent::MouseButtonDblClick:
        return true;

    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease:
    {
         return mouseEventProcess(object, event);
    }
    default:
        return QObject::eventFilter(object, event);
    }
    return true;
}

bool ListScroller::mouseEventProcess(QObject* object, QEvent *event)
{
    Log("mouse  Event ");
    const QEvent::Type eventType = event->type();
    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
    switch (eventType)
    {
    case QEvent::MouseButtonDblClick:
        return true;

    case QEvent::MouseButtonPress:
        if (m_bIsAnimating || m_bDisabled)
        {
            return false;
        }
        m_pointMousePressPos.setX(mouseEvent->x());
        m_pointMousePressPos.setY(mouseEvent->y());
        DragStartedAction(mouseEvent->pos());
        ListPressedProcess(mouseEvent->pos());
        break;

    case QEvent::MouseMove:
        if (m_bIsAnimating || m_bDisabled || /*!d->isMoving ||*/ m_bLongPressed)
        {
            return false;
        }

        m_pointMouseMovePos.setX(mouseEvent->x());
        m_pointMouseMovePos.setY(mouseEvent->y());
        DragUpdatedAction(mouseEvent->pos());
        ListMovedProcess();
        break;

    case QEvent::MouseButtonRelease:
        Log("[ListScroller::MouseButtonRelease]");
        if (m_bIsAnimating || m_bDisabled)
        {
            m_bLongPressed = false;
            return false;
        }
        if (d->isMoving)
        {
            d->isMoving = false;
            DragEndAction(mouseEvent->pos());
        }
        else
        {
            ListReleasedProcess(mouseEvent->pos());
        }
        m_bLongPressed = false;
        break;

    default:
        return QObject::eventFilter(object, event);
    }
    return true;
}

int ListScroller::value() const
{
    if (Qt::Horizontal == m_eListOrientation)
    {
        return d->scrollArea->horizontalScrollBar()->value();
    }
    else
    {
        return d->scrollArea->verticalScrollBar()->value();
    }
}

void ListScroller::setValue(const int value)
{
    if (Qt::Horizontal == m_eListOrientation)
    {
        d->scrollArea->horizontalScrollBar()->setValue(value);
    }
    else
    {
        d->scrollArea->verticalScrollBar()->setValue(value);
    }
}

int ListScroller::minimum() const
{
    if (Qt::Horizontal == m_eListOrientation)
    {
        return d->scrollArea->horizontalScrollBar()->minimum();
    }
    else
    {
        return d->scrollArea->verticalScrollBar()->minimum();
    }
}

void ListScroller::setMinimum(const int value)
{
    if (Qt::Horizontal == m_eListOrientation)
    {
        d->scrollArea->horizontalScrollBar()->setMinimum(value);
    }
    else
    {
        d->scrollArea->verticalScrollBar()->setMinimum(value);
    }
}

int ListScroller::maximum() const
{
    if (Qt::Horizontal == m_eListOrientation)
    {
        return d->scrollArea->horizontalScrollBar()->maximum();
    }
    else
    {
        return d->scrollArea->verticalScrollBar()->maximum();
    }
}

void ListScroller::setMaximum(const int value)
{
    if (Qt::Horizontal == m_eListOrientation)
    {
        d->scrollArea->horizontalScrollBar()->setMaximum(value);
    }
    else
    {
        d->scrollArea->verticalScrollBar()->setMaximum(value);
    }
}

void ListScroller::setMoveAnimation(int startValue, int endValue, int msecs)
{
    if (m_pAnimation)
    {
        m_pAnimation->setStartValue(startValue);
        m_pAnimation->setEndValue(endValue);
        m_pAnimation->setEasingCurve(QEasingCurve::OutCubic);
        m_pAnimation->setLoopCount(1);
        m_pAnimation->setDuration(msecs);
        m_pAnimation->start();
        m_bIsAnimating = true;
    }
}

void ListScroller::DragStartedAction(const QPoint &pos)
{
    d->lastPressedPoint = pos;
    d->lastScrollBarValue = value();
    if (eHListWidget == m_eListType && m_bScrollModePerPage) //Tuner FavList
    {
        if (m_nPageCount > 0)
        {
            setMaximum((m_nPageCount-1)*m_pScrollArea->width());
        }
    }
    if (m_bDoReboundAction)
    {
        m_nScrollBarMaximum = maximum();
        setMinimum(-m_pScrollArea->width());
        setMaximum(m_nScrollBarMaximum + m_pScrollArea->width());
    }
}

void ListScroller::DragUpdatedAction(const QPoint& pos)
{
    int dragDis = 0;
    if (Qt::Horizontal == m_eListOrientation)
    {
        //dragDis = pos.x() - d->lastPressedPoint.x();
        //dragDis = pos.x() - m_pointTouchBeginScreenPos.x();
        dragDis = pos.x() - m_pointMousePressPos.x();
    }
    else
    {
        //dragDis = pos.y() - d->lastPressedPoint.y();
        //dragDis = pos.y() - m_pointTouchBeginScreenPos.y();
        dragDis = pos.y() - m_pointMousePressPos.y();
    }
    setValue(d->lastScrollBarValue - dragDis);
    if (dragDis > 0)
    {
        m_eGestureDirection = eDragRight;
    }
    else if (dragDis < 0)
    {
        m_eGestureDirection = eDragLeft;
    }
    else
    {
        m_eGestureDirection = eNoDirection;
    }
}

void ListScroller::DragEndAction(const QPoint &)
{
    Log("[ListScroller::DragEndAction]");
    if (eHListWidget == m_eListType && m_bScrollModePerPage) //Tuner FavList
    {
        if (eDragLeft == m_eGestureDirection)
        {
            if (m_nPageCount <= 1)
            {
                return;
            }
            int nowValue = value();
            if (nowValue < maximum())
            {
                int endValue = 0;
                endValue = m_pScrollArea->width() * (m_nCurrentPageCount);
                if ((endValue - nowValue) > m_pScrollArea->width()/2)
                {
                    endValue -= m_pScrollArea->width();
                }
                if (endValue > maximum())
                {
                    endValue = maximum();
                }
                setMoveAnimation(nowValue, endValue, 600);
            }
        }
        else if(eDragRight == m_eGestureDirection)
        {
            if (m_nPageCount <= 1)
            {
                return;
            }
            int nowValue = value();
            if (nowValue > 0)
            {
                int endValue = m_pScrollArea->width() * (m_nCurrentPageCount-2);
                if ((nowValue - endValue) > m_pScrollArea->width()/2)
                {
                    endValue += m_pScrollArea->width();
                }
                if (endValue < 0)
                {
                    endValue = 0;
                }
                setMoveAnimation(nowValue, endValue, 600);
            }
        }
        else if (eFlickLeft == m_eGestureDirection)
        {
            scrollToNextPage();
        }
        else if (eFlickRight == m_eGestureDirection)
        {
            scrollToPreviousPage();
        }
        m_eGestureDirection = eNoDirection;
    }
    else if (eCVListWidget == m_eListType)
    {
        CVListWidget* pVListWidget = static_cast<CVListWidget*>(m_pScrollArea);
        pVListWidget->SetTopItemChanged();
        Log("ListScroller: SetTopItemChanged");
    }
    if (m_bDoReboundAction)
    {
        Log("[ListScroller::DragEndAction]: %d   %d", value(), m_nScrollBarMaximum);
        if (value() < 0)
        {
            setMoveAnimation(value(), 0, 300);
        }
        else if (value() > m_nScrollBarMaximum)
        {
            setMoveAnimation(value(), m_nScrollBarMaximum, 300);
        }
        else
        {
            setMinimum(0);
            setMaximum(m_nScrollBarMaximum);
        }
    }
}

void ListScroller::ListPressedProcess(const QPoint& pos)
{
   if (eCVListWidget == m_eListType)
    {
        CVListWidget* pVListWidget = static_cast<CVListWidget*>(m_pScrollArea);
        pVListWidget->PressedEventAction(pos);
    }
}

void ListScroller::ListMovedProcess()
{
    if (eCVListWidget == m_eListType)
    {
        CVListWidget* pVListWidget = static_cast<CVListWidget*>(m_pScrollArea);
        pVListWidget->MovedEventAction();
    }
}

void ListScroller::ListReleasedProcess(const QPoint& pos)
{
  if (eCVListWidget == m_eListType)
    {
        CVListWidget* pVListWidget = static_cast<CVListWidget*>(m_pScrollArea);
        pVListWidget->ReleasedEventAction(pos);
    }

}

void ListScroller::setFlickAnimation(int startValue, int endValue, int msecs)
{
    if (m_pFlickAnimation)
    {
        m_pFlickAnimation->setStartValue(startValue);
        m_pFlickAnimation->setEndValue(endValue);
        m_pFlickAnimation->setEasingCurve(QEasingCurve::OutCubic);
        m_pFlickAnimation->setLoopCount(1);
        m_pFlickAnimation->setDuration(msecs);
        m_pFlickAnimation->start();
        m_bIsAnimating = true;
    }
}

void ListScroller::animFinished()
{
    m_bIsAnimating = false;
    if (m_bDoReboundAction)
    {
        setMinimum(0);
        setMaximum(m_nScrollBarMaximum);
    }
}

void ListScroller::flickAnimFinished()
{
    d->isMoving = false;
    m_bIsAnimating = false;
 if (eCVListWidget == m_eListType)
    {
        CVListWidget* pVListWidget = static_cast<CVListWidget*>(m_pScrollArea);
        pVListWidget->SetTopItemChanged();
        Log("[ListScroller::flickAnimFinished]: SetTopItemChanged");
    }
}

void ListScroller::onVScrollBarValueChanged(int value)
{
    if (eCVListWidget == m_eListType)
    {
        CVListWidget* pVListWidget = static_cast<CVListWidget*>(m_pScrollArea);
        //if (!m_bSliderPressed)
        {
            pVListWidget->SetTopItemChanged(value);
        }
    }
}

void ListScroller::onSliderPressed()
{
    m_bSliderPressed = true;
}

void ListScroller::onSliderReleased()
{
    m_bSliderPressed = false;
    if (eCVListWidget == m_eListType)
    {
        CVListWidget* pVListWidget = static_cast<CVListWidget*>(m_pScrollArea);
        if (!m_bSliderPressed)
        {
            pVListWidget->SetTopItemChanged(this->value());
        }
    }
}
