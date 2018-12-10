#include "NonMediaShow.h"
#include <QUrl>
#include "HMIFrameWork/log_interface.h"
#include "SDLApps/app/SDLApps.h"
#include "HMIFrameWork/HMIFrameWork.h"

#define MUSICPICWIDTH 185
#define CMD_PREV 109
#define CMD_START 1022
#define CMD_PAUSE 1025
#define CMD_NEXT 112

CNonMediaShow::CNonMediaShow(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_pList(pList)
    ,m_pFrameLab(NULL)
    ,m_pAlbumCover(NULL)
    ,m_pRightArea(NULL)
    ,m_pTopWidget(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    //album
    m_pFrameLab = new QLabel(this);
    m_pFrameLab->setGeometry(QRect(40,78,300,300));
    m_pFrameLab->setStyleSheet("QLabel{border-image:url(:/SDLApps/Source/images/KUANG.png);background:transparent;}");
    m_pFrameLab->show();

    m_pAlbumCover = new QLabel(this);
    m_pAlbumCover->setGeometry(85,123,210,210);
    m_pAlbumCover->setStyleSheet("QLabel{background:transparent;}");
    m_pAlbumCover->show();
    //right area
    m_pRightArea = new QWidget(this);
    m_pRightArea->setGeometry(800-116,116,116,(32+20)*5-20);

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
        connect(&m_aSoftBtn[i], SIGNAL(clicked(int)), this, SLOT(SoftBtnClickedSlot(int)));
    }

    m_pRightArea->setLayout(pRightLayout);

    //top widget
    m_pTopWidget = new TopNavigateWidget(this);
    m_pTopWidget->SetReturnTitle(QString("Sources"));
    m_pTopWidget->ShowBack();
    m_pTopWidget->ShowTitle();
    m_pTopWidget->ShowMenu();
    m_pTopWidget->show();
    connect(m_pTopWidget, SIGNAL(SigMenuClicked()), this, SLOT(BtnMenuClickedSlots()));
    connect(m_pTopWidget, SIGNAL(SigBackClicked()), this, SLOT(BtnBackClickedSlots()));

    //textfield
    m_aShowLine[0].setParent(this);
    m_aShowLine[0].setStyleSheet("border:0px;font: 26px;color:#74767E");
    m_aShowLine[0].setGeometry(356,103,317,60);
    m_aShowLine[0].setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_aShowLine[0].show();

    m_aShowLine[1].setParent(this);
    m_aShowLine[1].setStyleSheet("border:0px;font: 26px;color:#74767E");
    m_aShowLine[1].setGeometry(356,163,317,60);
    m_aShowLine[1].setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    m_aShowLine[2].setParent(this);
    m_aShowLine[2].setStyleSheet("border:0px;font: 26px;color:#74767E");
    m_aShowLine[2].setGeometry(356,223,317,60);
    m_aShowLine[2].setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

}

CNonMediaShow::~CNonMediaShow()
{

}

void CNonMediaShow::SoftBtnClickedSlot(int iSoftBtnID) {
    if (iSoftBtnID >= 0) {
        AppControl->OnSoftButtonClick(iSoftBtnID, BUTTON_SHORT);
    }
}

void CNonMediaShow::BtnMenuClickedSlots() {
    AppControl->OnShowCommand();
}

void CNonMediaShow::BtnBackClickedSlots()
{
    SDLApps::Inst()->GetUIManager()->onAppShow(ID_APPLINK);
}
void CNonMediaShow::SetAppName(QString strName) {
    m_pTopWidget->SetTitle(strName);
}

void CNonMediaShow::showEvent(QShowEvent *e) {
    Q_UNUSED(e);

    for (int i = 0; i < RIGHT_BTN_NUM; ++i) {
        m_aSoftBtn[i].setText("");
    }

    for (int i = 0; i < SHOW_LINE_NUM; ++i) {
        m_aShowLine[i].setText(" ");
    }

    if (AppControl) {
        SetAppName(AppControl->getAppName().c_str());

        rpcValueInterface &pObj = AppControl->getShowData();
        if (pObj.isNull())
            return;
        rpcValueInterface &jsonParams = pObj["params"];
        Qt::AlignmentFlag alignMode =  Qt::AlignLeft;
        if (jsonParams.isMember("alignment")) {
            std::string align = jsonParams["alignment"].asString();
            if ("RIGHT_ALIGNED" == align) {
                alignMode = Qt::AlignRight;
            } else if ("CENTERED" == align) {
                alignMode = Qt::AlignVCenter;
            }
        }

        if (jsonParams.isMember("showStrings")) {
            for (unsigned int i = 0; i < jsonParams["showStrings"].size(); ++i) {
                rpcValueInterface  &fieldName = jsonParams["showStrings"][i];
                if ("mainField1" == fieldName["fieldName"].asString()) {
                    AppBase::SetEdlidedText(m_aShowLine, fieldName["fieldText"].asString().c_str(), m_aShowLine[0].width(), alignMode);
                } else if ("mainField2" == fieldName["fieldName"].asString()) {
                    AppBase::SetEdlidedText(m_aShowLine + 1, fieldName["fieldText"].asString().c_str(), m_aShowLine[1].width(), alignMode);
                } else if ("mainField3" == fieldName["fieldName"].asString()) {
                    AppBase::SetEdlidedText(m_aShowLine + 2, fieldName["fieldText"].asString().c_str(), m_aShowLine[2].width(), alignMode);
                }
            }
        }

        if (jsonParams.isMember("graphic")) {
            QUrl graphicUrl(jsonParams["graphic"]["value"].asString().c_str());
            if (graphicUrl.isEmpty()) {
                m_pAlbumCover->setPixmap(QPixmap(""));
            } else {
#if defined(WINCE)
                QString path = QString::fromStdString(ChangeSlash(graphicUrl.path().toLocal8Bit().data()));
#else
                QString path = QString::fromStdString(ChangeSlash(graphicUrl.path().toStdString()));
#endif
                m_pAlbumCover->setPixmap(QPixmap(path).scaled(210,210,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
            }
        } else {
            m_pAlbumCover->setPixmap(QPixmap(""));
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


void CNonMediaShow::setSoftButtons(std::vector<SSoftButton> vec_softButtons) {
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

