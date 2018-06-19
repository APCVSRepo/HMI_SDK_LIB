#include "CComboBoxDelegate.h"
#include "HMIFrameWork/log_interface.h"

CComboBoxDelegate::CComboBoxDelegate(QObject *parent)
    :m_iCount(0)
    ,m_size()
    ,m_iTextMarginLeft(48)
    ,m_iTextMarginRight(48)
{

}

void CComboBoxDelegate::SetRowCount(int count)
{
    m_iCount = count;
}

void CComboBoxDelegate::SetItemSize(const QSize &size)
{
    m_size = size;
}

void CComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem option2 = option;

    //draw background
    painter->fillRect(option2.rect,QColor("#000000"));

    //draw the border line
    painter->setPen(QColor("#818181"));

    painter->drawLine(option2.rect.topLeft(),option2.rect.bottomLeft());
    painter->drawLine(option2.rect.topRight(),option2.rect.bottomRight());

    if(0 == index.row())
    {
        painter->drawLine(option2.rect.topLeft(),option2.rect.topRight());
    }
    else if(m_iCount-1 == index.row())
    {
        painter->drawLine(option2.rect.bottomLeft(),option2.rect.bottomRight());
    }

    //customize the display of text and highlight item
    QRect textRect = QRect(QPoint(option2.rect.left()+m_iTextMarginLeft, option2.rect.top()),
                           QPoint(option2.rect.right()-m_iTextMarginRight, option2.rect.bottom()));
    option2.rect = textRect;    //set the text display area
    option2.displayAlignment = Qt::AlignRight|Qt::AlignVCenter;
    option2.palette.setBrush(QPalette::Highlight,QBrush(QColor("#2698ff")));
    option2.palette.setBrush(QPalette::Text,QBrush(QColor("#bbffffff")));

    //draw text
    drawDisplay(painter,option2,option.rect,QString(""));
    drawDisplay(painter,option2,option2.rect,index.data().toString());
}

QSize CComboBoxDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return m_size;
}
