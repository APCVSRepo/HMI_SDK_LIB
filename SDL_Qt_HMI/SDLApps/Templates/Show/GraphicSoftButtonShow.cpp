#include "GraphicSoftButtonShow.h"
#include <QUrl>

#define MUSICPICWIDTH 770
#define MUSICPICHEIGHT 210

CGraphicSoftButtonShow::CGraphicSoftButtonShow(AppListInterface *pList, QWidget *parent)
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

  QVBoxLayout *pMainLayout = new QVBoxLayout(this);
  QHBoxLayout *pTopLayout = new QHBoxLayout;
  QHBoxLayout *pCenterLayout = new QHBoxLayout;
  QHBoxLayout *pBottomLayout = new QHBoxLayout;
  QVBoxLayout *pBottomCenterLayout = new QVBoxLayout;
  m_pBtnLayout = new QHBoxLayout;

  m_pAppNameLab = new QLabel;
  m_pMenuBtn = new CCustomButton;
  m_pMusicPicLab = new QLabel;
  m_pShadowLab = new QLabel;

  pMainLayout->addLayout(pTopLayout);
  pMainLayout->addLayout(pCenterLayout, 1);
  pMainLayout->addLayout(pBottomLayout);
  pMainLayout->setContentsMargins(10, 20, 10, 10);
  pMainLayout->setSpacing(0);

  pTopLayout->addWidget(m_pAppNameLab);
  pTopLayout->setSpacing(5);

  pCenterLayout->addWidget(m_pMusicPicLab);
  pCenterLayout->setContentsMargins(5, 20, 5, 20);

  //pBottomLayout->addStretch(1);
  pBottomLayout->addLayout(pBottomCenterLayout);
  pBottomLayout->addStretch(1);
  pBottomLayout->setSpacing(0);
  pBottomCenterLayout->addLayout(m_pBtnLayout);
  pBottomCenterLayout->addWidget(m_pShadowLab);
  pBottomCenterLayout->addStretch(1);

  m_vSoftButtons.clear();

  m_pBtnLayout->addWidget(m_pMenuBtn);

  for (int i = 0; i != 5; ++i) {
    m_pBtnLayout->addWidget(m_aSplit + i);
    m_aSplit[i].setStyleSheet("max-height:0px;max-width:0px;border-image:url(:/images/MediaShow/split.png)");

    m_pBtnLayout->addWidget(m_aSoftBtn + i);
    m_aSoftBtn[i].setSize(0, 0);
    m_aSoftBtn[i].setTextStyle("border:0px;font: 28px \"Liberation Serif\";color:rgb(0,0,0)");
  }

  m_pAppNameLab->setStyleSheet("background:transparent;font:28px \"Liberation Serif\";color:rgb(0,0,0)");

  m_pMenuBtn->Init(125, 50, "菜单", ":/images/MediaShow/center_normal.png", ":/images/MediaShow/center_press.png");
  m_pMenuBtn->SetTextStyle("border:0px;font: 28px \"Liberation Serif\";color:rgb(0,0,0)");
  //m_pMenuBtn->SetPadding(0,0,0,5);

  m_pMusicPicLab->setMinimumSize(MUSICPICWIDTH, MUSICPICHEIGHT);
  m_pMusicPicLab->setMaximumSize(MUSICPICWIDTH, MUSICPICHEIGHT);
  m_pMusicPicLab->setStyleSheet("background:transparent");

  //set softBtnId
  for (int i = 0; i != 5; ++i) {
    m_aSoftBtn[i].setId(0);
    connect(&m_aSoftBtn[i], SIGNAL(clicked(int)), this, SLOT(SoftBtnClickedSlot(int)));
  }

  connect(m_pMenuBtn, SIGNAL(Clicked()), this, SLOT(BtnMenuClickedSlots()));
}

void CGraphicSoftButtonShow::SoftBtnClickedSlot(int iSoftBtnID) {
  if (iSoftBtnID != 0) {
    AppControl->OnSoftButtonClick(iSoftBtnID, BUTTON_SHORT);
  }
}

void CGraphicSoftButtonShow::BtnMenuClickedSlots() {
  AppControl->OnShowCommand();
}

void CGraphicSoftButtonShow::SetAppName(QString strName) {
  AppBase::SetEdlidedText(m_pAppNameLab, strName, width() * 0.5);
}

void CGraphicSoftButtonShow::showEvent(QShowEvent *e) {
  Q_UNUSED(e);
  for (int i = 0; i != 5; ++i) {
    m_aSoftBtn[i].setText("");
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

    m_vSoftButtons.clear();
    if (jsonParams.isMember("softButtons")) {
      for (unsigned int i = 0; i < jsonParams["softButtons"].size(); ++i) {
        SSoftButton tmpSoftButton;
        tmpSoftButton.b_isHighlighted = jsonParams["softButtons"][i]["isHighlighted"].asBool();
        tmpSoftButton.i_softButtonID = jsonParams["softButtons"][i]["softButtonID"].asInt();
        tmpSoftButton.str_text = jsonParams["softButtons"][i]["text"].asString();
        m_vSoftButtons.push_back(tmpSoftButton);
      }
      m_pShadowLab->setStyleSheet("max-height:6px;border-image:url(:/images/MediaShow/shadow.png)");
    } else {
      m_pShadowLab->setStyleSheet("background:transparent");
    }
    setSoftButtons(m_vSoftButtons);
  }
}

void CGraphicSoftButtonShow::setSoftButtons(std::vector<SSoftButton> vec_softButtons) {
  for (int i = 0; i != 5; ++i) {
    m_aSoftBtn[i].setSize(0, 0);
  }

  if (vec_softButtons.empty()) {
    m_pMenuBtn->Init(125, 50, "菜单", ":/images/MediaShow/center_normal.png", ":/images/MediaShow/center_press.png");
  } else {
    m_pMenuBtn->Init(125, 50, "菜单", ":/images/MediaShow/left_normal.png", ":/images/MediaShow/left_press.png");

    int iSize = vec_softButtons.size() > 5 ? 5 : vec_softButtons.size();
    for (int i = 0; i != iSize; ++i) {
      if (i == iSize - 1) {
        m_aSoftBtn[i].initParameter(125, 50, ":/images/MediaShow/right_normal.png", ":/images/MediaShow/right_press.png", "", vec_softButtons[i].str_text.c_str());
      } else {
        m_aSoftBtn[i].initParameter(125, 50, ":/images/MediaShow/center_normal.png", ":/images/MediaShow/center_press.png", "", vec_softButtons[i].str_text.c_str());
      }
      m_aSoftBtn[i].setId(vec_softButtons[i].i_softButtonID);

      if (vec_softButtons[i].b_isHighlighted)
        m_aSoftBtn[i].changeToPressed();

      if (i < iSize) {
        m_aSplit[i].setStyleSheet("max-width:1px;border-image:url(:/images/MediaShow/split.png)");
      }
    }
  }
}
