#include "PhonePicker.h"
#include <QMouseEvent>
#include <QScrollBar>
#include <QPalette>
#include <QTouchEvent>
#include <QMouseEvent>
PhonePicker::PhonePicker(QWidget *parent)
    : QListWidget(parent)
    ,m_nMouseDownX(0)
    ,m_nMouseDownY(0)
    ,m_nLastScrollBarValue(0)
    ,m_bCircularList(false)
    ,m_nItemCountPerPage(3)
    ,m_SaveY(-1)
    ,m_Index(-1)
    ,m_sizeH(80)
    ,m_MaxViewHit(270)
    ,m_MinViewHit(50)
    ,m_IsChangY(true)
    ,m_nResize(3)

{
    show();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollMode(QListView::ScrollPerPixel);
    setSortingEnabled(false);
    setFocusPolicy(Qt::NoFocus);
    viewport()->installEventFilter(this);
    connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemPressed_slot(QListWidgetItem*)),Qt::UniqueConnection);

    setStyleSheet("QListWidget {background-color: rgba(0, 0, 0, 0); border:0px; background-attachment: scroll;background:transparent;}"
                  "QListWidget::item:selected {"
                       "border: 0px solid 0;"
                       "background:transparent;"
                   "}"
                    "QListWidget::Item:hover{background:transparent; color:rgb(0, 138,255);}"
                    "QListWidget::item:selected:!active {"
                       "border:0px;"
                       "color:rgb(0, 138,255) ;"
                        "background: transparent;"
                   "}"
                   "QListWidget::item:selected:active {"
                       "border:0px;"
                       "color:rgb(255, 255,255) ;"
                       "background: transparent;"
                   "}"
                  );
}

PhonePicker::~PhonePicker()
{

}
void PhonePicker::itemPressed_slot(QListWidgetItem *item)
{
    m_Index = this->row(item);
}
void PhonePicker::InsertItem(int index, const QString &text, const QSize &itemSize, int fontSize, int specifiedID)
{
    m_sizeItem = itemSize;
    m_textFont = fontSize;
    QListWidgetItem* pItem = new QListWidgetItem;
    QFont font;
    font.setPixelSize(fontSize);
    pItem->setFont(font);
    pItem->setSizeHint(itemSize);
    pItem->setText(text);
    pItem->setForeground(QColor(255, 255, 255));
    pItem->setTextAlignment(Qt::AlignCenter);
    pItem->setBackgroundColor(QColor(0,0,0,0));
    pItem->setFlags(Qt::ItemIsEnabled);
    this->insertItem(index, pItem);
    if (-1 != specifiedID)
    {
        pItem->setData(Qt::UserRole+1, specifiedID);
    }
}

void PhonePicker::SetCircular(bool mode)
{
    m_bCircularList = mode;
}

QString PhonePicker::GetItemText(int index)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        return pItem->data(Qt::DisplayRole).toString();
    }
    return QString();
}

int PhonePicker::GetItemSpecifiedID(int index)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        return pItem->data(Qt::UserRole+1).toInt();
    }
    return -1;
}

void PhonePicker::SetItemCountPerPage(int count)
{
    m_nItemCountPerPage = count;
}

void PhonePicker::UpdateItemText(int index, const QString &qsText)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        pItem->setText(qsText);
    }
}

bool PhonePicker::eventFilter(QObject *object, QEvent *event)
{
    if (!isEnabled())
    {
        return QListWidget::eventFilter(object, event);
    }
    const QEvent::Type eventType = event->type();
    switch (eventType)
    {
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease:
        return MouseEvent(object,event);

    default:
        break;
    }
    return QListWidget::eventFilter(object, event);
}

bool PhonePicker::MouseEvent(QObject *object, QEvent *event)
{
    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
    if (!isEnabled())
    {
        return QListWidget::eventFilter(object, event);
    }
    const QEvent::Type eventType = event->type();
    switch (eventType) {
    case QEvent::MouseButtonPress:
    {
        m_IsChangY = true;
        m_nMouseDownX = mouseEvent->pos().x();
        m_nMouseDownY = mouseEvent->pos().y();
        m_nLastScrollBarValue = verticalScrollBar()->value();
        QListWidgetItem* pItem = this->itemAt(mouseEvent->pos().x(), mouseEvent->pos().y());
        if (pItem)
        {
            int index = this->row(pItem);
            m_Index =index;
            QString StrText = this->GetItemText(index);
            emit  CurrentText(index,StrText);
        //    emit pressIndex(indexPress);
        }
        break;
}
    case QEvent::MouseMove:
    {
        m_SaveY = mouseEvent->pos().y();
        int dragDistance;
        dragDistance = mouseEvent->y() - m_nMouseDownY;
         QListWidgetItem* pItem = this->itemAt(mouseEvent->pos().x(), mouseEvent->pos().y());
         if(pItem)
         {
             int index = this->row(pItem);
             if(m_Index != index)
             {
                 m_Index  = index;
                 QString StrText = this->GetItemText(index);
                 emit  CurrentText(index,StrText);
             }
         }

         if(m_IsChangY)
         {
            m_nMouseDownY = mouseEvent->pos().y();
            m_IsChangY = false;
         }
        if (m_bCircularList)
        {
            verticalScrollBar()->setValue(m_nLastScrollBarValue + dragDistance);
        }

        return true;
}
    case QEvent::MouseButtonRelease:
    {
        emit  CurrentText(-1,"");
        int currentValue;
        currentValue = verticalScrollBar()->value();
        int index;
        index = currentValue / m_sizeItem.height();
        int remainder;
        remainder = currentValue % m_sizeItem.height();
        if (remainder > m_sizeItem.height()/2)
        {
            index += 1;
        }
        verticalScrollBar()->setValue(index * m_sizeItem.height());
        m_SaveY = -1;
        break;
    }
    default:
        break;
    }
}
