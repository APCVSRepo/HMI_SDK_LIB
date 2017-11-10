#include "ChoiceSet.h"
#include <QBoxLayout>
#include "Common/AppBase.h"


#define LISTW 740
#define LISTH 280

CChoiceSet::CChoiceSet(AppListInterface *pList, QWidget *parent) :
  QWidget(parent), m_iInteractionMode(BOTH), m_pListView(NULL) {
  if (parent) {
    setGeometry(0, 0, parent->width(), parent->height());
  }
  m_pList = pList;

  setAutoFillBackground(true);
  QPixmap pixmap(":/images/MainWidget/Backgroud.png");
  pixmap = pixmap.scaled(width(), height(), Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation);
  QPalette palette;
  palette.setBrush(QPalette::Background, QBrush(pixmap));
  setPalette(palette);

  m_pMainLayout = new QVBoxLayout(this);
  m_pTopLayout = new QHBoxLayout;

  m_pReturnBtn = new CCustomButton;
  m_pInitText = new QLabel;
  m_pInitEdit = new QLineEdit;
  m_pTopText = m_pInitText;
  m_pListView = new CustomListView(LISTW, LISTH);

  m_pReturnBtn->Init(55, 45, "", ":images/ReturnBtnNormal.png",
                     ":images/ReturnBtnPress.png");

  m_pInitText->setStyleSheet("font: 36px \"Liberation Serif\";color:rgb(0,0,0)");
  m_pInitEdit->setStyleSheet("font: 36px \"Liberation Serif\";color:rgb(0,0,0)");

  m_pMainLayout->addLayout(m_pTopLayout, 1);
  m_pMainLayout->addWidget(m_pListView);
  m_pTopLayout->addWidget(m_pReturnBtn);
  m_pTopLayout->addWidget(m_pTopText, 1);

  m_pTimer = new QTimer;
  connect(m_pTimer, SIGNAL(timeout()), SLOT(OnTimeOut()));
  connect(m_pInitEdit, SIGNAL(textChanged(QString)),
          SLOT(OnEditChanged(QString)));
  connect(m_pReturnBtn, SIGNAL(Clicked()),
          SLOT(OnReturnBtnClicked()));


  m_pChoiceVR = new CChoiceSetVR(this);
  connect(m_pChoiceVR, SIGNAL(pressed()), SLOT(OnChoiceVRPressed()));
  m_pChoiceVR->hide();
}

CChoiceSet::~CChoiceSet() {
  delete m_pReturnBtn;
  delete m_pInitText;
  delete m_pInitEdit;
  if (m_pListView) {
    delete m_pListView;
  }
  delete m_pTimer;
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


    m_pMainLayout->removeWidget(m_pListView);
    delete m_pListView;
    m_pTopLayout->removeWidget(m_pTopText);
    m_pTopText->hide();

    std::string strLayout = "DEFAULT";
    if (jsonChoice.isMember("interactionLayout"))
      strLayout = jsonChoice["interactionLayout"].asString();

    if (strcmp(strLayout.c_str(), "LIST_ONLY") == 0) {
      m_pListView = new CustomListView(LISTW, LISTH, CustomListView::LIST);
      m_pTopText = m_pInitText;
    } else if (strcmp(strLayout.c_str(), "ICON_ONLY") == 0) {
      m_pListView = new CustomListView(LISTW, LISTH, CustomListView::ICON);
      m_pTopText = m_pInitText;
    } else if (strcmp(strLayout.c_str(), "LIST_WITH_SEARCH") == 0) {
      m_pListView = new CustomListView(LISTW, LISTH, CustomListView::LIST);
      m_pTopText = m_pInitEdit;
    } else if (strcmp(strLayout.c_str(), "ICON_WITH_SEARCH") == 0) {
      m_pListView = new CustomListView(LISTW, LISTH, CustomListView::ICON);
      m_pTopText = m_pInitEdit;
    }
    // Bug #9701
    else {
      m_pListView = new CustomListView(LISTW, LISTH, CustomListView::ICON);
      m_pTopText = m_pInitText;
    }
    m_pMainLayout->addWidget(m_pListView);
    m_pTopLayout->addWidget(m_pTopText, 1);
    m_pTopText->show();
    connect(m_pListView, SIGNAL(ItemClicked(int)), SLOT(OnListItemClicked(int)));


    if (jsonChoice.isMember("initialText")) {
      AppBase::SetEdlidedText(m_pInitText,
                              jsonChoice["initialText"]["fieldText"].asString().c_str(),
                              width() * 0.7);
      AppBase::SetEdlidedText(m_pInitEdit,
                              jsonChoice["initialText"]["fieldText"].asString().c_str(),
                              width() * 0.7);
    }

    if (jsonChoice.isMember("timeout")) {
      //setTimeOut(jsonChoice["timeout"].asInt());
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
      m_pTopText->hide();
    }
  }
}

void CChoiceSet::hideEvent(QHideEvent *) {
  if (m_pTimer->isActive())
    m_pTimer->stop();
}

void CChoiceSet::OnTimeOut() {
  m_pTimer->stop();
  m_pChoiceVR->hide();
  AppControl->OnPerformInteraction(PERFORMINTERACTION_TIMEOUT, 0, true);
  AppControl->OnPerformInteraction(PERFORMINTERACTION_TIMEOUT, 0);
}

void CChoiceSet::OnListItemClicked(int iChoiceId) {
  m_pTimer->stop();
  AppControl->OnPerformInteraction(PERFORMINTERACTION_CHOICE, iChoiceId);
}

void CChoiceSet::OnEditChanged(QString strkey) {
#if defined(WINCE)
  m_pListView->ItemFilter(strkey.toLocal8Bit().data());
#else
  m_pListView->ItemFilter(strkey.toStdString());
#endif
}

void CChoiceSet::OnReturnBtnClicked() {
  m_pTimer->stop();
  AppControl->OnPerformInteraction(RESULT_ABORTED, 0);
}

void CChoiceSet::OnChoiceVRPressed() {
  m_pChoiceVR->hide();
  if (VR_ONLY == m_iInteractionMode) {
    m_pTimer->stop();
    // Bug #9676
    AppControl->OnPerformInteraction(PERFORMINTERACTION_TIMEOUT, 0, true);
    AppControl->OnPerformInteraction(RESULT_ABORTED, 0);
  } else {
    AppControl->OnPerformInteraction(PERFORMINTERACTION_TIMEOUT, 0, true);
    m_pTopText->show();
    m_pListView->show();
  }
}
