#include "TilesWithGraphicShow.h"
#include <QUrl>
#include "HMIFrameWork/log_interface.h"
#include "SDLApps/app/SDLApps.h"
#include "HMIFrameWork/HMIFrameWork.h"

#define MUSICPICWIDTH 185
#define CMD_PREV 109
#define CMD_START 1022
#define CMD_PAUSE 1025
#define CMD_NEXT 112

CTilesWithGraphicShow::CTilesWithGraphicShow(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_pList(pList)
    ,m_btnWidth(150)
    ,m_btnHeight(150)
    ,m_btnTop(90)
    ,m_btnLeft(55)
    ,m_btnXSpace(29)
    ,m_btnYSpace(22)
    ,m_pGraphicFrame(NULL)
    ,m_pGraphic(NULL)
    ,m_pRightArea(NULL)
    ,m_pTopWidget(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    //Graphic
    m_pGraphicFrame = new QLabel(this);
    m_pGraphicFrame->setGeometry(415,90,321,321);
    m_pGraphicFrame->setStyleSheet("QLabel{border-image:url(:/SDLApps/Source/images/KUANG_321.png);background:transparent;}");
    m_pGraphicFrame->show();

    m_pGraphic = new QLabel(this);
    m_pGraphic->setGeometry(419,94,313,313);
    m_pGraphic->setStyleSheet("QLabel{background:transparent;}");
    m_pGraphic->show();

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

CTilesWithGraphicShow::~CTilesWithGraphicShow()
{

}

void CTilesWithGraphicShow::SoftBtnClickedSlot(int iSoftBtnID) {
    if (iSoftBtnID >= 0) {
        AppControl->OnSoftButtonClick(iSoftBtnID, BUTTON_SHORT);
    }
}

void CTilesWithGraphicShow::BtnMenuClickedSlots() {
    AppControl->OnShowCommand();
}

void CTilesWithGraphicShow::BtnBackClickedSlots()
{
    INFO("CTilesWithGraphicShow::BtnBackClickedSlots");
    SDLApps::Inst()->GetUIManager()->onAppShow(ID_APPLINK);
}
void CTilesWithGraphicShow::SetAppName(QString strName) {
    m_pTopWidget->SetTitle(strName);
}

void CTilesWithGraphicShow::DeleteButton(int index)
{
    CPushButton *button = m_lSoftButtons.at(index);
    m_lSoftButtons.removeAt(index);
    disconnect(button, SIGNAL(clicked(int)),
               this, SLOT(SoftBtnClickedSlot(int)));
    delete button;
}

void CTilesWithGraphicShow::removeAllButton()
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

void CTilesWithGraphicShow::showEvent(QShowEvent *e) {
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
                m_pGraphic->setPixmap(QPixmap(path).scaled(313,313,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
            }
        } else {
            m_pGraphic->setPixmap(QPixmap(""));
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


void CTilesWithGraphicShow::setSoftButtons(std::vector<SSoftButton> vec_softButtons) {
    int iSize = vec_softButtons.size();
    for (int i = 0; i < iSize; ++i) {

        CPushButton *newbutton = new CPushButton(this);
        newbutton->SetEnableEffect(false);
        int r = i / 2;
        int c = i % 2;
        newbutton->setGeometry((m_btnWidth +m_btnXSpace)* c + m_btnLeft, m_btnTop + (m_btnHeight + m_btnYSpace)* r,
                               m_btnWidth, m_btnHeight);

        newbutton->SetStatusStyle(QRect(0,0,m_btnWidth,m_btnHeight),":/SDLApps/Source/images/146_he.png",":/SDLApps/Source/images/146_he_P.png",":/SDLApps/Source/images/146_he_P.png");
        newbutton->SetText(QRect(0,m_btnHeight-36,m_btnWidth,28),QString::fromStdString(vec_softButtons[i].str_text),19);
        newbutton->SetId(vec_softButtons[i].i_softButtonID);

        if (vec_softButtons[i].b_isHighlighted){
            newbutton->SetStatus(CPushButton::eStatus_Select);
        }
        connect(newbutton, SIGNAL(clicked(int)),SLOT(SoftBtnClickedSlot(int)));
        newbutton->show();
        m_lSoftButtons.insert(i, newbutton);
    }
}

