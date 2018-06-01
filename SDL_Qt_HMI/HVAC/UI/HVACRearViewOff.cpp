#include "HVAC/UI/HVACRearViewOff.h"
#include <QDebug>
#include<unistd.h>
#include <QFont>
#include "AppLayer.h"
#include "HVAC/app/HVAC.h"
#include "HMIFrameWork/HMIFrameWork.h"
HVACRearViewOff::HVACRearViewOff(QWidget *parent)
    :QWidget(parent)
    ,CView(HVAC::eViewId_Rear_Off)
{
    this->setGeometry(QRect(0,0,800,480));
    this->show();
    InitHVACRearViewOff();
    InitConnect();

}

HVACRearViewOff::~HVACRearViewOff()
{

}

void HVACRearViewOff::viewAction(int state)
{
    INFO()<<" HVACRearViewOff  viewAction state = " << state;
    switch (state) {
    case eViewStatus_Active:
        this->show();
        break;
    default:
        break;
    }
}

void HVACRearViewOff::InitHVACRearViewOff()
{
     m_pTitleWhiteLineLabel = new QLabel(this);
     m_pTitleWhiteLineLabel->setGeometry(QRect(0,87,800,3));
     m_pTitleWhiteLineLabel->setStyleSheet("QLabel{border-image:url(:/HVAC/Source/images/top_line.png);backfground:transparent;}");
     m_pTitleWhiteLineLabel->show();

     m_pTitleFrontBtn = new CPushButton(this);
     m_pTitleFrontBtn->setGeometry(QRect(98,40,302,47));
     m_pTitleFrontBtn->setStyleSheet("QPushButton{border:none;background:transparent;color:#FFFFFF;font-size:30px;}");
     m_pTitleFrontBtn->setFocusPolicy(Qt::NoFocus);
     m_pTitleFrontBtn->setText(tr("Front"));
     m_pTitleFrontBtn->show();
     m_pTitleBlueLineLabel = new QLabel(this);
     m_pTitleBlueLineLabel->setGeometry(QRect(515,84,72,3));
     m_pTitleBlueLineLabel->setStyleSheet("QLabel{border-image:url(:/HVAC/Source/images/top_select.png);backfground:transparent;}");
     m_pTitleBlueLineLabel->show();

     m_pTitleReartBtn = new CPushButton(this);
     m_pTitleReartBtn->setGeometry(QRect(400,40,302,47));
     m_pTitleReartBtn->setStyleSheet("QPushButton{border:none;background:transparent;color:#4B9AFF;font-size:30px;}");
     m_pTitleReartBtn->setFocusPolicy(Qt::NoFocus);
     m_pTitleReartBtn->setText(tr("Rear"));
     m_pTitleReartBtn->show();

     m_pOffLabel = new QLabel(this);
     m_pOffLabel->setGeometry(QRect(0,221,800,50));
     m_pOffLabel->setStyleSheet("QLabel{border:none;background:transparent;color:#FFFFFF;font-size:40px;}");
     m_pOffLabel->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
     m_pOffLabel->setText("Rear Climate Off");
     m_pOffLabel->show();


}

void HVACRearViewOff::InitConnect()
{
    connect(m_pTitleFrontBtn,SIGNAL(clicked()),this,SLOT(OnTitleFront()),Qt::UniqueConnection);

}

void HVACRearViewOff::OnTitleFront()
{
    HVAC::Inst()->ViewForwardById(HVAC::eViewId_Front_Off);
}




