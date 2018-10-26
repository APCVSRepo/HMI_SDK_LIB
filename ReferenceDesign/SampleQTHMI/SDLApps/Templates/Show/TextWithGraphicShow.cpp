#include "TextWithGraphicShow.h"
#include <QUrl>
#include "SDLApps/Templates/Config/Config.h"
#include "SDLApps/app/SDLApps.h"
#include "HMIFrameWork/log_interface.h"

#define MUSICPICWIDTH 770
#define MUSICPICHEIGHT 210

CTextWithGraphicShow::CTextWithGraphicShow(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_pList(pList)
    ,m_pTopWidget(NULL)
    ,m_pFrameLab(NULL)
    ,m_pMusicPicLab(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    //top widget
    m_pTopWidget = new TopNavigateWidget(this);
    m_pTopWidget->SetReturnTitle(QString(""));
    m_pTopWidget->ShowTitle();
    m_pTopWidget->ShowMenu();
    m_pTopWidget->show();
    connect(m_pTopWidget, SIGNAL(SigMenuClicked()), this, SLOT(BtnMenuClickedSlots()));
    connect(m_pTopWidget, SIGNAL(SigBackClicked()), this, SLOT(BtnBackClickedSlots()));

    //textfield
    m_aShowLine[0].setParent(this);
    m_aShowLine[0].setStyleSheet("border:0px;font: 26px;color:#74767E");
    m_aShowLine[0].setGeometry(82,103,380,60);
    m_aShowLine[0].setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_aShowLine[0].show();

    m_aShowLine[1].setParent(this);
    m_aShowLine[1].setStyleSheet("border:0px;font: 26px;color:#74767E");
    m_aShowLine[1].setGeometry(82,163,380,60);
    m_aShowLine[1].setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    m_aShowLine[2].setParent(this);
    m_aShowLine[2].setStyleSheet("border:0px;font: 26px;color:#74767E");
    m_aShowLine[2].setGeometry(82,223,380,60);
    m_aShowLine[2].setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    //graphic
    m_pFrameLab = new QLabel(this);
    m_pFrameLab->setGeometry(QRect(82+380+39,118,218,218));
    m_pFrameLab->setStyleSheet("QLabel{border-image:url(:/SDLApps/Source/images/KUANG_218.png);background:transparent;}");
    m_pFrameLab->show();

    m_pMusicPicLab = new QLabel(this);
    m_pMusicPicLab->setGeometry(82+380+39+4,122,210,210);
    m_pMusicPicLab->setStyleSheet("background:transparent");
}

void CTextWithGraphicShow::BtnMenuClickedSlots() {
    AppControl->OnShowCommand();
}

void CTextWithGraphicShow::BtnBackClickedSlots()
{
    INFO("CTextWithGraphicShow::BtnBackClickedSlots");
    SDLApps::Inst()->GetUIManager()->onAppShow(ID_APPLINK);
}

void CTextWithGraphicShow::SetAppName(QString strName) {
    m_pTopWidget->SetTitle(strName);
}

void CTextWithGraphicShow::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    for (int i = 0; i < SHOW_LINE_NUM; ++i) {
        m_aShowLine[i].setText(" ");
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
                // Bug #9671
                if ("mainField1" == fieldName["fieldName"].asString()) {
                    AppBase::SetEdlidedText(m_aShowLine, fieldName["fieldText"].asString().c_str(), m_aShowLine[0].width(), alignMode);
                } else if ("mainField2" == fieldName["fieldName"].asString()) {
                    AppBase::SetEdlidedText(m_aShowLine + 1, fieldName["fieldText"].asString().c_str(), m_aShowLine[1].width(), alignMode);
                } else if ("mainField3" == fieldName["fieldName"].asString()) {
                    AppBase::SetEdlidedText(m_aShowLine + 2, fieldName["fieldText"].asString().c_str(), m_aShowLine[2].width(), alignMode);
                } /*else if ("mainField4" == fieldName["fieldName"].asString()) {
          AppBase::SetEdlidedText(m_aShowLine + 3, fieldName["fieldText"].asString().c_str(), m_aShowLine[3].width(), alignMode);
        } else if ("mediaTrack" == fieldName["fieldName"].asString()) {
          AppBase::SetEdlidedText(m_aShowLine + 4, fieldName["fieldText"].asString().c_str(), m_aShowLine[4].width(), alignMode);
        } else if ("mediaClock" == fieldName["fieldName"].asString()) {
          //该字段暂未使用
          //AppBase::SetEdlidedText(m_pTimeRemainLab,fieldName["fieldText"].asString().c_str(),width()*0.3);
        }*/
            }
        }
    }
}

