#include "CommandView.h"
#include "Common/AppBase.h"

CCommandView::CCommandView(AppListInterface *pList,QWidget *parent) :
    QWidget(parent),m_pCurrentMenu(NULL)
{
    int iHeight = 0;
    if (parent) {
        iHeight = parent->height();
        setGeometry(0,0,parent->width(),iHeight);
    }
    m_pList = pList;

    setAutoFillBackground(true);
    QPixmap pixmap(":/images/MainWidget/Backgroud.png");
    pixmap = pixmap.scaled(width(),height(), Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    setPalette(palette);

    m_pMainLayout = new QVBoxLayout(this);
    m_pTopLayout = new QHBoxLayout;
    m_pBottomLayout = new QHBoxLayout;
    m_pReturnBtn = new CButton;
    m_pAppNameLab = new QLabel;
    m_pCommandList = new CustomCombobox(iHeight - 80);
    m_pCommandList->setMinimumWidth(width()*0.9-20);
    m_pCommandList->setMaximumWidth(width()*0.9-20);

    m_pTopLayout->addWidget(m_pReturnBtn);
    m_pTopLayout->addWidget(m_pAppNameLab);
    m_pTopLayout->addStretch(1);
    m_pTopLayout->setContentsMargins(7,0,0,0);


    m_pBottomLayout->addStretch(1);
    m_pBottomLayout->addWidget(m_pCommandList);
    m_pBottomLayout->setContentsMargins(0,0,10,0);

    m_pMainLayout->addLayout(m_pTopLayout);
    m_pMainLayout->addLayout(m_pBottomLayout,1);
    m_pMainLayout->setSpacing(0);

    m_pAppNameLab->setStyleSheet(QString("margin-left:10px;font: 60 32px \"Liberation Serif\";color:rgb(0,0,0);border: 0px"));

    m_pReturnBtn->initParameter(50,50,":/images/ReturnBtnNormal.png",":/images/ReturnBtnPress.png","","");

    connect(m_pReturnBtn,SIGNAL(clicked()),this,SLOT(OnReturnBtnClicked()));
    connect(m_pCommandList,SIGNAL(ItemClickedSignal(QListWidgetItem*)),
            this,SLOT(OnCommandListItemClicked(QListWidgetItem*)));
}

CCommandView::~CCommandView()
{
    delete m_pMainLayout;
    delete m_pReturnBtn;
    delete m_pAppNameLab;
    delete m_pCommandList;
}

void CCommandView::AddCommand(int iCmdId,std::string strName,std::string strImagePath)
{
    tagCmdInf tempCmdInf;
    tempCmdInf.strCmd = strName;
    tempCmdInf.bMenu = false;
    tempCmdInf.iId = iCmdId;
    tempCmdInf.iParentId = 0;
    tempCmdInf.strImagePath = strImagePath;
    m_CmdVec.push_back(tempCmdInf);
}

void CCommandView::AddMenu(int iMenuId,std::string strName)
{
    tagCmdInf tempCmdInf;
    tempCmdInf.strCmd = strName;
    tempCmdInf.bMenu = true;
    tempCmdInf.iId = iMenuId;
    tempCmdInf.iParentId = 0;
    m_CmdVec.push_back(tempCmdInf);
}

void CCommandView::AddSubCommand(int iParentId,int iCmdId,std::string strName,std::string strImagePath)
{
    tagCmdInf tempCmdInf;
    tempCmdInf.strCmd = strName;
    tempCmdInf.bMenu = false;
    tempCmdInf.iId = iCmdId;
    tempCmdInf.iParentId = iParentId;
    tempCmdInf.strImagePath = strImagePath;
    for (int i = 0; i != m_CmdVec.size(); ++i) {
        if (m_CmdVec[i].bMenu && m_CmdVec[i].iId == iParentId) {
            m_CmdVec[i].CmdVec.push_back(tempCmdInf);
            return;
        }
    }
}

void CCommandView::RefreshCommandList(tagCmdInf *pMenu)
{
    m_pCommandList->ClearAllItem();

    if (NULL == pMenu) {
        for (int i = 0;i != m_CmdVec.size();++i) {
            m_pCommandList->AddListItem(m_CmdVec[i].strCmd.c_str(),
                                        m_CmdVec[i].bMenu,m_CmdVec[i].strImagePath);
        }
    } else {
        for (int i = 0;i != pMenu->CmdVec.size();++i) {
            m_pCommandList->AddListItem(pMenu->CmdVec[i].strCmd.c_str(),
                                        pMenu->CmdVec[i].bMenu,m_CmdVec[i].strImagePath);
        }
    }
    m_pCommandList->show();
}

void CCommandView::showEvent(QShowEvent * e)
{
    //m_pCommandList->SetPos(m_pMenuBtn->geometry().left(),m_pMenuBtn->geometry().top(),m_pMenuBtn->geometry().width()*2.5,0);
    m_CmdVec.clear();

    std::vector<SMenuCommand> CmdList = m_pList->getActiveApp()->getCommandList();
    std::vector<SMenuCommand> TmpCmdList;
    for (unsigned int i = 0; i < CmdList.size(); ++i) {
        if (0 != CmdList.at(i).i_cmdID && 0 == CmdList.at(i).i_menuID) {
            AddCommand(CmdList.at(i).i_cmdID,CmdList.at(i).str_menuName,CmdList.at(i).str_ImagePath);
        }else if (0 == CmdList.at(i).i_cmdID && 0 != CmdList.at(i).i_menuID) {
            AddMenu(CmdList.at(i).i_menuID,CmdList.at(i).str_menuName);

            TmpCmdList = m_pList->getActiveApp()->getCommandList(CmdList.at(i).i_menuID);
            for(unsigned int j = 0; j < TmpCmdList.size(); j++) {
                AddSubCommand(CmdList.at(i).i_menuID,
                              TmpCmdList.at(j).i_cmdID,
                              TmpCmdList.at(j).str_menuName.data(),TmpCmdList.at(j).str_ImagePath);
            }
        }
    }
    m_pCurrentMenu = NULL;
    RefreshCommandList();

    AppBase::SetEdlidedText(m_pAppNameLab,
                            m_pList->getActiveApp()->getAppName().c_str(),
                            width()*0.8);
}

void CCommandView::OnReturnBtnClicked()
{
    m_pList->getActiveApp()->OnCommandClick(-1);
}

void CCommandView::OnCommandListItemClicked(QListWidgetItem *pItem)
{
    int iRow = m_pCommandList->row(pItem);

    if (NULL == m_pCurrentMenu) {
        if (0 == iRow) {
            m_pList->OnAppExit();
        } else {
            if (m_CmdVec[iRow].bMenu) {
                m_pCurrentMenu = &m_CmdVec[iRow];
                RefreshCommandList(m_pCurrentMenu);
            } else {
                m_pList->getActiveApp()->OnCommandClick(m_CmdVec[iRow].iId);
            }
        }
    } else {
        m_pList->getActiveApp()->OnCommandClick(m_pCurrentMenu->CmdVec[iRow].iId);
    }
}
