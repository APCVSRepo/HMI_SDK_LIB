#include "SettingsDisplayUI.h"
#include "HMIFrameWork/log_interface.h"
#include "Home/app/Home.h"
#include "Home/data/Settings/SettingsDisplayData.h"
SettingsDisplayUI::SettingsDisplayUI(QWidget *parent)
    :QWidget(parent)
    ,CView(Home::eViewId_Settings_Display)
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
    m_pTitleLabel->setText(tr("Display settings"));
    m_pTitleLabel->show();

    m_pLuminanceRegulationLabel = new QLabel(this);
    m_pLuminanceRegulationLabel->setGeometry(QRect(54,70,300,40));
    m_pLuminanceRegulationLabel->setStyleSheet("QLabel{color:#FFFFFF;font-size:24px;border:none;background:transparent;}");
    m_pLuminanceRegulationLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_pLuminanceRegulationLabel->setText(tr("Luminance regulation"));
    m_pLuminanceRegulationLabel->show();


    m_pLeftBtn = new CPushButton(this);
    m_pLeftBtn->setStyleSheet("QPushButton{border-image:url(:/Settings/arrow_left.png);background:transparent;}");
    m_pLeftBtn->setGeometry(QRect(134,165,32,32));
    m_pLeftBtn->setFocusPolicy(Qt::NoFocus);
    m_pLeftBtn->show();

    m_pRightBtn = new CPushButton(this);
    m_pRightBtn->setStyleSheet("QPushButton{border-image:url(:/Settings/arrow_right.png);background:transparent;}");
    m_pRightBtn->setGeometry(QRect(642,165,32,32));
    m_pRightBtn->setFocusPolicy(Qt::NoFocus);
    m_pRightBtn->show();


    m_pLuminanceRegulationSlider = new QSlider(Qt::Horizontal,this);

    m_pLuminanceRegulationSlider->setStyleSheet("QSlider{border-color: #B0B0B0;}" \
                                            "QSlider::groove:horizontal {" \
                                             "border: 0px 0;"
                                             "height: 22px;"
                                             "margin: 0px 0;"
                                             "left: 0px; right: 0px;"
                                           " } "
                                            "QSlider::handle:horizontal"
                                            "{"
                                                "border:none;"
                                                 "margin: -11px -11px -11px -11px;"
                                                 "width: 22px;"
                                            "}"
                                            "QSlider::add-page:Horizontal {"
                                            "background: qlineargradient(x1:0, y1:1, x2:0, y2:0,"
                                                "stop:0 #B0B0B0, stop:1 #B0B0B0);"
                                            "}"
                                           " QSlider::sub-page:horizontal {  "
                                                    "background: qlineargradient("
                                                    "spread:pad,"
                                                    "x1:0, y1:1, x2:0, y2:0,"
                                                    "stop:0 #FFFFFF, stop:0.25 #FFFFFF,"
                                                    "stop:0.5 #FFFFFF, stop:1 #FFFFFF);"
                                                    "margin-left:2px;"
                                                    "margin-right:0px;"
                                            "}"

                                            );

    m_pLuminanceRegulationSlider->setGeometry(QRect(194,170,420,22));
    m_pLuminanceRegulationSlider->setMinimum(0);
    m_pLuminanceRegulationSlider->setMaximum(100);
    m_pLuminanceRegulationSlider->setValue(50);


    m_pLuminanceRegulationSlider->show();


    m_pVlist = new CVListWidget(this);
    m_pVlist->setGeometry(54,222,718,386);
    m_pVlist->SetLeftMargin(0);
    m_pVlist->SetSplitLine(":/Settings/line.png",":/Settings/line.png");
    m_pVlist->SetScrollBarStyle(4);
    m_pVlist->SetItemBackgroundInfo("",":/Settings/list_push_bg.png","");
    QStringList titieList;
    titieList <<tr("Automatic luminance regulation") << tr("Pattern") ;
    for(int i = 0 ; i < titieList.size() ;i++)
    {
        CListWidgetItem item (QSize(718,57));
        if(0 == i)
        {
            QStringList list;
            list<<":/Settings/button_h_on.png"<<":/Settings/button_h_close.png"<<":/Settings/button_h_close.png";
            item.SetSpecifiedID(-1);
            item.SetSpecifiedIDStatus(1);
            item.AddText(QRect(0,0,500,57),titieList.at(i),Qt::AlignLeft|Qt::AlignVCenter,24);
            item.AddButton(QRect(647,0,71,57),list);
        }
        else if(1 == i)
        {
            item.SetSpecifiedID(-1);
            item.AddText(QRect(0,0,300,57),titieList.at(i),Qt::AlignLeft|Qt::AlignVCenter,24);
            QStringList text;
            text<<tr("Auto")<<tr("Day mode")<<tr("Night mode");
            m_pVlist->AddComboBox(i,":/Settings/select_b.png",text,QRect(418,10,252,37),QSize(718,57));
        }
        m_pVlist->InsertItem(i,item);
    }
    m_pVlist->show();

    InitConnect();
}

SettingsDisplayUI::~SettingsDisplayUI()
{

}

void SettingsDisplayUI::InitConnect()
{
    connect(m_pBackBtn,SIGNAL(clicked()),this,SLOT(OnBack()),Qt::UniqueConnection);

    connect(m_pVlist,SIGNAL(listButtonReleased(int,int)),this,SLOT(OnListBtnClick(int,int)),Qt::UniqueConnection);
    connect(m_pVlist,SIGNAL(listItemReleased(int)),this,SLOT(OnListClick(int)),Qt::UniqueConnection);

    connect(m_pLuminanceRegulationSlider, SIGNAL(valueChanged(int)), this, SLOT(OnLuminanceRegulationValue(int)),Qt::UniqueConnection);
    connect(m_pLeftBtn, SIGNAL(clicked()), this, SLOT(OnSubLuminanceRegulationValue()),Qt::UniqueConnection);
    connect(m_pRightBtn, SIGNAL(clicked()), this, SLOT(OnAddLuminanceRegulationValue()),Qt::UniqueConnection);
    connect(m_pVlist,SIGNAL(ComboBoxActivated(int,QString)),this,SLOT(OnComboBoxActive(int,QString)),Qt::UniqueConnection);

}

void SettingsDisplayUI::OnBack()
{
    Home::Inst()->ViewBack();
}

void SettingsDisplayUI::viewAction(int state)
{

}



void SettingsDisplayUI::OnListBtnClick(int index, int btnIndex)
{
    INFO()<<"SettingsDisplayUI index = " << index <<" btnIndex = " <<btnIndex;
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
    default:
        break;
    }
}

void SettingsDisplayUI::OnListClick(int index)
{

}

void SettingsDisplayUI::OnLuminanceRegulationValue(int value)
{
    INFO() << "OnLuminanceRegulationValue = " << value;
}

void SettingsDisplayUI::OnAddLuminanceRegulationValue()
{
    INFO() <<"OnAddLuminanceRegulationValue = " << m_pLuminanceRegulationSlider->value() <<" "<<m_pLuminanceRegulationSlider->maximum();

    if(m_pLuminanceRegulationSlider->value() < m_pLuminanceRegulationSlider->maximum())
    {
        m_pLuminanceRegulationSlider->setValue(m_pLuminanceRegulationSlider->value()+1);
    }
}

void SettingsDisplayUI::OnSubLuminanceRegulationValue()
{
    INFO() <<"OnSubLuminanceRegulationValue = " << m_pLuminanceRegulationSlider->value() <<" "<<m_pLuminanceRegulationSlider->minimum();
    if(m_pLuminanceRegulationSlider->value() > m_pLuminanceRegulationSlider->minimum())
    {
        m_pLuminanceRegulationSlider->setValue(m_pLuminanceRegulationSlider->value()-1);
    }
}

void SettingsDisplayUI::OnComboBoxActive(int index, const QString &data)
{
    if( 1 == index)
    {
        SettingsDisplayData::Inst()->SetPattern(data);
    }
}
