#include "SettingsWifiPasswordUI.h"
#include "Home/data/Settings/SettingsWifiData.h"
#include "Home/app/Home.h"
#include "HMIFrameWork/log_interface.h"

SettingsWifiPasswordUI::SettingsWifiPasswordUI(QWidget *parent)
    :QWidget(parent)
    ,CView(Home::eViewId_Settings_WifiPassword)
    ,m_pBackBtn(NULL)
    ,m_pTitleLabel(NULL)
    ,m_pPasswordLabel(NULL)
    ,m_pPasswordEdit(NULL)
    ,m_pPasswordEditLine(NULL)
    ,m_pPasswordError(NULL)
    ,m_pConnectBtn(NULL)
    ,m_pCancelBtn(NULL)
{
    this->setGeometry(QRect(0,40,800,440));
    this->setStyleSheet("QWidget{border:none;background:transparent;}");

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
    m_pTitleLabel->setText(tr("Wi-Fi"));
    m_pTitleLabel->show();


    //password
    m_pPasswordLabel = new QLabel(this);
    m_pPasswordLabel->setGeometry(QRect(322-150,85-3,150,24));
    m_pPasswordLabel->setStyleSheet("QLabel{font-size: 24px; color: #ffffff; background:transparent;}");
    m_pPasswordLabel->setAlignment(Qt::AlignRight);
    m_pPasswordLabel->setText(QString(tr("Password:")));
    m_pPasswordLabel->show();

    m_pPasswordEdit = new QLineEdit(this);
    m_pPasswordEdit->setGeometry(345,85-3-12,255,24+24);
    m_pPasswordEdit->setStyleSheet("QLineEdit{font-size: 24px; color: #ffffff; background:transparent;}");
    m_pPasswordEdit->setEchoMode(QLineEdit::Password);

    m_pPasswordEditLine = new QLabel(this);
    m_pPasswordEditLine->setGeometry(340,107+4,265,1);
    m_pPasswordEditLine->setStyleSheet("QLabel{background:#66ffffff;}");

    m_pPasswordError = new QLabel(this);
    m_pPasswordError->setGeometry(340,118-9,265,18+18);
    m_pPasswordError->setStyleSheet("QLabel{font-size: 18px; color: #ffb121; background:transparent;}");
    m_pPasswordError->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_pPasswordError->setText(QString(tr("Password error,please retype")));
    m_pPasswordError->hide();

    //button
    m_pConnectBtn = new QPushButton(this);
    m_pConnectBtn->setStyleSheet("QPushButton{font-size:20px;color:#ffffffff;border:transparent;background-image:url(:/Settings/button_a.png);}\
                                 QPushButton:pressed{color:#66ffffff;background-image:url(:/Settings/button_a.png);border:none;}");
    m_pConnectBtn->setGeometry(229,356,131,32);
    m_pConnectBtn->setFocusPolicy(Qt::NoFocus);
    m_pConnectBtn->setText(QString(tr("Connect")));

    m_pCancelBtn = new QPushButton(this);
    m_pCancelBtn->setStyleSheet("QPushButton{font-size:20px;color:#ffffffff;border:transparent;background-image:url(:/Settings/button_a.png);}\
                                QPushButton:pressed{color:#66ffffff;background-image:url(:/Settings/button_a.png);border:none;}");
    m_pCancelBtn->setGeometry(440,356,131,32);
    m_pCancelBtn->setFocusPolicy(Qt::NoFocus);
    m_pCancelBtn->setText(QString(tr("Cancel")));

    connect(m_pConnectBtn,SIGNAL(clicked()),this,SLOT(OnConnectBtnClicked()));
    connect(m_pCancelBtn,SIGNAL(clicked()),this,SLOT(OnCancelBtnClicked()));
    connect(m_pBackBtn,SIGNAL(clicked()),this,SLOT(OnBack()),Qt::UniqueConnection);

}

SettingsWifiPasswordUI::~SettingsWifiPasswordUI()
{

}

void SettingsWifiPasswordUI::viewAction(int state)
{
    Q_UNUSED(state)
}

void SettingsWifiPasswordUI::OnBack()
{
    Home::Inst()->ViewBack();
}

void SettingsWifiPasswordUI::OnConnectBtnClicked()
{
    //TODO: check password, and do connect if right, else show error msg.
    QString enteredPassword = m_pPasswordEdit->text();
    INFO("enteredPassword: %s .",enteredPassword.toStdString().c_str());

    if(SettingsWifiData::GetInstance()->CheckPassword(enteredPassword))
    {
        //success
        m_pPasswordError->hide();
        //TODO: connect wifi, and show connecting view
        INFO("[SettingsWifiPasswordUI]CheckPassword success");
       // Home::Inst()->ViewForwardById(Home::eViewId_Settings_Wifi);
        Home::Inst()->ViewBack();
    }
    else
    {
        //failed
        m_pPasswordError->show();
        INFO("[SettingsWifiPasswordUI]CheckPassword failed");
    }
}

void SettingsWifiPasswordUI::OnCancelBtnClicked()
{
    //TODO: return to SettingsWifiUI view
   // Home::Inst()->ViewForwardById(Home::eViewId_Settings_Wifi);
    Home::Inst()->ViewBack();
}

void SettingsWifiPasswordUI::showEvent(QShowEvent *)
{
    m_pPasswordEdit->setText("");
    m_pPasswordError->hide();
}
