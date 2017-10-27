#include "MediaShow.h"
#include <QUrl>

#define MUSICPICWIDTH 185
#define CMD_PREV 109
#define CMD_START 1022
#define CMD_PAUSE 1025
#define CMD_NEXT 112

CMediaShow::CMediaShow(AppListInterface *pList, QWidget *parent)
  : QWidget(parent) {
  if (parent) {
    setGeometry(0, 0, parent->width(), parent->height());
  }

  m_timerId = 0;
  m_pList = pList;
  m_bDelayShowMedia = false;

  setAutoFillBackground(true);
  QPixmap pixmap(":/images/MainWidget/Backgroud.png");
  pixmap = pixmap.scaled(width(), height(), Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation);
  QPalette palette;
  palette.setBrush(QPalette::Background, QBrush(pixmap));
  setPalette(palette);

  const int iTopLayoutHeight = height() * 0.15;


  QVBoxLayout *pMainLayout = new QVBoxLayout(this);
  QHBoxLayout *pTopLayout = new QHBoxLayout;
  QHBoxLayout *pCenterLayout = new QHBoxLayout;
  QHBoxLayout *pBottomLayout = new QHBoxLayout;
  QVBoxLayout *pLeftCenterLayout = new QVBoxLayout;
  QHBoxLayout *pTimeShowLayout = new QHBoxLayout;
  QVBoxLayout *pStringsLayout = new QVBoxLayout;
  QVBoxLayout *pBottomCenterLayout = new QVBoxLayout;
  m_pBtnLayout = new QHBoxLayout;

  m_pSourceBtn = new CCustomButton;
  m_pAppNameLab = new QLabel;
  m_pMenuBtn = new CCustomButton;
  m_pTimeElapseLab = new QLabel;
  m_pTimeRemainLab = new QLabel;
  m_pMusicPB = new QProgressBar;
  m_pMusicPicLab = new QLabel;
  m_pShadowLab = new QLabel;

  pMainLayout->addLayout(pTopLayout);
  pMainLayout->addLayout(pCenterLayout, 1);
  pMainLayout->addLayout(pBottomLayout);
  pMainLayout->setContentsMargins(10, 20, 10, 10);
  pMainLayout->setSpacing(0);

  pTopLayout->addWidget(m_pSourceBtn);
  pTopLayout->addWidget(m_pAppNameLab, 1);
  pTopLayout->addWidget(m_pMenuBtn);
  pTopLayout->setSpacing(5);

  pCenterLayout->addLayout(pLeftCenterLayout, 1);
  pCenterLayout->addWidget(m_pMusicPicLab);
  //pCenterLayout->setContentsMargins(0,10,0,0);

  pLeftCenterLayout->addLayout(pTimeShowLayout);
  m_pMusicPB->setParent(this);
  m_pMusicPB->setGeometry(10, 110, 510, 14);
  //pLeftCenterLayout->addWidget(m_pMusicPB);
  pLeftCenterLayout->addLayout(pStringsLayout);
  pStringsLayout->setContentsMargins(0, 32, 0, 10);
  for (int i = 0; i != 5; ++i) {
    pStringsLayout->addWidget(m_aShowLine + i);
    m_aShowLine[i].setStyleSheet("border:0px;font: 20px \"Liberation Serif\";color:rgb(0,0,0)");
    m_aShowLine[i].setFixedHeight(27);
  }
  //pLeftCenterLayout->addStretch(1);
  pLeftCenterLayout->setContentsMargins(0, 10, 65, 10);

  pTimeShowLayout->addWidget(m_pTimeElapseLab);
  pTimeShowLayout->addStretch(1);
  pTimeShowLayout->addWidget(m_pTimeRemainLab);
  pTimeShowLayout->setContentsMargins(0, 0, 0, 5);

  //pBottomLayout->addStretch(1);
  pBottomLayout->addLayout(pBottomCenterLayout);
  pBottomLayout->addStretch(1);
  pBottomLayout->setSpacing(0);
  pBottomCenterLayout->addLayout(m_pBtnLayout);
  pBottomCenterLayout->addWidget(m_pShadowLab);
  pBottomCenterLayout->addStretch(1);

  m_vSoftButtons.clear();

  for (int i = 0; i != 6; ++i) {
    m_pBtnLayout->addWidget(m_aSoftBtn + i);
    m_aSoftBtn[i].setSize(0, 0);
    m_aSoftBtn[i].setTextStyle("border:0px;font: 28px \"Liberation Serif\";color:rgb(0,0,0)");

    if (i != 5) {
      m_pBtnLayout->addWidget(m_aSplit + i);
      m_aSplit[i].setStyleSheet("max-height:0px;max-width:0px;border-image:url(:/images/MediaShow/split.png)");
      //m_aSplit[i].hide();
    }
  }

  m_pSourceBtn->Init(250, iTopLayoutHeight, "来源", ":images/MediaShow/source_normal.png");
  m_pSourceBtn->SetTextStyle("font: 28px \"Liberation Serif\";color:rgb(0,0,0)");
  m_pSourceBtn->SetPadding(0, 0, 0, 5);

  m_pAppNameLab->setStyleSheet("background:transparent;font:28px \"Liberation Serif\";color:rgb(0,0,0)");

  m_pMenuBtn->Init(185, iTopLayoutHeight, "菜单", ":/images/MediaShow/menu_normal.png", ":/images/MediaShow/menu_press.png");
  m_pMenuBtn->SetTextStyle("border:0px;font: 28px \"Liberation Serif\";color:rgb(0,0,0)");
  m_pMenuBtn->SetPadding(0, 0, 0, 5);

  m_pTimeElapseLab->setStyleSheet("border:0px;font: 20px \"Liberation Serif\";color:rgb(0,0,0)");
  m_pTimeRemainLab->setStyleSheet("border:0px;font: 20px \"Liberation Serif\";color:rgb(0,0,0)");

  m_pMusicPB->setStyleSheet("QProgressBar{height:14px;border-color:rgb(240,240,240)}\
                              QProgressBar::chunk{width:0.5px;background-color:rgb(8,79,130)}");
  m_pMusicPB->setTextVisible(false);
  m_pMusicPB->hide();

  m_pMusicPicLab->setMinimumSize(MUSICPICWIDTH, MUSICPICWIDTH);
  m_pMusicPicLab->setMaximumSize(MUSICPICWIDTH, MUSICPICWIDTH);
  m_pMusicPicLab->setStyleSheet("background:transparent");

  m_aSoftBtn[6].setParent(this);
  m_aSoftBtn[7].setParent(this);
  m_aSoftBtn[8].setParent(this);
  m_aSoftBtn[6].setGeometry(width() * 0.5 - 155, height() * 0.65 - 40, 80, 80);
  m_aSoftBtn[6].initParameter(80, 80, ":/images/MediaShow/backward_normal.png", ":/images/MediaShow/backward_press.png", "", "");
  m_aSoftBtn[6].setStyleSheet("background:transparent");
  m_aSoftBtn[7].setGeometry(width() * 0.5 - 55, height() * 0.65 - 55, 110, 110);
  m_aSoftBtn[7].initParameter(110, 110, ":/images/MediaShow/play_normal.png", ":/images/MediaShow/play_press.png", "", "");
  m_aSoftBtn[7].setStyleSheet("background:transparent");
  m_aSoftBtn[8].setGeometry(width() * 0.5 + 75, height() * 0.65 - 40, 80, 80);
  m_aSoftBtn[8].initParameter(80, 80, ":/images/MediaShow/forward_normal.png", ":/images/MediaShow/forward_press.png", "", "");
  m_aSoftBtn[8].setStyleSheet("background:transparent");

  //set softBtnId
  for (int i = 0; i != 6; ++i) {
    m_aSoftBtn[i].setId(0);
  }
  m_aSoftBtn[6].setId(CMD_PREV);
  m_aSoftBtn[8].setId(CMD_NEXT);
  m_aSoftBtn[6].SetCustomName("SEEKLEFT");
  m_aSoftBtn[7].SetCustomName("OK");
  m_aSoftBtn[8].SetCustomName("SEEKRIGHT");
  SetPlayBtnID(false);

  for (int i = 0; i != 6; ++i) {
    connect(&m_aSoftBtn[i], SIGNAL(clicked(int)), this, SLOT(SoftBtnClickedSlot(int)));
  }
  connect(m_aSoftBtn + 6, SIGNAL(clicked(int, std::string)), this, SLOT(SoftBtnClickedSlot(int, std::string)));
  connect(m_aSoftBtn + 7, SIGNAL(clicked(int, std::string)), this, SLOT(SoftBtnClickedSlot(int, std::string)));
  connect(m_aSoftBtn + 8, SIGNAL(clicked(int, std::string)), this, SLOT(SoftBtnClickedSlot(int, std::string)));
  connect(m_pMenuBtn, SIGNAL(Clicked()), this, SLOT(BtnMenuClickedSlots()));

  connect(this, SIGNAL(startMediaClock(bool)), SLOT(mediaClockSlots(bool)));
}

void CMediaShow::SoftBtnClickedSlot(int iSoftBtnID, std::string strName) {
  AppControl->OnSoftButtonClick(iSoftBtnID, BUTTON_SHORT, strName);
}

void CMediaShow::SoftBtnClickedSlot(int iSoftBtnID) {
  if (iSoftBtnID != 0) {
    AppControl->OnSoftButtonClick(iSoftBtnID, BUTTON_SHORT);
  }
}

void CMediaShow::BtnMenuClickedSlots() {
  m_pList->getActiveApp()->OnShowCommand();
}

void CMediaShow::SetAppName(QString strName) {
  AppBase::SetEdlidedText(m_pAppNameLab, strName, width() * 0.5);
}

void CMediaShow::showEvent(QShowEvent *e) {
  Q_UNUSED(e);
  for (int i = 0; i != 9; ++i) {
    m_aSoftBtn[i].setText("");
  }

//  for (int i = 0; i != 5; ++i) {
//    m_aShowLine[i].setText(" ");
//  }

  m_pTimeElapseLab->setText(" ");
  m_pTimeRemainLab->setText(" ");

  if (m_pList->getActiveApp()) {
    m_pSourceBtn->SetLeftIcon(m_pList->getActiveApp()->getAppIconFile());
    SetAppName(m_pList->getActiveApp()->getAppName().c_str());

    rpcValueInterface &pObj = m_pList->getActiveApp()->getShowData();
    if (pObj.isNull())
      return;
    rpcValueInterface &jsonParams = pObj["params"];

    // Bug #9671
    Qt::AlignmentFlag alignMode =  Qt::AlignLeft;
    if (jsonParams.isMember("alignment")) {
      std::string align = jsonParams["alignment"].asString();
      if ("RIGHT_ALIGNED" == align) {
        alignMode = Qt::AlignRight;
      } else if ("CENTERED" == align) {
        alignMode = Qt::AlignHCenter;
      }
    }
    for (unsigned int i = 0; i < jsonParams["showStrings"].size(); ++i) {
      rpcValueInterface  &fieldName = jsonParams["showStrings"][i];
      // Bug #9671
      if ("mainField1" == fieldName["fieldName"].asString()) {
        AppBase::SetEdlidedText(m_aShowLine, fieldName["fieldText"].asString().c_str(), width() * 0.3, alignMode);
      } else if ("mainField2" == fieldName["fieldName"].asString()) {
        AppBase::SetEdlidedText(m_aShowLine + 1, fieldName["fieldText"].asString().c_str(), width() * 0.3, alignMode);
      } else if ("mainField3" == fieldName["fieldName"].asString()) {
        AppBase::SetEdlidedText(m_aShowLine + 2, fieldName["fieldText"].asString().c_str(), width() * 0.3, alignMode);
      } else if ("mainField4" == fieldName["fieldName"].asString()) {
        AppBase::SetEdlidedText(m_aShowLine + 3, fieldName["fieldText"].asString().c_str(), width() * 0.3, alignMode);
      } else if ("mediaTrack" == fieldName["fieldName"].asString()) {
        AppBase::SetEdlidedText(m_aShowLine + 4, fieldName["fieldText"].asString().c_str(), width() * 0.3, alignMode);
      } else if ("mediaClock" == fieldName["fieldName"].asString()) {
        //AppBase::SetEdlidedText(m_pTimeRemainLab,fieldName["fieldText"].asString().c_str(),width()*0.3);
      }
    }

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
    } else {
      m_pMusicPicLab->setStyleSheet("background:transparent");
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

  if (m_bDelayShowMedia)
    UpdateMediaColckTimer();
}

void CMediaShow::setSoftButtons(std::vector<SSoftButton> vec_softButtons) {
  for (int i = 0; i != 6; ++i) {
    m_aSoftBtn[i].setSize(0, 0);

    if (i < 5) {
      m_aSplit[i].setStyleSheet("max-width:0px;border-image:url(:/images/MediaShow/split.png)");
    }
  }

  if (vec_softButtons.size() == 1) {
    m_aSoftBtn[0].initParameter(125, 50, ":/images/MediaShow/center_normal.png", ":/images/MediaShow/center_press.png", "", vec_softButtons[0].str_text.c_str());
    m_aSoftBtn[0].setId(vec_softButtons[0].i_softButtonID);
    if (vec_softButtons[0].b_isHighlighted)
      m_aSoftBtn[0].changeToPressed();
  } else {
    int iSize = vec_softButtons.size() > 6 ? 6 : vec_softButtons.size();
    for (int i = 0; i != iSize; ++i) {
      if (i == 0) {
        m_aSoftBtn[i].initParameter(125, 50, ":/images/MediaShow/left_normal.png", ":/images/MediaShow/left_press.png", "", vec_softButtons[i].str_text.c_str());
      } else if (i == iSize - 1) {
        m_aSoftBtn[i].initParameter(125, 50, ":/images/MediaShow/right_normal.png", ":/images/MediaShow/right_press.png", "", vec_softButtons[i].str_text.c_str());
      } else {
        m_aSoftBtn[i].initParameter(125, 50, ":/images/MediaShow/center_normal.png", ":/images/MediaShow/center_press.png", "", vec_softButtons[i].str_text.c_str());
      }
      m_aSoftBtn[i].setId(vec_softButtons[i].i_softButtonID);

      if (vec_softButtons[i].b_isHighlighted)
        m_aSoftBtn[i].changeToPressed();

      if (i < iSize - 1) {
        m_aSplit[i].setStyleSheet("max-width:1px;border-image:url(:/images/MediaShow/split.png)");
      }
    }
  }
}

void CMediaShow::UpdateMediaColckTimer(bool bDelay) {
  if (bDelay) {
    m_bDelayShowMedia = true;
    return;
  }

  m_bDelayShowMedia = false;

  rpcValueInterface &jsonObj = AppControl->getMediaClockJson();

  m_i_startH = jsonObj["params"]["startTime"]["hours"].asInt();
  m_i_startM = jsonObj["params"]["startTime"]["minutes"].asInt();
  m_i_startS = jsonObj["params"]["startTime"]["seconds"].asInt();
  if (jsonObj["params"].isMember("endTime")) {
    m_i_endH = jsonObj["params"]["endTime"]["hours"].asInt();
    m_i_endM = jsonObj["params"]["endTime"]["minutes"].asInt();
    m_i_endS = jsonObj["params"]["endTime"]["seconds"].asInt();

    m_pMusicPB->show();
  } else {
    m_i_endH = m_i_endM = m_i_endS = -1;

    m_pMusicPB->hide();
  }

  m_MediaClockEndTime.setHMS(m_i_endH, m_i_endM, m_i_endS);

  if (jsonObj["params"]["updateMode"].asString() == "COUNTUP") {
    if (nowMeidaClockTime.setHMS(m_i_startH, m_i_startM, m_i_startS)) {
      m_b_countup = true;
      emit startMediaClock(true);
      AppControl->OnSetMediaClockTimerResponse(RESULT_SUCCESS);
    } else {
      emit startMediaClock(false);
      AppControl->OnSetMediaClockTimerResponse(RESULT_DATA_NOT_AVAILABLE);
    }
  } else if (jsonObj["params"]["updateMode"].asString() == "COUNTDOWN") {
    if (nowMeidaClockTime.setHMS(m_i_startH, m_i_startM, m_i_startS)) {
      m_b_countup = false;
      emit startMediaClock(true);
      AppControl->OnSetMediaClockTimerResponse(RESULT_SUCCESS);
    } else {
      emit startMediaClock(false);
      AppControl->OnSetMediaClockTimerResponse(RESULT_DATA_NOT_AVAILABLE);
    }
  } else if (jsonObj["params"]["updateMode"].asString() == "PAUSE") {
    emit startMediaClock(false);
    AppControl->OnSetMediaClockTimerResponse(RESULT_SUCCESS);
  } else if (jsonObj["params"]["updateMode"].asString() == "RESUME") {
    emit startMediaClock(true);
    AppControl->OnSetMediaClockTimerResponse(RESULT_SUCCESS);
  } else if (jsonObj["params"]["updateMode"].asString() == "CLEAR") {
    emit startMediaClock(false);
    setMediaClock(" ", " ");
    m_pMusicPB->hide();
    AppControl->OnSetMediaClockTimerResponse(RESULT_SUCCESS);
  }
}

void CMediaShow::mediaClockSlots(bool isStart) {
  if (isStart) {
    if (m_timerId != 0)
      this->killTimer(m_timerId);
    m_timerId = this->startTimer(1000);

    if (-1 != m_i_endH || -1 != m_i_endM || -1 != m_i_endS) {
      m_pMusicPB->setRange(0, m_i_endH * 3600 + m_i_endM * 60 + m_i_endS);
      m_pMusicPB->setValue(m_i_startH * 3600 + m_i_startM * 60 + m_i_startS);
    }
  } else {
    if (m_timerId != 0)
      this->killTimer(m_timerId);
  }

  SetPlayBtnID(isStart);
}

void CMediaShow::timerEvent(QTimerEvent *e) {
  Q_UNUSED(e);
  if (m_b_countup) {
    nowMeidaClockTime = nowMeidaClockTime.addSecs(1);
  } else {
    nowMeidaClockTime = nowMeidaClockTime.addSecs(-1);
  }

  if (-1 == m_i_endH && -1 == m_i_endM && -1 == m_i_endS) {
    setMediaClock(nowMeidaClockTime.toString("HH:mm:ss"), "");
    return;
  }

  m_pMusicPB->setValue(nowMeidaClockTime.hour() * 3600 +
                       nowMeidaClockTime.minute() * 60 +
                       nowMeidaClockTime.second());
  m_pMusicPB->update();

  if (nowMeidaClockTime.hour() == m_i_endH
      && nowMeidaClockTime.minute() == m_i_endM
      && nowMeidaClockTime.second() == m_i_endS) {
    SetPlayBtnID(false);
    this->killTimer(m_timerId);
  }

  int iRemain = m_MediaClockEndTime.secsTo(nowMeidaClockTime);
  iRemain = 0 - iRemain;
  int iHour = iRemain / 3600;
  iRemain = iRemain % 3600;
  int iMinute = iRemain / 60;
  int iSecond = iRemain % 60;
  QTime timeRemain;
  timeRemain.setHMS(iHour, iMinute, iSecond);

  setMediaClock(nowMeidaClockTime.toString("HH:mm:ss"), "-" + timeRemain.toString("HH:mm:ss"));
}

void CMediaShow::setMediaClock(QString strElapseTime, QString strRemainTime) {
  AppBase::SetEdlidedText(m_pTimeElapseLab, strElapseTime, width() * 0.3);
  AppBase::SetEdlidedText(m_pTimeRemainLab, strRemainTime, width() * 0.3);
}

void CMediaShow::SetPlayBtnID(bool bPlay) {
  if (bPlay) {
    m_aSoftBtn[7].setId(CMD_PAUSE);
  } else {
    m_aSoftBtn[7].setId(CMD_START);
  }
}
