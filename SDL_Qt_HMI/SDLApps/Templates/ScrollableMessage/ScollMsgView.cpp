#include "ScollMsgView.h"
#include <QBoxLayout>
#include "HMIFrameWork/log_interface.h"

CScollMsgView::CScollMsgView(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_pList(pList)
    ,m_pRightArea(NULL)
    ,m_pTopWidget(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    //right area
    m_pRightArea = new QWidget(this);
    m_pRightArea->setGeometry(800-116,75,116,(32+20)*5-20);

    QVBoxLayout *pRightLayout = new QVBoxLayout;
    pRightLayout->setSpacing(20);
    pRightLayout->setMargin(0);

    m_vSoftButtons.clear();

    for (int i = 0; i < RIGHT_BTN_NUM; ++i) {
        pRightLayout->addWidget(m_aSoftBtn + i, 0, Qt::AlignTop);
        m_aSoftBtn[i].setSize(116, 32);
        m_aSoftBtn[i].setTextStyle("border:0px; font:19px; color:rgb(238,238,238)");
        m_aSoftBtn[i].SetPadding(10,0,10,0);
        //set softBtnId
        m_aSoftBtn[i].setId(-1);
        connect(&m_aSoftBtn[i], SIGNAL(clicked(int)), this, SLOT(OnSoftBtnClicked(int)));
    }

    m_pRightArea->setLayout(pRightLayout);

    //top widget
    m_pTopWidget = new TopNavigateWidget(this);
    m_pTopWidget->SetReturnTitle(QString(""));
    m_pTopWidget->ShowBack();
    m_pTopWidget->ShowTitle();
    m_pTopWidget->show();
    connect(m_pTopWidget, SIGNAL(SigBackClicked()), this, SLOT(OnReturnBtnClicked()));

    //scroll msg
    m_pText = new QTextEdit(this);
    m_pText->setGeometry(54,70,800-116-10-54-20,480-40-70-70);
    m_pText->setStyleSheet("font: 22px;color:rgb(255,255,255)");
    m_pText->setReadOnly(true);
    //height of line
    QTextCursor textCursor = m_pText->textCursor();
    QTextBlockFormat textBlockFormat;
    textBlockFormat.setLineHeight(38, QTextBlockFormat::FixedHeight);
    textCursor.setBlockFormat(textBlockFormat);
    m_pText->setTextCursor(textCursor);

    //timer
    m_pTimer = new QTimer;
    connect(m_pTimer, SIGNAL(timeout()), SLOT(OnTimeOutSlot()));
}

CScollMsgView::~CScollMsgView() {

}

void CScollMsgView::SetTimeOut(int iDuration) {
    m_pTimer->start(iDuration);
}

void CScollMsgView::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    if(AppControl){
        m_pTopWidget->SetTitle(QString::fromStdString(AppControl->getAppName().c_str()));

        rpcValueInterface &jsonParams = AppControl->getScrollableMsgJson()["params"];
        SetTimeOut(jsonParams["timeout"].asInt());
        if (jsonParams.isMember("messageText")) {
            m_pText->insertPlainText(jsonParams["messageText"]["fieldText"].asString().c_str());
        }

        m_vSoftButtons.clear();
        if (jsonParams.isMember("softButtons")) {
            for (unsigned int i = 0; i < jsonParams["softButtons"].size(); ++i) {
                SSoftButton tmpSoftButton;
                tmpSoftButton.b_isHighlighted = jsonParams["softButtons"][i]["isHighlighted"].asBool();
                tmpSoftButton.i_softButtonID = jsonParams["softButtons"][i]["softButtonID"].asInt();
                tmpSoftButton.str_text = jsonParams["softButtons"][i]["text"].asString();
                m_vSoftButtons.push_back(tmpSoftButton);
            }
        }
        setSoftButtons(m_vSoftButtons);
    }
}

void CScollMsgView::hideEvent(QHideEvent *) {
    if(m_pTimer->isActive())
        m_pTimer->stop();
}

void CScollMsgView::OnTimeOutSlot() {
    m_pTimer->stop();
    AppControl->OnScrollMessageResponse(RESULT_SUCCESS);
}

void CScollMsgView::OnReturnBtnClicked() {
    m_pTimer->stop();
    AppControl->OnScrollMessageResponse(RESULT_ABORTED);
}

void CScollMsgView::OnSoftBtnClicked(int iBtnId) {
    if (1 == iBtnId) {
        // 特殊处理关闭按钮
        m_pTimer->stop();
        AppControl->OnScrollMessageResponse(RESULT_ABORTED);
    } else if (iBtnId != 0) {
        AppControl->OnSoftButtonClick(iBtnId, BUTTON_SHORT);
    }
}

void CScollMsgView::setSoftButtons(std::vector<SSoftButton> vec_softButtons) {
    int iSize = vec_softButtons.size() > RIGHT_BTN_NUM ? RIGHT_BTN_NUM : vec_softButtons.size();
    for (int i = 0; i < iSize; ++i) {
        m_aSoftBtn[i].initParameter(116, 32, ":/SDLApps/Source/images/right_btn_normal.png", ":/SDLApps/Source/images/right_btn_push.png", "", vec_softButtons[i].str_text.c_str());
        m_aSoftBtn[i].setId(vec_softButtons[i].i_softButtonID);

        if (vec_softButtons[i].b_isHighlighted){
            m_aSoftBtn[i].changeToPressed();
        }
    }

    for (int i = iSize; i < RIGHT_BTN_NUM; ++i) {
        m_aSoftBtn[i].initParameter(116, 32, "", "", "", "");
        m_aSoftBtn[i].setId(-1);
    }
}
