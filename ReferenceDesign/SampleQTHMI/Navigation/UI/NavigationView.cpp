#include "NavigationView.h"
#include "Navigation/app/Navigation.h"
#include "HMIFrameWork/log_interface.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HMIFrameWork/AppConfig.h"

NavigationView::NavigationView(QWidget *parent)
    :QWidget(parent)
    ,CView(Navigation::eViewId_Main)
    ,m_pNoDeviceMsg(NULL)
    ,m_pConnectDevice(NULL)
    ,m_pAppList(NULL)
{
    this->setGeometry(0,0,800,480);

    m_pNoDeviceMsg = new QLabel(this);
    m_pNoDeviceMsg->setGeometry(QRect(115,171,800-230,28));
    m_pNoDeviceMsg->setStyleSheet("QLabel{font-size:24px; color:#ffffff; background:transparent;}");
    m_pNoDeviceMsg->setText(QString(tr("Unconnected phone, please connect the phone first")));
    m_pNoDeviceMsg->setAlignment((Qt::AlignCenter));
    m_pNoDeviceMsg->hide();

    m_pConnectDevice = new CPushButton(this);
    m_pConnectDevice->setStyleSheet("QPushButton{font-size:20px; color:#ffffff; border-image:url(:/Navigation/Source/images/button.png);background:transparent;}");
    m_pConnectDevice->setGeometry(QRect(283,255,245,32));
    m_pConnectDevice->setText(QString(tr("Connection equipment")));
    m_pConnectDevice->setFocusPolicy(Qt::NoFocus);
    m_pConnectDevice->hide();

    connect(m_pConnectDevice, SIGNAL(clicked()), this, SLOT(OnConnectBtnClicked()));

    connect(Navigation::Inst(), SIGNAL(SigUpdateAppList()), this, SLOT(OnAppListUpdate()));;

    m_pAppList = new AppListWidget(this);
    m_pAppList->setGeometry(85,43+40,630,307);
    m_pAppList->hide();
    connect(m_pAppList, SIGNAL(appSelected(int)), this, SLOT(OnAppSelected(int)));
}

NavigationView::~NavigationView()
{

}

void NavigationView::viewAction(int state)
{
    INFO("NavigationView  viewAction state = %d", state);
    if(eviewStatus_Init == state)
    {

    }
    else if(eViewStatus_Inactive == state)
    {

    }
    else
    {
        INFO("NavigationView::viewAction eViewStatus_Active");
        this->OnAppListUpdate();
    }
}

void NavigationView::OnConnectBtnClicked()
{
    INFO("OnConnectBtnClicked");
    HMIFrameWork::Inst()->AppShow(HOME_ID, "BTSetting");
}

void NavigationView::OnAppListUpdate()
{
    INFO("NavigationView::OnAppListUpdate");
    m_pAppList->RemoveAll();

    const std::vector<NaviAppInfo> &applist = Navigation::Inst()->GetAppList();
    if(applist.size() > 0)
    {
        for(int i = 0; i < applist.size(); ++i)
        {
            m_pAppList->InsertChildApp(i, applist[i].appId,
                                       applist[i].appName.c_str(),
                                       applist[i].appIcon.c_str(),
                                       applist[i].appIcon.c_str(),
                                       true);
        }

        m_pNoDeviceMsg->hide();
        m_pConnectDevice->hide();
        m_pAppList->show();
    }
    else
    {
        m_pNoDeviceMsg->show();
        m_pConnectDevice->show();
        m_pAppList->hide();
    }

    this->update();
}

void NavigationView::OnAppSelected(int id)
{
    INFO("NavigationView::OnAppSelected: %d", id);
    map<string,string> tempMap;
    tempMap["NaviAppSelected"] = QString::number(id).toStdString();
    HMIFrameWork::Inst()->Notify(SDLAPPS_ID, tempMap);
}

