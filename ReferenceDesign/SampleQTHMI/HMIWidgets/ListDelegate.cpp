
#include "ListDelegate.h"
#include "CVListWidget.h"
#include <QStyledItemDelegate>
#include <QPainter>

ListDelegate::ListDelegate(CVListWidget *listWidget)
{
    m_pVListWidget = listWidget;
}

ListDelegate::~ListDelegate()
{

}

void ListDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,const QModelIndex& index)const
{
    //QStyledItemDelegate::paint(painter, option, index);

    //----------- Draw background pixmap -----------
    DrawBackgroundPixmap(painter, option, index);

    //----------- draw buttons -----------
    DrawButton(painter, option, index);

    DrawSpecialIcon(painter, option, index);

    //----------- draw icons -----------
    DrawIcon(painter, option, index);

    //----------- draw texts -----------
    DrawText(painter, option, index);

    //----------- draw checkboxs -----------
    DrawCheckBox(painter, option, index);

    //----------- draw indicator -----------
    DrawIndicator(painter, option, index);

    //------------- draw split line --------------
    QImage imageOutLine = m_pVListWidget->GetOutSplitLineImage();
    if (m_pVListWidget->IsDrawingSplitLine() && !imageOutLine.isNull())
    {
        QImage imageInLine = m_pVListWidget->GetInSplitLineImage();
        QPixmap pixmapLineIn = QPixmap::fromImage(imageInLine.scaled(option.rect.width(), imageInLine.height()));
        QPixmap pixmapLineOut = QPixmap::fromImage(imageOutLine.scaled(option.rect.width(), imageOutLine.height()));
        if (index.data(CListWidgetItem::eTitleNameMode).toString().isNull())
        {
            painter->drawPixmap(option.rect.left(), option.rect.top()+option.rect.height(), pixmapLineIn);
        }
        else
        {
            painter->drawPixmap(option.rect.left(), option.rect.top(), pixmapLineOut);
            painter->drawPixmap(option.rect.left(), option.rect.top()+option.rect.height(), pixmapLineOut);
        }
        if (index.row() == m_pVListWidget->count()-1)
        {
            painter->drawPixmap(option.rect.left(), option.rect.top()+option.rect.height(), pixmapLineOut);
        }
    }

    //------------- draw split line for Phone app --------------
    if (m_pVListWidget->IsDrawingSplitLineForPhoneApp())
    {
        QImage imageLine = m_pVListWidget->GetSplitLineImageForPhoneApp();
        if (imageLine.isNull())
        {
            return;
        }
        QPixmap pixmapLine = QPixmap::fromImage(imageLine.scaled(option.rect.width(), imageLine.height()));
        if (index.row() == m_pVListWidget->count()-1)
        {
            painter->drawPixmap(option.rect.left(), option.rect.top()+option.rect.height(), pixmapLine);
        }
        if (index.row() % 2)
        {
            return;
        }
        painter->drawPixmap(option.rect.left(), option.rect.top(), pixmapLine);
    }
}

void ListDelegate::DrawBackgroundPixmap(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    int itemW = m_pVListWidget->GetItemWidth(); //option.rect.width();
    int itemH = option.rect.height();

    QStringList qsList = index.data(CListWidgetItem::eBackgroundMode).toStringList();
    if (qsList.isEmpty() && !m_pVListWidget->GetItemNormalImage().isNull())
    {
        // The item background needs to be stretched.
        if (option.rect.height() - m_pVListWidget->GetItemNormalImage().height() > 3)
        {
            QPixmap pixmap = QPixmap::fromImage(m_pVListWidget->GetItemNormalImage().scaled(itemW, itemH));
            painter->drawPixmap(option.rect.left(), option.rect.top(), pixmap);
            return;
        }
    }
    //draw normal state
    QPixmap pixmapNormal;
    if (qsList.count() > 0)
    {
        pixmapNormal.load(qsList.at(0));
    }
    else
    {
        if(!m_pVListWidget->GetItemNormalImage().isNull())
        {
            pixmapNormal = QPixmap::fromImage(m_pVListWidget->GetItemNormalImage().scaled(itemW, itemH));
        }
    }
    if (!pixmapNormal.isNull())
    {
        painter->drawPixmap(option.rect.left(), option.rect.top(), pixmapNormal);
    }

    QPixmap pixmap;
    if (m_pVListWidget->GetPressedIndex() == index.row())
    {
        if (qsList.count() > 1)
        {
            pixmap.load(qsList.at(1));
        }
        else
        {
            pixmap = m_pVListWidget->GetItemPressededPixmap().scaled(itemW, itemH);
        }
    }
    else if (m_pVListWidget->GetCursorIndex() == index.row())
    {
        if (qsList.count() > 2)
        {
            pixmap.load(qsList.at(2));
        }
        else
        {
            pixmap = m_pVListWidget->GetItemCursoredPixmap();
        }
    }
    if (!pixmap.isNull())
    {
        painter->drawPixmap(option.rect.left()+m_pVListWidget->GetLeftMargin(), option.rect.top(), pixmap);
    }
}

void ListDelegate::DrawText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QList<QVariant> rectList = index.data(CListWidgetItem::eTextRectMode).toList();
    QStringList textList = index.data(CListWidgetItem::eTextStringMode).toStringList();
    QList<QVariant> alignList = index.data(CListWidgetItem::eTextAlignMode).toList();
    QList<QVariant> colorList = index.data(CListWidgetItem::eTextColorMode).toList();
    QList<QVariant> sizeList = index.data(CListWidgetItem::eTextSizeMode).toList();
    QList<QVariant> typeList = index.data(CListWidgetItem::eTextTypeMode).toList();
    QFont font;
    QRect rectText;
    for (int i = 0; i < rectList.count(); i++)
    {
        if (typeList.at(i).toBool()) // draw special text
        {
            QList<QVariant> specialRectList = index.data(CListWidgetItem::eSpecialTextRectMode).toList();
            QStringList specialTextList = index.data(CListWidgetItem::eSpecialTextStringMode).toStringList();
            QList<QVariant> specialTextTypeList = index.data(CListWidgetItem::eSpecialTextTypeMode).toList();
            if (sizeList.at(i).toInt() > 0)
            {
                font.setPixelSize(sizeList.at(i).toInt());
            }
            else
            {
                font.setPixelSize(20);
            }
            for (int j = 0; j < specialRectList.count(); ++j)
            {
                if (specialTextTypeList.at(j).toInt()) //highlight text
                {
                    font.setUnderline(true);
                    painter->setFont(font);
                    painter->setPen(QColor(0, 255, 255));
                }
                else
                {
                    font.setUnderline(false);
                    painter->setFont(font);
                    painter->setPen(colorList.at(i).value<QColor>());
                }
                QString qsText = specialTextList.at(j);
                rectText.setLeft(specialRectList.at(j).toRect().left() + m_pVListWidget->GetSpacing() + m_pVListWidget->GetLeftMargin());
                rectText.setTop(option.rect.top() + specialRectList.at(j).toRect().top());
                rectText.setWidth(specialRectList.at(j).toRect().width());
                rectText.setHeight(specialRectList.at(j).toRect().height());

                painter->drawText(rectText, alignList.at(i).toInt(), qsText);
            }
        }
        else // draw normal text
        {
            if (sizeList.at(i).toInt() > 0)
            {
                font.setPixelSize(sizeList.at(i).toInt());
            }
            else
            {
                font.setPixelSize(20);
            }
            font.setUnderline(false);
            painter->setFont(font);
            painter->setPen(colorList.at(i).value<QColor>());
            QString qsText = textList.at(i);
            QFontMetrics fontMetrics(font);
            if (m_pVListWidget->IsElidedTextEnabled())
            {
                if (fontMetrics.width(qsText) > rectList.at(i).toRect().width())
                {
                    if (index.row() == m_pVListWidget->GetSelectedIndex() && 2 != rectList.count() && i == rectList.count() - 1)
                    {
                        int x = rectList.at(i).toRect().left() + m_pVListWidget->GetSpacing() + m_pVListWidget->GetLeftMargin();
                        int y = option.rect.top() + rectList.at(i).toRect().top();
                        m_pVListWidget->ProcessScrollText(painter, x, y);
                        continue;
                    }
                    else
                    {
                        qsText = qsText.remove("\n");
                        qsText = fontMetrics.elidedText(qsText,
                                                        Qt::ElideRight,
                                                        rectList.at(i).toRect().width());
                    }
                }
            }
            rectText.setLeft(rectList.at(i).toRect().left() + m_pVListWidget->GetSpacing() + m_pVListWidget->GetLeftMargin());
            rectText.setWidth(rectList.at(i).toRect().width());
            rectText.setTop(option.rect.top() + rectList.at(i).toRect().top());
            rectText.setHeight(rectList.at(i).toRect().height());
            painter->drawText(rectText, alignList.at(i).toInt(), qsText);
        }
    }
}

void ListDelegate::DrawIcon(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QList<QVariant> rectList = index.data(CListWidgetItem::eIconRectMode).toList();
    QList<QVariant> pixmapList = index.data(CListWidgetItem::eIconPixmapMode).toList();
    QList<QVariant> indicatorList = index.data(CListWidgetItem::eIconIndicatorMode).toList();
    QList<QVariant> showList = index.data(CListWidgetItem::eIconShowHideMode).toList();
    for (int i = 0; i < rectList.count(); i++)
    {
        int topDis = (rectList.at(i).toRect().height() - pixmapList.at(i).value<QPixmap>().height())/2;
        bool bDrawIcon = false;
        if (indicatorList.at(i).toBool())
        {
            if (index.row() == m_pVListWidget->GetCursorIndex())
            {
                bDrawIcon = true;
            }
        }
        else
        {
            if (showList.at(i).toBool())
            {
                bDrawIcon = true;
            }
        }
        if (bDrawIcon)
        {
            painter->drawPixmap(rectList.at(i).toRect().left() + m_pVListWidget->GetSpacing() + m_pVListWidget->GetLeftMargin(),
                                option.rect.top() + rectList.at(i).toRect().top() + topDis,
                                pixmapList.at(i).value<QPixmap>());
        }
    }
}

void ListDelegate::DrawButton(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QList<QVariant> rectList = index.data(CListWidgetItem::eButtonRectMode).toList();
    QList<QVariant> pathList = index.data(CListWidgetItem::eButtonPixmapMode).toList();
    QList<QVariant> stateList = index.data(CListWidgetItem::eButtonStateMode).toList();
    QList<QVariant> indicatorList = index.data(CListWidgetItem::eButtonIndicatorMode).toList();
    QList<QVariant> bgDrawModeList = index.data(CListWidgetItem::eButtonBgDrawMode).toList();
    for (int i = 0; i < rectList.count(); i++)
    {   
        int state = (int)stateList.at(i).toInt();
        QString qsPath = pathList.at(i).toStringList().at(state);
        if ("none" == qsPath)
        {
            qsPath = pathList.at(i).toStringList().at(0);
        }
        QPixmap pixmapButton = QPixmap(qsPath);
        int nSpace = m_pVListWidget->GetSpacing() + m_pVListWidget->GetLeftMargin();
        bool bDrawButton = false;
        if (indicatorList.at(i).toBool())
        {
            if (index.row() == m_pVListWidget->GetCursorIndex())
            {
                bDrawButton = true;
            }
        }
        else
        {
            bDrawButton = true;
        }
        if (bDrawButton)
        {
            int leftDis = 0, topDis = 0;
            if (1 != state) //not pressed state
            {
                leftDis = (rectList.at(i).toRect().width() - pixmapButton.width())/2;
                topDis = (rectList.at(i).toRect().height() - pixmapButton.height())/2;
                painter->drawPixmap(rectList.at(i).toRect().left() + nSpace + leftDis,
                                    option.rect.top() + rectList.at(i).toRect().top() + topDis,
                                    pixmapButton);
            }
            else //pressed state
            {
                QPixmap pixmapPushed = QPixmap(pathList.at(i).toStringList().at(1));
                if (!pixmapPushed.isNull())
                {
                    leftDis = (rectList.at(i).toRect().width() - pixmapPushed.width())/2;
                    topDis = (rectList.at(i).toRect().height() - pixmapPushed.height())/2;
                    painter->drawPixmap(rectList.at(i).toRect().left() + nSpace + leftDis,
                                        option.rect.top() + rectList.at(i).toRect().top() + topDis,
                                        pixmapPushed);
                }
                QPixmap pixmapNormal = QPixmap(pathList.at(i).toStringList().at(0));
                if (!pixmapNormal.isNull() && 0 == bgDrawModeList.at(i).toInt())
                {
                    leftDis = (rectList.at(i).toRect().width() - pixmapNormal.width())/2;
                    topDis = (rectList.at(i).toRect().height() - pixmapNormal.height())/2;
                    painter->drawPixmap(rectList.at(i).toRect().left() + nSpace + leftDis,
                                        option.rect.top() + rectList.at(i).toRect().top() + topDis,
                                        pixmapNormal);
                }
            }
        }
    }
}

void ListDelegate::DrawIndicator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!m_pVListWidget->GetIndicatorState())
    {
        return;
    }
    QPixmap indicatorPixmap = m_pVListWidget->GetIndicatorPixamp();
    if (!indicatorPixmap.isNull() && index.row() == m_pVListWidget->GetIndicatorIndex())
    {
        int leftIndicator = m_pVListWidget->GetIndicatorRect().left();
        int nSpace = m_pVListWidget->GetSpacing() + m_pVListWidget->GetLeftMargin();
        int topDis = (option.rect.height() - indicatorPixmap.height())/2;
        painter->drawPixmap(leftIndicator + nSpace, option.rect.top() + topDis, indicatorPixmap);
    }
}

void ListDelegate::DrawCheckBox(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QList<QVariant> rectList = index.data(CListWidgetItem::eCheckBoxRectMode).toList();
    QList<QVariant> pixmapBgList = index.data(CListWidgetItem::eCheckBoxPixmapBgMode).toList();
    QList<QVariant> pixmapCheckList = index.data(CListWidgetItem::eCheckBoxPixmapCheckMode).toList();
    QList<QVariant> checkStateList = index.data(CListWidgetItem::eCheckBoxStateMode).toList();
    for (int i = 0; i < rectList.count(); i++)
    {
        int topDis = (rectList.at(i).toRect().height() - pixmapBgList.at(i).value<QPixmap>().height())/2;
        painter->drawPixmap(rectList.at(i).toRect().left() + m_pVListWidget->GetSpacing() + m_pVListWidget->GetLeftMargin(),
                            option.rect.top() + rectList.at(i).toRect().top() + topDis,
                            pixmapBgList.at(i).value<QPixmap>());

        if (checkStateList.at(i).toBool())
        {
            int leftDis = (pixmapBgList.at(i).value<QPixmap>().width() - pixmapCheckList.at(i).value<QPixmap>().width())/2;
            topDis = (rectList.at(i).toRect().height() - pixmapCheckList.at(i).value<QPixmap>().height())/2;
            painter->drawPixmap(rectList.at(i).toRect().left() + m_pVListWidget->GetSpacing() + leftDis + m_pVListWidget->GetLeftMargin(),
                                option.rect.top() + rectList.at(i).toRect().top() + topDis,
                                pixmapCheckList.at(i).value<QPixmap>());
        }
    }
}

void ListDelegate::DrawSpecialIcon(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QList<QVariant> rectList = index.data(CListWidgetItem::eSpecialTextBackgroundRectMode).toList();
    QList<QVariant> pixmapList = index.data(CListWidgetItem::eSpecialTextBackgroundIconMode).toList();
    for (int i = 0; i < rectList.count(); i++)
    {
        int topDis = (rectList.at(i).toRect().height() - pixmapList.at(i).value<QPixmap>().height())/2;
        bool bDrawIcon = true;

        if (bDrawIcon)
        {
            painter->drawPixmap(rectList.at(i).toRect().left() + m_pVListWidget->GetSpacing() + m_pVListWidget->GetLeftMargin(),
                                option.rect.top() + rectList.at(i).toRect().top() + topDis,
                                pixmapList.at(i).value<QPixmap>());
        }
    }
}


