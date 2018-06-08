#include "GraphicSoftButtonShow.h"
#include <QUrl>
#include "SDLApps/Templates/Config/Config.h"
#include "HMIFrameWork/log_interface.h"

#define MUSICPICWIDTH 770
#define MUSICPICHEIGHT 210

CGraphicSoftButtonShow::CGraphicSoftButtonShow(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_pList(pList)
    ,m_pTopWidget(NULL)
    ,m_pRightArea(NULL)
    ,m_pMusicPicLab(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    //top widget
    m_pTopWidget = new TopNavigateWidget(this);
    m_pTopWidget->SetReturnTitle(QString(""));
    m_pTopWidget->ShowBack();
    m_pTopWidget->ShowTitle();
    m_pTopWidget->ShowMenu();
    m_pTopWidget->show();
    connect(m_pTopWidget, SIGNAL(SigMenuClicked()), this, SLOT(BtnMenuClickedSlots()));
    connect(m_pTopWidget, SIGNAL(SigBackClicked()), this, SLOT(BtnBackClickedSlots()));

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
        //set softBtnId
        m_aSoftBtn[i].setId(-1);
        connect(&m_aSoftBtn[i], SIGNAL(clicked(int)), this, SLOT(SoftBtnClickedSlot(int)));
    }

    m_pRightArea->setLayout(pRightLayout);

    //graphic
    m_pMusicPicLab = new QLabel(this);
    m_pMusicPicLab->setGeometry(54,70,800-116-10-54-20,480-40-70-70);
    m_pMusicPicLab->setStyleSheet("background:transparent");
}

void CGraphicSoftButtonShow::SoftBtnClickedSlot(int iSoftBtnID) {
    if (iSoftBtnID != 0) {
        AppControl->OnSoftButtonClick(iSoftBtnID, BUTTON_SHORT);
    }
}

void CGraphicSoftButtonShow::BtnMenuClickedSlots() {
    AppControl->OnShowCommand();
}

void CGraphicSoftButtonShow::BtnBackClickedSlots()
{
    INFO("CGraphicSoftButtonShow::BtnBackClickedSlots");
    //TODO: change to previous view
}

void CGraphicSoftButtonShow::SetAppName(QString strName) {
    m_pTopWidget->SetTitle(strName);
}

void CGraphicSoftButtonShow::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    for (int i = 0; i < RIGHT_BTN_NUM; ++i) {
        m_aSoftBtn[i].setText("");
    }

    if (AppControl) {
        SetAppName(AppControl->getAppName().c_str());

        rpcValueInterface &pObj = AppControl->getShowData();
        if (pObj.isNull())
            return;
        rpcValueInterface &jsonParams = pObj["params"];

        if (jsonParams.isMember("graphic")) {
            QUrl graphicUrl(jsonParams["graphic"]["value"].asString().c_str());
            if (graphicUrl.isEmpty()) {
                m_pMusicPicLab->setStyleSheet("background:transparent");
            } else {
#if defined(WINCE)
                QString strStyle = QString("background:transparent;border-image:url(%1)").arg(ChangeSlash(graphicUrl.path().toLocal8Bit().data()).c_str());
#else
                QString strStyle = QString("background:transparent;border-image:url(%1)").arg(ChangeSlash(graphicUrl.path().toStdString()).c_str());
#endif
                m_pMusicPicLab->setStyleSheet(strStyle);
            }
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

void CGraphicSoftButtonShow::setSoftButtons(std::vector<SSoftButton> vec_softButtons) {
    int iSize = vec_softButtons.size() > RIGHT_BTN_NUM ? RIGHT_BTN_NUM : vec_softButtons.size();
    for (int i = 0; i < iSize; ++i) {
        m_aSoftBtn[i].initParameter(116, 32, ":/SDLApps/Source/images/right_btn_normal.png", ":/SDLApps/Source/images/right_btn_push.png", "", vec_softButtons[i].str_text.c_str());
        m_aSoftBtn[i].setId(vec_softButtons[i].i_softButtonID);

        if (vec_softButtons[i].b_isHighlighted){
            m_aSoftBtn[i].changeToPressed();
        }
    }
}
