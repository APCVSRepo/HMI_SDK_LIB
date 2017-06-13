#include "CustomCombobox.h"

#define PAGEITEM 5
#define PAGEITEMWEIGHT 0.2

CustomCombobox::CustomCombobox(int iMaxHeight,bool bUp,QWidget *parent) : QListWidget(parent)
  ,m_iHeight(0),m_iStartX(0),m_iStartY(0),m_iWidth(0),m_iOldHoverItemIndex(-1)
{
    m_bUp = bUp;
    m_iMaxHeight = iMaxHeight / PAGEITEM * PAGEITEM;
    setFixedHeight(m_iMaxHeight);

#ifndef ANDROID
    QPalette pll = palette();
    pll.setBrush(QPalette::Base,QBrush(QColor(255,255,255,0)));
    setPalette(pll);
#endif

    setStyleSheet(cssString());


    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setVerticalScrollBar(&m_scrollWidget);
    m_scrollWidget.init(m_iMaxHeight);
    //SetScrollParams(4,4);
    setFrameShape(QFrame::NoFrame);
    setFocusPolicy(Qt::NoFocus);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setBackgroundRole(QPalette::Background);

    SetScrollBarStyle(TOP);

    /*
    m_pTimer = new QTimer;
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(OnTimeOutSlot()));
    m_pTimer->start(50);
    */
    setMouseTracking(true);

    connect(&m_scrollWidget,SIGNAL(valueChanged(int)),
            this,SLOT(OnScrollBarValueChange(int)));
}

CustomCombobox::~CustomCombobox()
{

}

void CustomCombobox::ClearAllItem()
{
    QListWidgetItem *pTempItem = NULL;
    while (count() != 0) {
        pTempItem = item(0);
        removeItemWidget(pTempItem);
        delete pTempItem;
    }

    for (int i = 0;i != m_itemList.size();++i) {
        delete m_itemList[i];
    }
    m_itemList.clear();

    m_iHeight = 0;
    m_iOldHoverItemIndex = -1;
}

void CustomCombobox::SetScrollBarStyle(int iMode)
{
    if (iMode == TOP) {
        m_scrollWidget.setStyleSheet(QString::fromUtf8("\
                                                       QScrollBar::vertical {width:55px;margin-top:10px;margin-bottom:10px;padding-top:60px;padding-bottom:60px;border:0px;background-color:rgba(0,0,0,0%)}\
                                                       QScrollBar::sub-line{height:50px;border-image:url(:images/UpArrowDisable.png)}\
                                                       QScrollBar::add-line{height:50px;border-image:url(:images/DownArrowNormal.png)}\
                                                       QScrollBar::sub-page{border-image:url(:images/SliderBack.png);margin-left:13px;margin-right:13px}\
                                                       QScrollBar::add-page{border-image:url(:images/SliderBack.png);margin-left:13px;margin-right:13px}\
                                                       QScrollBar::handle{border-image:url(:images/Slider.png);margin-left:13px;margin-right:13px}\
                                                       "));
    }else if (iMode == MIDDLE) {
        m_scrollWidget.setStyleSheet(QString::fromUtf8("\
                                                       QScrollBar::vertical {width:55px;margin-top:10px;margin-bottom:10px;padding-top:60px;padding-bottom:60px;border:0px;background-color:rgba(0,0,0,0%)}\
                                                       QScrollBar::sub-line{height:50px;border-image:url(:images/UpArrowNormal.png)}\
                                                       QScrollBar::add-line{height:50px;border-image:url(:images/DownArrowNormal.png)}\
                                                       QScrollBar::sub-page{border-image:url(:images/SliderBack.png);margin-left:13px;margin-right:13px}\
                                                       QScrollBar::add-page{border-image:url(:images/SliderBack.png);margin-left:13px;margin-right:13px}\
                                                       QScrollBar::handle{border-image:url(:images/Slider.png);margin-left:13px;margin-right:13px}\
                                                       "));
    }else if (iMode == BOTTOM) {
        m_scrollWidget.setStyleSheet(QString::fromUtf8("\
                                                       QScrollBar::vertical {width:55px;margin-top:10px;margin-bottom:10px;padding-top:60px;padding-bottom:60px;border:0px;background-color:rgba(0,0,0,0%)}\
                                                       QScrollBar::sub-line{height:50px;border-image:url(:images/UpArrowNormal.png)}\
                                                       QScrollBar::add-line{height:50px;border-image:url(:images/DownArrowDisable.png)}\
                                                       QScrollBar::sub-page{border-image:url(:images/SliderBack.png);margin-left:13px;margin-right:13px}\
                                                       QScrollBar::add-page{border-image:url(:images/SliderBack.png);margin-left:13px;margin-right:13px}\
                                                       QScrollBar::handle{border-image:url(:images/Slider.png);margin-left:13px;margin-right:13px}\
                                                       "));
    }
}

void CustomCombobox::AddListItem(QString strText,bool bMenu,std::string strImagePath)
{
    QListWidgetItem *item = new QListWidgetItem;
    int w = width()-70;
    int h = m_iMaxHeight * PAGEITEMWEIGHT;
    item->setSizeHint(QSize(w,h));
    //item->setFlags(item->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsDragEnabled);
    addItem(item);
    CustomComboboxItem *itemWidget = new CustomComboboxItem(w,h,this);
    // insertItem(index,itemWidget);
    itemWidget->SetBkPic(":/images/CommandItemNormal.png",
                         ":/images/CommandItemPress.png",
                         ":/images/CommandItemNormal.png");
    setItemWidget(item,itemWidget);    
    itemWidget->setText(strText);
    itemWidget->setIsMenu(bMenu);
    if(strImagePath != "")
    {
        itemWidget->SetLeftIcon(strImagePath);
    }
    m_itemList.push_back(itemWidget);

    connect(itemWidget,SIGNAL(ItemClicked(CustomComboboxItem*)),
            this,SLOT(OnItemClicked(CustomComboboxItem*)));

    m_iHeight += h;
    if (m_iHeight > m_iMaxHeight) {
        m_iHeight = m_iMaxHeight;
    }

    //SetPos(m_iStartX,m_iStartY,m_iWidth,m_iHeight);
}

void CustomCombobox::SetPos(int iStartX,int iStartY,int iWidth,int iHeight)
{
    if (0 == m_iWidth) {
        m_iStartX = iStartX;
        m_iStartY = iStartY;
        m_iWidth = iWidth;
        m_iHeight = iHeight;
    }

    if (m_bUp) {
        setGeometry(iStartX,iStartY - iHeight,iWidth,iHeight);
    } else {
        setGeometry(iStartX,iStartY,iWidth,iHeight);
    }    
}

void CustomCombobox::SetScrollParams(int page,int range)
{
    /*
    if (page<=0 || range<=0)
        return;
    m_scrollWidget.setPageStep(page);
    m_scrollWidget.setRange(0,range-1);
    m_LineHeight = (height()-10)/page;
    for (int i = 0; i<m_itemList.count(); ++i) {
        AppItemWidget *item = m_itemList.at(i);
        item->setFixedHeight(m_LineHeight);
    }
    */
}

void CustomCombobox::OnTimeOutSlot()
{
    int x = QCursor::pos().x();
    int y = QCursor::pos().y();
    if (x > m_iStartX && x < m_iStartX + m_iWidth
            && y > m_iStartY - m_iHeight && y < m_iStartY) {
        y -= m_iStartY - m_iHeight;
        int iIndex = y * PAGEITEM / m_iMaxHeight + m_scrollWidget.sliderPosition();
        if (m_iOldHoverItemIndex != iIndex) {
            if (m_iOldHoverItemIndex != -1) {
                m_itemList[m_iOldHoverItemIndex]->ChangeBkPic(CustomComboboxItem::NORMAL_STATE);
            }
            m_iOldHoverItemIndex = iIndex;
            m_itemList[iIndex]->ChangeBkPic(CustomComboboxItem::HOVER_STATE);
        }
    }
}

void CustomCombobox::OnScrollBarValueChange(int iValue)
{
    if (iValue == m_scrollWidget.minimum()) {
        SetScrollBarStyle(TOP);
    } else if (iValue == m_scrollWidget.maximum()) {
        SetScrollBarStyle(BOTTOM);
    } else {
        SetScrollBarStyle(MIDDLE);
    }
}

void CustomCombobox::OnItemClicked(CustomComboboxItem *pItem)
{
    for(int i = 0;i != count();++i) {
        if (itemWidget(item(i)) == pItem) {
            emit ItemClickedSignal(item(i));
            return;
        }
    }
}

QString CustomCombobox::cssString()
{
#if 0
    return QString::fromUtf8("QListWidget{ \
                             border: none;\
                             color:white;\
                             background-color:transparent;\
                         }  \
                         QListWidget:item:hover{border: 0px;}\
                         QListWidget::item:selected { \
                              border:none;  \
                              background:none;\
                              border: 2px solid white;border-radius: 10px;padding: 2px;\
                         }  \
                         ");
#endif
#ifdef ANDROID
    return QString::fromUtf8("background-color:transparent;");
#else
    return QString::fromUtf8("QListWidget:item:hover{border:0px;}");
#endif
}



