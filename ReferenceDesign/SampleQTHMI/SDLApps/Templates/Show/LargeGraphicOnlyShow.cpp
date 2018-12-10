#include "LargeGraphicOnlyShow.h"
#include <QUrl>
#include "HMIFrameWork/log_interface.h"
#include "SDLApps/app/SDLApps.h"
#include "HMIFrameWork/HMIFrameWork.h"

#define MUSICPICWIDTH 185
#define CMD_PREV 109
#define CMD_START 1022
#define CMD_PAUSE 1025
#define CMD_NEXT 112

CLargeGraphicOnlyShow::CLargeGraphicOnlyShow(AppListInterface *pList, QWidget *parent)
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
    ,m_pTopWidget(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    //Graphic
    m_pGraphicFrame = new QLabel(this);
    m_pGraphicFrame->setGeometry(233,90,321,321);
    m_pGraphicFrame->setStyleSheet("QLabel{border-image:url(:/SDLApps/Source/images/KUANG_321.png);background:transparent;}");
    m_pGraphicFrame->show();


    m_pGraphic = new QLabel(this);
    m_pGraphic->setGeometry(237,94,313,313);
    m_pGraphic->setStyleSheet("QLabel{background:transparent;}");
    m_pGraphic->show();

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

CLargeGraphicOnlyShow::~CLargeGraphicOnlyShow()
{

}

void CLargeGraphicOnlyShow::BtnMenuClickedSlots() {
    AppControl->OnShowCommand();
}

void CLargeGraphicOnlyShow::BtnBackClickedSlots()
{
    SDLApps::Inst()->GetUIManager()->onAppShow(ID_APPLINK);
}

void CLargeGraphicOnlyShow::SetAppName(QString strName) {
    m_pTopWidget->SetTitle(strName);
}

void CLargeGraphicOnlyShow::showEvent(QShowEvent *e) {
    Q_UNUSED(e);

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
    }
}


