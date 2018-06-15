#include "HVAC/UI/HVACRearView.h"
#include "HMIFrameWork/log_interface.h"
#include<unistd.h>
#include <QFont>
#include "HVAC/app/HVAC.h"
#include "HMIFrameWork/HMIFrameWork.h"
HVACRearView::HVACRearView(QWidget *parent)
    :QWidget(parent)
    ,CView(HVAC::eViewId_Rear_On)
    ,m_iLeftTemperature(23)
    ,m_iTemperatureMin(16)
    ,m_iTemperatureMax(32)
    ,m_iAirVolume(3)
{
    this->setGeometry(QRect(0,0,800,480));
    this->show();
    InitHVACRearView();
    InitConnect();
}

HVACRearView::~HVACRearView()
{

}

void HVACRearView::viewAction(int state)
{
    INFO()<<" HVACRearView  viewAction state = " << state;
    switch (state) {
    case eViewStatus_Active:
        this->show();
        break;
    default:
        break;
    }
}

void HVACRearView::InitHVACRearView()
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

     m_pLeftAddTemperatureBtn = new CPushButton(this);
     m_pLeftAddTemperatureBtn->setGeometry(QRect(64,105,50,50));
     m_pLeftAddTemperatureBtn->setStyleSheet("QPushButton{border:none;background:transparent;}");
     m_pLeftAddTemperatureBtn->setFocusPolicy(Qt::NoFocus);
     m_pLeftAddTemperatureBtn->setIconSize(QSize(40,22));
     m_pLeftAddTemperatureBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/up.png")));
     m_pLeftAddTemperatureBtn->show();
     m_pLeftSubTemperatureBtn = new CPushButton(this);
     m_pLeftSubTemperatureBtn->setGeometry(QRect(64,273,50,50));
     m_pLeftSubTemperatureBtn->setStyleSheet("QPushButton{border:none;background:transparent;}");
     m_pLeftSubTemperatureBtn->setFocusPolicy(Qt::NoFocus);
     m_pLeftSubTemperatureBtn->setIconSize(QSize(40,22));
     m_pLeftSubTemperatureBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/down.png")));
     m_pLeftSubTemperatureBtn->show();
     m_LeftTemperatureDataLabel = new QLabel(this);
     m_LeftTemperatureDataLabel->setGeometry(QRect(49,155,80,118));
     m_LeftTemperatureDataLabel->setStyleSheet("QLabel{border:none;background:transparent;color:#4BA9FF;font-size:38px;}");
     m_LeftTemperatureDataLabel->setAlignment(Qt::AlignCenter);
     m_LeftTemperatureDataLabel->setText("23℃");
     m_LeftTemperatureDataLabel->show();



     m_pFrontHairModeBtn = new CPushButton(this);
     m_pFrontHairModeBtn->setGeometry(QRect(161,149,120,120));
     m_pFrontHairModeBtn->setStyleSheet("QPushButton{border:none;background:transparent;}");
     m_pFrontHairModeBtn->setFocusPolicy(Qt::NoFocus);
     m_pFrontHairModeBtn->setIconSize(QSize(120,120));
     m_pFrontHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_up_normal.png")));
     m_pFrontHairModeBtn->show();

     m_pFrontBelowHairModeBtn = new CPushButton(this);
     m_pFrontBelowHairModeBtn->setGeometry(QRect(281,149,120,120));
     m_pFrontBelowHairModeBtn->setStyleSheet("QPushButton{border:none;background:transparent;}");
     m_pFrontBelowHairModeBtn->setFocusPolicy(Qt::NoFocus);
     m_pFrontBelowHairModeBtn->setIconSize(QSize(120,120));
     m_pFrontBelowHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_upanddown_select.png")));
     m_pFrontBelowHairModeBtn->show();

     m_pBelowHairModeBtn = new CPushButton(this);
     m_pBelowHairModeBtn->setGeometry(QRect(400,149,120,120));
     m_pBelowHairModeBtn->setStyleSheet("QPushButton{border:none;background:transparent;}");
     m_pBelowHairModeBtn->setFocusPolicy(Qt::NoFocus);
     m_pBelowHairModeBtn->setIconSize(QSize(120,120));
     m_pBelowHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_down_normal.png")));
     m_pBelowHairModeBtn->show();

     m_pFrontHairModeBtn->SetStatus(CPushButton::eStatus_Normal);
     m_pFrontBelowHairModeBtn->SetStatus(CPushButton::eStatus_Select);
     m_pBelowHairModeBtn->SetStatus(CPushButton::eStatus_Normal);
     m_pFrontHairModeBtn->SetId(eFrontHairMode);
     m_pFrontBelowHairModeBtn->SetId(eFrontBelowHairMode);
     m_pBelowHairModeBtn->SetId(eBelowHairMode);
     m_pHairModeGroup  = new QButtonGroup;
     m_pHairModeGroup->addButton(m_pFrontHairModeBtn,eFrontHairMode);
     m_pHairModeGroup->addButton(m_pFrontBelowHairModeBtn,eFrontBelowHairMode);
     m_pHairModeGroup->addButton(m_pBelowHairModeBtn,eBelowHairMode);

     m_pSubAirVolumeBtn = new CPushButton(this);
     m_pSubAirVolumeBtn->setGeometry(QRect(200,325,40,40));
     m_pSubAirVolumeBtn->setStyleSheet("QPushButton{border:none;background:transparent;}");
     m_pSubAirVolumeBtn->setFocusPolicy(Qt::NoFocus);
     m_pSubAirVolumeBtn->setIconSize(QSize(30,30));
     m_pSubAirVolumeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_left.png")));
     m_pSubAirVolumeBtn->show();

     m_pAddAirVolumeBtn = new CPushButton(this);
     m_pAddAirVolumeBtn->setGeometry(QRect(560,325,40,40));
     m_pAddAirVolumeBtn->setStyleSheet("QPushButton{border:none;background:transparent;}");
     m_pAddAirVolumeBtn->setFocusPolicy(Qt::NoFocus);
     m_pAddAirVolumeBtn->setIconSize(QSize(40,40));
     m_pAddAirVolumeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_right.png")));
     m_pAddAirVolumeBtn->show();




     m_pAirVolumeDataSlider = new CSlider(Qt::Horizontal,this);
     m_pAirVolumeDataSlider->setStyleSheet("QSlider{border:none;background:transparent;}" \
                                             "QSlider::groove:horizontal {" \
                                              "border-image:url(:/HVAC/Source/images/tiao_bg.png);"
                                              "height: 12px;"
                                              "margin:  -2px 0;"
                                             "}"
                                             "QSlider::handle:horizontal"
                                             "{"
                                                 "border:none;"
                                                  "margin: -11px -11px -11px -11px;"
                                                  "width: 22px;"
                                             "}"
                                            "QSlider::add-page:horizontal{"
                                            "border-radius: 4px;"
                                            "height: 8px;"
                                            "}"
                                             "QSlider::sub-page:horizontal {  "
                                                   "background: qlineargradient("
                                                   "spread:pad,"
                                                   "x1:0, y1:1, x2:0, y2:0,"
                                                   "stop:0 #008AFF, stop:1 #1D94FF);"
                                                   "border-radius:4;"
                                                   "margin-left:0px;"
                                                   "margin-right:3px;"
                                                   "height:8px;"
                                            "}"
                                             );

    m_pAirVolumeDataSlider->setGeometry(QRect(268,339,262,12));
    m_pAirVolumeDataSlider->setMinimum(0);
    m_pAirVolumeDataSlider->setMaximum(6);
    m_pAirVolumeDataSlider->setValue(3);

    m_pAirVolumeDataSlider->show();



    m_pAutoBtn = new CPushButton(this);
    m_pAutoBtn->setGeometry(QRect(342,399,116,32));
    m_pAutoBtn->setStyleSheet("QPushButton{border-image:url(:/HVAC/Source/images/button_off.png);background:transparent;color:#FFFFFF;font-size:19px;}");
    m_pAutoBtn->setFocusPolicy(Qt::NoFocus);
    m_pAutoBtn->setText(tr("Auto"));
    m_pAutoBtn->show();


}

void HVACRearView::InitConnect()
{
    connect(m_pLeftAddTemperatureBtn,SIGNAL(clicked()),this,SLOT(OnLeftAddTemperature()),Qt::UniqueConnection);
    connect(m_pLeftSubTemperatureBtn,SIGNAL(clicked()),this,SLOT(OnLeftSubTemperature()),Qt::UniqueConnection);
    connect(m_pTitleFrontBtn,SIGNAL(clicked()),this,SLOT(OnTitleFront()),Qt::UniqueConnection);

    connect(m_pSubAirVolumeBtn,SIGNAL(clicked()),this,SLOT(OnSubAirVolume()),Qt::UniqueConnection);
    connect(m_pAddAirVolumeBtn,SIGNAL(clicked()),this,SLOT(OnAddAirVolume()),Qt::UniqueConnection);
    connect(m_pAirVolumeDataSlider, SIGNAL(valueChanged(int)), this, SLOT(OnAirVolumeDataSlider(int)),Qt::UniqueConnection);
    connect(m_pHairModeGroup,SIGNAL(buttonClicked(int)),this,SLOT(OnHairModeSelect(int)),Qt::UniqueConnection);
    connect(m_pAutoBtn,SIGNAL(clicked()),this,SLOT(OnAuto()),Qt::UniqueConnection);

}

void HVACRearView::FrontHairModeSelect(bool isSelect)
{
    if(isSelect)
    {
        m_pFrontHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_up_select.png")));
        m_pFrontHairModeBtn->SetStatus(CPushButton::eStatus_Select);
        m_pFrontBelowHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_upanddown_normal.png")));
        m_pFrontBelowHairModeBtn->SetStatus(CPushButton::eStatus_Normal);
        m_pBelowHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_down_normal.png")));
        m_pBelowHairModeBtn->SetStatus(CPushButton::eStatus_Normal);
    }else
    {
        m_pFrontHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_up_normal.png")));
        m_pFrontHairModeBtn->SetStatus(CPushButton::eStatus_Normal);
    }
}

void HVACRearView::FrontBelowHairModeSelect(bool isSelect)
{
    if(isSelect)
    {
        m_pFrontHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_up_normal.png")));
        m_pFrontHairModeBtn->SetStatus(CPushButton::eStatus_Normal);
        m_pFrontBelowHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_upanddown_select.png")));
        m_pFrontBelowHairModeBtn->SetStatus(CPushButton::eStatus_Select);
        m_pBelowHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_down_normal.png")));
        m_pBelowHairModeBtn->SetStatus(CPushButton::eStatus_Normal);
    }else
    {
        m_pFrontBelowHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_upanddown_normal.png")));
        m_pFrontBelowHairModeBtn->SetStatus(CPushButton::eStatus_Normal);

    }
}

void HVACRearView::BelowHairModeSelect(bool isSelect)
{
    if(isSelect)
    {
        m_pFrontHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_up_normal.png")));
        m_pFrontHairModeBtn->SetStatus(CPushButton::eStatus_Normal);
        m_pFrontBelowHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_upanddown_normal.png")));
        m_pFrontBelowHairModeBtn->SetStatus(CPushButton::eStatus_Normal);
        m_pBelowHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_down_select.png")));
        m_pBelowHairModeBtn->SetStatus(CPushButton::eStatus_Select);
    }else
    {
        m_pBelowHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_down_normal.png")));
        m_pBelowHairModeBtn->SetStatus(CPushButton::eStatus_Normal);
    }
}

void HVACRearView::OnLeftAddTemperature()
{
    if(m_iLeftTemperature < m_iTemperatureMax)
    {
        m_iLeftTemperature++;
    }
    QString value;
    if(m_iLeftTemperature == m_iTemperatureMax)
    {
        value = "HI";
    }
    else
    {
        value = QString::number(m_iLeftTemperature)+"℃";
    }
    m_LeftTemperatureDataLabel->setText(value);
}

void HVACRearView::OnLeftSubTemperature()
{
    if(m_iLeftTemperature > m_iTemperatureMin)
    {
        m_iLeftTemperature--;
    }

    QString value;
    if(m_iLeftTemperature == m_iTemperatureMin)
    {
        value = "LO";
    }
    else
    {
        value = QString::number(m_iLeftTemperature)+"℃";
    }
    m_LeftTemperatureDataLabel->setText(value);
}

void HVACRearView::OnTitleFront()
{
    HVAC::Inst()->ViewForwardById(HVAC::eViewId_Front_On);
}

void HVACRearView::OnTitleReart()
{

}

void HVACRearView::OnHairModeSelect(int  Id)
{
    switch (Id) {
    case eFrontHairMode:
    {
        if(CPushButton::eStatus_Normal == m_pFrontHairModeBtn->GetStatus())
        {
            FrontHairModeSelect(true);
            if(m_pAutoBtn->GetStatus() == CPushButton::eStatus_Select)
            {
                m_pAutoBtn->setStyleSheet("QPushButton{border-image:url(:/HVAC/Source/images/button_off.png);background:transparent;color:#FFFFFF;font-size:19px;}");
                m_pAutoBtn->SetStatus(CPushButton::eStatus_Normal);
            }
        }else if(CPushButton::eStatus_Select == m_pFrontHairModeBtn->GetStatus())
        {
            FrontHairModeSelect(false);
        }

    }
        break;
    case eFrontBelowHairMode:
    {
        if(CPushButton::eStatus_Normal == m_pFrontBelowHairModeBtn->GetStatus())
        {
            FrontBelowHairModeSelect(true);
            if(m_pAutoBtn->GetStatus() == CPushButton::eStatus_Select)
            {
                m_pAutoBtn->setStyleSheet("QPushButton{border-image:url(:/HVAC/Source/images/button_off.png);background:transparent;color:#FFFFFF;font-size:19px;}");
                m_pAutoBtn->SetStatus(CPushButton::eStatus_Normal);
            }
        }else if(CPushButton::eStatus_Select == m_pFrontBelowHairModeBtn->GetStatus())
        {
            FrontBelowHairModeSelect(false);
        }
    }
        break;
    case eBelowHairMode:
    {
        if(CPushButton::eStatus_Normal == m_pBelowHairModeBtn->GetStatus())
        {
            BelowHairModeSelect(true);
            if(m_pAutoBtn->GetStatus() == CPushButton::eStatus_Select)
            {
                m_pAutoBtn->setStyleSheet("QPushButton{border-image:url(:/HVAC/Source/images/button_off.png);background:transparent;color:#FFFFFF;font-size:19px;}");
                m_pAutoBtn->SetStatus(CPushButton::eStatus_Normal);
            }
        }else if(CPushButton::eStatus_Select == m_pBelowHairModeBtn->GetStatus())
        {
            BelowHairModeSelect(false);
        }
    }
        break;
    default:
        break;
    }
}

void HVACRearView::OnSubAirVolume()
{
    if(m_iAirVolume > m_pAirVolumeDataSlider->minimum())
    {
        m_iAirVolume --;
        m_pAirVolumeDataSlider->setValue(m_iAirVolume);

    }
}

void HVACRearView::OnAddAirVolume()
{
    if(m_iAirVolume < m_pAirVolumeDataSlider->maximum())
    {
        m_iAirVolume ++;
        m_pAirVolumeDataSlider->setValue(m_iAirVolume);

    }
}

void HVACRearView::OnAirVolumeDataSlider(int)
{

}

void HVACRearView::OnAuto()
{
    if(m_pAutoBtn->GetStatus() == CPushButton::eStatus_Select)
    {
        m_pAutoBtn->setStyleSheet("QPushButton{border-image:url(:/HVAC/Source/images/button_off.png);background:transparent;color:#FFFFFF;font-size:19px;}");
        m_pAutoBtn->SetStatus(CPushButton::eStatus_Normal);
    }else if(m_pAutoBtn->GetStatus() == CPushButton::eStatus_Normal)
    {
        m_pAutoBtn->setStyleSheet("QPushButton{border-image:url(:/HVAC/Source/images/button_on.png);background:transparent;color:#FFFFFF;font-size:19px;}");
        m_pAutoBtn->SetStatus(CPushButton::eStatus_Select);
        m_pFrontHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_up_normal.png")));
        m_pFrontHairModeBtn->SetStatus(CPushButton::eStatus_Normal);
        m_pFrontBelowHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_upanddown_normal.png")));
        m_pFrontBelowHairModeBtn->SetStatus(CPushButton::eStatus_Normal);
        m_pBelowHairModeBtn->setIcon(QIcon(QPixmap(":/HVAC/Source/images/wind_down_normal.png")));
        m_pBelowHairModeBtn->SetStatus(CPushButton::eStatus_Normal);
    }
}






