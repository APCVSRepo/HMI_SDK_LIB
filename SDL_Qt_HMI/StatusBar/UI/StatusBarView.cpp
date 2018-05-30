#include "StatusBarView.h"
#include "StatusBar/app/StatusBar.h"
#include "HMIFrameWork/log_interface.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HMIFrameWork/AppConfig.h"

#define INVALID_TEMPERATURE 9999

//#define ENABLE_STATUSBARVIEW_TEST
//#define ENABLE_STATUSBARVIEW_TEST_AUTO

StatusBarView::StatusBarView(QWidget *parent)
    :QWidget(parent)
    ,CView(StatusBar::eViewId_Main)
    ,m_pBackgroundLabel(NULL)
    ,m_pHomeBtn(NULL)
    ,m_pVRBtn(NULL)
    ,m_pBTIcon(NULL)
    ,m_pMsgIcon(NULL)
    ,m_pMsgCount(NULL)
    ,m_pWifiIcon(NULL)
    ,m_pUSBIcon(NULL)
    ,m_pStatusLayout(NULL)
    ,m_pStatusWidget(NULL)
    ,m_pSlash1(NULL)
    ,m_pLoadingIcon(NULL)
    ,m_pLoadingWidget(NULL)
    ,m_pSlash2(NULL)
    ,m_pTemperatureIcon(NULL)
    ,m_pSlash3(NULL)
    ,m_pTimeLabel(NULL)
    ,m_pTimer(NULL)
    ,m_iCurrentTemperature(INVALID_TEMPERATURE)
    ,m_bUnitCelsius(true)
    ,m_bIsLoading(false)
{
    this->setGeometry(0,0,800,40);

    m_pBackgroundLabel = new QLabel(this);
    m_pBackgroundLabel->setGeometry(QRect(0,0,800,40));
    m_pBackgroundLabel->setStyleSheet("QLabel{border-image:url(:/StatusBar/Source/images/bg.png);background:transparent;}");
    m_pBackgroundLabel->lower();
    m_pBackgroundLabel->show();

    m_pHomeBtn = new CPushButton(this);
    m_pHomeBtn->setStyleSheet("QPushButton{border-image:url(:/StatusBar/Source/images/home.png);background:transparent;}");
    m_pHomeBtn->setGeometry(QRect(66,4,32,32));
    m_pHomeBtn->setFocusPolicy(Qt::NoFocus);
    m_pHomeBtn->show();

    m_pVRBtn = new CPushButton(this);
    m_pVRBtn->setStyleSheet("QPushButton{border-image:url(:/StatusBar/Source/images/vr.png);background:transparent;}");
    m_pVRBtn->setGeometry(QRect(384,4,32,32));
    m_pVRBtn->setFocusPolicy(Qt::NoFocus);
    m_pVRBtn->show();

    //status icon
    m_pBTIcon = new QLabel(this);
    m_pBTIcon->setPixmap(QPixmap(":/StatusBar/Source/images/bluetooth.png"));
    m_pBTIcon->hide();

    m_pMsgIcon = new QLabel(this);
    m_pMsgIcon->setGeometry(5,5,22,22);
    m_pMsgIcon->setPixmap(QPixmap(":/StatusBar/Source/images/message.png"));
    m_pMsgIcon->hide();
    m_pMsgCount = new QLabel(m_pMsgIcon);
    m_pMsgCount->resize(22,22);
    m_pMsgCount->setAlignment(Qt::AlignCenter);
    m_pMsgCount->setStyleSheet("QLabel{color:#99eeeeee;font-size:12px;background:transparent;}");
    m_pMsgCount->setText("");

    m_pWifiIcon = new QLabel(this);
    m_pWifiIcon->setPixmap(QPixmap(":/StatusBar/Source/images/wifi.png"));
    m_pWifiIcon->hide();
    m_pUSBIcon = new QLabel(this);
    m_pUSBIcon->setPixmap(QPixmap(":/StatusBar/Source/images/lianjie.png"));
    m_pUSBIcon->hide();

    //loading
    m_pLoadingWidget = new QFrame(this);
    m_pLoadingWidget->setGeometry(551,0,608-551,40);
    m_pLoadingWidget->hide();

    m_pSlash1 = new QLabel(m_pLoadingWidget);
    m_pSlash1->setGeometry(QRect(0,4,12,32));
    m_pSlash1->resize(12,32);
    m_pSlash1->setStyleSheet("QLabel{border-image:url(:/StatusBar/Source/images/line.png);background:transparent;}");
    m_pSlash1->show();

    m_pLoadingIcon = new CRotationWidget(m_pLoadingWidget);
    m_pLoadingIcon->setGeometry(QRect(571-551,4,32,32));
    m_pLoadingIcon->resize(32,32);
    m_pLoadingIcon->setPixmap(QString(":/StatusBar/Source/images/loading.png"));
    m_pLoadingIcon->hide();

    //container
    m_pStatusLayout = new QHBoxLayout;
    m_pStatusLayout->setDirection(QBoxLayout::RightToLeft);
    m_pStatusLayout->setAlignment(Qt::AlignHCenter|Qt::AlignRight);
    m_pStatusLayout->setSpacing(1);
    m_pStatusLayout->addWidget(m_pWifiIcon);
    m_pStatusLayout->addWidget(m_pUSBIcon);
    m_pStatusLayout->addWidget(m_pMsgIcon);
    m_pStatusLayout->addWidget(m_pBTIcon);

    m_pStatusWidget = new QWidget(this);
    m_pStatusWidget->setGeometry(418+(608-551),0,551-1-418,40);
    m_pStatusWidget->setLayout(m_pStatusLayout);

    //temperature
    m_pSlash2 = new QLabel(this);
    m_pSlash2->setGeometry(QRect(608,4,12,32));
    m_pSlash2->setStyleSheet("QLabel{border-image:url(:/StatusBar/Source/images/line.png);background:transparent;}");
    m_pSlash2->show();

    m_pTemperatureIcon = new QLabel(this);
    m_pTemperatureIcon->setGeometry(QRect(621,4,32,32));
    m_pTemperatureIcon->setStyleSheet("QLabel{border-image:url(:/StatusBar/Source/images/temperature.png);background:transparent;}");
    m_pTemperatureIcon->show();

    m_pTemperature = new QLabel(this);
    m_pTemperature->setGeometry(QRect(636-25,4,100,32));
    m_pTemperature->setAlignment(Qt::AlignCenter);
    m_pTemperature->setText(QString("--℃"));
    m_pTemperature->setStyleSheet("QLabel{color:#99eeeeee;font-size:18px;border:none;background:transparent;}");
    m_pTemperature->show();

    m_pSlash3 = new QLabel(this);
    m_pSlash3->setGeometry(QRect(689,4,12,32));
    m_pSlash3->setStyleSheet("QLabel{border-image:url(:/StatusBar/Source/images/line.png);background:transparent;}");
    m_pSlash3->show();

    //time
    m_pTimeLabel = new QLabel(this);
    m_pTimeLabel->setGeometry(QRect(800-30-100,0,100,40));
    m_pTimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    m_pTimeLabel->setStyleSheet("QLabel{color:#99eeeeee;font-size:24px;border:none;background:transparent;}");
    m_pTimeLabel->setText(QTime::currentTime().toString("hh:mm"));
    m_pTimeLabel->show();

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(OnTimeUpdate()));
    m_pTimer->start(1000);

    connect(m_pHomeBtn,SIGNAL(clicked()),this,SLOT(OnHomeBtnClicked()));
    connect(m_pVRBtn,SIGNAL(clicked()),this,SLOT(OnVRClicked()));

    //TODO: sync system Celsius/Fahrenheit
    this->UpdateTemperature();
    //TODO: connect signal with loading status change

    //TODO: connect signal with Icon status change
    connect(StatusBar::Inst(),SIGNAL(SigIconStatusChanged(int,bool,int)),this,SLOT(OnIconStatusChanged(int,bool,int)));
}

StatusBarView::~StatusBarView()
{

}

void StatusBarView::SetBTStatus(bool visible)
{
    visible?m_pBTIcon->show():m_pBTIcon->hide();
}

void StatusBarView::SetMessageStatus(bool visible, int count)
{
    if(visible && count > 0)
    {
        m_pMsgCount->setText(QString::number(count));
        m_pMsgIcon->show();
    }
    else
    {
        m_pMsgIcon->hide();
    }
}

void StatusBarView::SetWifiStatus(bool visible)
{
    visible?m_pWifiIcon->show():m_pWifiIcon->hide();
}

void StatusBarView::SetUSBStatus(bool visible)
{
    visible?m_pUSBIcon->show():m_pUSBIcon->hide();
}

void StatusBarView::viewAction(int state)
{
    INFO("StatusBarView  viewAction state = %d", state);
}

void StatusBarView::OnHomeBtnClicked()
{
    HMIFrameWork::Inst()->AppShow(HOME_ID);


#ifdef ENABLE_STATUSBARVIEW_TEST
    //test
    this->OnLoadingStatusChanged(false);
    m_pLoadingIcon->stop();

    SetBTStatus(false);
    SetMessageStatus(false);
    SetWifiStatus(false);
    SetUSBStatus(false);

#endif
}

void StatusBarView::OnVRClicked()
{
    //TODO: show VR view

#ifdef ENABLE_STATUSBARVIEW_TEST
    SetBTStatus(true);
    SetMessageStatus(true,11);
    SetWifiStatus(true);
    SetUSBStatus(true);

    //test
    this->OnLoadingStatusChanged(true);
    m_pLoadingIcon->start();
#endif

}

void StatusBarView::OnTimeUpdate()
{
    m_pTimeLabel->setText(QTime::currentTime().toString("hh:mm"));

#ifdef ENABLE_STATUSBARVIEW_TEST_AUTO

    static int s_temp = -50;
    m_iCurrentTemperature = s_temp;
    s_temp +=9;
    if(s_temp > 100)
    {
        s_temp -= 150;
        m_bUnitCelsius = !m_bUnitCelsius;
    }
    this->UpdateTemperature();

    static int count = 0;
    if(count%15 == 1)
    {
        this->OnLoadingStatusChanged(true);
        m_pLoadingIcon->start();
    }
    else if(count%15 == 7)
    {
        this->OnLoadingStatusChanged(false);
        m_pLoadingIcon->stop();
    }

    if(count%3 == 2)
    {
        SetBTStatus(true);
    }
    if(count%4 == 2)
    {
        SetMessageStatus(true,count);
    }
    if(count%5 == 2)
    {
        SetWifiStatus(true);
    }
    if(count%3 == 0)
    {
        SetUSBStatus(true);
    }

    //hide
    if(count%10 == 2)
    {
        SetBTStatus(false);
    }
    if(count%13 == 2)
    {
        SetMessageStatus(false);
    }
    if(count%17 == 2)
    {
        SetWifiStatus(false);
    }
    if(count%19 == 2)
    {
        SetUSBStatus(false);
    }
    if(++count>100)
    {
        count = 0;
    }
#endif
}

void StatusBarView::OnLoadingStatusChanged(bool status)
{
    m_bIsLoading = status;
    if(m_bIsLoading)
    {
        m_pLoadingWidget->show();
        m_pStatusWidget->move(418,0);
    }
    else
    {
        m_pLoadingWidget->hide();
        m_pStatusWidget->move(418+(608-551),0);
    }
}

void StatusBarView::OnTemperatureChanged(int temperature)
{
    m_iCurrentTemperature = temperature;
    this->UpdateTemperature();
}

void StatusBarView::OnTemperatureUnitChanged(bool isCelsius)
{
    m_bUnitCelsius = isCelsius;
    this->UpdateTemperature();
}

void StatusBarView::OnIconStatusChanged(int type, bool active, int count)
{
    switch (type) {
    case ICON_WIFI:
        SetWifiStatus(active);
        break;
    case ICON_BT:
        SetBTStatus(active);
        break;
    case ICON_USB:
        SetUSBStatus(active);
        break;
    case ICON_MSG:
        SetMessageStatus(active, count);
        break;
    default:
        break;
    }
}

void StatusBarView::UpdateTemperature()
{
    QString unit = m_bUnitCelsius?QString("℃"):QString("℉");
    QString value;
    if(INVALID_TEMPERATURE == m_iCurrentTemperature)
    {
        value = QString("--");
    }
    else
    {
        if(m_bUnitCelsius)
        {
            //Celsius
            value = QString::number(m_iCurrentTemperature);
        }
        else
        {
            //Fahrenheit
            value = QString::number(m_iCurrentTemperature*9/5+32);
        }
    }
    m_pTemperature->setText(value.append(unit));
}

