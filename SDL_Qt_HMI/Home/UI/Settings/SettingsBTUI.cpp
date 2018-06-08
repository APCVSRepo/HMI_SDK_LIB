#include "SettingsBTUI.h"
#include "Home/data/Settings/SettingsBTData.h"
#include "Home/app/Home.h"
#include "HMIFrameWork/log_interface.h"
#include "HMIFrameWork/HMIFrameWork.h"
SettingsBTUI::SettingsBTUI(QWidget *parent)
    :QWidget(parent)
    ,CView(Home::eViewId_Settings_BT)
    ,m_pBackBtn(NULL)
    ,m_pTitleLabel(NULL)
    ,m_iBTStatus(0)
{
    this->setGeometry(QRect(0,40,800,440));
    this->setStyleSheet("QWidget{border:none;background:transparent;}");

    m_pBackBtn = new CPushButton(this);
    m_pBackBtn->setStyleSheet("QPushButton{border:none;background:transparent;}");
    m_pBackBtn->setGeometry(QRect(16,21,198,29));
    m_pBackBtn->SetText(QRect(38,0,160,29),tr("Setting"),22,Qt::AlignLeft|Qt::AlignVCenter,QColor(255,255,255,204));
    m_pBackBtn->SetIcon(QRect(0,0,29,29),":/Settings/button_back.png");
    m_pBackBtn->setFocusPolicy(Qt::NoFocus);
    m_pBackBtn->show();

    m_pTitleLabel = new QLabel(this);
    m_pTitleLabel->setGeometry(QRect(220,21,360,29));
    m_pTitleLabel->setStyleSheet("QLabel{color:#4BA9FF;font-size:24px;border:none;background:transparent;}");
    m_pTitleLabel->setAlignment(Qt::AlignCenter);
    m_pTitleLabel->setText(tr("Bluetooth"));
    m_pTitleLabel->show();

    //list
    m_pVlist = new CVListWidget(this);
    m_pVlist->setGeometry(54,67,718,347);
    m_pVlist->SetLeftMargin(0);
    m_pVlist->SetSplitLine(":/Settings/line.png",":/Settings/line.png");
    m_pVlist->SetScrollBarStyle(4);
    //TODO:
    m_pVlist->SetItemBackgroundInfo("",":/Settings/list_push_bg.png","");
    m_pVlist->AutoSetSelected(false);

    this->SetBTStatus(m_iBTStatus, true);

//    connect(m_pVlist,SIGNAL(listButtonReleased(int,int)),this,SLOT(OnListButtonReleased(int,int)),static_cast<Qt::ConnectionType>(Qt::QueuedConnection|Qt::UniqueConnection));
    connect(m_pVlist,SIGNAL(listButtonReleased(int,int,int)),this,SLOT(OnListButtonReleased(int,int,int)),static_cast<Qt::ConnectionType>(Qt::QueuedConnection|Qt::UniqueConnection));
    connect(m_pVlist,SIGNAL(listItemReleased(int,int)),this,SLOT(OnListItemClicked(int,int)),static_cast<Qt::ConnectionType>(Qt::QueuedConnection|Qt::UniqueConnection));

    m_pVlist->show();

    connect(this,SIGNAL(SigBTStatusChanged(int)),this,SLOT(OnBTStatusChanged(int)));
    connect(m_pBackBtn,SIGNAL(clicked()),this,SLOT(OnBack()),Qt::UniqueConnection);

}

SettingsBTUI::~SettingsBTUI()
{

}

void SettingsBTUI::viewAction(int state)
{

}

void SettingsBTUI::OnBack()
{
    if(Home::Inst()->GetNotifyBTShowStatus())
    {
        HMIFrameWork::Inst()->AppShow(Home::Inst()->GetNotifyBTShowId(),"Default");
        Home::Inst()->SetNotifyBTShowStatus(false);
    }
    else
    {
        Home::Inst()->ViewBack();
    }
}

void SettingsBTUI::OnListButtonReleased(int index, int btnIndex)
{
    INFO()<<"OnListButtonReleased: index: "<<index<<", btnIndex: "<<btnIndex;
}

void SettingsBTUI::OnListButtonReleased(int index, int btnIndex, int specifiedID)
{
    INFO()<<"OnListButtonReleased: index: "<<index<<", btnIndex: "<<btnIndex<<", specifiedID: "<<specifiedID;
    if(0 == index)
    {
        if(0 == specifiedID)
        {
            this->SetBTStatus(1);
        }
        else
        {
            this->SetBTStatus(0);
        }
    }
}

void SettingsBTUI::OnListItemClicked(int index, int specifiedID)
{
    INFO()<<"SettingsBTUI::OnListItemClicked: index: "<<index<<", specifiedID: "<<specifiedID;
    if(0 == index)
    {
        return;
    }

    if((m_pVlist->count()-1) == index)
    {
        INFO()<<"[SettingsBTUI]change to [add other hot spots] view";
        //TODO: change to [add other hot spots] view
        return;
    }

    if(0 == m_pVlist->GetSpecifiedID(index))
    {
        INFO()<<"other equipment text, do nothing";
        return;
    }

    const BTDeviceInfo &info = (BTStatus_NORMAL == m_pVlist->GetSpecifiedIDStatus(index))?
                SettingsBTData::GetInstance()->GetBTSearchListInfo(index-specifiedID):
                SettingsBTData::GetInstance()->GetBTPairedListInfo(index-specifiedID);
    SettingsBTData::GetInstance()->SetSelectedBTInfo(info);

    //TODO: connect BT
}

void SettingsBTUI::OnBTStatusChanged(int status)
{
    INFO()<<"OnBTStatusChanged: "<<status;
    if(1 == status)
    {
        this->StartBT();
    }
}

void SettingsBTUI::SetBTStatus(int status, bool init)
{
    if(!init)
    {
        if(status == m_iBTStatus)
        {
            INFO()<<"[SettingsBTUI]same BT status, no need SetBTStatus";
            return;
        }
    }
    m_iBTStatus = status;
    m_pVlist->RemoveAllItems();

    CListWidgetItem item(QSize(718,57));
    item.AddText(QRect(0,0,300,57),QString(tr("Bluetooth")),Qt::AlignLeft|Qt::AlignVCenter,24);
    QStringList list;
    if(0 == status)
    {
        list<<":/Settings/button_h_close.png"<<":/Settings/button_h_close.png"<<":/Settings/button_h_close.png";
    }
    else
    {
        list<<":/Settings/button_h_on.png"<<":/Settings/button_h_on.png"<<":/Settings/button_h_on.png";
    }
    item.AddButton(QRect(621,123-107,71,25), list);
    item.SetSpecifiedID(status);

    m_pVlist->InsertItem(0,item);

    emit SigBTStatusChanged(m_iBTStatus);
}

void SettingsBTUI::StartBT()
{
    this->UpdateBTList();
}

void SettingsBTUI::UpdateBTList()
{
    if(!m_iBTStatus)
    {
        INFO()<<"[SettingsBTUI]BT is OFF, can not UpdateBTList";
        return;
    }
    m_pVlist->RemoveItems(1, m_pVlist->count());

    //paired device list
    for(int i = 0 ; i < SettingsBTData::GetInstance()->GetBTPairedListSize() ;i++)
    {
        const BTDeviceInfo &info = SettingsBTData::GetInstance()->GetBTPairedListInfo(i);
        CListWidgetItem item(QSize(718,57));

        item.AddText(QRect(0,0,800-54-94-150-50,57),info.name,Qt::AlignLeft|Qt::AlignVCenter,24);

        item.SetSpecifiedID(1);
        item.SetSpecifiedIDStatus(info.status);
        switch (info.status) {
        case BTStatus_PAIRED:
            item.AddText(QRect(800-54-94-150,0,150,57),QString("Unconnected"),Qt::AlignRight|Qt::AlignVCenter,20,QColor(255,255,255,204));
            break;
        case BTStatus_CONNECTING:
            item.AddIcon(QRect(800-54-54-(94-54)-35,(57-35)/2,35,35),QPixmap(":/Settings/icon_connect.png"));
            break;
        case BTStatus_CONNECTED:
            item.AddText(QRect(800-54-94-150,0,150,57),QString("Connected"),Qt::AlignRight|Qt::AlignVCenter,20,QColor(255,255,255,204));
            break;
        default:
            INFO()<<"invalid status";
            break;
        }

        item.AddIcon(QRect(800-54-54-(63-54)-22,(57-22)/2,22,22),QPixmap(":/Settings/icon_notice.png"));
        m_pVlist->InsertItem(i,item);
    }

    //other equipment
    CListWidgetItem item (QSize(718,67));
    QStringList list;
    list<<"none"<<"none"<<"none";
    item.SetSpecifiedID(0);
    item.AddText(QRect(0,0,800-54-94-150-50,67),QString(tr("Other equipment")),Qt::AlignLeft|Qt::AlignVCenter,26,QColor(255,255,255,255*0.8));
    item.AddButton(QRect(0,0,718,67),list);
    m_pVlist->InsertItem(m_pVlist->count(),item);

    //other equipment list
    for(int i = 0 ; i < SettingsBTData::GetInstance()->GetBTSearchListSize() ;i++)
    {
        const BTDeviceInfo &info = SettingsBTData::GetInstance()->GetBTSearchListInfo(i);
        CListWidgetItem item(QSize(718,57));
        item.AddText(QRect(0,10,800-54-94-150-50,57),info.name,Qt::AlignLeft|Qt::AlignVCenter,24);
        item.SetSpecifiedID(SettingsBTData::GetInstance()->GetBTPairedListSize()+2);
        item.SetSpecifiedIDStatus(info.status);
        m_pVlist->InsertItem(i,item);
    }
}
