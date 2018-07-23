#include "DateTimePicker.h"
#include <QMouseEvent>
#include <QTouchEvent>
DateTimePicker::DateTimePicker(QWidget *parent)
    : QWidget(parent)
    , m_pYearPicker(NULL)
    , m_pMonthPicker(NULL)
    , m_pDayPicker(NULL)
    , m_pHourPicker(NULL)
    , m_pMinutePicker(NULL)
    , m_pAMPMPicker(NULL)
    , m_nMinYear(2013)
    , m_nMaxYear(2037)
    , m_recordMonth(0)
    , m_recordHour(0)
    , m_recordDirection(0)
    , m_recordAMAndPMDirection(-1)
    , m_nItemCountPerPage(3)
    , m_nItemAMAndFMCountPerPage(3)
    , m_nCurrentHour(1)
    , m_nCurrentMinute(0)
    , m_bAMOrPM(false)
    , m_nCurrentFontSize(20)
    , m_isUpdateYear(false)
    , m_b12HourSystem(false)
    , m_FontStyle(eKnownFontStyle)
    , m_isUpdateAMrOFM(false)
    , m_isPickSlide(false)
    , m_isPaintPickEnd(true)
    , m_isAllPickEnable(true)
    , m_IsSliderByTime(false)
    , m_pDayPickerAnimation(false)
    , m_needUpdateMon(-1)
    , m_needUpdateYear(-1)
    , m_IsneedUpdateMon(false)
    , m_IsneedUpdateYear(false)
{
    this->show();
}

DateTimePicker::~DateTimePicker()
{
    if (m_pYearPicker)
    {
        delete m_pYearPicker;
    }
    if (m_pMonthPicker)
    {
        delete m_pMonthPicker;
    }
    if (m_pDayPicker)
    {
        delete m_pDayPicker;
    }
    if (m_pHourPicker)
    {
        delete m_pHourPicker;
    }
    if (m_pMinutePicker)
    {
        delete m_pMinutePicker;
    }
    if (m_pAMPMPicker)
    {
        delete m_pAMPMPicker;
    }
}
bool DateTimePicker::eventFilter(QObject *object, QEvent *event)
{
    if (!isEnabled())
    {
        return QObject::eventFilter(object, event);
    }
    if(!object||!event)
        return true;
    const QEvent::Type eventType = event->type();
    QTouchEvent* const touchEvent = static_cast<QTouchEvent*>(event);
    if(!touchEvent)
        return true;

    switch (eventType)
    {
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease:
        return MouseEvent(object,event);

    case QEvent::TouchBegin:
    {
        if(!m_isPickSlide)
        {
            if(m_isAllPickEnable)
            {
               if(m_pYearPicker &&(m_pYearPicker->viewport() == object||m_pYearPicker == object))
               {
                   SetPickerEnabled(true,eYearPicker);
                   SetPickerEnabled(false,eMonthPicker);
                   SetPickerEnabled(false,eDayPicker);
                   SetPickerEnabled(false,eHourPicker);
                   SetPickerEnabled(false,eMinutePicker);
                   SetPickerEnabled(false,eAMPMPicker);
               }
               else if(m_pMonthPicker&&(m_pMonthPicker->viewport() == object||m_pMonthPicker == object))
               {
                   SetPickerEnabled(false,eYearPicker);
                   SetPickerEnabled(true,eMonthPicker);
                   SetPickerEnabled(false,eDayPicker);
                   SetPickerEnabled(false,eHourPicker);
                   SetPickerEnabled(false,eMinutePicker);
                   SetPickerEnabled(false,eAMPMPicker);
               }
               else if(m_pDayPicker&&(m_pDayPicker->viewport() == object||m_pDayPicker == object))
               {
                   m_pDayPickerAnimation = true;
                   SetPickerEnabled(false,eYearPicker);
                   SetPickerEnabled(false,eMonthPicker);
                   SetPickerEnabled(true,eDayPicker);
                   SetPickerEnabled(false,eHourPicker);
                   SetPickerEnabled(false,eMinutePicker);
                   SetPickerEnabled(false,eAMPMPicker);
               }
               else if(m_pHourPicker&&(m_pHourPicker->viewport() == object || m_pHourPicker == object))
               {
                   SetPickerEnabled(false,eYearPicker);
                   SetPickerEnabled(false,eMonthPicker);
                   SetPickerEnabled(false,eDayPicker);
                   SetPickerEnabled(true,eHourPicker);
                   SetPickerEnabled(false,eMinutePicker);
                   SetPickerEnabled(false,eAMPMPicker);
               }
               else if(m_pMinutePicker&&(m_pMinutePicker->viewport() == object||m_pMinutePicker == object))
               {
                   SetPickerEnabled(false,eYearPicker);
                   SetPickerEnabled(false,eMonthPicker);
                   SetPickerEnabled(false,eDayPicker);
                   SetPickerEnabled(false,eHourPicker);
                   SetPickerEnabled(true,eMinutePicker);
                   SetPickerEnabled(false,eAMPMPicker);
               }
               else if(m_pAMPMPicker&&(m_pAMPMPicker->viewport() == object||m_pAMPMPicker == object))
               {
                   SetPickerEnabled(false,eYearPicker);
                   SetPickerEnabled(false,eMonthPicker);
                   SetPickerEnabled(false,eDayPicker);
                   SetPickerEnabled(false,eHourPicker);
                   SetPickerEnabled(false,eMinutePicker);
                   SetPickerEnabled(true,eAMPMPicker);
               }
            }
           m_isPaintPickEnd = false;
           m_isPickSlide = true;
        }
        break;
    }
    case QEvent::TouchUpdate:
    {
        break;
    }
    case QEvent::TouchEnd:
    {
       m_isPickSlide = false;
       if(!m_isPickSlide && m_isPaintPickEnd)
       {
           if(m_isAllPickEnable)
           {

               if(!m_pDayPickerAnimation)
               {
                SetPickerEnabled(true,eYearPicker);
                SetPickerEnabled(true,eMonthPicker);
                SetPickerEnabled(true,eDayPicker);
                SetPickerEnabled(true,eHourPicker);
                SetPickerEnabled(true,eMinutePicker);
                SetPickerEnabled(true,eAMPMPicker);
               }
               else
               {
                    if(m_pDayPicker)
                    {
                        if(m_pDayPicker->getIsAnimatonEnd())
                        {
                            SetPickerEnabled(true,eYearPicker);
                            SetPickerEnabled(true,eMonthPicker);
                            SetPickerEnabled(true,eDayPicker);
                            SetPickerEnabled(true,eHourPicker);
                            SetPickerEnabled(true,eMinutePicker);
                            SetPickerEnabled(true,eAMPMPicker);
                        }
                     }
                     m_pDayPickerAnimation = false;
               }
           }
       }
       break;
    }
    default:
        break;
    }
    return QObject::eventFilter(object, event);
}
void DateTimePicker::SetCurrentDate(QDate date,bool isreturn)
{
    m_dateCurrent = date;
    if(date.year()<m_nMinYear)
        date.setDate(m_nMinYear,date.month(),date.day());
    else if(date.year()>m_nMaxYear)
        date.setDate(m_nMaxYear,date.month(),date.day());
    int nPage = m_nItemCountPerPage/2;
    if (m_pYearPicker)
    {
        QListWidgetItem* pItem1 = m_pYearPicker->item(date.year()-m_nMinYear + nPage);
        if (pItem1)
        {
            if(!isreturn)
            {
                m_pYearPicker->StopPickerRebound();
                m_pYearPicker->scrollToItem(pItem1, QAbstractItemView::PositionAtCenter);
                m_pYearPicker->SetCurrentIndex(m_pYearPicker->row(pItem1));
            }
            else
            {
                int startValue = m_pYearPicker->value();
                int endValue = (m_pYearPicker->row(pItem1)-m_nItemCountPerPage/2) * m_pYearPicker->getItemSize().height();
                m_pYearPicker->SetCurrentIndex(m_pYearPicker->row(pItem1));
                m_pYearPicker->PickerRebound(startValue,endValue);
            }
        }
    }
    if (m_pMonthPicker)
    {
        int month = date.month();
        if (month < nPage+1)
        {
            month += 12;
        }
        QListWidgetItem* pItem2 = m_pMonthPicker->item(month - 1);
        if (pItem2)
        {
            if(!isreturn)
            {
                m_pMonthPicker->StopPickerRebound();
                m_pMonthPicker->scrollToItem(pItem2, QAbstractItemView::PositionAtCenter);
                m_pMonthPicker->SetCurrentIndex(m_pMonthPicker->row(pItem2));
            }
            else
            {
                int startValue = m_pMonthPicker->value();
                int endValue = (m_pMonthPicker->row(pItem2)-m_nItemCountPerPage/2)* m_pMonthPicker->getItemSize().height();
                m_pMonthPicker->SetCurrentIndex(m_pMonthPicker->row(pItem2));
                m_pMonthPicker->PickerRebound(startValue,endValue);
            }
        }
    }
    if (m_pDayPicker)
    {
        CreateDayPicker(date.daysInMonth(), m_sizeDayPickerItem);
        int day = date.day();
        if (day < nPage+1)
        {
            day += date.daysInMonth();
        }
        QListWidgetItem* pItem3 = m_pDayPicker->item(day - 1);
        if (pItem3)
        {
            if(!isreturn)
            {
                m_pDayPicker->StopPickerRebound();
                m_pDayPicker->scrollToItem(pItem3, QAbstractItemView::PositionAtCenter);
                m_pDayPicker->SetCurrentIndex(m_pDayPicker->row(pItem3));
            }
            else
            {
                int startValue = m_pDayPicker->value();
                int endValue = (m_pDayPicker->row(pItem3) -m_nItemCountPerPage/2)* m_pDayPicker->getItemSize().height();
                m_pDayPicker->SetCurrentIndex(m_pDayPicker->row(pItem3));
                m_pDayPicker->PickerRebound(startValue,endValue);
            }
        }
    }
}

void DateTimePicker::SetCurrentHour(int hour,bool isreturn)
{
    int nMinHour, nMaxHour;
    if (m_b12HourSystem)
    {
        nMinHour = 1;
        nMaxHour = 12;
    }
    else
    {
        nMinHour = 0;
        nMaxHour = 23;
    }
    if (hour < nMinHour || hour > nMaxHour)
    {
        return;
    }
    m_nCurrentHour = hour;
    if (m_pHourPicker)
    {
        if(m_b12HourSystem)
        {
            if (m_nItemCountPerPage/2+1 > hour)
            {
                hour = nMaxHour + hour;
            }
        }
        else
        {
            if (m_nItemCountPerPage/2 > hour)
            {
                hour = nMaxHour + hour+1;
            }
        }
        QListWidgetItem* pItem = m_pHourPicker->item(hour-nMinHour);
        if (pItem)
        {
            if(!isreturn)
            {
                m_pHourPicker->StopPickerRebound();
                m_pHourPicker->scrollToItem(pItem, QAbstractItemView::PositionAtCenter);
                m_pHourPicker->SetCurrentIndex(m_pHourPicker->row(pItem));
            }
            else
            {
                int startValue = m_pHourPicker->value();    
                int endValue = (m_pHourPicker->row(pItem)-m_nItemCountPerPage/2) * m_pHourPicker->getItemSize().height();
                m_pHourPicker->SetCurrentIndex(m_pHourPicker->row(pItem));
                m_pHourPicker->PickerRebound(startValue,endValue);
            }
        }
    }
}

void DateTimePicker::SetCurrentMinute(int minute,bool isreturn)
{
    if (minute < 0 || minute > 59)
    {
        return;
    }
    m_nCurrentMinute = minute;
    if (m_pMinutePicker)
    {
        if(minute < m_nItemCountPerPage/2)
        {
           minute = 60 + minute;
        }
        QListWidgetItem* pItem = m_pMinutePicker->item(minute);
        if (pItem)
        {
            if(!isreturn)
            {
                m_pMinutePicker->StopPickerRebound();
                m_pMinutePicker->scrollToItem(pItem, QAbstractItemView::PositionAtCenter);
                m_pMinutePicker->SetCurrentIndex(m_pMinutePicker->row(pItem));
            }
            else
            {
                int startValue = m_pMinutePicker->value();
                int endValue = (m_pMinutePicker->row(pItem)-m_nItemCountPerPage/2) * m_pMinutePicker->getItemSize().height();
                m_pMinutePicker->SetCurrentIndex(m_pMinutePicker->row(pItem));
                m_pMinutePicker->PickerRebound(startValue,endValue);
            }
        }
    }
}

void DateTimePicker::SetCurrentAMPM(bool bAMOrPm,bool isreturn)
{
    m_bAMOrPM = bAMOrPm;
    QList<QListWidgetItem*> itemList;
    QList<QListWidgetItem*> ChainitemList;
    if (bAMOrPm)
    {
        itemList = m_pAMPMPicker->findItems("AM", Qt::MatchExactly);
       ChainitemList  = m_pAMPMPicker->findItems("上午", Qt::MatchExactly);
    }
    else
    {
        itemList = m_pAMPMPicker->findItems("PM", Qt::MatchExactly);
        ChainitemList = m_pAMPMPicker->findItems("下午", Qt::MatchExactly);
    }
    if (itemList.count())
    {
        if(!isreturn)
        {
            m_pAMPMPicker->StopPickerRebound();
            m_pAMPMPicker->scrollToItem(itemList.at(0), QAbstractItemView::PositionAtCenter);
            m_pAMPMPicker->SetCurrentIndex(m_pAMPMPicker->row(itemList.at(0)));
        }
        else
        {
            int startValue = m_pAMPMPicker->value();
            int endValue = (m_pAMPMPicker->row(itemList.at(0))-m_nItemAMAndFMCountPerPage/2) * m_pAMPMPicker->getItemSize().height();
            m_pAMPMPicker->SetCurrentIndex(m_pAMPMPicker->row(itemList.at(0)));
            m_pAMPMPicker->PickerRebound(startValue,endValue);
        }
    }
    else if (ChainitemList.count())
    {
        if(!isreturn)
        {
            m_pAMPMPicker->StopPickerRebound();
            m_pAMPMPicker->scrollToItem(ChainitemList.at(0), QAbstractItemView::PositionAtCenter);
            m_pAMPMPicker->SetCurrentIndex(m_pAMPMPicker->row(ChainitemList.at(0)));
        }
        else
        {
            int startValue = m_pAMPMPicker->value();
            int endValue = (m_pAMPMPicker->row(ChainitemList.at(0))-m_nItemAMAndFMCountPerPage/2) * m_pAMPMPicker->getItemSize().height();
            m_pAMPMPicker->SetCurrentIndex(m_pAMPMPicker->row(ChainitemList.at(0)));
            m_pAMPMPicker->PickerRebound(startValue,endValue);
        }
    }
}

QDate DateTimePicker::GetCurrentDate()
{
    return m_dateCurrent;
}

int DateTimePicker::GetCurrentHour()
{
    return m_nCurrentHour;
}

int DateTimePicker::GetCurrentMinute()
{
    return m_nCurrentMinute;
}

bool DateTimePicker::IsAMOrPM()
{
    return m_bAMOrPM;
}

void DateTimePicker::SetItemCountPerPage(int count)
{
    m_nItemCountPerPage = count;  
}
void DateTimePicker::SetCurrentFontSize(int fontSize)
{
    m_nCurrentFontSize = fontSize;
    if(m_pYearPicker)
       m_pYearPicker->SetCurrentFontSize(fontSize);
    if(m_pMonthPicker)
        m_pMonthPicker->SetCurrentFontSize(fontSize);
    if(m_pDayPicker)
        m_pDayPicker->SetCurrentFontSize(fontSize);
    if(m_pHourPicker)
        m_pHourPicker->SetCurrentFontSize(fontSize);
    if(m_pMinutePicker)
        m_pMinutePicker->SetCurrentFontSize(fontSize);
    if(m_pAMPMPicker)
        m_pAMPMPicker->SetCurrentFontSize(fontSize);
}
void DateTimePicker::SetYearFontStyle(Picker::eFontStyle type)
{
    if(m_pYearPicker)
        m_pYearPicker->SetFontStyle(type);
}
void DateTimePicker::SetMonthFontStyle(Picker::eFontStyle type)
{
    if(m_pMonthPicker)
        m_pMonthPicker->SetFontStyle(type);
}
void DateTimePicker::SetDayFontStyle(Picker::eFontStyle type)
{
    if(m_pDayPicker)
        m_pDayPicker->SetFontStyle(type);
}
void DateTimePicker::SetHourFontStyle(Picker::eFontStyle type)
{
    if(m_pHourPicker)
        m_pHourPicker->SetFontStyle(type);
}
void DateTimePicker::SetMinFontStyle(Picker::eFontStyle type)
{
    if(m_pMinutePicker)
        m_pMinutePicker->SetFontStyle(type);
}
void DateTimePicker::SetAMAndFMFontStyle(Picker::eFontStyle type)
{
    if(m_pAMPMPicker)
        m_pAMPMPicker->SetFontStyle(type);
}
void DateTimePicker::CreateYearPicker(int minYear, int maxYear, const QSize &itemSize,bool isUpdateYear)
{
    m_isUpdateYear = isUpdateYear;
    m_dateCurrent.setDate(minYear+1, 1, 1);
    m_nMinYear = minYear;
    m_nMaxYear = maxYear;
    if (NULL == m_pYearPicker)
    {
        m_pYearPicker = new Picker(this);
        m_pYearPicker->SetItemCountPerPage(m_nItemCountPerPage);
        m_pYearPicker->setPickType(Picker::EPickTypeYear);
        m_pYearPicker->setName("Year--");
        m_pYearPicker->installEventFilter(this);
        m_pYearPicker->viewport()->installEventFilter(this);
        connect(m_pYearPicker, SIGNAL(currentIndexChanged(int)), this, SLOT(onYearChanged(int)));
        connect(m_pYearPicker, SIGNAL(PaintEnd(QString)), this, SLOT(onPaintFinish(QString)));
    }
    if (m_pYearPicker->count())
    {
        m_pYearPicker->clear();
    }
    int count = m_nItemCountPerPage / 2;
    for (int i = 0; i < count; i++)
    {
        m_pYearPicker->InsertItem(i, "", itemSize, m_nCurrentFontSize);
    }
    int yearCount = maxYear-minYear+1;
    for (int i = 0; i < yearCount; i++)
    {
        m_pYearPicker->InsertItem(count+i, QString::number(minYear+i), itemSize, m_nCurrentFontSize);
    }
    for (int i = 0; i < count; i++)
    {
        m_pYearPicker->InsertItem(yearCount+count+i, "", itemSize, m_nCurrentFontSize);
    }
    m_pYearPicker->setPickerMinimum(-(m_nItemCountPerPage/2+1)*itemSize.height());
    m_pYearPicker->setPickerMaximum((yearCount+m_nItemCountPerPage/2)*itemSize.height());
    m_pYearPicker->setIsAnimation(true);
}

void DateTimePicker::CreateMonthPicker(const QSize &itemSize, eMonthPickerType type)
{
    QStringList qsMonth;
    if (eEngLishText == type)
    {
        qsMonth << "January" << "February" << "March" << "April" << "May" << "June" << "July"
                << "August" << "September" << "October" << "November" << "December";
    }
    else if (eEngLishAbbrText == type)
    {
        qsMonth << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun"
                << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";
    }
    else if (eEngLishWithComma == type)
    {
        qsMonth << "January," << "February," << "March," << "April," << "May," << "June," << "July,"
                << "August," << "September," << "October," << "November," << "December,";
    }
    else
    {
        qsMonth << "01" << "02" << "03" << "04" << "05" << "06" << "07" << "08"
                << "09" << "10" << "11" << "12";
    }
    if (NULL == m_pMonthPicker)
    {
        m_pMonthPicker = new Picker(this);
        m_pMonthPicker->SetItemCountPerPage(m_nItemCountPerPage);
        m_pMonthPicker->setPickType(Picker::EPickTypeMonth);
        m_pMonthPicker->SetCircular(true);
        m_pMonthPicker->setName("month");
        m_pMonthPicker->installEventFilter(this);
        m_pMonthPicker->viewport()->installEventFilter(this);
        connect(m_pMonthPicker, SIGNAL(currentIndexChanged(int)), this, SLOT(onMonthChanged(int)));
        //connect(m_pMonthPicker, SIGNAL(pressIndex(int)), this, SLOT(SaveCurrentMonth(int)));
        connect(m_pMonthPicker, SIGNAL(updateYear(int,int)), this, SLOT(onUpdateYearChanged(int,int)));
        connect(m_pMonthPicker, SIGNAL(PaintEnd(QString)), this, SLOT(onPaintFinish(QString)));

    }
    if (m_pMonthPicker->count())
    {
        m_pMonthPicker->clear();
    }
    for (int i = 0; i < 12; i++)
    {
        m_pMonthPicker->InsertItem(i, qsMonth.at(i), itemSize, m_nCurrentFontSize, i+1);
    }
    for (int i = 0; i < m_nItemCountPerPage; i++)
    {
        m_pMonthPicker->InsertItem(12+i, qsMonth.at(i), itemSize, m_nCurrentFontSize, i+1);
    }
}

void DateTimePicker::CreateMonthPicker(const QSize &itemSize, QStringList qsMonth)
{
    if (qsMonth.count() < 0)
    {
        return;
    }
    if (NULL == m_pMonthPicker)
    {
        m_pMonthPicker = new Picker(this);
        m_pMonthPicker->SetItemCountPerPage(m_nItemCountPerPage);
        m_pMonthPicker->setPickType(Picker::EPickTypeMonth);
        m_pMonthPicker->SetCircular(true);
        m_pMonthPicker->setName("month");
        m_pMonthPicker->installEventFilter(this);
        m_pMonthPicker->viewport()->installEventFilter(this);
        connect(m_pMonthPicker, SIGNAL(currentIndexChanged(int)), this, SLOT(onMonthChanged(int)));
        connect(m_pMonthPicker, SIGNAL(pressIndex(int)), this, SLOT(SaveCurrentMonth(int)));
        connect(m_pMonthPicker, SIGNAL(updateYear(int,int)), this, SLOT(onUpdateYearChanged(int,int)));
        connect(m_pMonthPicker, SIGNAL(PaintEnd(QString)), this, SLOT(onPaintFinish(QString)));
    }
    if (m_pMonthPicker->count())
    {
        m_pMonthPicker->clear();
    }
    for (int i = 0; i < qsMonth.count(); i++)
    {
        m_pMonthPicker->InsertItem(i, qsMonth.at(i), itemSize, m_nCurrentFontSize, i+1);
    }
    for (int i = 0; i < m_nItemCountPerPage; i++)
    {
        m_pMonthPicker->InsertItem(12+i, qsMonth.at(i), itemSize, m_nCurrentFontSize, i+1);
    }
}

void DateTimePicker::CreateDayPicker(int days, const QSize &itemSize)
{
    m_sizeDayPickerItem = itemSize;
    if (NULL == m_pDayPicker)
    {
        m_pDayPicker = new Picker(this);
        m_pDayPicker->SetItemCountPerPage(m_nItemCountPerPage);
        m_pDayPicker->setPickType(Picker::EPickTypeDay);
        m_pDayPicker->SetCircular(true);
        m_pDayPicker->setName("day");
        m_pDayPicker->installEventFilter(this);
        m_pDayPicker->viewport()->installEventFilter(this);
        connect(m_pDayPicker, SIGNAL(currentIndexChanged(int)), this, SLOT(onDayChanged(int)));
        connect(m_pDayPicker, SIGNAL(PaintEnd(QString)), this, SLOT(onPaintFinish(QString)));
        connect(m_pDayPicker, SIGNAL(pickerEnd(int)), this, SLOT(onPickFinish(int)));
    }
    if (m_pDayPicker->count())
    {
        m_pDayPicker->clear();
    }
    for (int i = 0; i < days; i++)
    {
        QString text = QString::number(i+1);
        if (i < 9)
            text.insert(0, "0");
        m_pDayPicker->InsertItem(i, text, itemSize, m_nCurrentFontSize);
    }
    for (int i = 0; i < m_nItemCountPerPage; i++)
    {
        QString text = QString::number(i+1);
        if (i < 9)
            text.insert(0, "0");
        m_pDayPicker->InsertItem(days+i, text, itemSize, m_nCurrentFontSize);
    }
}

void DateTimePicker::CreateHourPicker(const QSize &itemSize, bool b12HourSystem)
{
    m_b12HourSystem = b12HourSystem;
    if (NULL == m_pHourPicker)
    {
        m_pHourPicker = new Picker(this);
        m_pHourPicker->SetItemCountPerPage(m_nItemCountPerPage);
        m_pHourPicker->setPickType(Picker::EPickTypeHour);
        m_pHourPicker->SetCircular(true);
        m_pHourPicker->installEventFilter(this);
        m_pHourPicker->viewport()->installEventFilter(this);
        connect(m_pHourPicker, SIGNAL(currentIndexChanged(int)), this, SLOT(onHourChanged(int)));
        connect(m_pHourPicker, SIGNAL(PaintEnd(QString)), this, SLOT(onPaintFinish(QString)));
        connect(m_pHourPicker, SIGNAL(updateAmOrPm(int,int)), this, SLOT(onAMPMChanged(int,int)));

    }
    if (m_pHourPicker->count())
    {
        m_pHourPicker->clear();
    }
    int nMinHour, nHourCount;
    if (m_b12HourSystem)
    {
        if(m_pAMPMPicker)
        {
            m_pAMPMPicker->show();
        }
        nMinHour = 1;
        nHourCount = 12;
    }
    else
    {
        if(m_pAMPMPicker)
        {
            m_pAMPMPicker->hide();
        }
        nMinHour = 0;
        nHourCount = 24;
    }
    for (int i = 0; i < nHourCount; i++)
    {
        QString text = QString::number(i+nMinHour);
        if (i < 10 - nMinHour)
        {
            text.insert(0, "0");
        }
        m_pHourPicker->InsertItem(i, text, itemSize, m_nCurrentFontSize,i+1);
    }
    for (int i = 0; i < m_nItemCountPerPage; i++)
    {
        QString text = QString::number(i+nMinHour);
        if (i < 10 - nMinHour)
        {
            text.insert(0, "0");
        }
        m_pHourPicker->InsertItem(nHourCount+i, text, itemSize, m_nCurrentFontSize,i+1);
    }
}

void DateTimePicker::CreateMinutePicker(const QSize &itemSize)
{
    if (NULL == m_pMinutePicker)
    {
        m_pMinutePicker = new Picker(this);
        m_pMinutePicker->SetItemCountPerPage(m_nItemCountPerPage);
        m_pMinutePicker->setPickType(Picker::EPickTypeMin);
        m_pMinutePicker->SetCircular(true);
        m_pMinutePicker->installEventFilter(this);
        m_pMinutePicker->viewport()->installEventFilter(this);
        connect(m_pMinutePicker, SIGNAL(currentIndexChanged(int)), this, SLOT(onMinuteChanged(int)));
        connect(m_pMinutePicker, SIGNAL(PaintEnd(QString)), this, SLOT(onPaintFinish(QString)));
    }
    if (m_pMinutePicker->count())
    {
        m_pMinutePicker->clear();
    }
    for (int i = 0; i < 60; i++)
    {
        QString text = QString::number(i);
        if (i < 10)
            text.insert(0, "0");
        m_pMinutePicker->InsertItem(i, text, itemSize, m_nCurrentFontSize);
    }
    for (int i = 0; i < m_nItemCountPerPage; i++)
    {
        QString text = QString::number(i);
        if (i < 9)
            text.insert(0, "0");
        m_pMinutePicker->InsertItem(60+i, text, itemSize, m_nCurrentFontSize);
    }
}

void DateTimePicker::CreateAMPMPicker(const QSize &itemSize,int nPage,bool isSliderByTime)
{
    if (NULL == m_pAMPMPicker)
    {
        m_pAMPMPicker = new Picker(this);
        m_pAMPMPicker->SetItemCountPerPage(nPage);
        m_pAMPMPicker->installEventFilter(this);
        m_pAMPMPicker->viewport()->installEventFilter(this);
        m_pAMPMPicker->setPickType(Picker::EPickTypeAmAndPm);
        m_nItemAMAndFMCountPerPage = nPage;
        m_IsSliderByTime = isSliderByTime;
        connect(m_pAMPMPicker, SIGNAL(currentIndexChanged(int)), this, SLOT(onAMPMChanged(int)));
        connect(m_pAMPMPicker, SIGNAL(PaintEnd(QString)), this, SLOT(onPaintFinish(QString)));
    }  
    if (m_pAMPMPicker->count())
    {
        m_pAMPMPicker->clear();
    }
    int count = nPage / 2;
    for (int i = 0; i < count; i++)
    {
        m_pAMPMPicker->InsertItem(i, "", itemSize, m_nCurrentFontSize);
    }
    m_pAMPMPicker->InsertItem(count, "AM", itemSize, m_nCurrentFontSize);
    m_pAMPMPicker->InsertItem(count+1, "PM", itemSize, m_nCurrentFontSize);
    for (int i = 0; i < count; i++)
    {
        m_pAMPMPicker->InsertItem(2+count+i, "", itemSize, m_nCurrentFontSize);
    }
    m_pAMPMPicker->setPickerMinimum(-(nPage/2+1)*itemSize.height());
    m_pAMPMPicker->setPickerMaximum((2+nPage/2)*itemSize.height());
    m_pAMPMPicker->setIsAnimation(true);
}
void DateTimePicker::YearPickerHide()
{
    if(m_pYearPicker)
        m_pYearPicker->hide();
}
void DateTimePicker::SetYearPickerGeometry(int x, int y, int w, int h)
{
    if (m_pYearPicker)
        m_pYearPicker->setGeometry(x, y, w, h);
}

void DateTimePicker::SetMonthPickerGeometry(int x, int y, int w, int h)
{
    if (m_pMonthPicker)
        m_pMonthPicker->setGeometry(x, y, w, h);
}

void DateTimePicker::SetDayPickerGeometry(int x, int y, int w, int h)
{
    if (m_pDayPicker)
        m_pDayPicker->setGeometry(x, y, w, h);
}

void DateTimePicker::SetHourPickerGeometry(int x, int y, int w, int h)
{
    if (m_pHourPicker)
        m_pHourPicker->setGeometry(x, y, w, h);
}

void DateTimePicker::SetMinutePickerGeometry(int x, int y, int w, int h)
{
    if (m_pMinutePicker)
        m_pMinutePicker->setGeometry(x, y, w, h);
}

void DateTimePicker::SetAMPMPickerGeometry(int x, int y, int w, int h)
{
    if (m_pAMPMPicker)
        m_pAMPMPicker->setGeometry(x, y, w, h);
}

void DateTimePicker::SetPickerGeometry(int x, int y, int w, int h, DateTimePicker::ePickerType type)
{
    if (eYearPicker == type)
    {
        if (m_pYearPicker)
            m_pYearPicker->setGeometry(x, y, w, h);
    }
    else if (eMonthPicker == type)
    {
        if (m_pMonthPicker)
            m_pMonthPicker->setGeometry(x, y, w, h);
    }
    else if (eDayPicker == type)
    {
        if (m_pDayPicker)
            m_pDayPicker->setGeometry(x, y, w, h);
    }
    else if (eHourPicker == type)
    {
        if (m_pHourPicker)
            m_pHourPicker->setGeometry(x, y, w, h);
    }
    else if (eMinutePicker == type)
    {
        if (m_pMinutePicker)
            m_pMinutePicker->setGeometry(x, y, w, h);
    }
    else if (eAMPMPicker == type)
    {
        if (m_pAMPMPicker)
            m_pAMPMPicker->setGeometry(x, y, w, h);
    }
}

void DateTimePicker::SetPickerFontSize(int fontSize, DateTimePicker::ePickerType type)
{
    m_mapFontSize.insert(type, fontSize);
}

void DateTimePicker::SetPickerEnabled(bool enabled, DateTimePicker::ePickerType type)
{
    if (eYearPicker == type)
    {
        if (m_pYearPicker)
        {
            m_pYearPicker->setEnabled(enabled);
        }
    }
    else if (eMonthPicker == type)
    {
        if (m_pMonthPicker)
        {
            m_pMonthPicker->setEnabled(enabled);
        }
    }
    else if (eDayPicker == type)
    {
        if (m_pDayPicker)
        {
            m_pDayPicker->setEnabled(enabled);
        }
    }
    else if (eHourPicker == type)
    {
        if (m_pHourPicker)
        {
            m_pHourPicker->setEnabled(enabled);
        }
    }
    else if (eMinutePicker == type)
    {
        if (m_pMinutePicker)
        {
            m_pMinutePicker->setEnabled(enabled);
        }
    }
    else if (eAMPMPicker == type)
    {
        if (m_pAMPMPicker)
        {
            m_pAMPMPicker->setEnabled(enabled);
        }
    }
    else if (eAllPikcer == type)
    {
        m_isAllPickEnable = enabled;
        this->setEnabled(enabled);
        if (m_pYearPicker)
        {
            m_pYearPicker->setEnabled(enabled);
            m_pYearPicker->SetPickerEnabel(enabled);
        }
        if (m_pMonthPicker)
        {
            m_pMonthPicker->setEnabled(enabled);
            m_pMonthPicker->SetPickerEnabel(enabled);
        }
        if (m_pDayPicker)
        {
            m_pDayPicker->setEnabled(enabled);
            m_pDayPicker->SetPickerEnabel(enabled);
        }
        if (m_pHourPicker)
        {
            m_pHourPicker->setEnabled(enabled);
            m_pHourPicker->SetPickerEnabel(enabled);
        }
        if (m_pMinutePicker)
        {
            m_pMinutePicker->setEnabled(enabled);
            m_pMinutePicker->SetPickerEnabel(enabled);
        }
        if (m_pAMPMPicker)
        {
            m_pAMPMPicker->setEnabled(enabled);
            m_pAMPMPicker->SetPickerEnabel(enabled);
        }
    }
}

bool DateTimePicker::GetIs12HourSystem()
{
    return m_b12HourSystem;
}

void DateTimePicker::SetCurColor(QColor color)
{
    if (m_pYearPicker)
    {
        m_pYearPicker->SetCurColor(color);
    }
    if (m_pMonthPicker)
    {
        m_pMonthPicker->SetCurColor(color);
    }
    if (m_pDayPicker)
    {
        m_pDayPicker->SetCurColor(color);
    }
    if (m_pHourPicker)
    {
      m_pHourPicker->SetCurColor(color);
    }
    if (m_pMinutePicker)
    {
        m_pMinutePicker->SetCurColor(color);
    }
    if (m_pAMPMPicker)
    {
        m_pAMPMPicker->SetCurColor(color);
    }
}
void DateTimePicker::setAlPha(qreal al)
{
    if (m_pYearPicker)
    {
        m_pYearPicker->setAlPha(al);
    }
    if (m_pMonthPicker)
    {
        m_pMonthPicker->setAlPha(al);
    }
    if (m_pDayPicker)
    {
        m_pDayPicker->setAlPha(al);
    }
    if (m_pHourPicker)
    {
      m_pHourPicker->setAlPha(al);
    }
    if (m_pMinutePicker)
    {
        m_pMinutePicker->setAlPha(al);
    }
    if (m_pAMPMPicker)
    {
        m_pAMPMPicker->setAlPha(al);
    }
}
void DateTimePicker::SetUpAndDownColor(QColor color)
{
    if (m_pYearPicker)
    {
        m_pYearPicker->SetUpAndDownColor(color);
    }
    if (m_pMonthPicker)
    {
        m_pMonthPicker->SetUpAndDownColor(color);
    }
    if (m_pDayPicker)
    {
        m_pDayPicker->SetUpAndDownColor(color);
    }
    if (m_pHourPicker)
    {
      m_pHourPicker->SetUpAndDownColor(color);
    }
    if (m_pMinutePicker)
    {
        m_pMinutePicker->SetUpAndDownColor(color);
    }
    if (m_pAMPMPicker)
    {
        m_pAMPMPicker->SetUpAndDownColor(color);
    }
}
void DateTimePicker::UpdateMonthPickerText(QStringList qsMonth)
{
    if (m_pMonthPicker)
    {
        for (int i = 0; i < 12; i++)
        {
            m_pMonthPicker->UpdateItemText(i, qsMonth.at(i));
        }
        for (int i = 0; i < m_pMonthPicker->count() - 12; i++)
        {
            m_pMonthPicker->UpdateItemText(12 + i, qsMonth.at(i));
        }
    }
}

void DateTimePicker::UpdateMonthPickerText(DateTimePicker::eMonthPickerType type)
{
    QStringList qsMonth;
    if (eEngLishText == type)
    {
        qsMonth << "January" << "February" << "March" << "April" << "May" << "June" << "July"
                << "August" << "September" << "October" << "November" << "December";
    }
    else if (eEngLishAbbrText == type)
    {
        qsMonth << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun"
                << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";
    }
    else if (eEngLishWithComma == type)
    {
        qsMonth << "January," << "February," << "March," << "April," << "May," << "June," << "July,"
                << "August," << "September," << "October," << "November," << "December,";
    }
    else
    {
        qsMonth << "01" << "02" << "03" << "04" << "05" << "06" << "07" << "08"
                << "09" << "10" << "11" << "12";
    }
    UpdateMonthPickerText(qsMonth);
}
void DateTimePicker::UpdateAMAndMMPickerText(bool isChanese)
{
    if(m_pAMPMPicker)
    {
        if(isChanese)
        {
            int count = m_nItemAMAndFMCountPerPage / 2;
            m_pAMPMPicker->UpdateItemText(count, "上午");
            m_pAMPMPicker->UpdateItemText(count+1, "下午");
        }
        else
        {
            int count = m_nItemAMAndFMCountPerPage / 2;
            m_pAMPMPicker->UpdateItemText(count, "AM");
            m_pAMPMPicker->UpdateItemText(count+1, "PM");
        }
    }
}
void DateTimePicker::UpdateAMAndMMPickerText(QString StrAM,QString StrPM)
{
    if(m_pAMPMPicker)
    {
        int count = m_nItemAMAndFMCountPerPage / 2;
        m_pAMPMPicker->UpdateItemText(count, StrAM);
        m_pAMPMPicker->UpdateItemText(count+1,StrPM);
    }
}
bool DateTimePicker::getIsUpdateAmOrFm()
{
    return m_isUpdateAMrOFM;
}
int DateTimePicker::UpdateDayPickerByYear(int year,bool isAnimation)
{
    int currentDay = m_dateCurrent.day();
    if (year == m_dateCurrent.year())
    {
        return currentDay;
    }
    if (2 == m_dateCurrent.month())
    {
        QDate date(year, 2, 1);
        int days = date.daysInMonth();
        if (days != m_dateCurrent.daysInMonth())
        {
            int nindex = 0;
            CreateDayPicker(days, m_sizeDayPickerItem);
            if(currentDay>days)
            {
                currentDay = days;
                QListWidgetItem* pItem = m_pDayPicker->item(currentDay -1);
                if(pItem)
                {
                    if(!isAnimation)
                    {
                        nindex = m_pDayPicker->row(pItem);
                        m_pDayPicker->SetCurrentIndex(nindex);
                        m_pDayPicker->scrollToItem(pItem, QAbstractItemView::PositionAtCenter);
                    }
                    else
                    {
                        int startValue = m_pDayPicker->value();
                        int endValue = (m_pDayPicker->row(pItem)-m_nItemCountPerPage/2) * m_pDayPicker->getItemSize().height();
                        m_pDayPicker->SetCurrentIndex(m_pDayPicker->row(pItem));
                        m_pDayPicker->PickerRebound(startValue,endValue);
                    }
                }
            }
            else if(currentDay < (m_nItemCountPerPage /2 +1 ))
            {
                int day = currentDay + days;
                QListWidgetItem* pItem = m_pDayPicker->item(day -1);
                if(pItem)
                {
                    if(!isAnimation)
                    {
                        nindex = m_pDayPicker->row(pItem);
                        m_pDayPicker->SetCurrentIndex(nindex);
                        m_pDayPicker->scrollToItem(pItem, QAbstractItemView::PositionAtCenter);
                    }
                    else
                    {
                        int startValue = m_pDayPicker->value();
                        int endValue = (m_pDayPicker->row(pItem)-m_nItemCountPerPage/2) * m_pDayPicker->getItemSize().height();
                        m_pDayPicker->SetCurrentIndex(m_pDayPicker->row(pItem));
                        m_pDayPicker->PickerRebound(startValue,endValue);
                    }
                }
            }
            else
            {
                QListWidgetItem* pItem = m_pDayPicker->item(currentDay -1);
                if(pItem)
                {
                    if(!isAnimation)
                    {
                        nindex = m_pDayPicker->row(pItem);
                        m_pDayPicker->SetCurrentIndex(nindex);
                        m_pDayPicker->scrollToItem(pItem, QAbstractItemView::PositionAtCenter);
                    }
                    else
                    {
                        int startValue = m_pDayPicker->value();
                        int endValue = (m_pDayPicker->row(pItem)-m_nItemCountPerPage/2) * m_pDayPicker->getItemSize().height();
                        m_pDayPicker->SetCurrentIndex(m_pDayPicker->row(pItem));
                        m_pDayPicker->PickerRebound(startValue,endValue);
                    }
                }
            }
        }
    }
    return currentDay;
}

int DateTimePicker::UpdateDayPickerByMonth(int month,bool isAnimation)
{
    int currentDay = m_dateCurrent.day();
    int currentYear = m_dateCurrent.year();
    QDate date(currentYear, month, 1);
    int days = date.daysInMonth();
    CreateDayPicker(days, m_sizeDayPickerItem);
    int nindex = 0;
    if(currentDay>days)
    {
        currentDay = days;
        QListWidgetItem* pItem = m_pDayPicker->item(currentDay -1);
        if(pItem)
        {
            if(!isAnimation)
            {
                nindex = m_pDayPicker->row(pItem);
                m_pDayPicker->SetCurrentIndex(nindex);
                m_pDayPicker->scrollToItem(pItem, QAbstractItemView::PositionAtCenter);
            }
            else
            {
                int startValue = m_pDayPicker->value();
                int endValue = (m_pDayPicker->row(pItem)-m_nItemCountPerPage/2) * m_pDayPicker->getItemSize().height();
                m_pDayPicker->SetCurrentIndex(m_pDayPicker->row(pItem));
                m_pDayPicker->PickerRebound(startValue,endValue);
            }
        }
    }
    else if(currentDay < (m_nItemCountPerPage /2 +1 ))
    {
        int day = currentDay + days;
        QListWidgetItem* pItem = m_pDayPicker->item(day -1);
        if(pItem)
        {
            if(!isAnimation)
            {
                nindex = m_pDayPicker->row(pItem);
                m_pDayPicker->SetCurrentIndex(nindex);
                m_pDayPicker->scrollToItem(pItem, QAbstractItemView::PositionAtCenter);
            }
            else
            {
                int startValue = m_pDayPicker->value();
                int endValue = (m_pDayPicker->row(pItem)-m_nItemCountPerPage/2) * m_pDayPicker->getItemSize().height();
                m_pDayPicker->SetCurrentIndex(m_pDayPicker->row(pItem));
                m_pDayPicker->PickerRebound(startValue,endValue);
            }
        }
    }
    else
    {
        QListWidgetItem* pItem = m_pDayPicker->item(currentDay -1);
        if(pItem)
        {
            if(!isAnimation)
            {
                nindex = m_pDayPicker->row(pItem);
                m_pDayPicker->SetCurrentIndex(nindex);
                m_pDayPicker->scrollToItem(pItem, QAbstractItemView::PositionAtCenter);
            }
            else
            {
                int startValue = m_pDayPicker->value();
                int endValue = (m_pDayPicker->row(pItem)-m_nItemCountPerPage/2) * m_pDayPicker->getItemSize().height();
                m_pDayPicker->SetCurrentIndex(m_pDayPicker->row(pItem));
                m_pDayPicker->PickerRebound(startValue,endValue);
            }
        }
    }
    return currentDay;
}

bool DateTimePicker::MouseEvent(QObject *object, QEvent *event)
{
    const QEvent::Type eventType = event->type();
    QMoveEvent* const mouseEvent = static_cast<QMoveEvent*>(event);
    if(!mouseEvent)
        return true;

    switch (eventType)
    {

    case QEvent::MouseButtonPress:
    {
        if(!m_isPickSlide)
        {
            if(m_isAllPickEnable)
            {
               if(m_pYearPicker &&(m_pYearPicker->viewport() == object||m_pYearPicker == object))
               {
                   SetPickerEnabled(true,eYearPicker);
                   SetPickerEnabled(false,eMonthPicker);
                   SetPickerEnabled(false,eDayPicker);
                   SetPickerEnabled(false,eHourPicker);
                   SetPickerEnabled(false,eMinutePicker);
                   SetPickerEnabled(false,eAMPMPicker);
               }
               else if(m_pMonthPicker&&(m_pMonthPicker->viewport() == object||m_pMonthPicker == object))
               {
                   SetPickerEnabled(false,eYearPicker);
                   SetPickerEnabled(true,eMonthPicker);
                   SetPickerEnabled(false,eDayPicker);
                   SetPickerEnabled(false,eHourPicker);
                   SetPickerEnabled(false,eMinutePicker);
                   SetPickerEnabled(false,eAMPMPicker);
               }
               else if(m_pDayPicker&&(m_pDayPicker->viewport() == object||m_pDayPicker == object))
               {
                   m_pDayPickerAnimation = true;
                   SetPickerEnabled(false,eYearPicker);
                   SetPickerEnabled(false,eMonthPicker);
                   SetPickerEnabled(true,eDayPicker);
                   SetPickerEnabled(false,eHourPicker);
                   SetPickerEnabled(false,eMinutePicker);
                   SetPickerEnabled(false,eAMPMPicker);
               }
               else if(m_pHourPicker&&(m_pHourPicker->viewport() == object || m_pHourPicker == object))
               {
                   SetPickerEnabled(false,eYearPicker);
                   SetPickerEnabled(false,eMonthPicker);
                   SetPickerEnabled(false,eDayPicker);
                   SetPickerEnabled(true,eHourPicker);
                   SetPickerEnabled(false,eMinutePicker);
                   SetPickerEnabled(false,eAMPMPicker);
               }
               else if(m_pMinutePicker&&(m_pMinutePicker->viewport() == object||m_pMinutePicker == object))
               {
                   SetPickerEnabled(false,eYearPicker);
                   SetPickerEnabled(false,eMonthPicker);
                   SetPickerEnabled(false,eDayPicker);
                   SetPickerEnabled(false,eHourPicker);
                   SetPickerEnabled(true,eMinutePicker);
                   SetPickerEnabled(false,eAMPMPicker);
               }
               else if(m_pAMPMPicker&&(m_pAMPMPicker->viewport() == object||m_pAMPMPicker == object))
               {
                   SetPickerEnabled(false,eYearPicker);
                   SetPickerEnabled(false,eMonthPicker);
                   SetPickerEnabled(false,eDayPicker);
                   SetPickerEnabled(false,eHourPicker);
                   SetPickerEnabled(false,eMinutePicker);
                   SetPickerEnabled(true,eAMPMPicker);
               }
            }
           m_isPaintPickEnd = false;
           m_isPickSlide = true;
        }
        break;
    }
    case QEvent::MouseMove:
    {
        break;
    }
    case QEvent::MouseButtonRelease:
    {
       m_isPickSlide = false;
       if(!m_isPickSlide && m_isPaintPickEnd)
       {
           if(m_isAllPickEnable)
           {

               if(!m_pDayPickerAnimation)
               {
                SetPickerEnabled(true,eYearPicker);
                SetPickerEnabled(true,eMonthPicker);
                SetPickerEnabled(true,eDayPicker);
                SetPickerEnabled(true,eHourPicker);
                SetPickerEnabled(true,eMinutePicker);
                SetPickerEnabled(true,eAMPMPicker);
               }
               else
               {
                    if(m_pDayPicker)
                    {
                        if(m_pDayPicker->getIsAnimatonEnd())
                        {
                            SetPickerEnabled(true,eYearPicker);
                            SetPickerEnabled(true,eMonthPicker);
                            SetPickerEnabled(true,eDayPicker);
                            SetPickerEnabled(true,eHourPicker);
                            SetPickerEnabled(true,eMinutePicker);
                            SetPickerEnabled(true,eAMPMPicker);
                        }
                     }
                     m_pDayPickerAnimation = false;
               }
           }
       }
       break;
    }
    default:
        break;
    }
    return QObject::eventFilter(object, event);
}

void DateTimePicker::onYearChanged(int year)
{
    int showYear = m_dateCurrent.year();
    if (m_pYearPicker)
    {
        QString text = m_pYearPicker->GetItemText(year);
        showYear = text.toInt();
    }
    if (m_pDayPicker)
    {
        m_needUpdateYear = year;
        if(!m_pDayPicker->getIsAnimatonEnd())
        {
            m_IsneedUpdateYear = true;
            return ;
        }
        else
        {
            m_IsneedUpdateYear = false;
        }
        int currentDay = UpdateDayPickerByYear(showYear);
        m_dateCurrent.setDate(showYear, m_dateCurrent.month(), currentDay);
    }
    else
    {
        m_dateCurrent.setDate(showYear, m_dateCurrent.month(), m_dateCurrent.day());
    }
    emit currentDateTimeChanged();
}

void DateTimePicker::onMonthChanged(int month)
{
    int showMonth = 1;
    if (m_pMonthPicker)
    {
        showMonth = m_pMonthPicker->GetItemSpecifiedID(month);
    }
    if (m_pDayPicker)
    {
        m_needUpdateMon = month;
        if(!m_pDayPicker->getIsAnimatonEnd())
        {
            m_IsneedUpdateMon = true;
            return ;
        }
        else
        {
            m_IsneedUpdateMon = false;
        }
        int currentDay = UpdateDayPickerByMonth(showMonth);
        int year = m_dateCurrent.year();
        m_dateCurrent.setDate(year, showMonth, currentDay);
    }
    else
    {
        int year = m_dateCurrent.year();
        int day = m_dateCurrent.day();
        m_dateCurrent.setDate(year, showMonth, day);
    }
    emit currentDateTimeChanged();
}

void DateTimePicker::onUpdateYearChanged(int step,int month)
{
    if(!m_isUpdateYear)
        return;
    m_recordDirection = step;
    int showMonth = 0;
    if (m_pMonthPicker)
    {
        showMonth = m_pMonthPicker->GetItemSpecifiedID(month);
    }
    if(0>step)
    {
        if(1 == showMonth)
        {
            m_recordMonth = showMonth;
        }
        if(0>m_recordDirection )
        {
           if(1 == m_recordMonth)
           {
               if(12 == showMonth)
               {
                   if(m_dateCurrent.year()-1<m_nMinYear)
                   {
                       m_dateCurrent.setDate(m_nMinYear,m_dateCurrent.month(),m_dateCurrent.day());
                   }
                   else
                   {
                    m_dateCurrent.setDate(m_dateCurrent.year()-1,m_dateCurrent.month(),m_dateCurrent.day());
                   }
                   m_recordMonth = 0;
                   emit UpdateYear(-1);
               }
           }
        }
        else if(0<m_recordDirection)
        {
            m_recordMonth = 0;
        }
    }
    else if(0<step)
    {
        if(12 == showMonth)
        {
            m_recordMonth = showMonth;
        }
        if(0<m_recordDirection )
        {
            if(12 == m_recordMonth)
            {
                if(1 == showMonth)
                {
                    if(m_dateCurrent.year()+1>m_nMaxYear)
                    {
                        m_dateCurrent.setDate(m_nMaxYear,m_dateCurrent.month(),m_dateCurrent.day());
                    }
                    else
                    {
                        m_dateCurrent.setDate(m_dateCurrent.year()+1,m_dateCurrent.month(),m_dateCurrent.day());
                    }
                    m_recordMonth = 0;
                    emit UpdateYear(1);
                }
            }
        }
        else if(0>m_recordDirection)
        {
           m_recordMonth = 0;
        }
    }
}
void DateTimePicker::onDayChanged(int day)
{
    if (m_pDayPicker)
    {
        int showDay = 1;
        QString text = m_pDayPicker->GetItemText(day);
        showDay = text.toInt();
        m_dateCurrent.setDate(m_dateCurrent.year(), m_dateCurrent.month(), showDay);
        emit currentDateTimeChanged();
    }
}

void DateTimePicker::onHourChanged(int hour)
{
    if (m_pHourPicker)
    {
        QString text = m_pHourPicker->GetItemText(hour);
        m_nCurrentHour = text.toInt();
        emit currentDateTimeChanged();
    }
}

void DateTimePicker::onMinuteChanged(int minute)
{
    if (m_pMinutePicker)
    {
        QString text = m_pMinutePicker->GetItemText(minute);
        m_nCurrentMinute = text.toInt();
        emit currentDateTimeChanged();
    }
}

void DateTimePicker::onAMPMChanged(int ampm)
{
    if (m_pAMPMPicker)
    {
        QString text = m_pAMPMPicker->GetItemText(ampm);
        if (("AM" == text) || ("上午" == text))
        {
            m_bAMOrPM = true;
        }
        else if (("PM" == text)||("下午" == text))
        {
            m_bAMOrPM = false;
        }
        emit currentDateTimeChanged();
    }
}
void DateTimePicker::onAMPMChanged(int UpOrDown,int hour)
{
    if(!m_IsSliderByTime)
        return;
    m_recordAMAndPMDirection = UpOrDown;
    bool isAMOrPM = IsAMOrPM();


    if (m_pHourPicker)
    {
        int nhour = 0;
         nhour = m_pHourPicker->GetItemSpecifiedID(hour);
        if(0>UpOrDown)
        {
            if(12 == nhour)
            {
                m_recordHour = nhour;
            }
            if(0>m_recordAMAndPMDirection )
            {
               if(12 == m_recordHour)
               {
                   if(11 == nhour)
                   {
                       m_recordHour = 0;
                       if(isAMOrPM)
                       {
                         SetCurrentAMPM(false);
                       }
                       else
                       {
                         SetCurrentAMPM(true);
                       }
                   }
               }
            }
            else if(0<m_recordAMAndPMDirection)
            {
                m_recordHour = 0;
            }
        }
        else if(0<UpOrDown)
        {
            if(11 == nhour)
            {
                m_recordHour = nhour;
            }
            if(0<m_recordAMAndPMDirection )
            {
                if(11 == m_recordHour)
                {
                    if(12 == nhour)
                    {
                        m_recordHour = 0;
                        if(isAMOrPM)
                        {
                          SetCurrentAMPM(false);
                        }
                        else
                        {
                          SetCurrentAMPM(true);
                        }
                    }
                }
            }
            else if(0>m_recordAMAndPMDirection)
            {
               m_recordHour = 0;
            }
        }
    }
}
void DateTimePicker::onPaintFinish(QString name)
{
    m_isPaintPickEnd = true;
    if(!m_isPickSlide && m_isPaintPickEnd)
    {
        if(m_isAllPickEnable)
        {
           if("day" == name)
           {
               if(m_pDayPicker)
               {
                   if(m_pDayPicker->getIsAnimatonEnd() && (!m_pDayPickerAnimation))
                   {
                       SetPickerEnabled(true,eDayPicker);
                       SetPickerEnabled(true,eDayPicker);
                       SetPickerEnabled(true,eHourPicker);
                       SetPickerEnabled(true,eMinutePicker);
                       SetPickerEnabled(true,eAMPMPicker);
                       SetPickerEnabled(true,eYearPicker);
                       SetPickerEnabled(true,eMonthPicker);
                   }
               }
           }
        }
    }
}

void DateTimePicker::onPickFinish(int type)
{
    if(m_pDayPicker)
    {
        if(Picker::EPickTypeDay == (Picker::ePickType)type)
        {
            if(m_IsneedUpdateMon)
            {
                m_IsneedUpdateMon = false;
                onMonthChanged(m_needUpdateMon);
            }
            if(m_IsneedUpdateYear)
            {
                m_IsneedUpdateYear = false;
                onYearChanged(m_needUpdateYear);
            }
        }
    }
}
void DateTimePicker::initPicker()
{
   m_isPickSlide = false;
   m_isPaintPickEnd = true;
}
void DateTimePicker::PickerPosition(double xmove,double ymove,double Xzoom,double YZoom,int nrow,ePickerType type)
{
    switch (type) {
    case eYearPicker:
    {
        if(m_pYearPicker)
        {
            m_pYearPicker->setPickerPositionHandle(xmove,ymove,Xzoom,YZoom,nrow);
        }
    }
        break;
    case eMonthPicker:
    {
      if(m_pMonthPicker)
      {
          m_pMonthPicker->setPickerPositionHandle(xmove,ymove,Xzoom,YZoom,nrow);
      }
    }
        break;
    case eDayPicker:
    {
        if(m_pDayPicker)
        {
            m_pDayPicker->setPickerPositionHandle(xmove,ymove,Xzoom,YZoom,nrow);
        }
    }
        break;
    case eHourPicker:
    {
        if(m_pHourPicker)
        {
            m_pHourPicker->setPickerPositionHandle(xmove,ymove,Xzoom,YZoom,nrow);
        }
    }
        break;
    case eMinutePicker:
    {
        if(m_pMinutePicker)
        {
            m_pMinutePicker->setPickerPositionHandle(xmove,ymove,Xzoom,YZoom,nrow);
        }
    }
        break;
    case eAMPMPicker:
    {
        if(m_pAMPMPicker)
        {
            m_pAMPMPicker->setPickerPositionHandle(xmove,ymove,Xzoom,YZoom,nrow);
        }
    }
        break;
    case eAllPikcer:
    {

    }
        break;
    default:
        break;
    }
}
