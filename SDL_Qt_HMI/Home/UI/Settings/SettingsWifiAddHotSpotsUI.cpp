#include "SettingsWifiAddHotSpotsUI.h"
#include "Home/data/Settings/SettingsWifiData.h"
#include "HMIWidgets/CComboBoxDelegate.h"
#include "Home/app/Home.h"
#include <QDebug>

SettingsWifiAddHotSpotsUI::SettingsWifiAddHotSpotsUI(QWidget *parent)
    :QWidget(parent)
    ,CView(Home::eViewId_Settings_WifiAddHotSpots)
    ,m_pBackBtn(NULL)
    ,m_pTitleLabel(NULL)
    ,m_pNetNameLabel(NULL)
    ,m_pNetNameEdit(NULL)
    ,m_pNetNameEditLine(NULL)
    ,m_pSecurityTypeLabel(NULL)
    ,m_pSecurityTypeEditLine(NULL)
    ,m_pSecurityTypeComboBox(NULL)
    ,m_pPasswordLabel(NULL)
    ,m_pPasswordEdit(NULL)
    ,m_pPasswordEditLine(NULL)
    ,m_pPasswordError(NULL)
    ,m_pAddBtn(NULL)
    ,m_pCancelBtn(NULL)
{
    this->setGeometry(QRect(0,40,800,440));
    this->setStyleSheet("QWidget{border:none;background:transparent;}");

    m_pBackBtn = new CPushButton(this);
    m_pBackBtn->setStyleSheet("QPushButton{border-image:url(:/Settings/button_back.png);background:transparent;}");
    m_pBackBtn->setGeometry(QRect(16,21,29,29));
    m_pBackBtn->setFocusPolicy(Qt::NoFocus);
    m_pBackBtn->show();

    m_pTitleLabel = new QLabel(this);
    m_pTitleLabel->setGeometry(QRect(54,21,300,29));
    m_pTitleLabel->setStyleSheet("QLabel{color:#4BA9FF;font-size:24px;border:none;background:transparent;}");
    m_pTitleLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_pTitleLabel->setText(tr("Wi-Fi"));
    m_pTitleLabel->show();

    //Net Name
    m_pNetNameLabel = new QLabel(this);
    m_pNetNameLabel->setGeometry(QRect(322-150,85-3,150,24));
    m_pNetNameLabel->setStyleSheet("QLabel{font-size: 24px; color: #ffffff; background:transparent;}");
    m_pNetNameLabel->setAlignment(Qt::AlignRight);
    m_pNetNameLabel->setText(QString(tr("Net name:")));
    m_pNetNameLabel->show();

    m_pNetNameEdit = new QLineEdit(this);
    m_pNetNameEdit->setGeometry(345,85-3-12,255,24+24);
    m_pNetNameEdit->setStyleSheet("QLineEdit{font-size: 24px; color: #ffffff; background:transparent;}");

    m_pNetNameEditLine = new QLabel(this);
    m_pNetNameEditLine->setGeometry(340,107+4,265,1);
    m_pNetNameEditLine->setStyleSheet("QLabel{background:#66ffffff;}");

    //Security Type
    m_pSecurityTypeLabel = new QLabel(this);
    m_pSecurityTypeLabel->setGeometry(QRect(322-150,85-3+57,150,24));
    m_pSecurityTypeLabel->setStyleSheet("QLabel{font-size: 24px; color: #ffffff; background:transparent;}");
    m_pSecurityTypeLabel->setAlignment(Qt::AlignRight);
    m_pSecurityTypeLabel->setText(QString(tr("Security type:")));
    m_pSecurityTypeLabel->show();

    m_pSecurityTypeEditLine = new QLabel(this);
    m_pSecurityTypeEditLine->setGeometry(340,107+4+57,265,1);
    m_pSecurityTypeEditLine->setStyleSheet("QLabel{background:#66ffffff;}");

    //ComboBox
    m_pSecurityTypeComboBox = new CComboBox(this);
    m_pSecurityTypeComboBox->setGeometry(800-187-252,107+4+9,252,38);
    m_pSecurityTypeComboBox->setBtnStyle(":/Settings/select_b.png",QSize(36,38));
    m_pSecurityTypeComboBox->addItem(QString(tr("None")));
    m_pSecurityTypeComboBox->addItem(QString(tr("WEP")));
    m_pSecurityTypeComboBox->addItem(QString(tr("WPA")));
    m_pSecurityTypeComboBox->addItem(QString(tr("WPA2")));
    m_pSecurityTypeComboBox->addItem(QString(tr("WPA/WPA2")));

    //password
    m_pPasswordLabel = new QLabel(this);
    m_pPasswordLabel->setGeometry(QRect(322-150,85-3+57+57,150,24));
    m_pPasswordLabel->setStyleSheet("QLabel{font-size: 24px; color: #ffffff; background:transparent;}");
    m_pPasswordLabel->setAlignment(Qt::AlignRight);
    m_pPasswordLabel->setText(QString(tr("Password:")));
    m_pPasswordLabel->show();

    m_pPasswordEdit = new QLineEdit(this);
    m_pPasswordEdit->setGeometry(345,85-3-12+57+57,255,24+24);
    m_pPasswordEdit->setStyleSheet("QLineEdit{font-size: 24px; color: #ffffff; background:transparent;}");
    m_pPasswordEdit->setEchoMode(QLineEdit::Password);

    m_pPasswordEditLine = new QLabel(this);
    m_pPasswordEditLine->setGeometry(340,107+4+57+57,265,1);
    m_pPasswordEditLine->setStyleSheet("QLabel{background:#66ffffff;}");

    m_pPasswordError = new QLabel(this);
    m_pPasswordError->setGeometry(340,118-9+57+57,265,18+18);
    m_pPasswordError->setStyleSheet("QLabel{font-size: 18px; color: #ffb121; background:transparent;}");
    m_pPasswordError->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_pPasswordError->setText(QString(tr("Password error,please retype")));
    m_pPasswordError->hide();

    //button
    m_pAddBtn = new QPushButton(this);
    m_pAddBtn->setStyleSheet("QPushButton{font-size:20px;color:#ffffffff;border:transparent;background-image:url(:/Settings/button_a.png);}\
                                 QPushButton:pressed{color:#66ffffff;background-image:url(:/Settings/button_a.png);border:none;}");
    m_pAddBtn->setGeometry(229,356,131,32);
    m_pAddBtn->setFocusPolicy(Qt::NoFocus);
    m_pAddBtn->setText(QString(tr("Add")));

    m_pCancelBtn = new QPushButton(this);
    m_pCancelBtn->setStyleSheet("QPushButton{font-size:20px;color:#ffffffff;border:transparent;background-image:url(:/Settings/button_a.png);}\
                                QPushButton:pressed{color:#66ffffff;background-image:url(:/Settings/button_a.png);border:none;}");
    m_pCancelBtn->setGeometry(440,356,131,32);
    m_pCancelBtn->setFocusPolicy(Qt::NoFocus);
    m_pCancelBtn->setText(QString(tr("Cancel")));

    connect(m_pAddBtn,SIGNAL(clicked()),this,SLOT(OnAddBtnClicked()));
    connect(m_pCancelBtn,SIGNAL(clicked()),this,SLOT(OnCancelBtnClicked()));
    connect(m_pBackBtn,SIGNAL(clicked()),this,SLOT(OnBack()),Qt::UniqueConnection);
}

SettingsWifiAddHotSpotsUI::~SettingsWifiAddHotSpotsUI()
{

}

void SettingsWifiAddHotSpotsUI::viewAction(int state)
{

}

void SettingsWifiAddHotSpotsUI::OnBack()
{
    Home::Inst()->ViewBack();
}

void SettingsWifiAddHotSpotsUI::OnAddBtnClicked()
{
    qDebug()<<"[OnAddBtnClicked]currentIndex"<<m_pSecurityTypeComboBox->currentIndex();
    qDebug()<<"[OnAddBtnClicked]currentText"<<m_pSecurityTypeComboBox->currentText();
    //TODO: connect to Wifi with current setting, if succeed, change to connected wifi list view;
    //      if failed, show popup

    bool ret = SettingsWifiData::GetInstance()->CheckPasswordWithWifiInfo(
                m_pNetNameEdit->text(),
                m_pSecurityTypeComboBox->currentText(),
                m_pPasswordEdit->text());

    if(ret)
    {
        //change to connected wifi list view;
        //Home::Inst()->ViewForwardById(Home::eViewId_Settings_Wifi);
        Home::Inst()->ViewBack();
    }
    else
    {
        //TODO: show popup
    }
}

void SettingsWifiAddHotSpotsUI::OnCancelBtnClicked()
{
    //return to previous view
    Home::Inst()->ViewBack();
}

void SettingsWifiAddHotSpotsUI::showEvent(QShowEvent *)
{
    m_pNetNameEdit->setText("");
    m_pSecurityTypeComboBox->setCurrentIndex(0);
    m_pPasswordEdit->setText("");
}
