#include "MainWidget.h"
#include "Config/Config.h"

#define MARGIN 10

MainWidget::MainWidget(AppListInterface *pList, QWidget *parent)
  : QWidget(parent) {
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

  QVBoxLayout *pTopLayout = new QVBoxLayout;
  pTopLayout->setSpacing(1);
  pTopLayout->setMargin(MARGIN);
  m_pAppNameLab = new QLabel;
  pTopLayout->addWidget(m_pAppNameLab, 0, Qt::AlignLeft);
  m_pAppNameLab->setStyleSheet(QString("font: 60 40px \"Liberation Serif\";color:rgb(0,0,0);border: 0px"));


  //m_pShowLine = new QLabel[4];
  for (int i = 0; i != 4; ++i) {
    pTopLayout->addWidget(m_pShowLine + i, 0, Qt::AlignLeft);
    m_pShowLine[i].setStyleSheet("border:0px;font: 14px \"Liberation Serif\";color:rgb(0,0,0)");
  }

  QHBoxLayout *pCenterLayout = new QHBoxLayout;
  m_pIconLab = new QLabel;
  m_pMainTitleLab = new QLabel;
  pCenterLayout->addStretch(1);
  pCenterLayout->addWidget(m_pIconLab);
  pCenterLayout->addWidget(m_pMainTitleLab);
  pCenterLayout->addStretch(1);
  m_pMainTitleLab->setStyleSheet(QString("font: 60 35pt \"Liberation Serif\";color:rgb(0,0,0);border: 0px"));
  m_pMainTitleLab->setText("SmartDeviceLink");
  QPixmap IconPixmap(":/images/MainWidget/AppIcon.png");
  IconPixmap = IconPixmap.scaled(80, 80, Qt::IgnoreAspectRatio,
                                 Qt::SmoothTransformation);
  m_pIconLab->setPixmap(IconPixmap);
  m_pIconLab->setStyleSheet("background:transparent;background-image: none");

  QVBoxLayout *pBottomLayout = new QVBoxLayout;
  QHBoxLayout *pBtnLayout = new QHBoxLayout;
  pBtnLayout->setSpacing(0);
  pBtnLayout->setMargin(MARGIN);
  m_pMenuBtn = new CButton;
  m_pMenuBtn->initParameter(ui_btn_width, ui_btn_height, ":/images/MainWidget/BtnNormal.png", ":/images/MainWidget/BtnPress.png", "", "-");
  m_pMenuBtn->setTextStyle("border:0px;font: 36px \"Liberation Serif\";color:rgb(0,0,0)");
  m_pMenuBtn->SetLeftIcon(":/images/MainWidget/MenuIcon.png");
  //m_pSoftBtn = new CButton[3];
  pBtnLayout->addWidget(m_pMenuBtn, 0, Qt::AlignLeft);
  pBottomLayout->addStretch(1);
  pBottomLayout->addLayout(pBtnLayout);

  for (int i = 0; i != 3; ++i) {
    pBtnLayout->addWidget(&m_pSoftBtn[i], 0, Qt::AlignLeft);
    m_pSoftBtn[i].initParameter(ui_btn_width, ui_btn_height, ":/images/MainWidget/BtnNormal.png", ":/images/MainWidget/BtnPress.png", "", "-");
    m_pSoftBtn[i].setTextStyle("border:0px;font: 36px \"Liberation Serif\";color:rgb(0,0,0)");
  }
  pBtnLayout->addStretch(1);

  m_pMainLayout->addLayout(pTopLayout, 1);
  m_pMainLayout->addLayout(pCenterLayout);
  m_pMainLayout->addLayout(pBottomLayout, 1);

  m_pMenuBtn->setText("Menu");
  for (int i = 0; i != 3; ++i) {
    m_pSoftBtn[i].setText("-");
    connect(&m_pSoftBtn[i], SIGNAL(clicked(int)),
            this, SLOT(SoftBtnClickedSlot(int)));
  }

  connect(m_pMenuBtn, SIGNAL(clicked()),
          this, SLOT(BtnMenuClickedSlots()));
}

MainWidget::~MainWidget() {
  /*
  delete []m_pShowLine;

  delete m_pMainLayout;
  delete m_pAppNameLab;
  delete m_pIconLab;
  delete m_pMainTitleLab;

  delete []m_pSoftBtn;
  */
}

void MainWidget::SetAppName(QString strName) {
  AppBase::SetEdlidedText(m_pAppNameLab, strName, width() * 0.9);
}

void MainWidget::BtnMenuClickedSlots() {
  m_pList->getActiveApp()->OnShowCommand();
}

void MainWidget::SoftBtnClickedSlot(int iSoftBtnID) {
  if (iSoftBtnID != 0) {
    m_pList->getActiveApp()->OnSoftButtonClick(iSoftBtnID, 1);
  }
}

void MainWidget::setSoftButtons(std::vector<SSoftButton> vec_softButtons) {
  int iBtnCount = vec_softButtons.size() > 3 ? 3 : vec_softButtons.size();
  for (int i = 0; i != iBtnCount; ++i) {
    m_pSoftBtn[i].setText(vec_softButtons[i].str_text.c_str());
    m_pSoftBtn[i].setId(vec_softButtons[i].i_softButtonID);
  }
}

void MainWidget::showEvent(QShowEvent *e) {
  for (int i = 0; i != 4; ++i) {
    m_pShowLine[i].setText("");
  }
  for (int i = 0; i != 3; ++i) {
    m_pSoftBtn[i].setText("-");
  }

  std::vector <SSoftButton > vec_softButtons;
  vec_softButtons.clear();
  if (m_pList->getActiveApp()) {
    SetAppName(m_pList->getActiveApp()->getAppName().c_str());

    rpcValueInterface &pObj = m_pList->getActiveApp()->getShowData();
    if (pObj.isNull())
      return;
    rpcValueInterface &jsonParams = pObj["params"];

    for (unsigned int i = 0; i < jsonParams["showStrings"].size(); ++i) {
      rpcValueInterface  &fieldName = jsonParams["showStrings"][i];
      if ("mainField1" == fieldName["fieldName"].asString()) {
        AppBase::SetEdlidedText(m_pShowLine, fieldName["fieldText"].asString().c_str(), width() * 0.9);
      } else if ("mainField2" == fieldName["fieldName"].asString()) {
        AppBase::SetEdlidedText(m_pShowLine + 1, fieldName["fieldText"].asString().c_str(), width() * 0.9);
      } else if ("mainField3" == fieldName["fieldName"].asString()) {
        AppBase::SetEdlidedText(m_pShowLine + 2, fieldName["fieldText"].asString().c_str(), width() * 0.9);
      } else if ("mainField4" == fieldName["fieldName"].asString()) {
        AppBase::SetEdlidedText(m_pShowLine + 3, fieldName["fieldText"].asString().c_str(), width() * 0.9);
      }
    }

    if (jsonParams.isMember("softButtons")) {
      for (int i = 0; i < jsonParams["softButtons"].size(); ++i) {
        SSoftButton tmpSoftButton;
        tmpSoftButton.b_isHighlighted = jsonParams["softButtons"][i]["isHighlighted"].asBool();
        tmpSoftButton.i_softButtonID = jsonParams["softButtons"][i]["softButtonID"].asInt();
        tmpSoftButton.str_text = jsonParams["softButtons"][i]["text"].asString();
        vec_softButtons.push_back(tmpSoftButton);
      }
      setSoftButtons(vec_softButtons);
    }
  }
}
