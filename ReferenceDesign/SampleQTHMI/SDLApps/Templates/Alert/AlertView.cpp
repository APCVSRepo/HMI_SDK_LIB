#include "AlertView.h"
#include <QBoxLayout>
#include "HMIFrameWork/log_interface.h"
#include <QSettings>
#include <QApplication>
#define SOFTBTNWIDTH 120
#define SOFTBTNHEIGHT 50
#define CApplicationDirPath QApplication::applicationDirPath()


//TODO: move this view to Popup

AlertView::AlertView(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_aletIconPath("")
    ,m_pList(pList)
    ,m_pBackground(NULL)
    ,m_pLineTop(NULL)
    ,m_pLineBottom(NULL)
    ,m_pAlertIcon(NULL)
    ,m_pPopUpArea(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    m_pPopUpArea = new QWidget(this);
    if(parent)
    {
        m_pPopUpArea->setGeometry(parent->width()/6,parent->height()/6,2*parent->width()/3,2*parent->height()/3);
    }
    else
    {
        m_pPopUpArea->setGeometry(800/6,440/6,2*800/3,2*440/3);
    }

    QVBoxLayout *pMainLayout = new QVBoxLayout(m_pPopUpArea);
    QVBoxLayout *pCenterLayout = new QVBoxLayout;
    QHBoxLayout *pBottomLayout = new QHBoxLayout;

    m_pAppNameLab = new QLabel;

    pMainLayout->addWidget(m_pAppNameLab,0,Qt::AlignCenter);
    pMainLayout->addLayout(pCenterLayout, 1);
    pMainLayout->addLayout(pBottomLayout);
    pMainLayout->setContentsMargins(5, 26, 5, 26);

    pCenterLayout->setContentsMargins(m_pPopUpArea->width() * 0.05,0,m_pPopUpArea->width() * 0.05,0);
    pCenterLayout->addStretch(1);
    for (int i = 0; i != 3; ++i) {
        pCenterLayout->addWidget(m_aAlertLab + i,0,Qt::AlignCenter);
    }
    pCenterLayout->addStretch(1);

    m_pAppNameLab->setStyleSheet("font: 36px;color:rgb(255,255,255)");
    m_pAppNameLab->setAlignment(Qt::AlignCenter);

    for (int i = 0; i != 3; ++i) {
        m_aAlertLab[i].setStyleSheet("font: 24px;color:rgb(255,255,255)");
        m_aAlertLab[i].setAlignment(Qt::AlignCenter);
    }

    connect(&m_Timer, SIGNAL(timeout()), this, SLOT(OnTimeOut()));

    //softButton
    m_vSoftButtons.clear();

    for (int i = 0; i < MAX_BTN_NUM; ++i) {
        pBottomLayout->addWidget(m_aSoftBtn + i,0,Qt::AlignCenter);
        m_aSoftBtn[i].setSize(0, 0);
        m_aSoftBtn[i].setTextStyle("border:0px; font:20px; color:rgb(255,255,255)");
        m_aSoftBtn[i].SetPadding(10,0,10,0);
        //set softBtnId
        m_aSoftBtn[i].setId(-1);
        connect(&m_aSoftBtn[i], SIGNAL(clicked(int)), this, SLOT(OnSoftBtnClicked(int)));
    }

    m_pLineTop = new QLabel(this);
    m_pLineTop->setPixmap(QPixmap(QString(":/SDLApps/Source/images/line_a.png")));
    m_pLineTop->setGeometry(0,m_pPopUpArea->y(),this->width(),3);
    m_pLineTop->show();
    m_pLineBottom = new QLabel(this);
    m_pLineBottom->setPixmap(QPixmap(QString(":/SDLApps/Source/images/line_a.png")));
    m_pLineBottom->setGeometry(0,m_pPopUpArea->y()+m_pPopUpArea->height()-3,this->width(),3);
    m_pLineBottom->show();

    m_pAlertIcon = new QLabel(this);
    m_pAlertIcon->setGeometry(QRect(100,m_pPopUpArea->y()+20,64,64));
    m_pAlertIcon->setStyleSheet("QLabel{background:transparent;}");
    m_pAlertIcon->hide();

    QSettings settings("hmi.ini", QSettings::IniFormat);
    m_aletIconPath = settings.value("HMI/AlertIconStorageFolder").toString();

    m_aletIconPath = CApplicationDirPath + "/" + m_aletIconPath;

    INFO("alert icon path is %s",m_aletIconPath.toStdString().c_str());
}

AlertView::~AlertView() {
    delete m_pAppNameLab;
}

void AlertView::OnSoftBtnClicked(int iSoftBtnID) {
    m_Timer.stop();
    AppControl->OnAlertResponse(RESULT_SUCCESS);
    if (iSoftBtnID >= 0) {
        AppControl->OnSoftButtonClick(iSoftBtnID, RESULT_SUCCESS);
    } else if (-1 == iSoftBtnID) {
        m_Timer.stop();
        AppControl->OnAlertResponse(RESULT_SUCCESS);
    }
}

void AlertView::OnTimeOut() {
    m_Timer.stop();
    AppControl->OnAlertResponse(RESULT_SUCCESS);
}

void AlertView::setSoftButtons(std::vector<SSoftButton> vec_softButtons)
{
    int iSize = vec_softButtons.size() > MAX_BTN_NUM ? MAX_BTN_NUM : vec_softButtons.size();
    for (int i = 0; i < iSize; ++i) {
        m_aSoftBtn[i].initParameter(131, 32, ":/SDLApps/Source/images/button_a.png", ":/SDLApps/Source/images/button_a_push.png", "", vec_softButtons[i].str_text.c_str());
        m_aSoftBtn[i].setId(vec_softButtons[i].i_softButtonID);

        if (vec_softButtons[i].b_isHighlighted){
            m_aSoftBtn[i].changeToPressed();
        }
        m_aSoftBtn[i].show();
    }
}

void AlertView::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    int iCount = 0;
    if (AppControl) {
        AppBase::SetEdlidedText(m_pAppNameLab, AppControl->getAppName().c_str(),
                                m_pPopUpArea->width() * 0.9);

        // 获取 Alert画面Rpc数据接口
        rpcValueInterface &pObj = AppControl->getAlertJson();

        for (int i = 0; i != 3; ++i) {
            m_aAlertLab[i].setText("");
        }

        for (int i = 0; i < MAX_BTN_NUM; ++i) {
            m_aSoftBtn[i].setText("");
            m_aSoftBtn[i].hide();
        }

        // 判断alertStrings字段是否存在
        if (pObj["params"].isMember("alertStrings")) {
            // 获取alertStrings字段数组类型元素个数
            iCount = pObj["params"]["alertStrings"].size() >
                    3 ? 3 : pObj["params"]["alertStrings"].size();
            for (int i = 0; i < iCount; ++i) {
                // 获取alertStrings每个元素中fieldText对应的数值
                AppBase::SetEdlidedText(m_aAlertLab+i,
                                        pObj["params"]["alertStrings"][i]["fieldText"].asString().c_str(),
                        m_pPopUpArea->width()*0.9);
            }
        }
        //alertIcon
        if (pObj["params"].isMember("alertIcon")) {
            // 获取alertStrings字段数组类型元素个数
            INFO("alert icon path is %s",m_aletIconPath.toStdString().c_str());

            std::string icon = pObj["params"]["alertIcon"]["value"].asString();
            QString iconPath = QString::fromStdString(icon);
            if(pObj["params"]["alertIcon"]["imageType"].asString() == "STATIC")
            {
                //add static path for icon

                iconPath  = m_aletIconPath + "/" + iconPath;
            }
            m_pAlertIcon->setPixmap(QPixmap(iconPath));
            m_pAlertIcon->show();
        }else
        {
            m_pAlertIcon->hide();
        }

        m_vSoftButtons.clear();
        if (pObj["params"].isMember("softButtons")) {

            m_Timer.start(pObj["params"]["duration"].asInt() + 20000);
            for (unsigned int i = 0; i < pObj["params"]["softButtons"].size(); ++i) {
                SSoftButton tmpSoftButton;
                tmpSoftButton.i_softButtonID = pObj["params"]["softButtons"][i]["softButtonID"].asInt();
                tmpSoftButton.str_text = pObj["params"]["softButtons"][i]["text"].asString();
                m_vSoftButtons.push_back(tmpSoftButton);
            }
        } else {
            // 获取duration字段值并转换为整型
            m_Timer.start(pObj["params"]["duration"].asInt());
        }
        setSoftButtons(m_vSoftButtons);
    }
}

void AlertView::hideEvent(QHideEvent *) {
    if (m_Timer.isActive())
        m_Timer.stop();
}


