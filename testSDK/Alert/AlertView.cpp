#include "AlertView.h"
#include <QBoxLayout>

#define SOFTBTNWIDTH 120
#define SOFTBTNHEIGHT 50

AlertView::AlertView(AppListInterface * pList, QWidget *parent)
    : QWidget(parent)
{
    if (parent) {
        setGeometry(0,0,parent->width(),parent->height());
    }
    m_pList = pList;

    setAutoFillBackground(true);
    QPixmap pixmap(":/images/choicevr_back.png");
    pixmap = pixmap.scaled(width(),height(), Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    setPalette(palette);

    QVBoxLayout *pMainLayout = new QVBoxLayout(this);
    QVBoxLayout *pCenterLayout = new QVBoxLayout;
    QHBoxLayout *pBottomLayout = new QHBoxLayout;

    m_pAppNameLab = new QLabel;

    pMainLayout->addWidget(m_pAppNameLab);
    pMainLayout->addLayout(pCenterLayout,1);
    pMainLayout->addLayout(pBottomLayout);
    pMainLayout->setContentsMargins(5,5,5,20);

    pCenterLayout->addStretch(1);
    for (int i = 0;i != 3;++i) {
        pCenterLayout->addWidget(m_aAlertLab + i);
    }
    pCenterLayout->addStretch(1);

    pBottomLayout->addStretch(1);
    for (int i = 0;i != 6;++i) {
        pBottomLayout->addWidget(m_aSoftBtn + i);
    }
    pBottomLayout->addStretch(1);

    m_pAppNameLab->setStyleSheet("font: 36px \"Liberation Serif\";color:rgb(0,0,0)");
    m_pAppNameLab->setAlignment(Qt::AlignCenter);

    for (int i = 0; i != 3; ++i) {
        m_aAlertLab[i].setStyleSheet("font: 32px \"Liberation Serif\";color:rgb(0,0,0)");
        m_aAlertLab[i].setAlignment(Qt::AlignCenter);
    }

    for (int i = 0; i != 6; ++i) {
        m_aSoftBtn[i].SetSize(0,0);
        m_aSoftBtn[i].SetTextStyle("font: 32px \"Liberation Serif\";color:rgb(0,0,0)");
        connect(m_aSoftBtn + i,SIGNAL(Clicked(int)),
                this,SLOT(OnSoftBtnClicked(int)));
    }

    connect(&m_Timer,SIGNAL(timeout()),this,SLOT(OnTimeOut()));
}

AlertView::~AlertView()
{
    delete m_pAppNameLab;
}

void AlertView::OnSoftBtnClicked(int iSoftBtnID)
{
    m_Timer.stop();
    AppControl->OnAlertResponse(RESULT_SUCCESS);
    if (iSoftBtnID != 0) {
        AppControl->OnSoftButtonClick(iSoftBtnID,RESULT_SUCCESS);
    }
}

void AlertView::OnTimeOut()
{
    m_Timer.stop();
    AppControl->OnAlertResponse(RESULT_SUCCESS);
}

void AlertView::showEvent(QShowEvent * e)
{
    int iCount = 0;
    if (AppControl) {
        AppBase::SetEdlidedText(m_pAppNameLab,AppControl->getAppName().c_str(),
                                width()*0.9);

        rpcValueInterface& pObj = AppControl->getAlertJson();

        for (int i = 0;i != 3;++i) {
            m_aAlertLab[i].setText("");
        }

        for (int i = 0;i != 6;++i) {
            m_aSoftBtn[i].SetSize(0,0);
            m_aSoftBtn[i].SetText("");
        }


        if (pObj["params"].isMember("alertStrings")) {
            iCount = pObj["params"]["alertStrings"].size() >
                    3 ? 3 : pObj["params"]["alertStrings"].size();
            for (int i = 0; i < iCount; ++i) {
                AppBase::SetEdlidedText(m_aAlertLab+i,
                        pObj["params"]["alertStrings"][i]["fieldText"].asString().c_str(),
                        width()*0.9);
            }
        }

        if (pObj["params"].isMember("softButtons")) {
            m_Timer.start(pObj["params"]["duration"].asInt() + 20000);
            iCount = pObj["params"]["softButtons"].size() >
                    6 ? 6 : pObj["params"]["softButtons"].size();

            for (int i = 0; i < iCount; ++i) {
                m_aSoftBtn[i].Init(SOFTBTNWIDTH,SOFTBTNHEIGHT,"",
                                   ":/images/alert_softbtn_normal.png",
                                   ":/images/alert_softbtn_press.png");
                m_aSoftBtn[i].SetText(pObj["params"]["softButtons"][i]["text"].asString().c_str());
                m_aSoftBtn[i].SetId(pObj["params"]["softButtons"][i]["softButtonID"].asInt());
            }
        } else {
            m_Timer.start(pObj["params"]["duration"].asInt());
        }
    }
}


