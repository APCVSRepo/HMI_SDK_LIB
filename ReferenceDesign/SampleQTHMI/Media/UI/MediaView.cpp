#include "MediaView.h"
#include "Media/app/Media.h"
#include "HMIFrameWork/log_interface.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HMIFrameWork/AppConfig.h"

MediaView::MediaView(QWidget *parent)
    :QWidget(parent)
    ,CView(Media::eViewId_Main)
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

    connect(Media::Inst(), SIGNAL(SigUpdateAppList()), this, SLOT(OnAppListUpdate()));;

    m_pAppList = new AppListWidget(this);
    m_pAppList->setGeometry(85,43+40,630,307);
    m_pAppList->hide();
    connect(m_pAppList, SIGNAL(appSelected(int)), this, SLOT(OnAppSelected(int)));
}

MediaView::~MediaView()
{

}

void MediaView::viewAction(int state)
{
    INFO("MediaView  viewAction state = %d", state);
    if(eviewStatus_Init == state)
    {

    }
    else if(eViewStatus_Inactive == state)
    {

    }
    else
    {
        INFO("MediaView::viewAction eViewStatus_Active");
        this->OnAppListUpdate();
    }
}

void MediaView::OnConnectBtnClicked()
{
    INFO("OnConnectBtnClicked");
    HMIFrameWork::Inst()->AppShow(HOME_ID, "BTSetting");
}

void MediaView::OnAppListUpdate()
{
    INFO("MediaView::OnAppListUpdate");
    m_pAppList->RemoveAll();

    const std::vector<MediaAppInfo> &applist = Media::Inst()->GetAppList();
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

void MediaView::OnAppSelected(int id)
{
    INFO("MediaView::OnAppSelected: %d", id);
    map<string,string> tempMap;
    tempMap["MediaAppSelected"] = QString::number(id).toStdString();
    HMIFrameWork::Inst()->Notify(SDLAPPS_ID, tempMap);
}

