#include "SettingsWifiUI.h"
#include <QDebug>
#include "Home/data/Settings/SettingsWifiData.h"
#include "Home/app/Home.h"
SettingsWifiUI::SettingsWifiUI(QWidget *parent)
    :QWidget(parent)
    ,CView(Home::eViewId_Settings_Wifi)
    ,m_pBackBtn(NULL)
    ,m_pTitleLabel(NULL)
    ,m_iWifiStatus(0)
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
    m_pTitleLabel->setText(tr("Wi-Fi"));
    m_pTitleLabel->show();

    //list
    m_pVlist = new CVListWidget(this);
    m_pVlist->setGeometry(54,67,718,347);
    m_pVlist->SetLeftMargin(0);
    m_pVlist->SetSplitLine(":/Settings/line.png",":/Settings/line.png");
    m_pVlist->SetScrollBarStyle(4);
    m_pVlist->SetItemBackgroundInfo("",":/Settings/list_push_bg.png","");
    m_pVlist->AutoSetSelected(false);

    this->SetWifiStatus(m_iWifiStatus, true);

//    connect(m_pVlist,SIGNAL(listButtonReleased(int,int)),this,SLOT(OnListButtonReleased(int,int)),static_cast<Qt::ConnectionType>(Qt::QueuedConnection|Qt::UniqueConnection));
    connect(m_pVlist,SIGNAL(listButtonReleased(int,int,int)),this,SLOT(OnListButtonReleased(int,int,int)),static_cast<Qt::ConnectionType>(Qt::QueuedConnection|Qt::UniqueConnection));
    connect(m_pVlist,SIGNAL(listItemReleased(int,int)),this,SLOT(OnListItemClicked(int,int)),static_cast<Qt::ConnectionType>(Qt::QueuedConnection|Qt::UniqueConnection));

    m_pVlist->show();
    connect(m_pBackBtn,SIGNAL(clicked()),this,SLOT(OnBack()),Qt::UniqueConnection);
    connect(this,SIGNAL(SigWifiStatusChanged(int)),this,SLOT(OnWifiStatusChanged(int)));
    connect(SettingsWifiData::GetInstance(),SIGNAL(SigWifiListUpdate()),this,SLOT(OnWifiListUpdate()));
}

SettingsWifiUI::~SettingsWifiUI()
{

}

void SettingsWifiUI::viewAction(int state)
{

}

void SettingsWifiUI::OnBack()
{
   Home::Inst()->ViewBack();
}

void SettingsWifiUI::OnListButtonReleased(int index, int btnIndex)
{
    qDebug()<<"OnListButtonReleased: index: "<<index<<", btnIndex: "<<btnIndex;
}

void SettingsWifiUI::OnListButtonReleased(int index, int btnIndex, int specifiedID)
{
    qDebug()<<"OnListButtonReleased: index: "<<index<<", btnIndex: "<<btnIndex<<", specifiedID: "<<specifiedID;
    if(0 == index)
    {
        if(0 == specifiedID)
        {
            this->SetWifiStatus(1);
        }
        else
        {
            this->SetWifiStatus(0);
        }
    }
}

void SettingsWifiUI::OnListItemClicked(int index, int specifiedID)
{
    qDebug()<<"OnListItemClicked: index: "<<index<<", specifiedID: "<<specifiedID;
    if(0 == index)
    {
        return;
    }

    if((m_pVlist->count()-1) == index)
    {
        qDebug()<<"[SettingsWifiUI]change to [add other hot spots] view";
        //TODO: change to [add other hot spots] view
        Home::Inst()->ViewForwardById(Home::eViewId_Settings_WifiAddHotSpots);
        return;
    }

    const WifiDeviceInfo &info = SettingsWifiData::GetInstance()->GetWifiListInfo(index-1);
    SettingsWifiData::GetInstance()->SetSelectedWifiInfo(info);
    if(SecurityType_NONE == info.securityType)
    {
        qDebug()<<"[SettingsWifiUI]connect to wifi without password";
        //TODO: connect to wifi without password
        SettingsWifiData::GetInstance()->CheckPassword();
    }
    else
    {
        qDebug()<<"[SettingsWifiUI]change to password view";
        //TODO: change to password view
        Home::Inst()->ViewForwardById(Home::eViewId_Settings_WifiPassword);
    }
}

void SettingsWifiUI::OnWifiStatusChanged(int status)
{
    qDebug()<<"OnWifiStatusChanged: "<<status;
    if(1 == status)
    {
        this->StartWifi();
    }
}

void SettingsWifiUI::OnWifiListUpdate()
{
    this->UpdateWifiList();
}

void SettingsWifiUI::SetWifiStatus(int status, bool init)
{
    if(!init)
    {
        if(status == m_iWifiStatus)
        {
            qDebug()<<"[SettingsWifiUI]same wifi status, no need SetWifiStatus";
            return;
        }
    }
    m_iWifiStatus = status;
    m_pVlist->RemoveAllItems();

    CListWidgetItem item(QSize(718,57));
    item.AddText(QRect(0,0,300,57),QString(tr("Wi-Fi services")),Qt::AlignLeft|Qt::AlignVCenter,24);
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

    emit SigWifiStatusChanged(m_iWifiStatus);
}

void SettingsWifiUI::StartWifi()
{
    this->UpdateWifiList();
}

void SettingsWifiUI::UpdateWifiList()
{
    if(!m_iWifiStatus)
    {
        qDebug()<<"[SettingsWifiUI]Wifi is OFF, can not UpdateWifiList";
        return;
    }
    m_pVlist->RemoveItems(1, m_pVlist->count());

    //add wifi list
    for(int i = 0 ; i < SettingsWifiData::GetInstance()->GetWifiListSize() ;i++)
    {
        const WifiDeviceInfo &info = SettingsWifiData::GetInstance()->GetWifiListInfo(i);
        CListWidgetItem item (QSize(718,57));
        QStringList list;
        list<<"none"<<"none"<<"none";
        item.SetSpecifiedID(info.securityType);
        item.AddText(QRect(0,12,600,20),info.name,Qt::AlignLeft|Qt::AlignVCenter,20);

        QString tips;
        switch (info.securityType) {
        case SecurityType_NONE:
            tips.append(QString(tr("Unsecured Network")));
            break;
        case SecurityType_WEP:
            tips.append(QString(tr("WEP Safeguard")));
            break;
        case SecurityType_WPA:
            tips.append(QString(tr("WPA Safeguard")));
            break;
        case SecurityType_WPA2:
            tips.append(QString(tr("WPA2 Safeguard")));
            break;
        case SecurityType_WPA_WPA2:
            tips.append(QString(tr("WPA/WPA2 Safeguard")));
            break;
        default:
            break;
        }
        item.AddText(QRect(0,36,600,14),tips,Qt::AlignLeft|Qt::AlignVCenter,14);

        if(SecurityType_NONE != info.securityType)
        {
            item.AddIcon(QRect(619,11,34,34),QPixmap(":/Settings/icon_suo.png"));
        }
        item.AddIcon(QRect(657,11,34,34),QPixmap(":/Settings/icon_wifi.png"));
        m_pVlist->InsertItem(i,item);

        if(info.connected)
        {
            m_pVlist->SetItemSelected(info.id);
        }
    }

    //add other hot spots
    CListWidgetItem item (QSize(718,81));
    QStringList list;
    list<<"none"<<"none"<<"none";
    item.SetSpecifiedID(-1);
    item.AddText(QRect(49,0,600,81),QString(tr("add other hot spots")),Qt::AlignLeft|Qt::AlignVCenter,24);
    item.AddIcon(QRect(0,22,36,36),QPixmap(":/Settings/button_add.png"));
    m_pVlist->InsertItem(m_pVlist->count(),item);

}


