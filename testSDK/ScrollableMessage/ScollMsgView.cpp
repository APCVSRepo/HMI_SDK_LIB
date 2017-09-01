#include "ScollMsgView.h"
#include <QBoxLayout>

CScollMsgView::CScollMsgView(AppListInterface * pList, QWidget *parent)
    : QWidget(parent)
{
    if (parent) {
        setGeometry(0,0,parent->width(),parent->height());
    }
    m_pList = pList;

    setAutoFillBackground(true);
    QPixmap pixmap(":/images/MainWidget/Backgroud.png");
    pixmap = pixmap.scaled(width(),height(),
                           Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    setPalette(palette);

    QVBoxLayout *pMainLayout = new QVBoxLayout(this);
    QHBoxLayout *pTopLayout = new QHBoxLayout;
    m_pReturnBtn = new CCustomButton;
    m_pAppNameLab = new QLabel;
    m_pSoftBtn = new CCustomButton;
    m_pText = new QTextEdit;

    pMainLayout->addLayout(pTopLayout);
    pMainLayout->addWidget(m_pText,1);
    pMainLayout->setContentsMargins(0,0,0,0);
    pMainLayout->setSpacing(0);

    pTopLayout->addWidget(m_pReturnBtn);
    pTopLayout->addWidget(m_pAppNameLab,1);
    pTopLayout->addWidget(m_pSoftBtn);
    pTopLayout->setContentsMargins(width()*0.015,width()*0.015,
                                   width()*0.015,width()*0.015);
    pTopLayout->setSpacing(5);

    m_pReturnBtn->Init(width()*0.07,width()*0.065,"",":/images/ReturnBtnNormal.png",":/images/ReturnBtnPress.png");
    m_pAppNameLab->setStyleSheet("font: 36px \"Liberation Serif\";color:rgb(0,0,0)");
    m_pSoftBtn->Init(width()*0.13,height()*0.13,"softbtn",":/images/alert_softbtn_normal.png",":/images/alert_softbtn_press.png");
    m_pSoftBtn->SetTextStyle("font: 32px \"Liberation Serif\";color:rgb(0,0,0)");
    m_pText->setStyleSheet("font: 22px \"Liberation Serif\";color:rgb(0,0,0)");

    m_pTimer = new QTimer;
    connect(m_pTimer,SIGNAL(timeout()),SLOT(OnTimeOutSlot()));
    connect(m_pReturnBtn,SIGNAL(Clicked()),SLOT(OnReturnBtnClicked()));
    connect(m_pSoftBtn,SIGNAL(Clicked(int)),SLOT(OnSoftBtnClicked(int)));
}

CScollMsgView::~CScollMsgView()
{
    delete m_pReturnBtn;
    delete m_pAppNameLab;
    delete m_pSoftBtn;
    delete m_pText;
}

void CScollMsgView::SetTimeOut(int iDuration)
{
    m_pTimer->start(iDuration);
}

void CScollMsgView::showEvent(QShowEvent * e)
{
    if (AppControl) {
        AppBase::SetEdlidedText(m_pAppNameLab,AppControl->getAppName().c_str(),width()*0.7);

        rpcValueInterface& m_jsonData = AppControl->getScrollableMsgJson()["params"];
        SetTimeOut(m_jsonData["timeout"].asInt());
        if (m_jsonData.isMember("messageText")) {
            m_pText->setText(m_jsonData["messageText"]["fieldText"].asString().c_str());
        }

        if (m_jsonData.isMember("softButtons")) {
            m_pSoftBtn->SetId(m_jsonData["softButtons"][0]["softButtonID"].asInt());
            m_pSoftBtn->SetText(m_jsonData["softButtons"][0]["text"].asString().c_str());
            m_pSoftBtn->show();
        } else {
            m_pSoftBtn->hide();
        }
    }
}

void CScollMsgView::OnTimeOutSlot()
{
    m_pTimer->stop();
    AppControl->OnScrollMessageResponse(RESULT_SUCCESS);
}

void CScollMsgView::OnReturnBtnClicked()
{
    m_pTimer->stop();
    AppControl->OnScrollMessageResponse(RESULT_ABORTED);
}

void CScollMsgView::OnSoftBtnClicked(int iBtnId)
{
    //m_pTimer->stop();
    if (iBtnId != 0) {
        AppControl->OnSoftButtonClick(iBtnId,BUTTON_SHORT);
    }
}
