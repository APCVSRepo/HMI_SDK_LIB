#include "ChoiceSet.h"
#include <QBoxLayout>
#include "SDLApps/Templates/Common/AppBase.h"
#include "HMIFrameWork/log_interface.h"

#define LISTW 800
#define LISTH 337

CChoiceSet::CChoiceSet(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_iInteractionMode(BOTH)
    ,m_pList(pList)
    ,m_pInitEdit(NULL)
    ,m_bEditable(false)
    ,m_pListView(NULL)
    ,m_pChoiceVR(NULL)
    ,m_pTimer(NULL)
    ,m_pBackground(NULL)
    ,m_pReturnBtn(NULL)
    ,m_pBackIcon(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), SLOT(OnTimeOut()));

    m_pChoiceVR = new CChoiceSetVR(this);
    connect(m_pChoiceVR, SIGNAL(released()), SLOT(OnChoiceVRClicked()));
    m_pChoiceVR->hide();

    //Return
    m_pReturnBtn = new CPushButton(this);
    m_pReturnBtn->setGeometry(0,0,53,70);
    m_pReturnBtn->setStyleSheet("QPushButton{border:none;background:transparent;}");
    m_pReturnBtn->setFocusPolicy(Qt::NoFocus);
    m_pReturnBtn->show();

    m_pBackIcon = new QLabel(m_pReturnBtn);
    m_pBackIcon->setPixmap(QPixmap(QString(":/SDLApps/Source/images/back.png")));
    m_pBackIcon->setGeometry(23,62-40,15,27);

    connect(m_pReturnBtn, SIGNAL(clicked()), this, SLOT(OnReturnBtnClicked()));

    //InitEdit
    m_pInitEdit = new QLineEdit(this);
    m_pInitEdit->setStyleSheet("QLineEdit{font: 22px;color:#bbffffff;background-color:#2d2d2d;border:none;padding:0 8px}");
    m_pInitEdit->setGeometry(54,10,223+354,50);
    m_pInitEdit->setFocusPolicy(Qt::ClickFocus);
    connect(m_pInitEdit, SIGNAL(textChanged(QString)), this, SLOT(OnEditChanged(QString)));
    this->SetEditable(false);
}

CChoiceSet::~CChoiceSet() {

}

void CChoiceSet::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    if (AppControl) {
        rpcValueInterface &jsonData = AppControl->getInteractionJson();
        rpcValueInterface &jsonChoice = jsonData["Choiceset"]["params"];

        if (jsonChoice.isMember("interactionLayout") && jsonChoice.isMember("vrHelp")) {
            m_iInteractionMode = BOTH;
        } else if (jsonChoice.isMember("interactionLayout")) {
            m_iInteractionMode = MANUAL_ONLY;
        } else if (jsonChoice.isMember("vrHelp")) {
            m_iInteractionMode = VR_ONLY;
        }

        delete m_pListView;
        m_pListView = NULL;

        std::string strLayout = "DEFAULT";
        if (jsonChoice.isMember("interactionLayout"))
            strLayout = jsonChoice["interactionLayout"].asString();

        if (strcmp(strLayout.c_str(), "LIST_ONLY") == 0) {
            m_pListView = new CustomListView(LISTW, LISTH, CustomListView::LIST, this);
            this->SetEditable(false);
        } else if (strcmp(strLayout.c_str(), "ICON_ONLY") == 0) {
            m_pListView = new CustomListView(LISTW, LISTH, CustomListView::ICON, this);
            this->SetEditable(false);
        } else if (strcmp(strLayout.c_str(), "LIST_WITH_SEARCH") == 0) {
            m_pListView = new CustomListView(LISTW, LISTH, CustomListView::LIST, this);
            this->SetEditable(true);
        } else if (strcmp(strLayout.c_str(), "ICON_WITH_SEARCH") == 0) {
            m_pListView = new CustomListView(LISTW, LISTH, CustomListView::ICON, this);
            this->SetEditable(true);
        }
        // Bug #9701
        else {
            m_pListView = new CustomListView(LISTW, LISTH, CustomListView::ICON, this);
            this->SetEditable(false);
        }
        m_pListView->move(0,77);
        connect(m_pListView, SIGNAL(ItemClicked(int)), this, SLOT(OnListItemClicked(int)));

        if (jsonChoice.isMember("timeout")) {
            m_pTimer->start(jsonChoice["timeout"].asInt());
        }

        if (jsonChoice.isMember("choiceSet")) {
            for (unsigned int i = 0; i < jsonChoice["choiceSet"].size(); ++i) {
                if (m_pListView) {
                    if (jsonChoice["choiceSet"][i].isMember("image"))
                        m_pListView->AddItem(
                                    jsonChoice["choiceSet"][i]["menuName"].asString(),
                                jsonChoice["choiceSet"][i]["choiceID"].asInt(),
                                jsonChoice["choiceSet"][i]["image"]["value"].asString());
                    else
                        m_pListView->AddItem(
                                    jsonChoice["choiceSet"][i]["menuName"].asString(),
                                jsonChoice["choiceSet"][i]["choiceID"].asInt());
                }
            }
        }

        if (jsonChoice.isMember("initialText")) {
            AppBase::SetEdlidedText(m_pInitEdit,
                                    jsonChoice["initialText"]["fieldText"].asString().c_str(),
                    560);
        }
        else
        {
            m_pInitEdit->setText("");
        }

        if (jsonChoice.isMember("vrHelpTitle")) {
            m_pChoiceVR->SetTitle(jsonChoice["vrHelpTitle"].asString());
        }

        if (jsonChoice.isMember("vrHelp")) {
            for (unsigned int i = 0; i < jsonChoice["vrHelp"].size(); ++i) {
                m_pChoiceVR->SetChoice(
                            jsonChoice["vrHelp"][i]["position"].asInt() - 1,
                        jsonChoice["vrHelp"][i]["text"].asString());
            }
            m_pChoiceVR->show();
            if (m_pListView) {
                m_pListView->hide();
            }
            m_pReturnBtn->hide();
            m_pInitEdit->hide();
        }
        else
        {
            m_pListView->show();
            m_pReturnBtn->show();
            m_pInitEdit->show();
        }
    }
}

void CChoiceSet::hideEvent(QHideEvent *) {
    if (m_pTimer->isActive())
        m_pTimer->stop();
}

void CChoiceSet::OnTimeOut() {
    INFO("CChoiceSet::OnTimeOut");
    m_pTimer->stop();
    m_pChoiceVR->hide();
    AppControl->OnPerformInteraction(PERFORMINTERACTION_TIMEOUT, 0, true);
    AppControl->OnPerformInteraction(PERFORMINTERACTION_TIMEOUT, 0);
}

void CChoiceSet::OnListItemClicked(int iChoiceId) {
    INFO("CChoiceSet::OnListItemClicked");
    m_pTimer->stop();
    AppControl->OnPerformInteraction(PERFORMINTERACTION_CHOICE, iChoiceId);
}

void CChoiceSet::OnEditChanged(QString strkey) {
    INFO("CChoiceSet::OnEditChanged");
    if(!m_bEditable)
    {
        INFO("CChoiceSet::OnEditChanged: Not editable, return");
        return;
    }

    if(m_pListView)
    {
#if defined(WINCE)
        m_pListView->ItemFilter(strkey.toLocal8Bit().data());
#else
        m_pListView->ItemFilter(strkey.toStdString());
#endif
    }
}

void CChoiceSet::SetEditable(bool editable)
{
    m_bEditable = editable;
    INFO("SetEditable: %d", m_bEditable);
    if(editable)
    {
        m_pInitEdit->setReadOnly(false);
        m_pInitEdit->setStyleSheet("QLineEdit{font: 22px;color:#bbffffff;background-color:#2d2d2d;border:none;padding:0 8px}");
    }
    else
    {
        m_pInitEdit->setReadOnly(true);
        m_pInitEdit->setStyleSheet("QLineEdit{font: 22px;color:#bbffffff;background:transparent;border:none;padding:0 8px}");
    }
}

void CChoiceSet::OnReturnBtnClicked() {
    INFO("CChoiceSet::OnReturnBtnClicked");
    m_pTimer->stop();
    AppControl->OnPerformInteraction(RESULT_ABORTED, 0);
}

void CChoiceSet::OnChoiceVRClicked() {
    INFO("CChoiceSet::OnChoiceVRClicked");
    m_pChoiceVR->hide();
    if (VR_ONLY == m_iInteractionMode) {
        m_pTimer->stop();
        // Bug #9676
        AppControl->OnPerformInteraction(PERFORMINTERACTION_TIMEOUT, 0, true);
        AppControl->OnPerformInteraction(RESULT_ABORTED, 0);
    } else {
        AppControl->OnPerformInteraction(PERFORMINTERACTION_TIMEOUT, 0, true);
        m_pInitEdit->show();
        m_pReturnBtn->show();
        if(m_pListView)
        {
            m_pListView->show();
        }
    }
}
