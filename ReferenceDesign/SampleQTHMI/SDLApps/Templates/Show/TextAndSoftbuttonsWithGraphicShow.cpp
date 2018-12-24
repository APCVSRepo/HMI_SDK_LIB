#include "TextAndSoftbuttonsWithGraphicShow.h"
#include <QUrl>
#include "HMIFrameWork/log_interface.h"
#include "SDLApps/app/SDLApps.h"
#include "HMIFrameWork/HMIFrameWork.h"

#define MUSICPICWIDTH 185
#define CMD_PREV 109
#define CMD_START 1022
#define CMD_PAUSE 1025
#define CMD_NEXT 112

CTextAndSoftbuttonsWithGraphicShow::CTextAndSoftbuttonsWithGraphicShow(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_pList(pList)
    ,m_btnWidth(150)
    ,m_btnHeight(150)
    ,m_btnTop(262)
    ,m_btnLeft(55)
    ,m_btnXSpace(29)
    ,m_btnYSpace(0)
    ,m_pGraphicFrame(NULL)
    ,m_pGraphic(NULL)
    ,m_pTopWidget(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    //Graphic
    m_pGraphicFrame = new QLabel(this);
    m_pGraphicFrame->setGeometry(435,90,321,321);
    m_pGraphicFrame->setStyleSheet("QLabel{border-image:url(:/SDLApps/Source/images/KUANG_321.png);background:transparent;}");
    m_pGraphicFrame->show();

    m_pGraphic = new QLabel(this);
    m_pGraphic->setGeometry(439,94,313,313);
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

    //textfield
    m_aShowLine[0].setParent(this);
    m_aShowLine[0].setStyleSheet("border:0px;font: 26px;color:#74767E");
    m_aShowLine[0].setGeometry(55,75,317,60);
    m_aShowLine[0].setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_aShowLine[0].show();

    m_aShowLine[1].setParent(this);
    m_aShowLine[1].setStyleSheet("border:0px;font: 26px;color:#74767E");
    m_aShowLine[1].setGeometry(55,135,317,60);
    m_aShowLine[1].setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    m_aShowLine[2].setParent(this);
    m_aShowLine[2].setStyleSheet("border:0px;font: 26px;color:#74767E");
    m_aShowLine[2].setGeometry(55,195,317,60);
    m_aShowLine[2].setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
}

CTextAndSoftbuttonsWithGraphicShow::~CTextAndSoftbuttonsWithGraphicShow()
{

}

void CTextAndSoftbuttonsWithGraphicShow::SoftBtnClickedSlot(int iSoftBtnID) {
    if (iSoftBtnID >= 0) {
        AppControl->OnSoftButtonClick(iSoftBtnID, BUTTON_SHORT);
    }
}

void CTextAndSoftbuttonsWithGraphicShow::BtnMenuClickedSlots() {
    AppControl->OnShowCommand();
}

void CTextAndSoftbuttonsWithGraphicShow::BtnBackClickedSlots()
{
     SDLApps::Inst()->GetUIManager()->onAppShow(ID_APPLINK);
}
void CTextAndSoftbuttonsWithGraphicShow::SetAppName(QString strName) {
    m_pTopWidget->SetTitle(strName);
}

void CTextAndSoftbuttonsWithGraphicShow::DeleteButton(int index)
{
    CPushButton *button = m_lSoftButtons.at(index);
    m_lSoftButtons.removeAt(index);
    disconnect(button, SIGNAL(clicked(int)),
               this, SLOT(SoftBtnClickedSlot(int)));
    delete button;
}

void CTextAndSoftbuttonsWithGraphicShow::removeAllButton()
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

void CTextAndSoftbuttonsWithGraphicShow::showEvent(QShowEvent *e) {
    Q_UNUSED(e);

    removeAllButton();

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
                m_pGraphic->setPixmap(QPixmap(""));
            } else {
#if defined(WINCE)
                QString path = QString::fromStdString(ChangeSlash(graphicUrl.path().toLocal8Bit().data()));
#else
                QString path = QString::fromStdString(ChangeSlash(graphicUrl.path().toStdString()));
#endif
                m_pGraphic->setPixmap(QPixmap(path).scaled(313,313,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));;
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


void CTextAndSoftbuttonsWithGraphicShow::setSoftButtons(std::vector<SSoftButton> vec_softButtons) {
    int iSize = vec_softButtons.size();
    iSize = iSize > 2? 2: iSize;
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

