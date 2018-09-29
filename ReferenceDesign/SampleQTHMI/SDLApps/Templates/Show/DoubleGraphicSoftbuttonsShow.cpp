#include "DoubleGraphicSoftbuttons.h"
#include <QUrl>
#include "HMIFrameWork/log_interface.h"
#include "SDLApps/app/SDLApps.h"
#include "HMIFrameWork/HMIFrameWork.h"

#define MUSICPICWIDTH 185
#define CMD_PREV 109
#define CMD_START 1022
#define CMD_PAUSE 1025
#define CMD_NEXT 112

CDoubleGraphicSoftbuttonsShow::CDoubleGraphicSoftbuttonsShow(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_pList(pList)
    ,m_btnWidth(116)
    ,m_btnHeight(32)
    ,m_btnTop(119)
    ,m_btnLeft(684)
    ,m_btnXSpace(29)
    ,m_btnYSpace(20)
    ,m_pGraphicFrame(NULL)
    ,m_pGraphic(NULL)
    ,m_pSecGraphic(NULL)
    ,m_pRightArea(NULL)
    ,m_pTopWidget(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    //Graphic
    m_pGraphicFrame = new QLabel(this);
    m_pGraphicFrame->setGeometry(81,119,212,212);
    m_pGraphicFrame->setStyleSheet("QLabel{border-image:url(:/SDLApps/Source/images/KUANG_321.png);background:transparent;}");
    m_pGraphicFrame->show();


    m_pGraphic = new QLabel(this);
    m_pGraphic->setGeometry(85,123,204,204);
    m_pGraphic->setStyleSheet("QLabel{background:transparent;}");
    m_pGraphic->show();

    m_pSecGraphic = new QLabel(this);
    m_pSecGraphic->setGeometry(400,123,204,204);
    m_pSecGraphic->setStyleSheet("QLabel{background:transparent;}");
    m_pSecGraphic->show();

    m_vSoftButtons.clear();
    m_lSoftButtons.clear();
    //top widget
    m_pTopWidget = new TopNavigateWidget(this);
    m_pTopWidget->SetReturnTitle(QString(""));
    m_pTopWidget->ShowBack();
    m_pTopWidget->ShowTitle();
    m_pTopWidget->ShowMenu();
    m_pTopWidget->show();
    connect(m_pTopWidget, SIGNAL(SigMenuClicked()), this, SLOT(BtnMenuClickedSlots()));
    connect(m_pTopWidget, SIGNAL(SigBackClicked()), this, SLOT(BtnBackClickedSlots()));
}

CDoubleGraphicSoftbuttonsShow::~CDoubleGraphicSoftbuttonsShow()
{

}

void CDoubleGraphicSoftbuttonsShow::SoftBtnClickedSlot(int iSoftBtnID) {
    if (iSoftBtnID >= 0) {
        AppControl->OnSoftButtonClick(iSoftBtnID, BUTTON_SHORT);
    }
}

void CDoubleGraphicSoftbuttonsShow::BtnMenuClickedSlots() {
    AppControl->OnShowCommand();
}

void CDoubleGraphicSoftbuttonsShow::BtnBackClickedSlots()
{
    INFO("CDoubleGraphicSoftbuttonsShow::BtnBackClickedSlots");
    SDLApps::Inst()->GetUIManager()->onAppShow(ID_APPLINK);
}
void CDoubleGraphicSoftbuttonsShow::SetAppName(QString strName) {
    m_pTopWidget->SetTitle(strName);
}

void CDoubleGraphicSoftbuttonsShow::DeleteButton(int index)
{
    CPushButton *button = m_lSoftButtons.at(index);
    m_lSoftButtons.removeAt(index);
    disconnect(button, SIGNAL(clicked(int)),
               this, SLOT(SoftBtnClickedSlot(int)));
    delete button;
}

void CDoubleGraphicSoftbuttonsShow::removeAllButton()
{
    QList<CPushButton*>::iterator it = m_lSoftButtons.begin();
    for(;it!=m_lSoftButtons.end();++it)
    {
       CPushButton *button = *it;
       m_lSoftButtons.erase(it);
       disconnect(button, SIGNAL(clicked(int)),
                  this, SLOT(SoftBtnClickedSlot(int)));
       delete button;
       button = NULL;

    }
}

void CDoubleGraphicSoftbuttonsShow::showEvent(QShowEvent *e) {
    Q_UNUSED(e);

    removeAllButton();

    if (AppControl) {
        SetAppName(AppControl->getAppName().c_str());

        rpcValueInterface &pObj = AppControl->getShowData();
        if (pObj.isNull())
            return;
        rpcValueInterface &jsonParams = pObj["params"];

        if (jsonParams.isMember("graphic")) {
            QUrl graphicUrl(jsonParams["graphic"]["value"].asString().c_str());
            if (graphicUrl.isEmpty()) {
                m_pGraphic->setPixmap(QPixmap(""));
            } else {
#if defined(WINCE)
                QString path = QString::fromStdString(ChangeSlash(graphicUrl.path().toLocal8Bit().data()));
#else
                QString path = QString::fromStdString(ChangeSlash(graphicUrl.path().toStdString()));
#endif
                m_pGraphic->setPixmap(QPixmap(path).scaled(204,204,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
            }
        } else {
            m_pGraphic->setPixmap(QPixmap(""));
        }


        if (jsonParams.isMember("secondaryGraphic")) {
            QUrl graphicUrl(jsonParams["secondaryGraphic"]["value"].asString().c_str());
            if (graphicUrl.isEmpty()) {
                m_pSecGraphic->setPixmap(QPixmap(""));
            } else {
#if defined(WINCE)
                QString path = QString::fromStdString(ChangeSlash(graphicUrl.path().toLocal8Bit().data()));
#else
                QString path = QString::fromStdString(ChangeSlash(graphicUrl.path().toStdString()));
#endif
                m_pSecGraphic->setPixmap(QPixmap(path).scaled(204,204,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
            }
        } else {
            m_pSecGraphic->setPixmap(QPixmap(""));
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


void CDoubleGraphicSoftbuttonsShow::setSoftButtons(std::vector<SSoftButton> vec_softButtons) {
    int iSize = vec_softButtons.size();
    for (int i = 0; i < iSize; ++i) {

        CPushButton *newbutton = new CPushButton(this);
        newbutton->SetEnableEffect(false);
        newbutton->setGeometry(m_btnLeft, m_btnTop  + (m_btnHeight + m_btnYSpace)* i,
                               m_btnWidth, m_btnHeight);

        newbutton->SetStatusStyle(QRect(0,0,m_btnWidth,m_btnHeight),":/SDLApps/Source/images/right_btn_normal.png",":/SDLApps/Source/images/right_btn_push.png",":/SDLApps/Source/images/right_btn_push.png");
        newbutton->SetText(QRect(0,0,m_btnWidth,m_btnHeight),QString::fromStdString(vec_softButtons[i].str_text),19,Qt::AlignCenter);
        newbutton->SetId(vec_softButtons[i].i_softButtonID);

        if (vec_softButtons[i].b_isHighlighted){
            newbutton->SetStatus(CPushButton::eStatus_Select);
        }
        connect(newbutton, SIGNAL(clicked(int)),SLOT(SoftBtnClickedSlot(int)));
        newbutton->show();
        m_lSoftButtons.insert(i, newbutton);
    }
}

