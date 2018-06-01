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
    , m_bCircularList(false)
    , m_nItemCountPerPage(3)
    ,m_SaveY(-1)
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
    setStyleSheet("QListWidget {background-color: rgba(0, 0, 0, 0); border:0px; background-attachment: scroll;}");
}

PhonePicker::~PhonePicker()
{

}
void PhonePicker::itemPressed_slot(QListWidgetItem *item)
{
    m_PressIndex = this->row(item);
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
    QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
    QPoint pos;
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

    case QEvent::TouchBegin:
    {
        m_IsChangY = true;
        m_nMouseDownX = touchEvent->touchPoints().at(0).pos().x();
        m_nMouseDownY = touchEvent->touchPoints().at(0).pos().y();
        m_nLastScrollBarValue = verticalScrollBar()->value();
        QListWidgetItem* pItem = this->itemAt(touchEvent->touchPoints().at(0).pos().x(), touchEvent->touchPoints().at(0).pos().y());
        if (pItem)
        {
            pItem->setSizeHint(QSize(m_sizeItem.width()*m_nResize,m_sizeItem.height()*m_nResize));
            QFont font;
            font.setPixelSize(m_textFont*m_nResize);
            pItem->setFont(font);
            int index = this->row(pItem);
            int count = this->count();
            int diff = index - CODEZOOM;
            int diffcountAndIndex =count-index;
            m_PressIndex =index;
            if(diff>=0)
            {
                if(CODEZOOM-diffcountAndIndex<0)
                {
                    PChangeListItemSize(CODEZOOM);
                }
                else if(CODEZOOM-diffcountAndIndex>=0)
                {
                    PChangeListItemSize(diffcountAndIndex);
                }
                PmChangeListItemSize(CODEZOOM);
            }
            else if(diff<= 0)
            {
                PChangeListItemSize(CODEZOOM);
                PmChangeListItemSize(CODEZOOM+diff);
            }
        }
        QString StrText = this->GetItemText(m_PressIndex);
        emit  CurrentText(m_PressIndex,StrText);
      //  emit pressIndex(indexPress);
        break;
}
    case QEvent::TouchUpdate:
    {
        m_SaveY = touchEvent->touchPoints().at(0).pos().y();
        int dragDistance;
        dragDistance = touchEvent->touchPoints().at(0).pos().y() - m_nMouseDownY;
         QListWidgetItem* pItem = this->itemAt(touchEvent->touchPoints().at(0).pos().x(), touchEvent->touchPoints().at(0).pos().y());
         if(pItem)
         {
             m_MoveIndex = this->row(pItem);
             pItem->setSizeHint(QSize(m_sizeItem.width()*m_nResize,m_sizeItem.height()*m_nResize));
             QFont font;
             font.setPixelSize(m_textFont*m_nResize);
             pItem->setFont(font);
             int index = m_MoveIndex;
             int count = this->count();
             int diff = index - CODEZOOM+1;
             int diffcountAndIndex =count-index;
             if(diff>=0)
             {
                 if(CODEZOOM-diffcountAndIndex<0)
                 {
                     MChangeListItemSize(CODEZOOM);
                 }
                 else if(CODEZOOM-diffcountAndIndex>=0)
                 {
                     MChangeListItemSize(diffcountAndIndex);
                 }
                 MmChangeListItemSize(CODEZOOM);
             }
             else if(diff<= 0)
             {
                 MChangeListItemSize(CODEZOOM);
                 MmChangeListItemSize(CODEZOOM+diff);
             }
         }
         QString StrText = this->GetItemText(m_MoveIndex);
         emit  CurrentText(m_MoveIndex,StrText);
         if( (dragDistance>0&& touchEvent->touchPoints().at(0).pos().y()<m_MaxViewHit)||\
             (dragDistance<0&&touchEvent->touchPoints().at(0).pos().y()>m_MinViewHit))
            break;
         if(m_IsChangY)
         {
            m_nMouseDownY = touchEvent->touchPoints().at(0).pos().y();
            m_IsChangY = false;
         }
      //  emit addPage();
        if (m_bCircularList)
        {
            verticalScrollBar()->setValue(m_nLastScrollBarValue + dragDistance);
        }

        return true;
}
    case QEvent::TouchEnd:
    {
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
        for(int i =0;i<27;++i)
       {
            QListWidgetItem *item = this->item(i);
            item->setSizeHint(QSize(m_sizeItem.width(),m_sizeItem.height()));
            QFont font;
            font.setPixelSize(m_textFont);
            item->setFont(font);
       }
      verticalScrollBar()->setValue(index * m_sizeItem.height());
       // emit currentIndexChanged(index);
        m_SaveY = -1;
        break;
}
    default:
        break;
    }
    return QListWidget::eventFilter(object, event);
}

bool PhonePicker::MouseEvent(QObject *object, QEvent *event)
{
    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
    QPoint pos;
    if (!isEnabled())
    {
        return QListWidget::eventFilter(object, event);
    }
    const QEvent::Type eventType = event->type();
    switch (eventType) {
    case QEvent::TouchBegin:
    {
        m_IsChangY = true;
        m_nMouseDownX = mouseEvent->pos().x();
        m_nMouseDownY = mouseEvent->pos().y();
        m_nLastScrollBarValue = verticalScrollBar()->value();
        QListWidgetItem* pItem = this->itemAt(mouseEvent->pos().x(), mouseEvent->pos().y());
        if (pItem)
        {
            pItem->setSizeHint(QSize(m_sizeItem.width()*m_nResize,m_sizeItem.height()*m_nResize));
            QFont font;
            font.setPixelSize(m_textFont*m_nResize);
            pItem->setFont(font);
            int index = this->row(pItem);
            int count = this->count();
            int diff = index - CODEZOOM;
            int diffcountAndIndex =count-index;
            m_PressIndex =index;
            if(diff>=0)
            {
                if(CODEZOOM-diffcountAndIndex<0)
                {
                    PChangeListItemSize(CODEZOOM);
                }
                else if(CODEZOOM-diffcountAndIndex>=0)
                {
                    PChangeListItemSize(diffcountAndIndex);
                }
                PmChangeListItemSize(CODEZOOM);
            }
            else if(diff<= 0)
            {
                PChangeListItemSize(CODEZOOM);
                PmChangeListItemSize(CODEZOOM+diff);
            }
        }
        QString StrText = this->GetItemText(m_PressIndex);
        emit  CurrentText(m_PressIndex,StrText);
      //  emit pressIndex(indexPress);
        break;
}
    case QEvent::TouchUpdate:
    {
        m_SaveY = mouseEvent->pos().y();
        int dragDistance;
        dragDistance = mouseEvent->y() - m_nMouseDownY;
         QListWidgetItem* pItem = this->itemAt(mouseEvent->pos().x(), mouseEvent->pos().y());
         if(pItem)
         {
             m_MoveIndex = this->row(pItem);
             pItem->setSizeHint(QSize(m_sizeItem.width()*m_nResize,m_sizeItem.height()*m_nResize));
             QFont font;
             font.setPixelSize(m_textFont*m_nResize);
             pItem->setFont(font);
             int index = m_MoveIndex;
             int count = this->count();
             int diff = index - CODEZOOM+1;
             int diffcountAndIndex =count-index;
             if(diff>=0)
             {
                 if(CODEZOOM-diffcountAndIndex<0)
                 {
                     MChangeListItemSize(CODEZOOM);
                 }
                 else if(CODEZOOM-diffcountAndIndex>=0)
                 {
                     MChangeListItemSize(diffcountAndIndex);
                 }
                 MmChangeListItemSize(CODEZOOM);
             }
             else if(diff<= 0)
             {
                 MChangeListItemSize(CODEZOOM);
                 MmChangeListItemSize(CODEZOOM+diff);
             }
         }
         QString StrText = this->GetItemText(m_MoveIndex);
         emit  CurrentText(m_MoveIndex,StrText);
         if( (dragDistance>0&& mouseEvent->pos().y()<m_MaxViewHit)||\
             (dragDistance<0&&mouseEvent->pos().y()>m_MinViewHit))
            break;
         if(m_IsChangY)
         {
            m_nMouseDownY = mouseEvent->pos().y();
            m_IsChangY = false;
         }
      //  emit addPage();
        if (m_bCircularList)
        {
            verticalScrollBar()->setValue(m_nLastScrollBarValue + dragDistance);
        }

        return true;
}
    case QEvent::TouchEnd:
    {
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
        for(int i =0;i<27;++i)
       {
            QListWidgetItem *item = this->item(i);
            item->setSizeHint(QSize(m_sizeItem.width(),m_sizeItem.height()));
            QFont font;
            font.setPixelSize(m_textFont);
            item->setFont(font);
       }
      verticalScrollBar()->setValue(index * m_sizeItem.height());
       // emit currentIndexChanged(index);
        m_SaveY = -1;
        break;
    }
    default:
        break;
    }
}


  void PhonePicker::PChangeListItemSize(int number){
      for(int i = 1;i<number;i++)
      {
          QListWidgetItem *item = this->item(m_PressIndex+i);
          item->setSizeHint(QSize(m_sizeItem.width()*m_nResize -m_sizeItem.width()*(m_nResize-1)*(i)/(CODEZOOM-1),\
                                  m_sizeItem.height()*m_nResize-m_sizeItem.height()*(m_nResize-1)*(i)/(CODEZOOM-1)));
          QFont font;
          font.setPixelSize(m_textFont*m_nResize-m_textFont*(m_nResize-1)*(i)/(CODEZOOM-1));
          item->setFont(font);
      }
  }
  void PhonePicker::PmChangeListItemSize(int number){
      for(int i = 1;i<number;++i)
      {
          QListWidgetItem *item = this->item(m_PressIndex-i);
          item->setSizeHint(QSize(m_sizeItem.width()*m_nResize -m_sizeItem.width()*(m_nResize-1)*(i)/(CODEZOOM-1),\
                                  m_sizeItem.height()*m_nResize-m_sizeItem.height()*(m_nResize-1)*(i)/(CODEZOOM-1)));
          QFont font;
          font.setPixelSize(m_textFont*m_nResize-m_textFont*(m_nResize-1)*(i)/(CODEZOOM-1));
          item->setFont(font);
      }
  }

  void PhonePicker::MChangeListItemSize(int number){
      for(int i = 1;i<number;i++)
      {
          QListWidgetItem *item = this->item(m_MoveIndex+i);
          item->setSizeHint(QSize(m_sizeItem.width()*m_nResize -m_sizeItem.width()*(m_nResize-1)*(i)/(CODEZOOM-1),\
                                  m_sizeItem.height()*m_nResize-m_sizeItem.height()*(m_nResize-1)*(i)/(CODEZOOM-1)));
          QFont font;
          font.setPixelSize(m_textFont*m_nResize-m_textFont*(m_nResize-1)*(i)/(CODEZOOM-1));
          item->setFont(font);
      }
  }

  void PhonePicker::MmChangeListItemSize(int number){
      for(int i = 1;i<number;++i)
      {
          QListWidgetItem *item = this->item(m_MoveIndex-i);
          item->setSizeHint(QSize(m_sizeItem.width()*m_nResize -m_sizeItem.width()*(m_nResize-1)*(i)/(CODEZOOM-1),\
                                  m_sizeItem.height()*m_nResize-m_sizeItem.height()*(m_nResize-1)*(i)/(CODEZOOM-1)));
          QFont font;
          font.setPixelSize(m_textFont*m_nResize-m_textFont*(m_nResize-1)*(i)/(CODEZOOM-1));
          item->setFont(font);
      }
  }
  void PhonePicker::RChangeListItemSize(int number){
      for(int i = 1;i<number;i++)
      {
          QListWidgetItem *item = this->item(m_RealseIndex+i);
          item->setSizeHint(QSize(m_sizeItem.width(),m_sizeItem.height()));
          QFont font;
          font.setPixelSize(m_textFont);
          item->setFont(font);
      }
  }

  void PhonePicker::RmChangeListItemSize(int number){
      for(int i = 1;i<number;i++)
      {
          QListWidgetItem *item = this->item(m_RealseIndex-i);
          item->setSizeHint(QSize(m_sizeItem.width(),m_sizeItem.height()));
          QFont font;
          font.setPixelSize(m_textFont);
          item->setFont(font);
      }
  }
