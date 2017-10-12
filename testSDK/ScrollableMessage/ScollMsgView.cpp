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
    QHBoxLayout *pCenterLayout = new QHBoxLayout;
    QHBoxLayout *pBottomLayout = new QHBoxLayout;
    QVBoxLayout *pBottomCenterLayout = new QVBoxLayout;
    QHBoxLayout *m_pBtnLayout = new QHBoxLayout;

    m_pReturnBtn = new CCustomButton;
    m_pAppNameLab = new QLabel;
    m_pText = new QTextEdit;
    m_pShadowLab = new QLabel;

    pMainLayout->addLayout(pTopLayout);
    pMainLayout->addLayout(pCenterLayout,1);
    pMainLayout->addLayout(pBottomLayout);
    pMainLayout->setContentsMargins(10,10,10,10);
    pMainLayout->setSpacing(0);

    pTopLayout->addWidget(m_pReturnBtn);
    pTopLayout->addWidget(m_pAppNameLab,1);
    pTopLayout->setContentsMargins(0, 0, 0, 5);
    pTopLayout->setSpacing(10);

    pCenterLayout->addWidget(m_pText);

    pBottomLayout->addLayout(pBottomCenterLayout);
    pBottomLayout->addStretch(1);
    pBottomLayout->setSpacing(0);
    pBottomLayout->setContentsMargins(0, 5, 0, 0);
    pBottomCenterLayout->addLayout(m_pBtnLayout);
    pBottomCenterLayout->addWidget(m_pShadowLab);
    pBottomCenterLayout->addStretch(1);

    m_vSoftButtons.clear();

    for (int i = 0;i != 6;++i) {
        m_pBtnLayout->addWidget(m_aSoftBtn + i);
        m_aSoftBtn[i].setSize(0,0);
        m_aSoftBtn[i].setTextStyle("font: 32px \"Liberation Serif\";color:rgb(0,0,0)");

        if (i != 5) {
            m_pBtnLayout->addWidget(m_aSplit + i);
            m_aSplit[i].setStyleSheet("max-height:0px;max-width:0px;border-image:url(:/images/MediaShow/split.png)");
            //m_aSplit[i].hide();
        }
        connect(&m_aSoftBtn[i],SIGNAL(clicked(int)),this,SLOT(OnSoftBtnClicked(int)));
    }

    m_pReturnBtn->Init(width()*0.07,width()*0.065,"",":/images/ReturnBtnNormal.png",":/images/ReturnBtnPress.png");
    m_pAppNameLab->setStyleSheet("font: 36px \"Liberation Serif\";color:rgb(0,0,0)");
    m_pText->setStyleSheet("font: 22px \"Liberation Serif\";color:rgb(0,0,0)");
    m_pText->setReadOnly(true);;

    m_pTimer = new QTimer;
    connect(m_pTimer,SIGNAL(timeout()),SLOT(OnTimeOutSlot()));
    connect(m_pReturnBtn,SIGNAL(Clicked()),SLOT(OnReturnBtnClicked()));
}

CScollMsgView::~CScollMsgView()
{
    delete m_pReturnBtn;
    delete m_pAppNameLab;
    delete m_pText;
    delete m_pShadowLab;
}

void CScollMsgView::SetTimeOut(int iDuration)
{
    m_pTimer->start(iDuration);
}

void CScollMsgView::showEvent(QShowEvent * e)
{
    Q_UNUSED(e);
    if (AppControl) {
        AppBase::SetEdlidedText(m_pAppNameLab,AppControl->getAppName().c_str(),width()*0.7);

        rpcValueInterface& jsonParams = AppControl->getScrollableMsgJson()["params"];
        SetTimeOut(jsonParams["timeout"].asInt());
        if (jsonParams.isMember("messageText")) {
            m_pText->setText(jsonParams["messageText"]["fieldText"].asString().c_str());
        }

        if (jsonParams.isMember("softButtons")) {
            m_vSoftButtons.clear();
            for (unsigned int i = 0; i < jsonParams["softButtons"].size(); ++i) {
                SSoftButton tmpSoftButton;
                tmpSoftButton.b_isHighlighted = jsonParams["softButtons"][i]["isHighlighted"].asBool();
                tmpSoftButton.i_softButtonID = jsonParams["softButtons"][i]["softButtonID"].asInt();
                tmpSoftButton.str_text = jsonParams["softButtons"][i]["text"].asString();
                m_vSoftButtons.push_back(tmpSoftButton);
            }
            m_pShadowLab->setStyleSheet("max-height:6px;border-image:url(:/images/MediaShow/shadow.png)");
        } else {
            m_pShadowLab->setStyleSheet("background:transparent");
        }
        setSoftButtons(m_vSoftButtons);
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

void CScollMsgView::setSoftButtons(std::vector<SSoftButton> vec_softButtons)
{
    for (int i = 0;i != 6;++i) {
        m_aSoftBtn[i].setSize(0,0);

        if (i < 5) {
            m_aSplit[i].setStyleSheet("max-width:0px;border-image:url(:/images/MediaShow/split.png)");
        }
    }

    if (vec_softButtons.size() == 1) {
        m_aSoftBtn[0].initParameter(125,50,":/images/MediaShow/center_normal.png",":/images/MediaShow/center_press.png","",vec_softButtons[0].str_text.c_str());
        m_aSoftBtn[0].setId(vec_softButtons[0].i_softButtonID);
        if(vec_softButtons[0].b_isHighlighted)
            m_aSoftBtn[0].changeToPressed();
    } else {
        int iSize = vec_softButtons.size()>6?6:vec_softButtons.size();
        for(int i = 0;i != iSize;++i) {
            if (i == 0) {
                m_aSoftBtn[i].initParameter(125,50,":/images/MediaShow/left_normal.png",":/images/MediaShow/left_press.png","",vec_softButtons[i].str_text.c_str());
            } else if (i == iSize - 1) {
                m_aSoftBtn[i].initParameter(125,50,":/images/MediaShow/right_normal.png",":/images/MediaShow/right_press.png","",vec_softButtons[i].str_text.c_str());
            } else {
                m_aSoftBtn[i].initParameter(125,50,":/images/MediaShow/center_normal.png",":/images/MediaShow/center_press.png","",vec_softButtons[i].str_text.c_str());
            }
            m_aSoftBtn[i].setId(vec_softButtons[i].i_softButtonID);

            if(vec_softButtons[i].b_isHighlighted)
                m_aSoftBtn[i].changeToPressed();

            if (i < iSize - 1) {
                m_aSplit[i].setStyleSheet("max-width:1px;border-image:url(:/images/MediaShow/split.png)");
            }
        }
    }
}
