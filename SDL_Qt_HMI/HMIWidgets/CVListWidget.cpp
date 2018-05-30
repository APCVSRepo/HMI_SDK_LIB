
#include "CVListWidget.h"
#include "ListDelegate.h"
#include <QFontMetrics>
#include <QPainter>
#include <QDate>
#include <QDebug>
#include <QPixmap>
#define Log qDebug
CVListWidget::CVListWidget(QWidget *parent)
    : QListWidget(parent)
    , m_pScroller(new ListScroller(this))
    , m_pScrollText(new ScrollText(this))
    , m_pPressedItem(NULL)
    , m_rectIndicator(0, 0, 0, 0)
    , m_itemSize(0, 0)
    , m_colorNormal(QColor(255, 255, 255))
    , m_colorSelected(QColor(75, 169, 255))
    , m_colorDisabled(QColor(255, 255, 255, 100))
    , m_pointPressed(0, 0)
    , m_nCursorIdx(0)
    , m_nIndicatorIdx(-1)
    , m_nPressedIdx(-1)
    , m_nFontPixelSize(26)
    , m_nPressedButtonIdx(-1)
    , m_nPressedCheckBoxIdx(-1)
    , m_nSpacing(0)
    , m_nLeftMargin(17)
    , m_nItemSelectedIndex(0)
    , m_nSelectedIdx(-1)
    , m_bDrawSplitLine(false)
    , m_bDrawSplitLineForPhoneApp(false)
    , m_bAutoSetSelected(true)
    , m_bAutoScrollCursoredItem(false)
    , m_bDrawIndicator(true)
    , m_bElidedTextEnabled(true)
    , m_bAutoResizeGeometry(false)
    , m_bCheckBoxDisabled(false)
    , m_eBtnPushStyle(ePushStyle_UnKnow)
{
    if (m_pScroller)
    {
        m_pScroller->enableScroller(this, ListScroller::eCVListWidget);
        m_pScroller->setOrientation(Qt::Vertical);
    }
    this->show();

    InitListWidget();
}

CVListWidget::~CVListWidget()
{

}

void CVListWidget::InsertItem(int index, CListWidgetItem *item)
{
    QListWidgetItem* pListItem = new QListWidgetItem(this);
    if (pListItem)
    {
        m_itemSize = item->m_sizeItem;
        pListItem->setSizeHint(item->m_sizeItem);
        pListItem->setData(CListWidgetItem::eDisabledMode, false);
        this->insertItem(index, pListItem);

        // for background
        if (item->m_qsListBackground.count() > 0)
        {
            pListItem->setData(CListWidgetItem::eBackgroundMode, item->m_qsListBackground);
        }
        // for texts
        if (item->m_textRectList.count() > 0)
        {
            pListItem->setData(CListWidgetItem::eTextRectMode, item->m_textRectList);
            pListItem->setData(CListWidgetItem::eTextStringMode, item->m_textStringList);
            pListItem->setData(CListWidgetItem::eTextAlignMode, item->m_textAlignList);
            pListItem->setData(CListWidgetItem::eTextColorMode, item->m_textColorList);
            pListItem->setData(CListWidgetItem::eTextSizeMode, item->m_textSizeList);
            pListItem->setData(CListWidgetItem::eTextTypeMode, item->m_textTypeList);
            pListItem->setData(CListWidgetItem::eSpecialTextRectMode, item->m_textTypeList);
        }
        // for special texts
        //if (item->m_specialTextRectList.count() > 0)
        {
            pListItem->setData(CListWidgetItem::eSpecialTextRectMode, item->m_specialTextRectList);
            pListItem->setData(CListWidgetItem::eSpecialTextStringMode, item->m_specialTextStringList);
            pListItem->setData(CListWidgetItem::eSpecialTextTypeMode, item->m_specialTextTypeList);
        }
        // for icons
        if (item->m_iconRectList.count() > 0)
        {
            pListItem->setData(CListWidgetItem::eIconRectMode, item->m_iconRectList);
            pListItem->setData(CListWidgetItem::eIconPixmapMode, item->m_iconPixmapList);
            pListItem->setData(CListWidgetItem::eIconIndicatorMode, item->m_iconIndicatorList);
            pListItem->setData(CListWidgetItem::eIconShowHideMode, item->m_iconShowHideList);
        }
        // for buttons
        if (item->m_buttonRectList.count() > 0)
        {
            pListItem->setData(CListWidgetItem::eButtonRectMode, item->m_buttonRectList);
            pListItem->setData(CListWidgetItem::eButtonPixmapMode, item->m_buttonPathList);
            pListItem->setData(CListWidgetItem::eButtonStateMode, item->m_buttonStateList);
            pListItem->setData(CListWidgetItem::eButtonIndicatorMode, item->m_buttonIndicatorList);
            pListItem->setData(CListWidgetItem::eButtonBgDrawMode, item->m_buttonBgDrawModeList);
        }
        // for checkboxs
        if (item->m_checkBoxRectList.count() > 0)
        {
            pListItem->setData(CListWidgetItem::eCheckBoxRectMode, item->m_checkBoxRectList);
            pListItem->setData(CListWidgetItem::eCheckBoxPixmapBgMode, item->m_checkBoxBgPixmapList);
            pListItem->setData(CListWidgetItem::eCheckBoxPixmapCheckMode, item->m_checkBoxCheckPixmapList);
            pListItem->setData(CListWidgetItem::eCheckBoxStateMode, item->m_checkBoxStateList);
        }
        // for title and specified id
        pListItem->setData(CListWidgetItem::eSpecifiedIDMode, item->m_nSpecifiedID);
        pListItem->setData(CListWidgetItem::eSpecifiedIDStatusMode, item->m_nSpecifiedIDStatus);
        pListItem->setData(CListWidgetItem::eTrackIDMode, item->m_lluSpecifiedTrackID);
        pListItem->setData(CListWidgetItem::eTitleNameMode, item->m_qsTitleName);
        pListItem->setData(CListWidgetItem::eSpecifiedIDNumMode,item->m_qsPhoneNum);
    }
}

void CVListWidget::InsertItem(int index, const CListWidgetItem& item)
{
    QListWidgetItem* pListItem = new QListWidgetItem(this);
    if (pListItem)
    {
        m_itemSize = item.m_sizeItem;
        pListItem->setSizeHint(item.m_sizeItem);
        pListItem->setData(CListWidgetItem::eDisabledMode, false);
        this->insertItem(index, pListItem);

        // for background
        if (item.m_qsListBackground.count() > 0)
        {
            pListItem->setData(CListWidgetItem::eBackgroundMode, item.m_qsListBackground);
        }
        // for texts
        if (item.m_textRectList.count() > 0)
        {
            pListItem->setData(CListWidgetItem::eTextRectMode, item.m_textRectList);
            pListItem->setData(CListWidgetItem::eTextStringMode, item.m_textStringList);
            pListItem->setData(CListWidgetItem::eTextAlignMode, item.m_textAlignList);
            pListItem->setData(CListWidgetItem::eTextColorMode, item.m_textColorList);
            pListItem->setData(CListWidgetItem::eTextSizeMode, item.m_textSizeList);
            pListItem->setData(CListWidgetItem::eTextTypeMode, item.m_textTypeList);
            pListItem->setData(CListWidgetItem::eSpecialTextRectMode, item.m_textTypeList);
        }
        // for special texts
        //if (item->m_specialTextRectList.count() > 0)
        {
            pListItem->setData(CListWidgetItem::eSpecialTextRectMode, item.m_specialTextRectList);
            pListItem->setData(CListWidgetItem::eSpecialTextStringMode, item.m_specialTextStringList);
            pListItem->setData(CListWidgetItem::eSpecialTextTypeMode, item.m_specialTextTypeList);
        }
        // for icons
        if (item.m_iconRectList.count() > 0)
        {
            pListItem->setData(CListWidgetItem::eIconRectMode, item.m_iconRectList);
            pListItem->setData(CListWidgetItem::eIconPixmapMode, item.m_iconPixmapList);
            pListItem->setData(CListWidgetItem::eIconIndicatorMode, item.m_iconIndicatorList);
            pListItem->setData(CListWidgetItem::eIconShowHideMode, item.m_iconShowHideList);
        }
        // for buttons
        if (item.m_buttonRectList.count() > 0)
        {
            pListItem->setData(CListWidgetItem::eButtonRectMode, item.m_buttonRectList);
            pListItem->setData(CListWidgetItem::eButtonPixmapMode, item.m_buttonPathList);
            pListItem->setData(CListWidgetItem::eButtonStateMode, item.m_buttonStateList);
            pListItem->setData(CListWidgetItem::eButtonIndicatorMode, item.m_buttonIndicatorList);
            pListItem->setData(CListWidgetItem::eButtonBgDrawMode, item.m_buttonBgDrawModeList);
        }
        // for checkboxs
        if (item.m_checkBoxRectList.count() > 0)
        {
            pListItem->setData(CListWidgetItem::eCheckBoxRectMode, item.m_checkBoxRectList);
            pListItem->setData(CListWidgetItem::eCheckBoxPixmapBgMode, item.m_checkBoxBgPixmapList);
            pListItem->setData(CListWidgetItem::eCheckBoxPixmapCheckMode, item.m_checkBoxCheckPixmapList);
            pListItem->setData(CListWidgetItem::eCheckBoxStateMode, item.m_checkBoxStateList);
        }
        // for title and specified id
        pListItem->setData(CListWidgetItem::eSpecifiedIDMode, item.m_nSpecifiedID);
        pListItem->setData(CListWidgetItem::eSpecifiedIDStatusMode, item.m_nSpecifiedIDStatus);
        pListItem->setData(CListWidgetItem::eTrackIDMode, item.m_lluSpecifiedTrackID);
        pListItem->setData(CListWidgetItem::eTitleNameMode, item.m_qsTitleName);
        pListItem->setData(CListWidgetItem::eSpecifiedIDNumMode,item.m_qsPhoneNum);
    }
}

/*
 * Removes the item from the given index in the list widget,
 */
void CVListWidget::RemoveItem(int index)
{
    // Removes and returns the item from the given row in the list widget;
    // otherwise returns 0. And it will need to be deleted manually.
    QListWidgetItem* pItem = this->takeItem(index);
    if (NULL == pItem)
    {
        Log("[CVListWidget::RemoveItem]: Remove item failed!");
    }
    else
    {
        delete pItem;
    }
}

void CVListWidget::RemoveItems(int start, int end)
{
    for(int index = end; index >= start; --index)
    {
        RemoveItem(index);
    }
}

/*
 * Removes all items and selections in the view.
 * Warning: All items will be permanently deleted.
 */
void CVListWidget::RemoveAllItems(bool bRemoveCursorIndex)
{
    this->clear();
    m_pPressedItem = NULL;
    if (bRemoveCursorIndex)
    {
        m_nCursorIdx = 0;
    }
    m_nSelectedIdx = -1;
    m_nIndicatorIdx = -1;
    m_nPressedIdx = -1;
    m_nPressedButtonIdx = -1;
    m_nPressedCheckBoxIdx = -1;
    m_bCheckBoxDisabled = false;
    if (!m_listCheckedItem.isEmpty())
    {
        m_listCheckedItem.clear();
    }
}

void CVListWidget::UpdateItemText(int index, const QString &text, int nTextIndexInItem)
{
    QListWidgetItem* pItem = item(index);
    if (NULL == pItem)
    {
        Log("[CVListWidget::UpdateItemText]: pItem = NULL, index = %d", index);
        return;
    }
    QVariant dataString = pItem->data(CListWidgetItem::eTextStringMode);
    if (dataString.isNull())
    {
        Log("[CVListWidget::UpdateItemText]: dataString is null.");
        return;
    }
    QStringList qsTextList = dataString.toStringList();
    if (nTextIndexInItem < 0 || nTextIndexInItem >= qsTextList.count())
    {
        return;
    }
    else
    {
        qsTextList.replace(nTextIndexInItem, text);
        pItem->setData(CListWidgetItem::eTextStringMode, qsTextList);
    }
}

QString CVListWidget::GetItemText(int index, int nTextIndexInItem) const
{
    QListWidgetItem* pItem = item(index);
    if (NULL == pItem)
    {
        Log("[CVListWidget::GetItemText]: pItem = NULL, index = %d", index);
        return QString();
    }
    QVariant dataString = pItem->data(CListWidgetItem::eTextStringMode);
    if (dataString.isNull())
    {
        Log("[CVListWidget::GetItemText]: dataString is null.");
        return QString();
    }
    QStringList qsTextList = dataString.toStringList();
    if (nTextIndexInItem < 0 || nTextIndexInItem >= qsTextList.count())
    {
        return QString();
    }
    else
    {
        return qsTextList.at(nTextIndexInItem);
    }
}

void CVListWidget::SetIndicator(const QRect& rect, const QString &qsIndicatorPath)
{
    m_pixmapIndicator = QPixmap(qsIndicatorPath);
    m_rectIndicator = rect;
}

void CVListWidget::SetIndicatorIndex(int index, bool bAutoScrollCursoredItem)
{
    m_nIndicatorIdx = index;
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        //visualItemRect(pItem);
        if (m_bAutoScrollCursoredItem && bAutoScrollCursoredItem)
        {
            scrollToItem(pItem, QAbstractItemView::PositionAtTop);
        }
    }
    SetItemSelected(index);
    update();
}

void CVListWidget::SetItemBackgroundInfo(const QString &qsNormalPath,
                                           const QString &qsPressedPath,
                                           const QString &qsCursoredPath)
{
    m_imageItemNormal = QImage(qsNormalPath);
    m_pixmapItemPressed = QPixmap(qsPressedPath);
    m_pixmapItemCursored = QPixmap(qsCursoredPath);
}

void CVListWidget::SetSplitLine(const QString &qsOutLinePath, const QString &qsInLinePath)
{
    m_bDrawSplitLine = true;
    m_imageOutSplitLine = QImage(qsOutLinePath);
    m_imageInSplitLine = QImage(qsInLinePath);
}

void CVListWidget::SetSplitLineForPhoneApp(const QString &qsLine)
{
    m_bDrawSplitLineForPhoneApp = true;
    m_imageSplitLineForPhoneApp = QImage(qsLine);
}

bool CVListWidget::IsDrawingSplitLine()
{
    return m_bDrawSplitLine;
}

bool CVListWidget::IsDrawingSplitLineForPhoneApp()
{
    return m_bDrawSplitLineForPhoneApp;
}

void CVListWidget::SetScrollBarStyleSheet(int , int)
{
    ;
}

void CVListWidget::SetSpacing(int space)
{
    QListWidget::setSpacing(space);
    m_nSpacing = space;
    //SetScrollBarStyleSheet(m_nScrollBarWidth, m_nHandleWidth);
    setGeometry(this->geometry().left()-space, this->geometry().top(),
                this->geometry().width()+space, this->geometry().height());
}

void CVListWidget::AutoSetSelected(bool state)
{
    m_bAutoSetSelected = state;
}

void CVListWidget::AutoScrollCursoredItem(bool state)
{
    m_bAutoScrollCursoredItem = state;
}

void CVListWidget::SetIndicatorState(bool state)
{
    m_bDrawIndicator = state;
}
//const QStringList& list
void CVListWidget::AddComboBox(int index,const QString& icon,const QStringList& listtext, const QRect& comboboxrect,const QSize& itemsize)
{
    CComboBox *combobox = new CComboBox(this);
    QPixmap p(icon);

    int y = index*itemsize.height()+(itemsize.height()-comboboxrect.height())/2;
    int x = comboboxrect.x();
    combobox->setGeometry(QRect(x,y,comboboxrect.width(),comboboxrect.height()));

    combobox->setBtnStyle(icon,QSize(p.width(),comboboxrect.height()));
    combobox->SetIndex(index);
    for(int i = 0; i < listtext.size();i++)
    {
        combobox->addItem(listtext.at(i));
    }
    connect(combobox,SIGNAL(activated(int,QString)),this,SLOT(OnComboBoxActivated(int,QString)));
    connect(combobox,SIGNAL(activated(int,int)),this,SLOT(OnComboBoxActivated(int,int)));

    combobox->show();
    
}

void CVListWidget::InitListWidget()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollMode(QListView::ScrollPerPixel);
    setSortingEnabled(false);
    setFocusPolicy(Qt::NoFocus);
    setItemDelegate(new ListDelegate(this));
    SetScrollBarStyle1(32);
}

int CVListWidget::GetIndexBySpecifiedID(int specifiedID)
{
    for (int i = 0; i < count(); i++)
    {
        QListWidgetItem* pItem = item(i);
        if (pItem)
        {
            QVariant dataSpecifiedID = pItem->data(CListWidgetItem::eSpecifiedIDMode);
            int id = -1;
            if (!dataSpecifiedID.isNull())
            {
                id = dataSpecifiedID.toInt();
            }
            else
            {
                Log("[CVListWidget::GetIndexBySpecifiedID]: dataSpecifiedID is null.");
            }
            if (specifiedID == id)
            {
                return i;
            }
        }
    }
    return -1;
}

int CVListWidget::GetSpecifiedID(int index)
{
    QListWidgetItem* pItem = item(index);
    int id = -1;
    if (pItem)
    {
        QVariant dataSpecifiedID = pItem->data(CListWidgetItem::eSpecifiedIDMode);
        if (!dataSpecifiedID.isNull())
        {
            id = dataSpecifiedID.toInt();
        }
        else
        {
            Log("[CVListWidget::GetSpecifiedID]: dataSpecifiedID is null.");
        }
    }
    return id;
}

int CVListWidget::GetSpecifiedIDStatus(int index)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        QVariant dataSpecifiedIDStatus = pItem->data(CListWidgetItem::eSpecifiedIDStatusMode);
        if (!dataSpecifiedIDStatus.isNull())
        {
            return dataSpecifiedIDStatus.toInt();
        }
    }
    return -1;
}

unsigned long long CVListWidget::GetSpecifiedTrackID(int index)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        QVariant dataTrackID = pItem->data(CListWidgetItem::eTrackIDMode);
        if (!dataTrackID.isNull())
        {
            return static_cast<unsigned long long>(dataTrackID.toString().toULongLong());
        }
    }
    return 0;
}

QString CVListWidget::GetSpecifiedText(int index)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        QVariant dataSpecifiedIDNum = pItem->data(CListWidgetItem::eSpecifiedIDNumMode);
        if (!dataSpecifiedIDNum.isNull())
        {
            return dataSpecifiedIDNum.toString();
        }
    }
    return QString();
}

bool CVListWidget::IsElidedTextEnabled()
{
    return m_bElidedTextEnabled;
}

void CVListWidget::SetItemTextColor(int index, unsigned int nIndexInItem, const QColor &color)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        QVariant dataTextColor = pItem->data(CListWidgetItem::eTextColorMode);
        if (!dataTextColor.isNull())
        {
            QVariantList colorList = dataTextColor.toList();
            unsigned int count = colorList.count();
            if (nIndexInItem < count)
            {
                colorList.replace(nIndexInItem, color);
                pItem->setData(CListWidgetItem::eTextColorMode, colorList);
            }
            update();
        }
    }
}

void CVListWidget::SetItemTextSize(int index, unsigned int nIndexInItem, const int fontSize)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        QVariant dataTextSize = pItem->data(CListWidgetItem::eTextSizeMode);
        if (!dataTextSize.isNull())
        {
            QVariantList sizeList = dataTextSize.toList();
            unsigned int count = sizeList.count();
            if (nIndexInItem < count)
            {
                sizeList.replace(nIndexInItem, fontSize);
                pItem->setData(CListWidgetItem::eTextSizeMode, sizeList);
            }
            update();
        }
    }
}

void CVListWidget::SetItemIconPixmap(int index, unsigned int nIndexInItem, const QPixmap &pixmap)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        QVariant dataIconPixmap = pItem->data(CListWidgetItem::eIconPixmapMode);
        if (!dataIconPixmap.isNull())
        {
            QVariantList pixmapList = dataIconPixmap.toList();
            unsigned int count = pixmapList.count();
            if (nIndexInItem < count)
            {
                pixmapList.replace(nIndexInItem, pixmap);
                pItem->setData(CListWidgetItem::eIconPixmapMode, pixmapList);
            }
            update();
        }
    }
}

void CVListWidget::SetItemIconShowHide(int index, unsigned int nIndexInItem, bool bShow)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        QVariant dataIconShowHide = pItem->data(CListWidgetItem::eIconShowHideMode);
        if (!dataIconShowHide.isNull())
        {
            QVariantList showList = dataIconShowHide.toList();
            unsigned int count = showList.count();
            if (nIndexInItem < count)
            {
                showList.replace(nIndexInItem, bShow);
                pItem->setData(CListWidgetItem::eIconShowHideMode, showList);
            }
            update();
        }
    }
}

void CVListWidget::SetItemButtonPixmap(int index, unsigned int nIndexInItem, const QStringList pathList)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        QVariant dataButtonPixmap = pItem->data(CListWidgetItem::eButtonPixmapMode);
        if (!dataButtonPixmap.isNull())
        {
            QVariantList list = dataButtonPixmap.toList();
            if (nIndexInItem < (unsigned int)list.count())
            {
                list.replace(nIndexInItem, pathList);
                pItem->setData(CListWidgetItem::eButtonPixmapMode, list);
            }
            update();
        }
    }
}

void CVListWidget::SetItemFontSize(int fontSize)
{
    m_nFontPixelSize = fontSize;
    update();
}

void CVListWidget::SetItemDisabled(int index, bool disabled)
{
    if (index < 0 || index >= this->count())
    {
        return;
    }
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        pItem->setData(CListWidgetItem::eDisabledMode, disabled);
        if (disabled)
        {
            QVariant dataTextColor = pItem->data(CListWidgetItem::eTextColorMode);
            if (!dataTextColor.isNull())
            {
                QVariantList colorList = dataTextColor.toList();
                for (int i = 0; i < colorList.count(); i++)
                {
                    SetItemTextColor(index, i, m_colorDisabled);
                }
            }
        }
        else
        {
            if (index == m_nSelectedIdx)
            {
                QVariant dataTextColor = pItem->data(CListWidgetItem::eTextColorMode);
                if (!dataTextColor.isNull())
                {
                    QVariantList colorList = dataTextColor.toList();
                    for (int i = 0; i < colorList.count(); i++)
                    {
                        if (i == m_nItemSelectedIndex)
                        {
                            SetItemTextColor(index, i, m_colorSelected);
                        }
                        else
                        {
                            SetItemTextColor(index, i, m_colorNormal);
                        }
                    }
                }
            }
            else
            {
                QVariant dataTextColor = pItem->data(CListWidgetItem::eTextColorMode);
                if (!dataTextColor.isNull())
                {
                    QVariantList colorList = dataTextColor.toList();
                    for (int i = 0; i < colorList.count(); i++)
                    {
                        SetItemTextColor(index, i, m_colorNormal);
                    }
                }
            }
        }
        update();
    }
}

void CVListWidget::SetItemButtonDisabled(int index, unsigned int nBtnNumber, bool disabled)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        QVariant dataButtonState = pItem->data(CListWidgetItem::eButtonStateMode);
        if (!dataButtonState.isNull())
        {
            QVariantList list = dataButtonState.toList();
            int nState;
            if (disabled)
            {
                nState = CListWidgetItem::eDisabledState;
            }
            else
            {
                nState = CListWidgetItem::eNormalState;
            }
            if (nBtnNumber < (unsigned int)list.count())
            {
                list.replace(nBtnNumber, nState);
                pItem->setData(CListWidgetItem::eButtonStateMode, list);
            }
            update();
        }
    }
}

void CVListWidget::SetSpecifiedID(int index, int id)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        pItem->setData(CListWidgetItem::eSpecifiedIDMode, id);
        update();
    }
}

void CVListWidget::SetSpecifiedIDStatus(int index, int status)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        pItem->setData(CListWidgetItem::eSpecifiedIDStatusMode, status);
        update();
    }
}

void CVListWidget::SetSpecifiedText(int index, QString text)
{
    QListWidgetItem* pItem = item(index);
    if(pItem)
    {
        pItem->setData(CListWidgetItem::eSpecifiedIDNumMode,text);
        update();
    }
}

void CVListWidget::SetElidedTextEnabled(bool flag)
{
    m_bElidedTextEnabled = flag;
}

void CVListWidget::SetItemCheckBoxState(int index, bool bChecked)
{
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        QVariant dataCheckBoxState = pItem->data(CListWidgetItem::eCheckBoxStateMode);
        if (dataCheckBoxState.isNull())
        {
            return;
        }
        QVariantList list = dataCheckBoxState.toList();
        list.replace(0, bChecked);
        pItem->setData(CListWidgetItem::eCheckBoxStateMode, list);
        if (bChecked)
        {
            bool bHaved = false;
            for (int i = 0; i < m_listCheckedItem.count(); i++)
            {
                if (pItem == m_listCheckedItem.at(i))
                {
                    bHaved = true;
                    break;
                }
            }
            if (!bHaved)
            {
                m_listCheckedItem << pItem;
            }
        }
        else
        {
            for (int j = 0; j < m_listCheckedItem.count(); j++)
            {
                if (pItem == m_listCheckedItem.at(j))
                {
                    m_listCheckedItem.removeOne(pItem);
                    break;
                }
            }
        }
        update();
    }
}

void CVListWidget::SetItemCheckBoxDisabled(bool mode)
{
    m_bCheckBoxDisabled = mode;
}

void CVListWidget::ClearCheckBoxState()
{
    for (int i = 0; i < m_listCheckedItem.count(); i++)
    {
        QListWidgetItem* pItem = m_listCheckedItem.at(i);
        if (pItem)
        {
            QVariant dataCheckBoxState = pItem->data(CListWidgetItem::eCheckBoxStateMode);
            if (!dataCheckBoxState.isNull())
            {
                QVariantList list = dataCheckBoxState.toList();
                if (!list.isEmpty())
                {
                    list.replace(0, false);
                    pItem->setData(CListWidgetItem::eCheckBoxStateMode, list);
                }
            }
        }
    }
    m_listCheckedItem.clear();
    update();
}

void CVListWidget::SetItemSelectedTextIndex(int index)
{
    m_nItemSelectedIndex = index;
}

void CVListWidget::SetLeftMargin(int margin)
{
    m_nLeftMargin = margin;
}

int CVListWidget::GetLeftMargin()
{
    return m_nLeftMargin;
}

void CVListWidget::SetCursor(int index)
{
    m_nCursorIdx = index;
    update();
}

void CVListWidget::SetItemSelected(int index)
{
    if (-1 != index && index == m_nSelectedIdx)
    {
        return;
    }
    //remove item selected
    QListWidgetItem* pOldItem = item(m_nSelectedIdx);
    if (pOldItem)
    {
        if (!IsItemDisabled(pOldItem))
        {
            SetItemTextColor(m_nSelectedIdx, m_nItemSelectedIndex, m_colorNormal);
        }
    }
    //set item selected
    if (-1 == index)
    {
        m_nSelectedIdx = -1;
        return;
    }
    QListWidgetItem* pItem = item(index);
    if (pItem)
    {
        //--- eTextStringMode ---
        QVariant dataString = pItem->data(CListWidgetItem::eTextStringMode);
        QStringList qsTextList;
        if (!dataString.isNull())
        {
           qsTextList = dataString.toStringList();
        }
        //--- eTextRectMode ---
        QVariant dataTextRect = pItem->data(CListWidgetItem::eTextRectMode);
        QList<QVariant> rectList;
        if (!dataTextRect.isNull())
        {
            rectList = dataTextRect.toList();
        }
        //--- eTextSizeMode ---
        QVariant dataTextSize = pItem->data(CListWidgetItem::eTextSizeMode);
        QList<QVariant> sizeList;
        if (!dataTextSize.isNull())
        {
            sizeList = dataTextSize.toList();
        }
        //
        if (qsTextList.isEmpty() || rectList.isEmpty() || sizeList.isEmpty())
        {
            return;
        }
        int nScrollTextIndex = 0;
        if (3 == qsTextList.count())
        {
            nScrollTextIndex = 2;
        }
        QFont font;
        font.setPixelSize(sizeList.at(nScrollTextIndex).toInt());
        m_pScrollText->setText(qsTextList.at(nScrollTextIndex),
                               rectList.at(nScrollTextIndex).toRect().width(),
                               rectList.at(nScrollTextIndex).toRect().height(),
                               font);
        m_pScrollText->startScrollText();
        m_nSelectedIdx = index;
        SetItemTextColor(index, m_nItemSelectedIndex, m_colorSelected);
    }
    update();
}

bool CVListWidget::IsCursored(int index)
{
    if (-1 != index && index == m_nCursorIdx)
    {
        return true;
    }
    return false;
}

int CVListWidget::IsButtonPushed(QListWidgetItem* pItem, const QPoint &pos)
{
    QVariant dataButtonRect = pItem->data(CListWidgetItem::eButtonRectMode);
    QVariant dataButtonIndicator = pItem->data(CListWidgetItem::eButtonIndicatorMode);
    if (dataButtonRect.isNull() || dataButtonIndicator.isNull())
    {
        return -1;
    }
    QVariantList buttonRectList = dataButtonRect.toList();
    QVariantList indicatorList = dataButtonIndicator.toList();
    for (int i = 0; i < buttonRectList.count(); i++)
    {
        QRect rect = buttonRectList.at(i).toRect();
        int left = rect.left();
        int width = rect.width();
        rect.setLeft(left + m_nLeftMargin);
        rect.setWidth(width);
        if (rect.contains(pos.x(), pos.y() - this->visualItemRect(pItem).y()))
        {
            if (i >= indicatorList.count())
            {
                break;
            }
            if (!indicatorList.at(i).toBool() ||
                (indicatorList.at(i).toBool() && this->row(pItem) == m_nCursorIdx))
            {
                return i;
            }
        }
    }
    return -1;
}

int CVListWidget::IsCheckBoxPushed(QListWidgetItem *pItem, const QPoint &pos)
{
    QVariant dataCheckBoxRect = pItem->data(CListWidgetItem::eCheckBoxRectMode);
    QVariant dataCheckBoxState = pItem->data(CListWidgetItem::eCheckBoxStateMode);
    if (dataCheckBoxRect.isNull() || dataCheckBoxState.isNull())
    {
        return -1;
    }
    QVariantList rectList = dataCheckBoxRect.toList();
    QVariantList list = dataCheckBoxState.toList();
    for (int i = 0; i < rectList.count(); i++)
    {
        QRect rect = rectList.at(i).toRect();
        if (rect.contains(pos.x(), pos.y() - this->visualItemRect(pItem).y()))
        {
            if (m_bCheckBoxDisabled)
            {
                if (i >= list.count())
                {
                    break;
                }
                bool bChecked = list.at(i).toBool();
                if (!bChecked)
                {
                    return -1;
                }
                else
                {
                    return i;
                }
            }
            else
            {
                return i;
            }
        }
    }
    return -1;
}

QString CVListWidget::IsHighlightText(QListWidgetItem *pItem, const QPoint &pos, int& highlightTextType)
{
    QVariant dataSpecialTextRect = pItem->data(CListWidgetItem::eSpecialTextRectMode);
    QVariant dataSpecialTextType = pItem->data(CListWidgetItem::eSpecialTextTypeMode);
    QVariant dataSpecialTextString = pItem->data(CListWidgetItem::eSpecialTextStringMode);
    if (dataSpecialTextRect.isNull() || dataSpecialTextType.isNull() || dataSpecialTextString.isNull())
    {
        return QString();
    }
    QVariantList textRectList = dataSpecialTextRect.toList();
    QVariantList textTypeList = dataSpecialTextType.toList();
    QStringList  textList = dataSpecialTextString.toStringList();

    for (int i = 0; i < textRectList.count(); i++)
    {
        highlightTextType = textTypeList.at(i).toInt();
        if (!highlightTextType)
        {
            continue;
        }
        QRect rect = textRectList.at(i).toRect();
        if (rect.contains(pos.x(), pos.y() - this->visualItemRect(pItem).y()))
        {
            return textList.at(i);
        }
    }
    return QString();
}

QString CVListWidget::GetHighlightText(const QStringList &qsList)
{
    if(2 == qsList.count())
    {
        return qsList.at(0) + qsList.at(1);
    }
    return QString();
}

void CVListWidget::SetScrollBarStyle1(int nScrollBarWidth)
{
    QString qsHandleColor = "qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
                            "stop:0 rgba(255, 255, 255, 0), "
                            "stop:0.459795 rgba(255, 255, 255, 0), "
                            "stop:0.459799 rgba(0, 204, 204, 255), "
                            "stop:0.652444 rgba(0, 204, 204, 255), "
                            "stop:0.652469 rgba(255, 255, 255, 0), "
                            "stop:1 rgba(255, 255, 255, 0))";

    QString qsWidth = QString::number(nScrollBarWidth) + "px";
    setStyleSheet( "*{background-color: transparent; border: 0px; background-attachment: scroll; }"
                   "QScrollBar::vertical            { border: 0px solid transparent; width: "+qsWidth+";}"
                   "QScrollBar::handle:vertical     { background-color: "+qsHandleColor+"; min-height: 12px; }"
                   "QScrollBar::add-line:vertical   { border: none; background: transparent; height: 0px; }"
                   "QScrollBar::sub-line:vertical   { border: none; background: transparent; height: 0px; }"
                   "QScrollBar::up-arrow:vertical   { border: 0px; background: transparent; }"
                   "QScrollBar::down-arrow:vertical { border: 0px; background: transparent; }"
                   "QScrollBar::add-page:vertical   { background: none; }"
                   "QScrollBar::sub-page:vertical   { background: none; }" );
}

void CVListWidget::SetScrollBarStyle2(int nScrollBarWidth)
{
    QString qsWidth = QString::number(nScrollBarWidth) + "px";
    setStyleSheet( "*{background-color: transparent; border: 0px; background-attachment: scroll; }"
                   "QScrollBar::vertical            { border: 0px solid transparent; width: "+qsWidth+";}"
                   "QScrollBar::handle:vertical     { background-color: rgb(0, 204, 204); min-height: 12px; }"
                   "QScrollBar::add-line:vertical   { border: none; background: transparent; height: 0px; }"
                   "QScrollBar::sub-line:vertical   { border: none; background: transparent; height: 0px; }"
                   "QScrollBar::up-arrow:vertical   { border: 0px; background: transparent; }"
                   "QScrollBar::down-arrow:vertical { border: 0px; background: transparent; }"
                   "QScrollBar::add-page:vertical   { background: none; }"
                   "QScrollBar::sub-page:vertical   { background: none; }" );
}

void CVListWidget::SetScrollBarStyle3(int nScrollBarWidth)
{

    QString qsWidth = QString::number(nScrollBarWidth) + "px";
    setStyleSheet( "*{background-color: transparent; border: 0px; background-attachment: scroll; }"
                   "QScrollBar::vertical            { border:0px solid transparent; width: "+qsWidth+";}"
                   "QScrollBar::handle:vertical     { border:none;background-color: rgba(255, 255, 255,20%); border-radius:2px;min-height: 12px; }"
                   "QScrollBar::add-line:vertical   { height:2px;width:4px;border-radius:2px; background: transparent; subcontrol-position:bottom; }"
                   "QScrollBar::sub-line:vertical   { height:2px;width:4px;border-radius:2px;background: transparent;}"
                   "QScrollBar::up-arrow:vertical   { border:none; background: transparent;}"
                   "QScrollBar::down-arrow:vertical { border:none; background: transparent;}"
                   "QScrollBar::add-page:vertical   { background: none; }"
                   "QScrollBar::sub-page:vertical   { background: none; }" );
}

QDate CVListWidget::GetDateFromString(const QStringList &qsList)
{
    int year = 0;
    int month = 0;
    int day = 0;
    if (3 == qsList.count())
    {
        if (4 == qsList.at(0).count())
        {
            year = qsList.at(0).toInt();
            month = qsList.at(1).toInt();
            day = qsList.at(2).toInt();
        }
        else
        {
            month = qsList.at(0).toInt();
            day = qsList.at(1).toInt();
            year = qsList.at(2).toInt();
        }
    }
    else if (2 == qsList.count())
    {
        month = qsList.at(0).toInt();
        day = qsList.at(1).toInt();
    }
    QDate date(year, month, day);
    return date;
}

QTime CVListWidget::GetTimeFromString(const QStringList &qsList)
{
    int hour = 0;
    int minute = 0;
    int second = 0;
    if (3 == qsList.count())
    {
        hour = qsList.at(0).toInt();
        minute = qsList.at(1).toInt();
        second = qsList.at(2).toInt();
    }
    else if (2 == qsList.count())
    {
        hour = qsList.at(0).toInt();
        minute = qsList.at(1).toInt();
    }
    QTime time(hour, minute, second);
    return time;
}

void CVListWidget::RecoverButtonState(QListWidgetItem* pItem)
{
    if (pItem && -1 != m_nPressedButtonIdx)
    {
        QVariant dataButtonState = pItem->data(CListWidgetItem::eButtonStateMode);
        if (!dataButtonState.isNull())
        {
            QVariantList list = dataButtonState.toList();
            list.replace(m_nPressedButtonIdx, (int)CListWidgetItem::eNormalState);
            pItem->setData(CListWidgetItem::eButtonStateMode, list);
            m_nPressedButtonIdx = -1;
        }
    }
}

bool CVListWidget::IsItemDisabled(QListWidgetItem *pItem)
{
    if (NULL == pItem)
    {
        return false;
    }
    bool disabled = false;
    QVariant dataDisabled = pItem->data(CListWidgetItem::eDisabledMode);
    if (!dataDisabled.isNull())
    {
        disabled = dataDisabled.toBool();
    }
    return disabled;
}

void CVListWidget::OnComboBoxActivated(int ComboBoxIndex, const QString &data)
{
    emit ComboBoxActivated(ComboBoxIndex,data);
}

void CVListWidget::OnComboBoxActivated(int ComboBoxIndex, int itemIndex)
{
    emit ComboBoxActivated(ComboBoxIndex,itemIndex);
}

void CVListWidget::PressedEventAction(const QPoint& pos)
{
    m_pointPressed = pos;
    m_pPressedItem = this->itemAt(pos.x(), pos.y());
    if (m_pPressedItem)
    {
        if (IsItemDisabled(m_pPressedItem))
        {
            return;
        }
        //--- Check if Button is pressed ---
        m_nPressedButtonIdx = IsButtonPushed(m_pPressedItem, pos);
        if (m_nPressedButtonIdx >= 0)
        {
            QVariant dataButtonState = m_pPressedItem->data(CListWidgetItem::eButtonStateMode);
            if (!dataButtonState.isNull())
            {
                QVariantList list = dataButtonState.toList();
                if ((int)CListWidgetItem::eDisabledState == list.at(m_nPressedButtonIdx).toInt())
                {
                    return;
                }
                int nState = CListWidgetItem::ePressedState;
                list.replace(m_nPressedButtonIdx, nState);
                m_pPressedItem->setData(CListWidgetItem::eButtonStateMode, list);
            }
            return;
        }
        //--- Check if CheckBox is pressed ---
        m_nPressedCheckBoxIdx = IsCheckBoxPushed(m_pPressedItem, pos);
        if (m_nPressedCheckBoxIdx >= 0)
        {
            return;
        }
        m_nPressedIdx = row(m_pPressedItem);
        update();
    }
}

void CVListWidget::MovedEventAction()
{
    if (IsCursored(m_nPressedIdx))
    {
        m_nPressedIdx = -1;
        update();
        return;
    }
    m_nPressedIdx = -1;
    if (-1 != m_nPressedButtonIdx)
    {
        RecoverButtonState(m_pPressedItem);
        m_pPressedItem = NULL;
    }
    update();
}

void CVListWidget::ReleasedEventAction(const QPoint& pos)
{
    QListWidgetItem* pItem = this->itemAt(pos.x(), pos.y());
    if (NULL == pItem)
    {
        Log("[CVListWidget::releasedEventAction]: pItem = NULL");
        RecoverButtonState(m_pPressedItem);
        m_nPressedIdx = -1;
        m_pPressedItem = NULL;
        update();
        return;
    }
    if (IsItemDisabled(pItem))
    {
        Log("[CVListWidget::releasedEventAction]: IsItemDisabled");
        RecoverButtonState(m_pPressedItem);
        m_nPressedIdx = -1;
        m_pPressedItem = NULL;
        update();
        return;
    }
    int index = this->row(pItem);
    //--- Check if Button is released ---
    if (-1 != m_nPressedButtonIdx)
    {
        int releaseIdx = IsButtonPushed(pItem, pos);
        QVariant dataButtonState = pItem->data(CListWidgetItem::eButtonStateMode);
        if (!dataButtonState.isNull())
        {
            QVariantList list = dataButtonState.toList();
            if ((int)CListWidgetItem::eDisabledState == list.at(m_nPressedButtonIdx).toInt())
            {
                return;
            }
        }
        if (m_pPressedItem == pItem)
        {
            if (releaseIdx == m_nPressedButtonIdx)
            {
                emit listButtonReleased(index, m_nPressedButtonIdx);
                //
                QVariant dataSpecifiedID = pItem->data(CListWidgetItem::eSpecifiedIDMode);
                int specifiedId = -1;
                if (!dataSpecifiedID.isNull())
                {
                    specifiedId = dataSpecifiedID.toInt();
                }
                else
                {
                    Log("[CVListWidget::ReleasedEventAction]: dataSpecifiedID is null.");
                }
                emit listButtonReleased(index, m_nPressedButtonIdx, specifiedId);
                Log("[CVListWidget]: emit listButtonReleased(%d, %d)", index, m_nPressedButtonIdx);
            }
            RecoverButtonState(pItem);
        }
        else
        {
            RecoverButtonState(m_pPressedItem);
        }
        m_pPressedItem = NULL;
        m_nPressedIdx = -1;
        m_nPressedButtonIdx = -1;
        update();
        return;
    }
    //--- Check if CheckBox is released ---
    if (-1 != m_nPressedCheckBoxIdx)
    {
        QVariant dataCheckBoxState = pItem->data(CListWidgetItem::eCheckBoxStateMode);
        if (!dataCheckBoxState.isNull())
        {
            int releaseIdx = IsCheckBoxPushed(pItem, pos);
            QVariantList list = dataCheckBoxState.toList();
            bool bChecked = !list.at(m_nPressedCheckBoxIdx).toBool();
            if (releaseIdx == m_nPressedCheckBoxIdx)
            {
                emit listCheckBoxReleased(index, bChecked);
                Log("[CVListWidget]: emit listCheckBoxReleased(%d, %d)", index, bChecked);
                SetItemCheckBoxState(index, bChecked);
            }
            m_pPressedItem = NULL;
            m_nPressedIdx = -1;
            m_nPressedCheckBoxIdx = -1;
        }
        return;
    }
    int nHighlightTextType = 0;
    QString qsHighlightText = IsHighlightText(pItem, pos, nHighlightTextType);
    QString _qsHighlightText = "";
    if ("" != qsHighlightText)
    {
        if (1 == nHighlightTextType) //Phone Number
        {
            if(qsHighlightText.contains("-"))
            {
                QStringList qsList = qsHighlightText.split("-");
                _qsHighlightText = GetHighlightText(qsList);
                if("" != _qsHighlightText)
                {
                    qsHighlightText = _qsHighlightText;
                }
            }
            emit phoneNumberReleased(qsHighlightText);
            Log("[CVListWidget]: emit phoneNumberReleased(%s)", qsHighlightText.toStdString().c_str());
        }
        else if (2 == nHighlightTextType) //DateTime
        {
            QDateTime dateTime;
            dateTime.setDate(QDate(0, 0, 0));
            dateTime.setTime(QTime(0, 0, 0));
            if (qsHighlightText.contains("/"))
            {
                QStringList qsList = qsHighlightText.split("/");
                dateTime.setDate(GetDateFromString(qsList));
            }
            else if (qsHighlightText.contains("-"))
            {
                QStringList qsList = qsHighlightText.split("-");
                dateTime.setDate(GetDateFromString(qsList));
            }
            else if (qsHighlightText.contains(":"))
            {
                QStringList qsList = qsHighlightText.split(":");
                dateTime.setTime(GetTimeFromString(qsList));
            }
            else if (qsHighlightText.contains(":"))
            {
                QStringList qsList = qsHighlightText.split("：");
                dateTime.setTime(GetTimeFromString(qsList));
            }
            emit dateTimeReleased(dateTime);
            Log("[CVListWidget]: emit dateTimeReleased(%s)", qsHighlightText.toStdString().c_str());
        }
        else if (3 == nHighlightTextType) //DateTime String
        {
            emit dateTimeReleased(qsHighlightText);
            Log("[CVListWidget]: emit dateTimeReleased(%s)", qsHighlightText.toStdString().c_str());
        }
        return;
    }
    if (-1 != m_nPressedIdx)
    {
        if (index == m_nPressedIdx)
        {
            emit listItemReleased(m_nPressedIdx);
            //
            QVariant dataSpecifiedID = pItem->data(CListWidgetItem::eSpecifiedIDMode);
            int specifiedId = -1;
            if (!dataSpecifiedID.isNull())
            {
                specifiedId = dataSpecifiedID.toInt();
            }
            else
            {
                Log("[CVListWidget::ReleasedEventAction]: dataSpecifiedID is null.");
            }
            emit listItemReleased(m_nPressedIdx, specifiedId);
            Log("[CVListWidget]: emit listItemReleased(%d)", m_nPressedIdx);
            //
            SetCursor(index);
            if (m_bAutoSetSelected)
            {
                SetItemSelected(index);
            }
        }
        m_pPressedItem = NULL;
        m_nPressedIdx = -1;
        m_nPressedButtonIdx = -1;
    }
    update();
}

void CVListWidget::setGeometry(int x, int y, int w, int h)
{
    if (!m_bAutoResizeGeometry)
    {
        w += 8;
        m_bAutoResizeGeometry = true;
    }
    QListWidget::setGeometry(x, y, w, h);
}

void CVListWidget::setGeometry(const QRect &rect)
{
    int w = rect.width();
    if (!m_bAutoResizeGeometry)
    {
        w += 8;
        m_bAutoResizeGeometry = true;
    }
    QListWidget::setGeometry(rect.x(), rect.y(), w, rect.height());
}

void CVListWidget::ProcessScrollText(QPainter *painter, int x, int y)
{
    m_pScrollText->paintTextImage(painter, x, y);
}

void CVListWidget::SetItemTop(int index)
{
    QListWidgetItem *item = this->item(index);
    if (item)
    {
        scrollToItem(item, PositionAtTop);
        update();
    }
}

void CVListWidget::SetItemBottom(int index)
{
    QListWidgetItem *item = this->item(index);
    if (item)
    {
        scrollToItem(item, PositionAtBottom);
        update();
    }
}

void CVListWidget::SetSpecialStyle()
{
    SetScrollBarStyle2(7);
}

void CVListWidget::SetTopItemChanged()
{
    QListWidgetItem* pTopItem = this->itemAt(QPoint(10, 2));
    if (pTopItem)
    {
        emit topItemChanged(this->row(pTopItem));
    }
}

void CVListWidget::SetTopItemChanged(int value)
{
    Log("[CVListWidget::SetTopItemChanged]: value = %d", value);
    QListWidgetItem* pTopItem = this->itemAt(QPoint(10, 10));
    QListWidgetItem* pBottomItem = this->itemAt(QPoint(10, this->height()-10));
    if (pTopItem && pBottomItem)
    {
        QListWidgetItem* pCursoredItem = this->item(m_nCursorIdx);
        if (pCursoredItem)
        {
            QRect rectCursoredItem = this->visualItemRect(pCursoredItem);
            if (rectCursoredItem.isEmpty())
            {
                return;
            }
            if (rectCursoredItem.bottom() <= 0)
            {
                SetCursor(this->row(pTopItem));
            }
            else if (rectCursoredItem.top() >= this->height())
            {
                SetCursor(this->row(pBottomItem));
            }
        }
    }
}

void CVListWidget::SetScrollBarStyle(int nScrollBarWidth)
{
    SetScrollBarStyle3(nScrollBarWidth);
}

void CVListWidget::SetButtonPushStyle(CVListWidget::eButtonPushStyle style)
{
    m_eBtnPushStyle = style;
}

CVListWidget::eButtonPushStyle CVListWidget::getButtonPushStyle()
{
    return m_eBtnPushStyle;
}

void CVListWidget::setEnabled(bool mode)
{
    m_pScroller->setDisabled(!mode);
    update();
}

void CVListWidget::setDisabled(bool mode)
{
    m_pScroller->setDisabled(mode);
    update();
}
