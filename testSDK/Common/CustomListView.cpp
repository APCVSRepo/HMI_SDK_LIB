#include "CustomListView.h"
#include "Common/CustomButton.h"
#include "AppListView/CAppButton.h"

CustomListView::CustomListView(int iWidth,int iHeight,int iMode,QWidget *parent) :
    QWidget(parent),m_iItemSpace(0)
{
    setMinimumSize(iWidth,iHeight);
    setMaximumSize(iWidth,iHeight);
    m_iMode = iMode;

    if (iMode == LIST) {
        m_iItemWidth = iWidth*0.9;
        m_iItemHeight = iHeight*0.25;

        InitScroll();
    } else if (iMode == ICON) {
        m_iItemWidth = 185;
        m_iItemHeight = 140;
    }
}

CustomListView::~CustomListView()
{

}

void CustomListView::AddItem(std::string strText,int iId,std::string strIconPath)
{
    if (m_iMode == LIST) {
        CCustomButton *pNewItem = new CCustomButton(this);
        pNewItem->Init(m_iItemWidth,m_iItemHeight,"",":/images/choice_item_normal.png",":/images/choice_item_press.png");
        pNewItem->SetTextStyle("margin-left:10px;font: 36px \"Liberation Serif\";color:rgb(0,0,0)");
        pNewItem->SetText(strText,Qt::AlignLeft|Qt::AlignVCenter);
        pNewItem->SetSize(0,0);
        pNewItem->SetId(iId);
        m_ListItemVec.push_back(pNewItem);
        connect(pNewItem, SIGNAL(Clicked(int)), SLOT(OnChoiceSelected(int)));        
    } else if (m_iMode == ICON) {
        CAppButton *pNewItem = new CAppButton(this);
        int r = m_ListItemVec.size()/4;
        int c = m_ListItemVec.size()%4;
        pNewItem->setGeometry(5 + m_iItemWidth*c, 5 + m_iItemHeight*r,
                              m_iItemWidth - 40, m_iItemHeight - 15);
        pNewItem->setFuncId(iId);
        pNewItem->setIcon(strIconPath.c_str(),strIconPath.c_str(),true);
        pNewItem->setText(strText.c_str());
        pNewItem->show();

        m_ListItemVec.push_back(pNewItem);
        connect(pNewItem, SIGNAL(clickedWitchFuncId(int)),
                SLOT(OnChoiceSelected(int)));
    }
}

void CustomListView::SetScrollBarStyle(int iMode)
{
    if (iMode == TOP) {
        m_pScrollBar->setStyleSheet(QString::fromUtf8("\
                                                       QScrollBar::vertical {width:55px;margin-left:10px;padding-top:60px;padding-bottom:60px;border:0px;background-color:rgba(0,0,0,0%)}\
                                                       QScrollBar::sub-line{height:50px;border-image:url(:images/UpArrowDisable.png)}\
                                                       QScrollBar::add-line{height:50px;border-image:url(:images/DownArrowNormal.png)}\
                                                       QScrollBar::sub-page{border-image:url(:images/SliderBack.png);margin-left:13px;margin-right:13px}\
                                                       QScrollBar::add-page{border-image:url(:images/SliderBack.png);margin-left:13px;margin-right:13px}\
                                                       QScrollBar::handle{border-image:url(:images/Slider.png);margin-left:13px;margin-right:13px}\
                                                       "));
    } else if (iMode == MIDDLE) {
        m_pScrollBar->setStyleSheet(QString::fromUtf8("\
                                                       QScrollBar::vertical {width:55px;margin-left:10px;padding-top:60px;padding-bottom:60px;border:0px;background-color:rgba(0,0,0,0%)}\
                                                       QScrollBar::sub-line{height:50px;border-image:url(:images/UpArrowNormal.png)}\
                                                       QScrollBar::add-line{height:50px;border-image:url(:images/DownArrowNormal.png)}\
                                                       QScrollBar::sub-page{border-image:url(:images/SliderBack.png);margin-left:13px;margin-right:13px}\
                                                       QScrollBar::add-page{border-image:url(:images/SliderBack.png);margin-left:13px;margin-right:13px}\
                                                       QScrollBar::handle{border-image:url(:images/Slider.png);margin-left:13px;margin-right:13px}\
                                                       "));
    } else if (iMode == BOTTOM) {
        m_pScrollBar->setStyleSheet(QString::fromUtf8("\
                                                       QScrollBar::vertical {width:55px;margin-left:10px;padding-top:60px;padding-bottom:60px;border:0px;background-color:rgba(0,0,0,0%)}\
                                                       QScrollBar::sub-line{height:50px;border-image:url(:images/UpArrowNormal.png)}\
                                                       QScrollBar::add-line{height:50px;border-image:url(:images/DownArrowDisable.png)}\
                                                       QScrollBar::sub-page{border-image:url(:images/SliderBack.png);margin-left:13px;margin-right:13px}\
                                                       QScrollBar::add-page{border-image:url(:images/SliderBack.png);margin-left:13px;margin-right:13px}\
                                                       QScrollBar::handle{border-image:url(:images/Slider.png);margin-left:13px;margin-right:13px}\
                                                       "));
    }
}

void CustomListView::UpdateItemShow(int iStartItemIndex)
{
    if (m_iMode == LIST) {
        for (int i = 0;i != m_ListItemVec.size();++i) {
            ((CCustomButton *)m_ListItemVec[i])->SetSize(0,0);
        }

        if (iStartItemIndex < m_pItemShowVec->size()) {
            for(int i = iStartItemIndex;i != m_pItemShowVec->size();++i) {
                ((CCustomButton *)m_pItemShowVec->at(i))->SetSize(m_iItemWidth,m_iItemHeight);
                m_pItemShowVec->at(i)->setGeometry(0,(i-iStartItemIndex)*(m_iItemHeight+m_iItemSpace),m_iItemWidth,m_iItemHeight);
            }
        }

        UpdateScrollParam(m_pItemShowVec->size());
    } else if (m_iMode == ICON) {
        for(int i = 0;i != m_ListItemVec.size();++i) {
            m_ListItemVec[i]->hide();
        }

        int r = 0,c = 0;
        if (iStartItemIndex < m_pItemShowVec->size()) {
            for(int i = iStartItemIndex;i != m_pItemShowVec->size();++i) {
                r = i / 4;
                c = i % 4;
                m_pItemShowVec->at(i)->show();
                m_pItemShowVec->at(i)->setGeometry(5 + m_iItemWidth*c,
                                                   5 + m_iItemHeight*r,
                                                   m_iItemWidth-40,
                                                   m_iItemHeight-15);
            }
        }
    }

    repaint();
}

void CustomListView::InitScroll()
{
    m_pScrollBar = new QScrollBar(this);
    m_pScrollBar->setGeometry(width()*0.9,0,width()*0.1,height());
    m_pScrollBar->setMinimum(0);
    m_pScrollBar->setMaximum(0);
    SetScrollBarStyle(TOP);
    int iPage = (int)((double)(height() + m_iItemSpace)/(m_iItemHeight+m_iItemSpace));
    m_pScrollBar->setPageStep(iPage);
    m_pScrollBar->hide();

    connect(m_pScrollBar,SIGNAL(valueChanged(int)),this,SLOT(OnScrollBarValueChange(int)));
}

void CustomListView::OnScrollBarValueChange(int iValue)
{
    if (iValue == m_pScrollBar->minimum()) {
        SetScrollBarStyle(TOP);
    } else if (iValue == m_pScrollBar->maximum()) {
        SetScrollBarStyle(BOTTOM);
    } else {
        SetScrollBarStyle(MIDDLE);
    }
    UpdateItemShow(iValue);
}

void CustomListView::SetSpace(int iSpace)
{
    m_iItemSpace = iSpace;
}

void CustomListView::SetScrollBarStyle(QString strStyle)
{
    m_pScrollBar->setStyleSheet(strStyle);
}

void CustomListView::OnChoiceSelected(int iIndex)
{
    emit ItemClicked(iIndex);
}

void CustomListView::showEvent(QShowEvent * event)
{    
    m_pItemShowVec = &m_ListItemVec;
    if (m_iMode == LIST) {
        UpdateItemShow();
    }
}

void CustomListView::ItemFilter(std::string strKey)
{
    m_FilterItemVec.clear();
    std::string strText;
    if (!strKey.empty()) {
        for(int i = 0;i != m_ListItemVec.size();++i) {
            if (m_iMode == LIST) {
                strText = ((CCustomButton *)m_ListItemVec[i])->Text();
            } else if (m_iMode == ICON) {
                strText = ((CAppButton *)m_ListItemVec[i])->Text();
            } if (strText.find(strKey) != std::string::npos) {
                m_FilterItemVec.push_back(m_ListItemVec[i]);
            }
        }
        m_pItemShowVec = &m_FilterItemVec;
    } else {
        m_pItemShowVec = &m_ListItemVec;
    }

    UpdateItemShow();
}

void CustomListView::UpdateScrollParam(int iItemCount)
{
    int iMax = iItemCount*(m_iItemHeight+m_iItemSpace) - m_iItemSpace - height();
    if (iMax > 0) {
        m_pScrollBar->show();
        m_pScrollBar->setMaximum(iItemCount - m_pScrollBar->pageStep());
    } else {
        m_pScrollBar->hide();
    }
}
