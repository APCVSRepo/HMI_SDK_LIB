#include "TextButtonsOnlyShow.h"
#include <QUrl>
#include "HMIFrameWork/log_interface.h"
#include "SDLApps/app/SDLApps.h"
#include "HMIFrameWork/HMIFrameWork.h"

#define MUSICPICWIDTH 185
#define CMD_PREV 109
#define CMD_START 1022
#define CMD_PAUSE 1025
#define CMD_NEXT 112

CTextButtonsOnlyShow::CTextButtonsOnlyShow(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_pList(pList)
    ,m_btnWidth(320)
    ,m_btnHeight(45)
    ,m_btnTop(90)
    ,m_btnLeft(55)
    ,m_btnXSpace(29)
    ,m_btnYSpace(62)
    ,m_pRightArea(NULL)
    ,m_pTopWidget(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

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

CTextButtonsOnlyShow::~CTextButtonsOnlyShow()
{

}

void CTextButtonsOnlyShow::SoftBtnClickedSlot(int iSoftBtnID) {
    if (iSoftBtnID >= 0) {
        AppControl->OnSoftButtonClick(iSoftBtnID, BUTTON_SHORT);
    }
}

void CTextButtonsOnlyShow::BtnMenuClickedSlots() {
    AppControl->OnShowCommand();
}

void CTextButtonsOnlyShow::BtnBackClickedSlots()
{
    INFO("CTextButtonsOnlyShow::BtnBackClickedSlots");
    SDLApps::Inst()->GetUIManager()->onAppShow(ID_APPLINK);
}
void CTextButtonsOnlyShow::SetAppName(QString strName) {
    m_pTopWidget->SetTitle(strName);
}

void CTextButtonsOnlyShow::DeleteButton(int index)
{
    CPushButton *button = m_lSoftButtons.at(index);
    m_lSoftButtons.removeAt(index);
    disconnect(button, SIGNAL(clicked(int)),
               this, SLOT(SoftBtnClickedSlot(int)));
    delete button;
}

void CTextButtonsOnlyShow::removeAllButton()
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

void CTextButtonsOnlyShow::showEvent(QShowEvent *e) {
    Q_UNUSED(e);

    removeAllButton();

    if (AppControl) {
        SetAppName(AppControl->getAppName().c_str());

        rpcValueInterface &pObj = AppControl->getShowData();
        if (pObj.isNull())
            return;
        rpcValueInterface &jsonParams = pObj["params"];
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


void CTextButtonsOnlyShow::setSoftButtons(std::vector<SSoftButton> vec_softButtons) {
    int iSize = vec_softButtons.size();
    for (int i = 0; i < iSize; ++i) {

        CPushButton *newbutton = new CPushButton(this);
        newbutton->SetEnableEffect(false);
        newbutton->setGeometry(m_btnLeft, m_btnTop + (m_btnHeight + m_btnYSpace)* i,
                               m_btnWidth, m_btnHeight);

        newbutton->SetStatusStyle(QRect(0,0,m_btnWidth,m_btnHeight),":/SDLApps/Source/images/button_320.png",":/SDLApps/Source/images/button_320_P.png",":/SDLApps/Source/images/button_320_P.png");
        newbutton->SetText(QRect(0,0,m_btnWidth,m_btnHeight),QString::fromStdString(vec_softButtons[i].str_text),18,Qt::AlignCenter);
        newbutton->SetId(vec_softButtons[i].i_softButtonID);

        if (vec_softButtons[i].b_isHighlighted){
            newbutton->SetStatus(CPushButton::eStatus_Select);
        }
        connect(newbutton, SIGNAL(clicked(int)),SLOT(SoftBtnClickedSlot(int)));
        newbutton->show();
        m_lSoftButtons.insert(i, newbutton);
    }
}

