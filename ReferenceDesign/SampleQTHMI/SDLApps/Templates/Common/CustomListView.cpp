#include "CustomListView.h"
//#include "SDLApps/Templates/AppListView/CAppButton.h"
#include "HMIWidgets/CAppButton.h"
#include "HMIFrameWork/log_interface.h"

ListItemData::ListItemData(string text, int id, string path)
    :m_text(text)
    ,m_id(id)
    ,m_path(path)
{
}

CustomListView::CustomListView(int iWidth, int iHeight, int iMode, QWidget *parent)
    :QWidget(parent)
    ,m_iMode(iMode)
    ,m_pressx(0)
    ,m_pressy(0)
    ,m_curpage(0)
    ,m_pVlist(NULL)
    ,m_AppWidth(150)
    ,m_AppHeight(120+5+21)
    ,m_pAppListArea(NULL)
{
    setMinimumSize(iWidth, iHeight);
    setMaximumSize(iWidth, iHeight);

    //list
    m_pVlist = new CVListWidget(this);
    m_pVlist->setGeometry(54,0,718,iHeight);
    m_pVlist->SetLeftMargin(0);
    m_pVlist->SetSplitLine(":/Settings/line.png",":/Settings/line.png");
    m_pVlist->SetScrollBarStyle(4);
    m_pVlist->SetItemBackgroundInfo("",":/Settings/list_push_bg.png","");
    m_pVlist->AutoSetSelected(false);
    m_pVlist->hide();

    connect(m_pVlist,SIGNAL(listItemReleased(int, int)),this,SLOT(OnChoiceSelected(int, int)),static_cast<Qt::ConnectionType>(Qt::QueuedConnection|Qt::UniqueConnection));

    m_pAppListArea = new QWidget(this);
    m_pAppListArea->setGeometry(85,0,630,307);

    m_pItemShowVec = &m_ListItemVec;
    m_pShowItemDataVec = &m_ListItemDataVec;
}

CustomListView::~CustomListView() {

}

void CustomListView::AddItem(std::string strText, int iId, std::string strIconPath) {
    if (m_iMode == LIST) {
        ListItemData itemData(strText, iId, strIconPath);
        m_ListItemDataVec.push_back(itemData);

        if (m_pVlist) {
            CListWidgetItem item (QSize(718,57));
            item.SetSpecifiedID(iId);
            item.AddText(QRect(0,0,800-54-94-150-50,57),QString::fromStdString(strText),Qt::AlignLeft|Qt::AlignVCenter,24);
            m_pVlist->InsertItem(m_pVlist->count(),item);
        }
    } else if (m_iMode == ICON) {
        CAppButton *pNewItem = new CAppButton(m_pAppListArea);
        int r = m_ListItemVec.size() / 4;
        int c = m_ListItemVec.size() % 4;
        pNewItem->setGeometry((m_AppWidth+10) * c, (m_AppHeight+15) * r,
                              m_AppWidth, m_AppHeight);
        pNewItem->setFuncId(iId);
        pNewItem->setIcon(strIconPath.c_str(), strIconPath.c_str(), true, true);
        pNewItem->setText(strText.c_str());
        pNewItem->show();

        m_ListItemVec.push_back(pNewItem);
        connect(pNewItem, SIGNAL(clickedWitchFuncId(int)),
                SLOT(OnChoiceSelected(int)));
    }
}

void CustomListView::UpdateItemShow(unsigned int iStartItemIndex) {
    m_pVlist->hide();
    m_pAppListArea->hide();

    if (m_iMode == LIST) {
        m_pVlist->RemoveAllItems();

        for(int i = 0; i < m_pShowItemDataVec->size(); ++i)
        {
            CListWidgetItem item (QSize(718,57));
            item.SetSpecifiedID(m_pShowItemDataVec->at(i).GetID());
            item.AddText(QRect(0,0,800-54-94-150-50,57),QString::fromStdString(m_pShowItemDataVec->at(i).GetText()),Qt::AlignLeft|Qt::AlignVCenter,24);
            m_pVlist->InsertItem(m_pVlist->count(),item);
        }

        m_pVlist->show();
    } else if (m_iMode == ICON) {
        for (unsigned int i = 0; i != m_ListItemVec.size(); ++i) {
            m_ListItemVec[i]->hide();
        }

        int r = 0, c = 0;
        if (iStartItemIndex < m_pItemShowVec->size()) {
            for (unsigned int i = iStartItemIndex; i != m_pItemShowVec->size() && i < ICON_PAGE + iStartItemIndex; ++i) {
                r = (i / 4) % 2;
                c = i % 4;
                m_pItemShowVec->at(i)->show();
                m_pItemShowVec->at(i)->setGeometry((m_AppWidth+10) * c, (m_AppHeight+15) * r,
                                                   m_AppWidth, m_AppHeight);
            }
        }

        m_pAppListArea->show();
    }

    repaint();
}

void CustomListView::OnChoiceSelected(int iIndex) {
    INFO("CustomListView::OnChoiceSelected(int iIndex) index: %d", iIndex);
    emit ItemClicked(iIndex);
}

void CustomListView::OnChoiceSelected(int iIndex, int iId)
{
    INFO("CustomListView::OnChoiceSelected(int iIndex, int iId) index: %d, id: %d", iIndex, iId);
    emit ItemClicked(iId);
}

void CustomListView::showEvent(QShowEvent *event) {
    Q_UNUSED(event);
    if (m_iMode == LIST) {
        UpdateItemShow();
    }
}

void CustomListView::ItemFilter(std::string strKey) {
    m_FilterItemVec.clear();
    m_FilterItemDataVec.clear();
    std::string strText;

    if (m_iMode == LIST) {
        if (!strKey.empty()) {
            for (unsigned int i = 0; i != m_ListItemDataVec.size(); ++i) {

                strText = m_ListItemDataVec[i].GetText();
                if (strText.find(strKey) != std::string::npos) {
                    m_FilterItemDataVec.push_back(m_ListItemDataVec[i]);
                }

            }
            m_pShowItemDataVec = &m_FilterItemDataVec;
        } else {
            m_pShowItemDataVec = &m_ListItemDataVec;
        }
    }
    else if (m_iMode == ICON) {
        if (!strKey.empty()) {
            for (unsigned int i = 0; i != m_ListItemVec.size(); ++i) {
                strText = ((CAppButton *)m_ListItemVec[i])->Text();
                if (strText.find(strKey) != std::string::npos) {
                    m_FilterItemVec.push_back(m_ListItemVec[i]);
                }
            }
            m_pItemShowVec = &m_FilterItemVec;
        } else {
            m_pItemShowVec = &m_ListItemVec;
        }
    }

    UpdateItemShow();
}

void CustomListView::mousePressEvent(QMouseEvent *e) {
    if (m_iMode != ICON)
        return;

    m_pressx = e->x();
    m_pressy = e->y();
}

void CustomListView::mouseReleaseEvent(QMouseEvent *e) {
    if (m_iMode != ICON)
        return;

    int x = e->x();
    int page = (m_pItemShowVec->size() + (ICON_PAGE - 1)) / ICON_PAGE;
    if ((m_pressx - x) > 30 && page > m_curpage) {
        // 下页
        UpdateItemShow(m_curpage * ICON_PAGE);
        m_curpage++;
    } else if ((x - m_pressx) > 30 && m_curpage > 1) {
        // 上页
        UpdateItemShow((m_curpage - 2)*ICON_PAGE);
        m_curpage--;
    }
}

