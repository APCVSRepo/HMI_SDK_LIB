#include "Picker.h"
#include <QMouseEvent>
#include <QTouchEvent>
#include <QScrollBar>
#include <QStyledItemDelegate>
#include <QPainter>
class CPickerDelegate : public QStyledItemDelegate
{
public:
    CPickerDelegate(Picker* picker);
protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
private:
    Picker*        m_pPicker;
};

CPickerDelegate::CPickerDelegate(Picker* picker)
{
    m_pPicker = picker;
}
void CPickerDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)const
{
    int Currentindex = m_pPicker->getCurrentIndex();
    Picker::eFontStyle FontStyle = m_pPicker->GetFontStyle();
    int nItemCountPerPage = m_pPicker->getItemCountPerPage();
    int fontSize = m_pPicker->getCurrentFontSize();
    qreal valueShear;
    QColor UpAndDowncolor = m_pPicker->getUpAndDownColor();
    QColor curcolor = m_pPicker->getCurColor();
    switch (FontStyle) {
    case Picker::eDefaultFontStyle:
    {
        if(3 == nItemCountPerPage)
        {
            if (index.row()== Currentindex - 1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0, 0);
                t.rotate(0.0, Qt::XAxis);
                t.translate(0,0);
                painter->setTransform(t);
                painter->drawText(option.rect,Qt::AlignLeft|Qt::AlignVCenter,index.data().toString());
            }
           else if (index.row() == Currentindex)
            {
                valueShear = 0.5;
                painter->setPen(curcolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0, 0);
                t.rotate(0.0, Qt::XAxis);
                t.translate(0,0);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignLeft|Qt::AlignVCenter,index.data().toString());
            }
           else if (index.row() == Currentindex+1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0, 0);
                t.rotate(0.0, Qt::XAxis);
                t.translate(0,0);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignLeft|Qt::AlignVCenter,index.data().toString());
            }
        }
        else if(5 == nItemCountPerPage)
        {

            if (index.row()== Currentindex-2)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0,0);
                t.rotate(45.0, Qt::XAxis);
                if(m_pPicker->getPositionHandle().end()!= m_pPicker->getPositionHandle().find(1))
                {
                    if(1 == m_pPicker->getPositionHandle().find(1).value().i_row)
                    {
                        t.scale(1.03+m_pPicker->getPositionHandle().find(1).value().d_xZoom, \
                                1+m_pPicker->getPositionHandle().find(1).value().d_yZoom);
                        t.translate(-1+m_pPicker->getPositionHandle().find(1).value().d_xMove,\
                                    -1.5+m_pPicker->getPositionHandle().find(1).value().d_yMove);
                    }
                    else
                    {
                        t.scale(1.03, 1);
                        t.translate(-1,-1.5);
                    }
                }
                else
                {
                    t.scale(1.03, 1);
                    t.translate(-1,-1.5);
                }
                painter->setTransform(t);
                painter->drawText(option.rect,Qt::AlignCenter,index.data().toString());
            }
            else if (index.row() == Currentindex-1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0,0);
                t.rotate(30.0, Qt::XAxis);
                if(m_pPicker->getPositionHandle().end()!= m_pPicker->getPositionHandle().find(2))
                {
                    if(2 == m_pPicker->getPositionHandle().find(2).value().i_row)
                    {
                        t.scale(1+m_pPicker->getPositionHandle().find(2).value().d_xZoom,\
                                1+m_pPicker->getPositionHandle().find(2).value().d_yZoom);
                        t.translate(0+m_pPicker->getPositionHandle().find(2).value().d_xMove,\
                                    -4+m_pPicker->getPositionHandle().find(2).value().d_yMove);
                    }
                    else
                    {
                        t.scale(1, 1);
                        t.translate(0,-4);
                    }
                }
                else
                {
                    t.scale(1, 1);
                    t.translate(0,-4);
                }
                painter->setTransform(t);
                painter->drawText(option.rect,Qt::AlignCenter,index.data().toString());
            }
           else if (index.row() == Currentindex)
            {
                valueShear = 0.5;
                painter->setPen(curcolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0,0);
                t.rotate(0.0, Qt::XAxis);
               // t.scale(1, 1);
                t.translate(0,0);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignCenter,index.data().toString());
            }
           else if (index.row()== Currentindex+1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0,0);
                t.rotate(-30.0, Qt::XAxis);
                if(m_pPicker->getPositionHandle().end()!= m_pPicker->getPositionHandle().find(4))
                {
                    if(4 == m_pPicker->getPositionHandle().find(4).value().i_row)
                    {
                        t.scale(1.1+m_pPicker->getPositionHandle().find(4).value().d_xZoom, \
                                1.2+m_pPicker->getPositionHandle().find(4).value().d_yZoom);
                        t.translate(0+m_pPicker->getPositionHandle().find(4).value().d_xMove,\
                                    19.2+m_pPicker->getPositionHandle().find(4).value().d_yMove);
                    }
                    else
                    {
                        t.scale(1.1, 1.2);
                        t.translate(0,19.2);
                    }
                }
                else
                {
                    t.scale(1.1, 1.2);
                    t.translate(0,19.2);
                }
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignCenter,index.data().toString());
            }
            else if (index.row()== Currentindex+2)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0,0);
                t.rotate(-45.0, Qt::XAxis);
                if(m_pPicker->getPositionHandle().end()!= m_pPicker->getPositionHandle().find(5))
                {
                    if(5 == m_pPicker->getPositionHandle().find(5).value().i_row)
                    {
                        t.scale(1.23+m_pPicker->getPositionHandle().find(5).value().d_xZoom,\
                                1.6+m_pPicker->getPositionHandle().find(5).value().d_yZoom);
                        t.translate(0+m_pPicker->getPositionHandle().find(5).value().d_xMove,\
                                    21+m_pPicker->getPositionHandle().find(5).value().d_yMove);
                    }
                    else
                    {
                        t.scale(1.23, 1.6);
                        t.translate(0,21);
                    }
                }
                else
                {
                    t.scale(1.23, 1.6);
                    t.translate(0,21);
                }
                painter->setTransform(t);
                painter->drawText(option.rect,Qt::AlignCenter,index.data().toString());
            }
        }
    }
        break;
    case Picker::eToRightSmallIStyle:
    {
        if(3 == nItemCountPerPage)
        {
            if (index.row()== Currentindex - 1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(-0.4,0);
                t.rotate(-45.0, Qt::XAxis);
                t.scale(1.1, 1.1);
                t.translate(10,3);
                painter->setTransform(t);
                painter->drawText(option.rect,Qt::AlignCenter,index.data().toString());
            }
           else if (index.row() == Currentindex)
            {
                valueShear = 0.5;
                painter->setPen(curcolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0, 0);
                t.rotate(0.0, Qt::XAxis);
                t.translate(0,0);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignCenter,index.data().toString());
            }
           else if (index.row() == Currentindex+1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0.4, 0);
                t.rotate(-45.0,Qt::XAxis);
                t.scale(1.1, 1.5);
                t.translate(-45,13);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignCenter,index.data().toString());
            }
        }
        else if(5 == nItemCountPerPage)
        {
            if (index.row()== Currentindex-2)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(-0.4,0);
                t.rotate(-45.0, Qt::XAxis);
                t.scale(1, 1);
                t.translate(40,35);
                painter->setTransform(t);
                painter->drawText(option.rect,Qt::AlignCenter,index.data().toString());
            }
            else if (index.row() == Currentindex-1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                painter->drawText(option.rect,Qt::AlignCenter,index.data().toString());
            }
           else if (index.row() == Currentindex)
            {
                valueShear = 0.5;
                painter->setPen(curcolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0, 0);
                t.rotate(0.0, Qt::XAxis);
                t.translate(0,0);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignCenter,index.data().toString());
            }
           else if (index.row()== Currentindex+1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0.4, 0);
                t.rotate(-45.0,Qt::XAxis);
                t.scale(1.2, 1.4);
                t.translate(-65,40);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignCenter,index.data().toString());
            }
            else if (index.row()== Currentindex+2)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                painter->drawText(option.rect,Qt::AlignCenter,index.data().toString());
            }
        }
    }
        break;
    case Picker::eToLeftSmallIStyle:

    {
        if(3 == nItemCountPerPage)
        {
            if (index.row()== Currentindex - 1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0.4,0);
                t.rotate(-45.0, Qt::XAxis);
                t.scale(1.1, 1.1);
                t.translate(-15,3);
                painter->setTransform(t);
                painter->drawText(option.rect,Qt::AlignCenter,index.data().toString());
            }
           else if (index.row() == Currentindex)
            {
                valueShear = 0.5;
                painter->setPen(curcolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0, 0);
                t.rotate(0.0, Qt::XAxis);
                t.translate(0,0);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignCenter,index.data().toString());
            }
           else if (index.row() == Currentindex+1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(-0.4,0);
                t.rotate(-45.0,Qt::XAxis);
                t.scale(1.1, 1.5);
                t.translate(50,13);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignCenter,index.data().toString());
            }
        }
        else if(5 == nItemCountPerPage)
        {
            if (index.row()== Currentindex-2)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0.4,0);
                t.rotate(-45.0, Qt::XAxis);
                t.scale(1, 1);
                t.translate(-40,35);
                painter->setTransform(t);
                painter->drawText(option.rect,Qt::AlignCenter,index.data().toString());
            }
            else if (index.row() == Currentindex-1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                painter->drawText(option.rect,Qt::AlignCenter,index.data().toString());
            }
           else if (index.row() == Currentindex)
            {
                valueShear = 0.5;
                painter->setPen(curcolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0, 0);
                t.rotate(0.0, Qt::XAxis);
                t.translate(0,0);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignCenter,index.data().toString());
            }
           else if (index.row()== Currentindex+1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(-0.4, 0);
                t.rotate(-45.0,Qt::XAxis);
                t.scale(1.2, 1.4);
                t.translate(65,40);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignCenter,index.data().toString());
            }
            else if (index.row()== Currentindex+2)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                painter->drawText(option.rect,Qt::AlignCenter,index.data().toString());
            }
        }
    }
        break;
    case Picker::eToRightBigIStyle:
    {
        if(3 == nItemCountPerPage)
        {
            if (index.row()== Currentindex - 1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(-0.6,0);
                t.rotate(-45.0, Qt::XAxis);
                t.scale(1.1, 1.1);
                t.translate(20,3);
                painter->setTransform(t);
                painter->drawText(option.rect,Qt::AlignCenter,index.data().toString());
            }
           else if (index.row() == Currentindex)
            {
                valueShear = 0.5;
                painter->setPen(curcolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0, 0);
                t.rotate(0.0, Qt::XAxis);
                t.translate(0,0);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignCenter,index.data().toString());
            }
           else if (index.row() == Currentindex+1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0.6, 0);
                t.rotate(-45.0,Qt::XAxis);
                t.scale(1.1, 1.5);
                t.translate(-70,13);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignCenter,index.data().toString());
            }
        }
        else if(5 == nItemCountPerPage)
        {

        }
    }
        break;
    case Picker::eToLeftBigIStyle:
    {
        if(3 == nItemCountPerPage)
        {
            if (index.row()== Currentindex - 1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0.6,0);
                t.rotate(-45.0, Qt::XAxis);
                t.scale(1.1, 1.1);
                t.translate(-25,3);
                painter->setTransform(t);
                painter->drawText(option.rect,Qt::AlignCenter,index.data().toString());
            }
           else if (index.row() == Currentindex)
            {
                valueShear = 0.5;
                painter->setPen(curcolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(0, 0);
                t.rotate(0.0, Qt::XAxis);
                t.translate(0,0);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignCenter,index.data().toString());
            }
           else if (index.row() == Currentindex+1)
            {
                valueShear = 0.5;
                painter->setPen(UpAndDowncolor);
                QFont font;
                font.setPixelSize(fontSize);
                painter->setFont(font);
                painter->setOpacity(1.0);
                QTransform t;
                t.shear(-0.6, 0);
                t.rotate(-45.0,Qt::XAxis);
                t.scale(1.1, 1.5);
                t.translate(75,13);
                painter->setTransform(t);
                painter->drawText(option.rect, Qt::AlignCenter,index.data().toString());
            }
        }
        else if(5 == nItemCountPerPage)
        {

        }
    }
        break;
    default:
        break;
    }
}

Picker::Picker(QWidget *parent)
    : QListWidget(parent)
    ,m_nMouseDownX(0)
    ,m_nMouseDownY(0)
    ,m_nLastScrollBarValue(0)
    , m_bCircularList(false)
    , m_nItemCountPerPage(3)
    , m_currentIndex(-1)
    , m_releaseIndex(-1)
    , m_nCurrentFontSize(32)
    , m_FontStyle(eDefaultFontStyle)
    , m_isPickerEnable(true)
    ,m_alph(102)
    ,m_maxMum(0)
    ,m_minMum(0)
    ,m_isSetMaxMum(false)
    ,m_isSetMinMum(false)
    ,m_am(NULL)
    ,m_isPickerAnimation(false)
    ,m_isrealse(false)
    ,m_name("")
    ,m_AnimationIsEnd(true)
    ,m_pickType(EPickTypeKnown)
{
    m_curColor.setRgb(255,177,3,255);
    m_Color.setRgb(255,255,255,255);
    show();
    m_PosionHandle.i_row = 0;
    m_PosionHandle.d_xMove = 0;
    m_PosionHandle.d_xZoom = 0;
    m_PosionHandle.d_yMove = 0;
    m_PosionHandle.d_yZoom = 0;
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollMode(QListView::ScrollPerPixel);
    setSortingEnabled(false);
    setFocusPolicy(Qt::NoFocus);
    setItemDelegate(new CPickerDelegate(this));
    setAttribute(Qt::WA_AcceptTouchEvents);
    viewport()->installEventFilter(this);
    setStyleSheet("QListWidget {background-color: rgba(0, 0, 0, 0); border:0px; background-attachment: scroll;}");
}

Picker::~Picker()
{

}

void Picker::InsertItem(int index, const QString &text, const QSize &itemSize, int fontSize, int specifiedID)
{
    m_sizeItem = itemSize;
    QListWidgetItem* pItem = new QListWidgetItem;
    if(pItem)
    {
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
}
void Picker::SetFontStyle(eFontStyle type)
{
    m_FontStyle = type;
}
void Picker::SetCircular(bool mode)
{
    m_bCircularList = mode;
}
Picker::eFontStyle Picker::GetFontStyle()
{
    return m_FontStyle;
}
QString Picker::GetItemText(int index)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        return pItem->data(Qt::DisplayRole).toString();
    }
    return QString();
}

int Picker::GetItemSpecifiedID(int index)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        return pItem->data(Qt::UserRole+1).toInt();
    }
    return -1;
}

void Picker::SetItemCountPerPage(int count)
{
    m_nItemCountPerPage = count;
}
int Picker::getItemCountPerPage()
{
    return m_nItemCountPerPage;
}
void Picker::UpdateItemText(int index, const QString &qsText)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        pItem->setText(qsText);
    }
}
void Picker::SetCurrentIndex(int index)
{
    m_currentIndex = index;
}
void Picker::SetReleaseIndex(int index)
{
    m_releaseIndex = index;
}
int Picker::getReleaseIndex()
{
    return m_releaseIndex;
}
void Picker::SetIsRelease(bool is)
{
    m_isrealse = is;
}
bool Picker::getIsRelease()
{
    return m_isrealse;
}
void Picker::SetCurrentFontSize(int fontSize)
{
    m_nCurrentFontSize = fontSize;
}
int Picker::getCurrentFontSize()
{
   return  m_nCurrentFontSize;
}
int  Picker::getCurrentIndex()
{
    return m_currentIndex;
}
int Picker::getCount()
{
    return this->count();
}
void Picker::SetPickerEnabel(bool isEnabel)
{
    m_isPickerEnable = isEnabel;
    if(isEnabel)
    {
        SetTextAlpha(255);

    }
    else
    {
        SetTextAlpha(m_alph);
    }
    update();
}
bool Picker::GetPickerEnabel()
{
    return m_isPickerEnable;
}
void Picker::SetTextAlpha(qreal transparent)
{
    m_Color.setAlpha(transparent);
    m_curColor.setAlpha(transparent);
}

void Picker::SetUpAndDownColor(QColor& color)
{
    m_Color = color;
}
QColor Picker::getUpAndDownColor()
{
    return m_Color;
}
void Picker::setAlPha(qreal al)
{
    m_alph = al;
}
void Picker::setPickerMaximum(int max)
{
    m_maxMum = max;
    m_isSetMaxMum = true;
}
void Picker::setPickerMinimum(int min)
{
    m_minMum = min;
    m_isSetMinMum = true;
}
void Picker::PickerRebound(int startValue,int endValue)
{
    if(!m_am)
    {
        m_am = new QPropertyAnimation;
        m_am->setPropertyName("value");
        connect(m_am,SIGNAL(finished()),this,SLOT(PaintFinish()),Qt::UniqueConnection);
    }
    if(m_am)
    {
        m_AnimationIsEnd = false;
        m_am->setTargetObject(this);
        m_am->setStartValue(startValue);
        m_am->setEasingCurve(QEasingCurve::OutCubic);
        m_am->setLoopCount(1);
        m_am->setDuration(500);
        m_am->setEndValue(endValue);
        m_am->start();
    }
}

void Picker::StopPickerRebound()
{
  if(m_am)
  {
      m_am->stop();
  }
}
int Picker::value() const
{
      return verticalScrollBar()->value();
}

void Picker::setValue(const int value)
{
   verticalScrollBar()->setValue(value);
   update();
}
void Picker::setIsAnimation(bool is)
{
    m_isPickerAnimation = is;
}
QSize Picker::getItemSize()
{
    return m_sizeItem;
}
void Picker::setName(QString name)
{
    m_name = name;
}
QString Picker::getName()
{
    return m_name;
}
void Picker::setPickerPositionHandle(double xmove,double ymove,double xzoom,double yzoom,int nrow)
{
    m_PosionHandle.i_row = nrow;
    m_PosionHandle.d_xMove = xmove;
    m_PosionHandle.d_xZoom = xzoom;
    m_PosionHandle.d_yMove = ymove;
    m_PosionHandle.d_yZoom = yzoom;
    QMap<int,SPositionHandle>::iterator _itfind = m_PosionHandleMap.find(nrow);
    if(m_PosionHandleMap.end() != _itfind)
    {
       m_PosionHandleMap.remove(nrow);
    }
     m_PosionHandleMap.insert(nrow,m_PosionHandle);
     update();
}
QMap<int,Picker::SPositionHandle>  Picker::getPositionHandle()
{
    return m_PosionHandleMap;
}

bool Picker::getIsAnimatonEnd()
{
    return m_AnimationIsEnd;
}

void Picker::setPickType(Picker::ePickType type)
{
    m_pickType = type;
}
void Picker::PaintFinish()
{
   m_AnimationIsEnd = true;
   emit  pickerEnd((int)m_pickType);
   emit  PaintEnd(m_name);
}
void Picker::SetCurColor(QColor& color)
{
    m_curColor = color;
}
QColor Picker::getCurColor()
{
    return m_curColor;
}
bool Picker::eventFilter(QObject *object, QEvent *event)
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
        if(m_isSetMinMum)
        {
          verticalScrollBar()->setMinimum(-400);
          m_isSetMinMum = false;
        }
        if(m_isSetMaxMum)
        {
           verticalScrollBar()->setMaximum(m_maxMum);
           m_isSetMaxMum = false;
        }
        m_nMouseDownX = touchEvent->touchPoints().at(0).pos().x();
        m_nMouseDownY = touchEvent->touchPoints().at(0).pos().y();
        m_nLastScrollBarValue = verticalScrollBar()->value();
        int indexPress;
        indexPress = m_nLastScrollBarValue / m_sizeItem.height();
        int remPress;
        remPress = m_nLastScrollBarValue % m_sizeItem.height();
        if (remPress > m_sizeItem.height()/2)
        {
            indexPress += 1;
        }
        SetCurrentIndex(indexPress+m_nItemCountPerPage/2);
        this->SetIsRelease(false);
        emit pressIndex(indexPress+m_nItemCountPerPage/2);
        return true;

    }
    case QEvent::TouchUpdate:
    {
        int dragDistance;
        dragDistance = touchEvent->touchPoints().at(0).pos().y() - m_nMouseDownY;
        if (m_bCircularList)
        {
            int maxValue = verticalScrollBar()->maximum();
            if (m_nLastScrollBarValue - dragDistance >= maxValue)
            {
                verticalScrollBar()->setValue(m_nLastScrollBarValue - dragDistance - maxValue);
            }
            else if (m_nLastScrollBarValue - dragDistance < 0)
            {
                verticalScrollBar()->setValue(maxValue + m_nLastScrollBarValue - dragDistance);
            }
            else
            {
                verticalScrollBar()->setValue(m_nLastScrollBarValue - dragDistance);
            }
        }
        else
        {
            verticalScrollBar()->setValue(m_nLastScrollBarValue - dragDistance);
        }
        int MoveValue;
        MoveValue = verticalScrollBar()->value();
        int Moveindex;
        Moveindex = MoveValue / m_sizeItem.height();
        int Movereminder;
        Movereminder = MoveValue % m_sizeItem.height();
        if (Movereminder > m_sizeItem.height()/2)
        {
            Moveindex += 1;
        }
        SetCurrentIndex(Moveindex+m_nItemCountPerPage/2);
        if(0 < dragDistance)
        {
            emit updateYear(-1,Moveindex+m_nItemCountPerPage/2);
            emit updateAmOrPm(-1,Moveindex+m_nItemCountPerPage/2);
        }
        else if(0 > dragDistance)
        {
            emit updateYear(1,Moveindex+m_nItemCountPerPage/2);
            emit updateAmOrPm(1,Moveindex+m_nItemCountPerPage/2);
        }
       return true;
    }
    case QEvent::TouchEnd:
    {
        this->SetIsRelease(true);
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
        if(!m_isPickerAnimation)
        {
            int startValue = value();
            int endValue = index * m_sizeItem.height();
            this->SetCurrentIndex(index+m_nItemCountPerPage/2);
            PickerRebound(startValue, endValue);
            emit currentIndexChanged(index+m_nItemCountPerPage/2);
        }
        else
        {
            int nCount = this->count();
            if(((index+m_nItemCountPerPage/2)-m_nItemCountPerPage/2)<0)
            {
                int startValue = value();
                int endValue = 0;
                this->SetCurrentIndex(m_nItemCountPerPage/2);
                PickerRebound(startValue, endValue);
                emit currentIndexChanged(m_nItemCountPerPage/2);
            }
            else if((nCount-(m_nItemCountPerPage/2)-(index+m_nItemCountPerPage/2))<=0)
            {
                int startValue = value();
                int endValue = verticalScrollBar()->maximum()-(m_nItemCountPerPage/2+1)*m_sizeItem.height();
                this->SetCurrentIndex(nCount-(m_nItemCountPerPage/2+1));
                PickerRebound(startValue, endValue);
                emit currentIndexChanged(nCount-(m_nItemCountPerPage/2+1));
            }
            else if((((index+m_nItemCountPerPage/2)-m_nItemCountPerPage/2)>=0) && ((nCount-(m_nItemCountPerPage/2)-(index+m_nItemCountPerPage/2))>0))
            {
                int startValue = value();
                int endValue = index * m_sizeItem.height();
                this->SetCurrentIndex(index+m_nItemCountPerPage/2);
                PickerRebound(startValue, endValue);
                emit currentIndexChanged(index+m_nItemCountPerPage/2);
            }
        }
        return true;
    }
    default:
        break;
    }
    return QObject::eventFilter(object, event);
}

bool Picker::MouseEvent(QObject *object, QEvent *event)
{   if (!isEnabled())
    {
        return QObject::eventFilter(object, event);
    }
    if(!object||!event)
        return true;
    const QEvent::Type eventType = event->type();
    QMouseEvent* const mouseEvent = static_cast<QMouseEvent*>(event);
    switch (eventType)
    {
    case QEvent::MouseButtonPress:
    {
        if(m_isSetMinMum)
        {
          verticalScrollBar()->setMinimum(-400);
          m_isSetMinMum = false;
        }
        if(m_isSetMaxMum)
        {
           verticalScrollBar()->setMaximum(m_maxMum);
           m_isSetMaxMum = false;
        }
        m_nMouseDownX = mouseEvent->pos().x();
        m_nMouseDownY = mouseEvent->pos().y();
        m_nLastScrollBarValue = verticalScrollBar()->value();
        int indexPress;
        indexPress = m_nLastScrollBarValue / m_sizeItem.height();
        int remPress;
        remPress = m_nLastScrollBarValue % m_sizeItem.height();
        if (remPress > m_sizeItem.height()/2)
        {
            indexPress += 1;
        }
        SetCurrentIndex(indexPress+m_nItemCountPerPage/2);
        this->SetIsRelease(false);
        emit pressIndex(indexPress+m_nItemCountPerPage/2);
        return true;

    }
    case QEvent::MouseMove:
    {
        int dragDistance;
        dragDistance = mouseEvent->pos().y() - m_nMouseDownY;
        if (m_bCircularList)
        {
            int maxValue = verticalScrollBar()->maximum();
            if (m_nLastScrollBarValue - dragDistance >= maxValue)
            {
                verticalScrollBar()->setValue(m_nLastScrollBarValue - dragDistance - maxValue);
            }
            else if (m_nLastScrollBarValue - dragDistance < 0)
            {
                verticalScrollBar()->setValue(maxValue + m_nLastScrollBarValue - dragDistance);
            }
            else
            {
                verticalScrollBar()->setValue(m_nLastScrollBarValue - dragDistance);
            }
        }
        else
        {
            verticalScrollBar()->setValue(m_nLastScrollBarValue - dragDistance);
        }
        int MoveValue;
        MoveValue = verticalScrollBar()->value();
        int Moveindex;
        Moveindex = MoveValue / m_sizeItem.height();
        int Movereminder;
        Movereminder = MoveValue % m_sizeItem.height();
        if (Movereminder > m_sizeItem.height()/2)
        {
            Moveindex += 1;
        }
        SetCurrentIndex(Moveindex+m_nItemCountPerPage/2);
        if(0 < dragDistance)
        {
            emit updateYear(-1,Moveindex+m_nItemCountPerPage/2);
            emit updateAmOrPm(-1,Moveindex+m_nItemCountPerPage/2);
        }
        else if(0 > dragDistance)
        {
            emit updateYear(1,Moveindex+m_nItemCountPerPage/2);
            emit updateAmOrPm(1,Moveindex+m_nItemCountPerPage/2);
        }
       return true;
    }
    case QEvent::MouseButtonRelease:
    {
        this->SetIsRelease(true);
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
        if(!m_isPickerAnimation)
        {
            int startValue = value();
            int endValue = index * m_sizeItem.height();
            this->SetCurrentIndex(index+m_nItemCountPerPage/2);
            PickerRebound(startValue, endValue);
            emit currentIndexChanged(index+m_nItemCountPerPage/2);
        }
        else
        {
            int nCount = this->count();
            if(((index+m_nItemCountPerPage/2)-m_nItemCountPerPage/2)<0)
            {
                int startValue = value();
                int endValue = 0;
                this->SetCurrentIndex(m_nItemCountPerPage/2);
                PickerRebound(startValue, endValue);
                emit currentIndexChanged(m_nItemCountPerPage/2);
            }
            else if((nCount-(m_nItemCountPerPage/2)-(index+m_nItemCountPerPage/2))<=0)
            {
                int startValue = value();
                int endValue = verticalScrollBar()->maximum()-(m_nItemCountPerPage/2+1)*m_sizeItem.height();
                this->SetCurrentIndex(nCount-(m_nItemCountPerPage/2+1));
                PickerRebound(startValue, endValue);
                emit currentIndexChanged(nCount-(m_nItemCountPerPage/2+1));
            }
            else if((((index+m_nItemCountPerPage/2)-m_nItemCountPerPage/2)>=0) && ((nCount-(m_nItemCountPerPage/2)-(index+m_nItemCountPerPage/2))>0))
            {
                int startValue = value();
                int endValue = index * m_sizeItem.height();
                this->SetCurrentIndex(index+m_nItemCountPerPage/2);
                PickerRebound(startValue, endValue);
                emit currentIndexChanged(index+m_nItemCountPerPage/2);
            }
        }
        return true;
    }
    default:
        break;
    }
    return QObject::eventFilter(object, event);
}

