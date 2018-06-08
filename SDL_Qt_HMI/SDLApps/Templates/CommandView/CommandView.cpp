#include "CommandView.h"
#include "SDLApps/Templates/Common/AppBase.h"
#include "HMIFrameWork/log_interface.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "SDLApps/app/SDLApps.h"

CCommandView::CCommandView(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_pList(pList)
    ,m_pTopWidget(NULL)
    ,m_pCurrentMenu(NULL)
    ,m_pVlist(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    //top widget
    m_pTopWidget = new TopNavigateWidget(this);
    m_pTopWidget->SetReturnTitle(QString(""));
    m_pTopWidget->ShowBack();
    m_pTopWidget->ShowTitle();
    m_pTopWidget->show();
    connect(m_pTopWidget, SIGNAL(SigBackClicked()), this, SLOT(OnReturnBtnClicked()));

    //list
    m_pVlist = new CVListWidget(this);
    m_pVlist->setGeometry(54,67,718,347);
    m_pVlist->SetLeftMargin(0);
    m_pVlist->SetSplitLine(":/Settings/line.png",":/Settings/line.png");
    m_pVlist->SetScrollBarStyle(4);
    m_pVlist->SetItemBackgroundInfo("",":/Settings/list_push_bg.png","");
    m_pVlist->AutoSetSelected(false);
    m_pVlist->show();

    connect(m_pVlist,SIGNAL(listItemReleased(int)),this,SLOT(OnListItemClicked(int)),static_cast<Qt::ConnectionType>(Qt::QueuedConnection|Qt::UniqueConnection));
}

CCommandView::~CCommandView() {

}

void CCommandView::AddCommand(int iCmdId, std::string strName, std::string strImagePath) {
    tagCmdInf tempCmdInf;
    tempCmdInf.strCmd = strName;
    tempCmdInf.bMenu = false;
    tempCmdInf.iId = iCmdId;
    tempCmdInf.iParentId = 0;
    tempCmdInf.strImagePath = strImagePath;
    m_CmdVec.push_back(tempCmdInf);
}

void CCommandView::AddMenu(int iMenuId, std::string strName) {
    tagCmdInf tempCmdInf;
    tempCmdInf.strCmd = strName;
    tempCmdInf.bMenu = true;
    tempCmdInf.iId = iMenuId;
    tempCmdInf.iParentId = 0;
    m_CmdVec.push_back(tempCmdInf);
}

void CCommandView::AddSubCommand(int iParentId, int iCmdId, std::string strName, std::string strImagePath) {
    tagCmdInf tempCmdInf;
    tempCmdInf.strCmd = strName;
    tempCmdInf.bMenu = false;
    tempCmdInf.iId = iCmdId;
    tempCmdInf.iParentId = iParentId;
    tempCmdInf.strImagePath = strImagePath;
    for (unsigned int i = 0; i != m_CmdVec.size(); ++i) {
        if (m_CmdVec[i].bMenu && m_CmdVec[i].iId == iParentId) {
            m_CmdVec[i].CmdVec.push_back(tempCmdInf);
            return;
        }
    }
}

void CCommandView::RefreshCommandList(tagCmdInf *pMenu) {

    m_pVlist->RemoveAllItems();

    if (NULL == pMenu) {
        for (unsigned int i = 0; i != m_CmdVec.size(); ++i) {
            CListWidgetItem item(QSize(718,57));
            if(m_CmdVec[i].bMenu)
            {
                item.AddIcon(QRect(800-148+18,0,22,57),QPixmap(":/Settings/select_a.png"));
                item.AddText(QRect(0,0,800-148,57),QString::fromStdString(m_CmdVec[i].strCmd),Qt::AlignLeft|Qt::AlignVCenter,24);
            }
            else
            {
                if("" != m_CmdVec[i].strImagePath)
                {
                    item.AddIcon(QRect(0,8,40,40),QPixmap(QString::fromStdString(m_CmdVec[i].strImagePath)).scaled(40,40));
                    item.AddText(QRect(58,0,800-148-58,57),QString::fromStdString(m_CmdVec[i].strCmd),Qt::AlignLeft|Qt::AlignVCenter,24);
                }
                else
                {
                    item.AddText(QRect(0,0,800-148,57),QString::fromStdString(m_CmdVec[i].strCmd),Qt::AlignLeft|Qt::AlignVCenter,24);
                }
            }

            m_pVlist->InsertItem(i,item);
        }
    } else {
        for (unsigned int i = 0; i != pMenu->CmdVec.size(); ++i) {
            CListWidgetItem item(QSize(718,57));
            if(pMenu->CmdVec[i].bMenu)
            {

                item.AddIcon(QRect(800-148+18,0,22,57),QPixmap(":/Settings/select_a.png"));
                item.AddText(QRect(0,0,800-148,57),QString::fromStdString(pMenu->CmdVec[i].strCmd),Qt::AlignLeft|Qt::AlignVCenter,24);
            }
            else
            {
                if("" != pMenu->CmdVec[i].strImagePath)
                {
                    item.AddIcon(QRect(0,8,40,40),QPixmap(QString::fromStdString(pMenu->CmdVec[i].strImagePath)).scaled(40,40));
                    item.AddText(QRect(58,0,800-148-58,57),QString::fromStdString(pMenu->CmdVec[i].strCmd),Qt::AlignLeft|Qt::AlignVCenter,24);
                }
                else
                {
                    item.AddText(QRect(0,0,800-148,57),QString::fromStdString(pMenu->CmdVec[i].strCmd),Qt::AlignLeft|Qt::AlignVCenter,24);
                }
            }

            m_pVlist->InsertItem(i,item);
        }
    }
}

void CCommandView::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    m_CmdVec.clear();

    std::vector<SMenuCommand> CmdList = AppControl->getCommandList();
    std::vector<SMenuCommand> TmpCmdList;
    for (unsigned int i = 0; i < CmdList.size(); ++i) {
        if (0 != CmdList.at(i).i_cmdID && 0 == CmdList.at(i).i_menuID) {
            AddCommand(CmdList.at(i).i_cmdID, CmdList.at(i).str_menuName, CmdList.at(i).str_ImagePath);
        } else if (0 == CmdList.at(i).i_cmdID && 0 != CmdList.at(i).i_menuID) {
            AddMenu(CmdList.at(i).i_menuID, CmdList.at(i).str_menuName);

            TmpCmdList = AppControl->getCommandList(CmdList.at(i).i_menuID);
            for (unsigned int j = 0; j < TmpCmdList.size(); j++) {
                AddSubCommand(CmdList.at(i).i_menuID,
                              TmpCmdList.at(j).i_cmdID,
                              TmpCmdList.at(j).str_menuName.data(), TmpCmdList.at(j).str_ImagePath);
            }
        }
    }
    m_pCurrentMenu = NULL;
    RefreshCommandList();

    m_pTopWidget->SetReturnTitle(QString::fromStdString(AppControl->getAppName()));
}

void CCommandView::OnReturnBtnClicked() {
    AppControl->OnCommandClick(-1);
//    if(SDLApps::Inst()->FromNavi())
//    {
//        HMIFrameWork::Inst()->AppShow(NAV_ID);
//        AppControl->OnCommandClick(-1);
//    }
//    else
//    {
//        AppControl->OnCommandClick(-1);
//    }
}

void CCommandView::OnListItemClicked(int index)
{
    INFO("CCommandView::OnListItemClicked, index:", index);
    if (NULL == m_pCurrentMenu) {
        if (0 == index) {
            if(SDLApps::Inst()->FromNavi())
            {
                HMIFrameWork::Inst()->AppShow(NAV_ID);
                m_pList->OnAppExit();
            }
            else if(SDLApps::Inst()->FromMedia())
            {
                HMIFrameWork::Inst()->AppShow(MEDIA_ID);
                m_pList->OnAppExit();
            }
            else
            {
                m_pList->OnAppExit();
            }
        } else {
            if (m_CmdVec[index].bMenu) {
                m_pCurrentMenu = &m_CmdVec[index];
                RefreshCommandList(m_pCurrentMenu);
            } else {
                AppControl->OnCommandClick(m_CmdVec[index].iId);
            }
        }
    } else {
        AppControl->OnCommandClick(m_pCurrentMenu->CmdVec[index].iId);
    }
}
