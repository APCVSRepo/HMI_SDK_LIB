#include "SettingsRoutineSettingUI.h"
#include "HMIFrameWork/log_interface.h"
#include "Home/app/Home.h"
#include "Home/data/Settings/SettingsRoutineSettingData.h"
#include "HMIFrameWork/HMIFrameWork.h"
SettingsRoutineSettingUI::SettingsRoutineSettingUI(QWidget *parent)
    :QWidget(parent)
    ,CView(Home::eViewId_Settings_RoutineSetting)
    ,m_pBackBtn(NULL)
    ,m_pTitleLabel(NULL)
{
    this->setGeometry(QRect(0,40,800,440));
    this->setStyleSheet("QWidget{border:none;background:transparent;}");
    m_pBackgroundLabel = new QLabel(this);
    m_pBackgroundLabel->setGeometry(QRect(0,0,800,440));
    m_pBackgroundLabel->setStyleSheet("QLabel{border-image:url(:/images/bg.png);background:transparent;}");
    m_pBackgroundLabel->lower();
    m_pBackgroundLabel->show();
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
    m_pTitleLabel->setText(tr("Routine setting"));
    m_pTitleLabel->show();

    m_pVList = new CVListWidget(this);
    m_pVList->setGeometry(54,67,718,386);
    m_pVList->SetLeftMargin(0);
    m_pVList->SetSplitLine(":/Settings/line.png",":/Settings/line.png");
    m_pVList->SetScrollBarStyle(4);
    m_pVList->SetItemBackgroundInfo("",":/Settings/list_push_bg.png","");
    QStringList titieList;
    titieList <<tr("Language") << tr("Touch-screen hint") <<  tr("Temperature") << \
                tr("Length unit");
    for(int i = 0 ; i < titieList.size() ;i++)
    {
        CListWidgetItem item (QSize(718,57));

        if(0 == i)
        {
            item.SetSpecifiedID(-1);
            item.AddText(QRect(0,0,300,57),titieList.at(i),Qt::AlignLeft|Qt::AlignVCenter,24);
            QStringList text;
            text<<tr("English")<<tr("Chinese");
            m_pVList->AddComboBox(i,":/Settings/select_b.png",text,QRect(418,10,252,37),QSize(718,57));
        }else if(1 == i)
        {
            QStringList list;
            list<<":/Settings/button_h_close.png"<<""<<"";
            item.SetSpecifiedID(-1);
            item.SetSpecifiedIDStatus(0);
            item.AddText(QRect(0,0,300,57),titieList.at(i),Qt::AlignLeft|Qt::AlignVCenter,24);
            item.AddButton(QRect(647,0,71,57),list);
        }else if(2 == i){
            item.SetSpecifiedID(-1);
            item.AddText(QRect(0,0,300,57),titieList.at(i),Qt::AlignLeft|Qt::AlignVCenter,24);
            QStringList text;
            text<<tr("Centigrade")<<tr("Fahrenheit");
            m_pVList->AddComboBox(i,":/Settings/select_b.png",text,QRect(418,10,252,37),QSize(718,57));
        }
        else if(3 == i)
        {
            item.SetSpecifiedID(-1);
            item.AddText(QRect(0,0,300,57),titieList.at(i),Qt::AlignLeft|Qt::AlignVCenter,24);
            QStringList text;
            text<<"Mile"<<tr("Kilometers");
            m_pVList->AddComboBox(i,":/Settings/select_b.png",text,QRect(418,10,252,37),QSize(718,57));
        }
        m_pVList->InsertItem(i,item);
    }
    m_pVList->show();

    InitConnect();
}

SettingsRoutineSettingUI::~SettingsRoutineSettingUI()
{

}

void SettingsRoutineSettingUI::InitConnect()
{
    connect(m_pBackBtn,SIGNAL(clicked()),this,SLOT(OnBack()),Qt::UniqueConnection);

    connect(m_pVList,SIGNAL(listButtonReleased(int,int)),this,SLOT(OnListBtnClick(int,int)),Qt::UniqueConnection);
    connect(m_pVList,SIGNAL(listItemReleased(int)),this,SLOT(OnListClick(int)),Qt::UniqueConnection);
    connect(m_pVList,SIGNAL(ComboBoxActivated(int,int)),this,SLOT(OnComboBoxActive(int,int)),Qt::UniqueConnection);

}

void SettingsRoutineSettingUI::OnBack()
{
  Home::Inst()->ViewBack();
}

void SettingsRoutineSettingUI::viewAction(int state)
{

}



void SettingsRoutineSettingUI::OnListBtnClick(int index, int btnIndex)
{
    INFO()<<"SettingsRoutineSettingUI index = " << index <<" btnIndex = " <<btnIndex;
    switch (index) {
    case 1:
        if(0 == btnIndex)
        {
            int idStatus =  m_pVList->GetSpecifiedIDStatus(index);
            if(0 == idStatus)
            {
                QStringList list;
                list<<":/Settings/button_h_on.png"<<"none"<<"none";
                m_pVList->SetItemButtonPixmap(index,btnIndex,list);
                m_pVList->SetSpecifiedIDStatus(index,1);
            }
            else if(1 == idStatus)
            {
                QStringList list;
                list<<":/Settings/button_h_close.png"<<"none"<<"none";
                m_pVList->SetItemButtonPixmap(index,btnIndex,list);
                m_pVList->SetSpecifiedIDStatus(index,0);
            }
        }
        break;
    default:
        break;
    }
}

void SettingsRoutineSettingUI::OnListClick(int index)
{

}

void SettingsRoutineSettingUI::OnComboBoxActive(int index, int itemIndex)
{

    switch (index) {
    case 0:
    {
        if(0 == itemIndex)
        {
           SettingsRoutineSettingData::Inst()->SetLanguage("English");
        }else if(1 == itemIndex)
        {
            SettingsRoutineSettingData::Inst()->SetLanguage("Chinese");
        }
    }
        break;
    case 2:
    {
        if(0 == itemIndex)
        {
            map<string,string> p;
            p.insert(make_pair("TemperatureUnit","Centigrade"));
            HMIFrameWork::Inst()->Notify(STATUSBAR_ID,p);
        }else if(1 == itemIndex)
        {
            map<string,string> p;
            p.insert(make_pair("TemperatureUnit","Fahrenheit"));
            HMIFrameWork::Inst()->Notify(STATUSBAR_ID,p);
        }
    }
        break;
    default:
        break;
    }
}

