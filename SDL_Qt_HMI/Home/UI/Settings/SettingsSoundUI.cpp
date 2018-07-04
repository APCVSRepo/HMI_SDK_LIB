#include "SettingsSoundUI.h"
#include "HMIFrameWork/log_interface.h"
#include "Home/app/Home.h"
SettingsSoundUI::SettingsSoundUI(QWidget *parent)
    :QWidget(parent)
    ,CView(Home::eViewId_Settings_Sound)
{
    this->setGeometry(QRect(0,40,800,440));
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
    m_pTitleLabel->setText(tr("Sound effect setting"));
    m_pTitleLabel->show();

    m_pResetBtn = new CPushButton(this);
    m_pResetBtn->setGeometry(QRect(54,83,131,32));
    m_pResetBtn->setStyleSheet("QPushButton{color:rgb(255,255,255);font-size:24px;border-image:url(:/Settings/button_a.png);background:transparent;}");
    m_pResetBtn->setFocusPolicy(Qt::NoFocus);
    m_pResetBtn->setText(tr("Reset all"));
    m_pResetBtn->show();

    m_pTrebleLabel = new QLabel(this);
    m_pTrebleLabel->setGeometry(QRect(54,141,79,28));
    m_pTrebleLabel->setStyleSheet("QLabel{color:rgb(255,255,255);font-size:24px;border:none;background:transparent;}");
    m_pTrebleLabel->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    m_pTrebleLabel->setText(tr("Treble"));
    m_pTrebleLabel->show();

    m_pTrebleDataLabel = new QLabel(this);
    m_pTrebleDataLabel->setGeometry(QRect(340,141,120,28));
    m_pTrebleDataLabel->setStyleSheet("QLabel{color:rgb(255,255,255);font-size:24px;border:none;background:transparent;}");
    m_pTrebleDataLabel->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    m_pTrebleDataLabel->setText(tr("0"));
    m_pTrebleDataLabel->show();

    m_pTrebleLeftBtn = new CPushButton(this);
    m_pTrebleLeftBtn->setGeometry(QRect(133,137,32,32));
    m_pTrebleLeftBtn->setStyleSheet("QPushButton{color:rgb(255,255,255);font-size:24px;border-image:url(:/Settings/arrow_left.png);background:transparent;}");
    m_pTrebleLeftBtn->setFocusPolicy(Qt::NoFocus);
    m_pTrebleLeftBtn->show();

    m_pTrebleRightBtn = new CPushButton(this);
    m_pTrebleRightBtn->setGeometry(QRect(635,137,32,32));
    m_pTrebleRightBtn->setStyleSheet("QPushButton{color:rgb(255,255,255);font-size:24px;border-image:url(:/Settings/arrow_right.png);background:transparent;}");
    m_pTrebleRightBtn->setFocusPolicy(Qt::NoFocus);
    m_pTrebleRightBtn->show();

    m_pAltoLabel = new QLabel(this);
    m_pAltoLabel->setGeometry(QRect(54,203,79,28));
    m_pAltoLabel->setStyleSheet("QLabel{color:rgb(255,255,255);font-size:24px;border:none;background:transparent;}");
    m_pAltoLabel->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    m_pAltoLabel->setText(tr("Alto"));
    m_pAltoLabel->show();

    m_pAltoDataLabel = new QLabel(this);
    m_pAltoDataLabel->setGeometry(QRect(340,203,120,28));
    m_pAltoDataLabel->setStyleSheet("QLabel{color:rgb(255,255,255);font-size:24px;border:none;background:transparent;}");
    m_pAltoDataLabel->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    m_pAltoDataLabel->setText(tr("0"));
    m_pAltoDataLabel->show();

    m_pAltoLeftBtn = new CPushButton(this);
    m_pAltoLeftBtn->setGeometry(QRect(133,199,32,32));
    m_pAltoLeftBtn->setStyleSheet("QPushButton{color:rgb(255,255,255);font-size:24px;border-image:url(:/Settings/arrow_left.png);background:transparent;}");
    m_pAltoLeftBtn->setFocusPolicy(Qt::NoFocus);
    m_pAltoLeftBtn->show();

    m_pAltoRightBtn = new CPushButton(this);
    m_pAltoRightBtn->setGeometry(QRect(635,199,32,32));
    m_pAltoRightBtn->setStyleSheet("QPushButton{color:rgb(255,255,255);font-size:24px;border-image:url(:/Settings/arrow_right.png);background:transparent;}");
    m_pAltoRightBtn->setFocusPolicy(Qt::NoFocus);
    m_pAltoRightBtn->show();

    m_pBassLabel = new QLabel(this);
    m_pBassLabel->setGeometry(QRect(54,265,79,28));
    m_pBassLabel->setStyleSheet("QLabel{color:rgb(255,255,255);font-size:24px;border:none;background:transparent;}");
    m_pBassLabel->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    m_pBassLabel->setText(tr("Bass"));
    m_pBassLabel->show();

    m_pBassDataLabel = new QLabel(this);
    m_pBassDataLabel->setGeometry(QRect(340,265,120,28));
    m_pBassDataLabel->setStyleSheet("QLabel{color:rgb(255,255,255);font-size:24px;border:none;background:transparent;}");
    m_pBassDataLabel->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    m_pBassDataLabel->setText(tr("0"));
    m_pBassDataLabel->show();

    m_pBassLeftBtn = new CPushButton(this);
    m_pBassLeftBtn->setGeometry(QRect(133,261,32,32));
    m_pBassLeftBtn->setStyleSheet("QPushButton{color:rgb(255,255,255);font-size:24px;border-image:url(:/Settings/arrow_left.png);background:transparent;}");
    m_pBassLeftBtn->setFocusPolicy(Qt::NoFocus);
    m_pBassLeftBtn->show();

    m_pBassRightBtn = new CPushButton(this);
    m_pBassRightBtn->setGeometry(QRect(635,261,32,32));
    m_pBassRightBtn->setStyleSheet("QPushButton{color:rgb(255,255,255);font-size:24px;border-image:url(:/Settings/arrow_right.png);background:transparent;}");
    m_pBassRightBtn->setFocusPolicy(Qt::NoFocus);
    m_pBassRightBtn->show();

    InitTrebleVoice();
    InitAltoVoice();
    InitBassVoice();
    InitList();
    InitConnect();

}

SettingsSoundUI::~SettingsSoundUI()
{

}

void SettingsSoundUI::viewAction(int state)
{

}

void SettingsSoundUI::InitTrebleVoice()
{
    int xLeft = 177;
    int y = 140;
    int space = 5;
    for(int i = 0; i< 12 ;++i)//left
    {
       SliderSelect *slider = new SliderSelect(this);
       slider->setIndex(i);
       slider->SetPosionID(0);
       slider->SetNormalStyle(":/Settings/voice_b.png");
       slider->SetSelectStyle(":/Settings/voice_a.png");
       slider->setRect(QRect(xLeft+(9+space)*i,y,9,26));
       m_trebleList.append(slider);
    }

    int xRight =460;
    for(int i = 0; i< 12 ;++i)//left
    {
       SliderSelect *slider = new SliderSelect(this);
       slider->setIndex(i);
       slider->SetPosionID(1);
       slider->SetNormalStyle(":/Settings/voice_b.png");
       slider->SetSelectStyle(":/Settings/voice_a.png");
       slider->setRect(QRect(xRight+(9+space)*i,y,9,26));
       m_trebleList.append(slider);
    }
}

void SettingsSoundUI::InitAltoVoice()
{
    int xLeft = 177;
    int y = 202;
    int space = 5;
    for(int i = 0; i< 12 ;++i)//left
    {
       SliderSelect *slider = new SliderSelect(this);
       slider->setIndex(i);
       slider->SetPosionID(0);
       slider->SetNormalStyle(":/Settings/voice_b.png");
       slider->SetSelectStyle(":/Settings/voice_a.png");
       slider->setRect(QRect(xLeft+(9+space)*i,y,9,26));
       m_altoList.append(slider);
    }

    int xRight =460;
    for(int i = 0; i< 12 ;++i)//left
    {
       SliderSelect *slider = new SliderSelect(this);
       slider->setIndex(i);
       slider->SetPosionID(1);
       slider->SetNormalStyle(":/Settings/voice_b.png");
       slider->SetSelectStyle(":/Settings/voice_a.png");
       slider->setRect(QRect(xRight+(9+space)*i,y,9,26));
       m_altoList.append(slider);
    }
}

void SettingsSoundUI::InitBassVoice()
{
    int xLeft = 177;
    int y = 264;
    int space = 5;
    for(int i = 0; i< 12 ;++i)//left
    {
       SliderSelect *slider = new SliderSelect(this);
       slider->setIndex(i);
       slider->SetPosionID(0);
       slider->SetNormalStyle(":/Settings/voice_b.png");
       slider->SetSelectStyle(":/Settings/voice_a.png");
       slider->setRect(QRect(xLeft+(9+space)*i,y,9,26));
       m_bassList.append(slider);
    }

    int xRight =460;
    for(int i = 0; i< 12 ;++i)//left
    {
       SliderSelect *slider = new SliderSelect(this);
       slider->setIndex(i);
       slider->SetPosionID(1);
       slider->SetNormalStyle(":/Settings/voice_b.png");
       slider->SetSelectStyle(":/Settings/voice_a.png");
       slider->setRect(QRect(xRight+(9+space)*i,y,9,26));
       m_bassList.append(slider);
    }
}

void SettingsSoundUI::InitList()
{
    m_pVlist = new CVListWidget(this);
    m_pVlist->setGeometry(54,311,718,129);
    m_pVlist->SetLeftMargin(0);
    m_pVlist->SetSplitLine(":/Settings/line.png",":/Settings/line.png");
    m_pVlist->SetScrollBarStyle(4);
    m_pVlist->AutoSetSelected(false);
    QStringList titieList;
    titieList <<tr("Balance/attenuation") << tr("Sound field model");
    for(int i = 0 ; i < titieList.size() ;i++)
    {
        CListWidgetItem item (QSize(718,57));
        if(i == 0)
        {
            QStringList list;
            list<<":/Settings/button_h_close.png"<<":/Settings/button_h_close.png"<<":/Settings/button_h_close.png";
            item.SetSpecifiedID(-1);
            item.SetSpecifiedIDStatus(0);
            item.AddText(QRect(0,0,300,57),titieList.at(i),Qt::AlignLeft|Qt::AlignVCenter,24);
            item.AddButton(QRect(647,0,71,57),list);
        }else if(1 == i)
        {
            item.SetSpecifiedID(-1);
            item.AddText(QRect(0,0,300,57),titieList.at(i),Qt::AlignLeft|Qt::AlignVCenter,24);
            QStringList text;
            text<<tr("Routine")<<tr("Centerpoint");
            m_pVlist->AddComboBox(i,":/Settings/select_b.png",text,QRect(418,10,252,37),QSize(718,57),22);
        }
        m_pVlist->InsertItem(i,item);
    }
    m_pVlist->show();
}

void SettingsSoundUI::InitConnect()
{
    connect(m_pBackBtn,SIGNAL(clicked()),this,SLOT(OnBack()),Qt::UniqueConnection);
    connect(m_pResetBtn,SIGNAL(clicked()),this,SLOT(OnReset()),Qt::UniqueConnection);
    connect(m_pTrebleLeftBtn,SIGNAL(clicked()),this,SLOT(OnTerbleLeft()),Qt::UniqueConnection);
    connect(m_pTrebleRightBtn,SIGNAL(clicked()),this,SLOT(OnTerbleRight()),Qt::UniqueConnection);
    connect(m_pAltoLeftBtn,SIGNAL(clicked()),this,SLOT(OnAltoLeft()),Qt::UniqueConnection);
    connect(m_pAltoRightBtn,SIGNAL(clicked()),this,SLOT(OnAltoRight()),Qt::UniqueConnection);
    connect(m_pBassLeftBtn,SIGNAL(clicked()),this,SLOT(OnBassLeft()),Qt::UniqueConnection);
    connect(m_pBassRightBtn,SIGNAL(clicked()),this,SLOT(OnBassRight()),Qt::UniqueConnection);
    connect(m_pVlist,SIGNAL(listButtonReleased(int,int)),this,SLOT(OnListBtnRelease(int,int)),Qt::UniqueConnection);


}

void SettingsSoundUI::OnTerbleLeft()
{
   TrebleHandler(1);
}

void SettingsSoundUI::OnTerbleRight()
{
    TrebleHandler(-1);
}

void SettingsSoundUI::OnAltoLeft()
{
    AltoHandler(1);
}

void SettingsSoundUI::OnAltoRight()
{
    AltoHandler(-1);
}

void SettingsSoundUI::OnBassLeft()
{
    BassHandler(1);
}

void SettingsSoundUI::OnBassRight()
{
    BassHandler(-1);
}

void SettingsSoundUI::OnBack()
{
    Home::Inst()->ViewBack();
}

void SettingsSoundUI::OnReset()
{
    for(int i = 0; i < m_trebleList.size();i++)
    {
        m_trebleList.at(i)->UpdateStatus(SliderSelect::eNormal);
    }
    for(int i = 0; i < m_altoList.size();i++)
    {
        m_altoList.at(i)->UpdateStatus(SliderSelect::eNormal);
    }
    for(int i = 0; i < m_bassList.size();i++)
    {
        m_bassList.at(i)->UpdateStatus(SliderSelect::eNormal);
    }
    m_pTrebleDataLabel->setText("0");
    m_pAltoDataLabel->setText("0");
    m_pBassDataLabel->setText("0");

}

void SettingsSoundUI::OnListBtnRelease(int index, int btnIndex)
{
    switch (index) {
    case 0:
    {
        int idStatus =  m_pVlist->GetSpecifiedIDStatus(index);
        if(0 == idStatus)
        {
            QStringList list;
            list<<":/Settings/button_h_on.png"<<"none"<<"none";
            m_pVlist->SetItemButtonPixmap(index,btnIndex,list);
            m_pVlist->SetSpecifiedIDStatus(index,1);
        }
        else if(1 == idStatus)
        {
            QStringList list;
            list<<":/Settings/button_h_close.png"<<"none"<<"none";
            m_pVlist->SetItemButtonPixmap(index,btnIndex,list);
            m_pVlist->SetSpecifiedIDStatus(index,0);
        }
    }
        break;
    case 1:
    {

    }
        break;
    default:
        break;
    }
}

void SettingsSoundUI::TrebleHandler(int step)
{
    int value =  GetTerbleVoice();
    value += step;

    if(value > 0 && value <= 12)
    {
        for(int i = m_trebleList.size()/2 -1; i >= 0;i--)
        {
            if( 0 == m_trebleList.at(i)->GetPosionID() &&m_trebleList.size()/2 -1- i < value )
            {
                if(m_trebleList.at(i)->getStatus() != SliderSelect::eSelect)
                    m_trebleList.at(i)->UpdateStatus(SliderSelect::eSelect);
            }else
            {
                if(SliderSelect::eSelect == m_trebleList.at(i)->getStatus() )
                    m_trebleList.at(i)->UpdateStatus(SliderSelect::eNormal);
            }
        }
    }else if(value < 0 && value >= -12)
    {
        for(int i = m_trebleList.size()/2; i < m_trebleList.size();i++)
        {
            if(1 == m_trebleList.at(i)->GetPosionID() && i < m_trebleList.size()/2 - value)
            {
                if(SliderSelect::eSelect != m_trebleList.at(i)->getStatus() )
                    m_trebleList.at(i)->UpdateStatus(SliderSelect::eSelect);
            }else
            {
                if(SliderSelect::eSelect == m_trebleList.at(i)->getStatus())
                    m_trebleList.at(i)->UpdateStatus(SliderSelect::eNormal);
            }
        }
    }else if(0 == value)
    {
        for(int i = 0; i < m_trebleList.size();i++)
        {
            m_trebleList.at(i)->UpdateStatus(SliderSelect::eNormal);
        }
    }

    if(value >0 && value <= 12)
    {
        QString _data = "+"+QString::number(value);
        m_pTrebleDataLabel->setText(_data);
    }else if(value >= -12 && value <=0)
    {
        QString _data = QString::number(value);
        m_pTrebleDataLabel->setText(_data);
    }

}

void SettingsSoundUI::AltoHandler(int step)
{
    int value =  GetAltoVoice();
    value += step;

    if(value > 0 && value <= 12)
    {
        for(int i = m_altoList.size()/2 -1; i >= 0;i--)
        {
            if(0 == m_altoList.at(i)->GetPosionID() &&m_altoList.size()/2 -1- i < value )
            {
                if(SliderSelect::eSelect != m_altoList.at(i)->getStatus())
                    m_altoList.at(i)->UpdateStatus(SliderSelect::eSelect);
            }else
            {
                if(SliderSelect::eSelect == m_altoList.at(i)->getStatus())
                    m_altoList.at(i)->UpdateStatus(SliderSelect::eNormal);
            }
        }
    }else if(value < 0 && value >= -12)
    {
        for(int i = m_altoList.size()/2; i < m_altoList.size();i++)
        {
            if(1 == m_altoList.at(i)->GetPosionID() && i < m_altoList.size()/2 - value)
            {
                if(m_altoList.at(i)->getStatus() != SliderSelect::eSelect)
                    m_altoList.at(i)->UpdateStatus(SliderSelect::eSelect);
            }else
            {
                if(SliderSelect::eSelect == m_altoList.at(i)->getStatus())
                    m_altoList.at(i)->UpdateStatus(SliderSelect::eNormal);
            }
        }
    }else if(0 == value)
    {
        for(int i = 0; i < m_altoList.size();i++)
        {
            m_altoList.at(i)->UpdateStatus(SliderSelect::eNormal);
        }
    }

    if(value >0 && value <= 12)
    {
        QString _data = "+"+QString::number(value);
        m_pAltoDataLabel->setText(_data);
    }else if(value >= -12 && value <=0)
    {
        QString _data = QString::number(value);
        m_pAltoDataLabel->setText(_data);
    }
}

void SettingsSoundUI::BassHandler(int step)
{
    int value =  GetBassVoice();
    value += step;

    if(value > 0 && value <= 12)
    {
        for(int i = m_bassList.size()/2 -1; i >= 0;i--)
        {
            if(0 == m_bassList.at(i)->GetPosionID() &&m_bassList.size()/2 -1- i < value )
            {
                if(m_bassList.at(i)->getStatus() != SliderSelect::eSelect)
                    m_bassList.at(i)->UpdateStatus(SliderSelect::eSelect);
            }else
            {
                if(SliderSelect::eSelect == m_bassList.at(i)->getStatus())
                    m_bassList.at(i)->UpdateStatus(SliderSelect::eNormal);
            }
        }
    }else if(value < 0 && value >= -12)
    {
        for(int i = m_bassList.size()/2; i < m_bassList.size();i++)
        {
            if(1 == m_bassList.at(i)->GetPosionID() && i < m_bassList.size()/2 - value)
            {
                if(m_bassList.at(i)->getStatus() != SliderSelect::eSelect)
                    m_bassList.at(i)->UpdateStatus(SliderSelect::eSelect);
            }else
            {
                if(SliderSelect::eSelect == m_bassList.at(i)->getStatus() )
                    m_bassList.at(i)->UpdateStatus(SliderSelect::eNormal);
            }
        }
    }else if(0 == value)
    {
        for(int i = 0; i < m_bassList.size();i++)
        {
            m_bassList.at(i)->UpdateStatus(SliderSelect::eNormal);
        }
    }

    if(value >0 && value <= 12)
    {
        QString _data = "+"+QString::number(value);
        m_pBassDataLabel->setText(_data);
    }else if(value >= -12 && value <=0)
    {
        QString _data = QString::number(value);
        m_pBassDataLabel->setText(_data);
    }
}

int SettingsSoundUI::GetTerbleVoice()
{
    int leftValue = 0;
    int rightValue = 0;
    for(int i = 0; i<m_trebleList.size();i++)
    {
        if(SliderSelect::eSelect == m_trebleList.at(i)->getStatus() )
        {
            if(0 == m_trebleList.at(i)->GetPosionID())
            {
                leftValue ++;
            }else if(1 == m_trebleList.at(i)->GetPosionID())
            {
               rightValue --;
            }
        }
    }

    return leftValue + rightValue;
}

int SettingsSoundUI::GetAltoVoice()
{
    int leftValue = 0;
    int rightValue = 0;
    for(int i = 0; i<m_altoList.size();i++)
    {
        if(SliderSelect::eSelect == m_altoList.at(i)->getStatus())
        {
            if(0 == m_altoList.at(i)->GetPosionID())
            {
                leftValue ++;
            }else if(1 == m_altoList.at(i)->GetPosionID())
            {
               rightValue --;
            }
        }
    }

    return leftValue + rightValue;
}

int SettingsSoundUI::GetBassVoice()
{
    int leftValue = 0;
    int rightValue = 0;
    for(int i = 0; i<m_bassList.size();i++)
    {
        if(SliderSelect::eSelect == m_bassList.at(i)->getStatus())
        {
            if(0 == m_bassList.at(i)->GetPosionID())
            {
                leftValue ++;
            }else if(1 == m_bassList.at(i)->GetPosionID())
            {
               rightValue --;
            }
        }
    }

    return leftValue + rightValue;
}
