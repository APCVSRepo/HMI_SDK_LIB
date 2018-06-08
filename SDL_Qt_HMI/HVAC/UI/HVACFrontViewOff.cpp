#include "HVAC/UI/HVACFrontViewOff.h"
#include "HMIFrameWork/log_interface.h"
#include<unistd.h>
#include <QFont>
#include "AppLayer.h"
#include "HVAC/app/HVAC.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HVAC/data/HVACData.h"
HVACFrontViewOff::HVACFrontViewOff(QWidget *parent)
    :QWidget(parent)
    ,CView(HVAC::eViewId_Front_Off)
    ,m_iHvacZone(HVAC_FRONT_LEFT_RIGHT_ZONE)
{
    this->setGeometry(QRect(0,0,800,480));
    this->show();
    InitHVACFrontViewOff();
    InitConnect();


}

HVACFrontViewOff::~HVACFrontViewOff()
{

}

void HVACFrontViewOff::viewAction(int state)
{
    INFO()<<" HVACFrontViewOff  viewAction state = " << state;
    switch (state) {
    case eviewStatus_Init:
    {
        m_iHvacZone = HVACData::Inst()->GetZone();
        OnZone(m_iHvacZone);
    }
        break;
    case eViewStatus_Active:
        this->show();
        break;
    default:
        break;
    }
}

void HVACFrontViewOff::InitHVACFrontViewOff()
{
     m_pTitleWhiteLineLabel = new QLabel(this);
     m_pTitleWhiteLineLabel->setGeometry(QRect(0,87,800,3));
     m_pTitleWhiteLineLabel->setStyleSheet("QLabel{border-image:url(:/HVAC/Source/images/top_line.png);backfground:transparent;}");
     m_pTitleWhiteLineLabel->show();

     m_pTitleFrontBtn = new CPushButton(this);
     m_pTitleFrontBtn->setGeometry(QRect(98,40,302,47));
     m_pTitleFrontBtn->setStyleSheet("QPushButton{border:none;background:transparent;color:#4B9AFF;font-size:30px;}");
     m_pTitleFrontBtn->setFocusPolicy(Qt::NoFocus);
     m_pTitleFrontBtn->setText(tr("Front"));
     m_pTitleFrontBtn->show();
     m_pTitleBlueLineLabel = new QLabel(this);
     m_pTitleBlueLineLabel->setGeometry(QRect(213,84,72,3));
     m_pTitleBlueLineLabel->setStyleSheet("QLabel{border-image:url(:/HVAC/Source/images/top_select.png);backfground:transparent;}");
     m_pTitleBlueLineLabel->show();

     m_pTitleReartBtn = new CPushButton(this);
     m_pTitleReartBtn->setGeometry(QRect(400,40,302,47));
     m_pTitleReartBtn->setStyleSheet("QPushButton{border:none;background:transparent;color:#FFFFFF;font-size:30px;}");
     m_pTitleReartBtn->setFocusPolicy(Qt::NoFocus);
     m_pTitleReartBtn->setText(tr("Rear"));
     m_pTitleReartBtn->show();


     m_pOffLabel = new QLabel(this);
     m_pOffLabel->setGeometry(QRect(0,221,800,50));
     m_pOffLabel->setStyleSheet("QLabel{border:none;background:transparent;color:#FFFFFF;font-size:40px;}");
     m_pOffLabel->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
     m_pOffLabel->setText("Climate Off");
     m_pOffLabel->show();

     m_pPowerBtn = new CPushButton(this);
     m_pPowerBtn->setGeometry(QRect(120,399,116,32));
     m_pPowerBtn->setStyleSheet("QPushButton{border:none;background:transparent;}");
     m_pPowerBtn->setFocusPolicy(Qt::NoFocus);
     m_pPowerBtn->setIconSize(QSize(30,32));
     m_pPowerBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/swish_off.png")));
     m_pPowerBtn->show();

}


void HVACFrontViewOff::InitConnect()
{

    connect(m_pTitleReartBtn,SIGNAL(clicked()),this,SLOT(OnTitleReart()),Qt::UniqueConnection);

    connect(m_pPowerBtn,SIGNAL(clicked()),this,SLOT(OnPower()),Qt::UniqueConnection);
    connect(HVACData::Inst(),SIGNAL(SigZone(int)),this,SLOT(OnZone(int)),Qt::UniqueConnection);

}


void HVACFrontViewOff::OnTitleReart()
{
    HVAC::Inst()->ViewForwardById(HVAC::eViewId_Rear_Off);
}

void HVACFrontViewOff::OnPower()
{
    HVAC::Inst()->ViewForwardById(HVAC::eViewId_Front_On);
}

void HVACFrontViewOff::OnZone(int zone)
{
    m_iHvacZone = zone;
    switch (m_iHvacZone) {
    case HVAC_FRONT_SIGLE_ZONE:
    {
        m_pTitleBlueLineLabel->hide();
        m_pTitleWhiteLineLabel->hide();
        m_pTitleFrontBtn->hide();
        m_pTitleReartBtn->hide();
        m_pPowerBtn->show();

    }
        break;
    case HVAC_FRONT_LEFT_RIGHT_ZONE:
    {
        m_pTitleBlueLineLabel->hide();
        m_pTitleWhiteLineLabel->hide();
        m_pTitleFrontBtn->hide();
        m_pTitleReartBtn->hide();
        m_pPowerBtn->show();
    }
        break;
    case HVAC_FRONT_REAR_ZONE:
    {

    }
        break;
    case HVAC_FRONT_LEFT_RIGRT_AND_REAR_ZONE:
    {


    }
        break;
    default:
        break;
    }
}






