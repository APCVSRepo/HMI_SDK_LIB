#include "MediaShow.h"
#include <QUrl>
#include "HMIFrameWork/log_interface.h"
#include "SDLApps/app/SDLApps.h"
#include "HMIFrameWork/HMIFrameWork.h"

#define MUSICPICWIDTH 185
#define CMD_PREV 109
#define CMD_START 1022
#define CMD_PAUSE 1025
#define CMD_NEXT 112

CMediaShow::CMediaShow(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,m_pList(pList)
    ,m_timerId(0)
    ,m_MeidaClockCurrentTime()
    ,m_MediaClockEndTime()
    ,m_i_startH(0)
    ,m_i_startM(0)
    ,m_i_startS(0)
    ,m_i_endH(0)
    ,m_i_endM(0)
    ,m_i_endS(0)
    ,m_b_countup(false)
    ,m_pTimeElapseLab(NULL)
    ,m_pTimeRemainLab(NULL)
    ,m_pMusicPB(NULL)
    ,m_pBottomBackground(NULL)
    ,m_pAlbumCover(NULL)
    ,m_pSeekLeft(NULL)
    ,m_pPlayPause(NULL)
    ,m_pSeekRight(NULL)
    ,m_bPlaying(false)
    ,m_pRightArea(NULL)
    ,m_pTopWidget(NULL)
    ,m_pCircleMode(NULL)
    ,m_pShuffleMode(NULL)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

    m_pBottomBackground = new QLabel(this);
    m_pBottomBackground->setGeometry(0,480-40-90,800,90);
    m_pBottomBackground->setStyleSheet("QWidget{border-image:url(:/SDLApps/Source/images/btn_bg.png);background:transparent;}");
    m_pBottomBackground->show();

    //album
    m_pAlbumCover = new AlbumCoverWidget(this);
    m_pAlbumCover->setGeometry(80,59-40+33+2,262,262);
    m_pAlbumCover->setMask(QBitmap(QString(":/SDLApps/Source/images/mask.png")));
    m_pAlbumCover->setLight(QPixmap(QString(":/SDLApps/Source/images/light.png")));
    m_pAlbumCover->setAlbumCover(QPixmap(QString("")));
    m_pAlbumCover->setRotateDirection(CRotationWidget::ROTATE_ANTICLOCKWISE);

    //play/pause,pre/next
    m_pSeekLeft = new CPushButton(this);
    m_pSeekLeft->setStyleSheet("QPushButton{border-image:url(:/SDLApps/Source/images/the_last_song.png);background:transparent;}");
    m_pSeekLeft->setGeometry(QRect(110+80+45,397-40,80,80));
    m_pSeekLeft->setFocusPolicy(Qt::NoFocus);
    m_pSeekLeft->show();

    m_pPlayPause = new CPushButton(this);
    m_pPlayPause->setStyleSheet("QPushButton{border-image:url(:/SDLApps/Source/images/play.png);background:transparent;}");
    m_pPlayPause->setGeometry(QRect(110+80+45+80+45,397-40,80,80));
    m_pPlayPause->setFocusPolicy(Qt::NoFocus);
    m_pPlayPause->show();

    m_pSeekRight = new CPushButton(this);
    m_pSeekRight->setStyleSheet("QPushButton{border-image:url(:/SDLApps/Source/images/next_song.png);background:transparent;}");
    m_pSeekRight->setGeometry(QRect(110+80+45+80+45+80+45,397-40,80,80));
    m_pSeekRight->setFocusPolicy(Qt::NoFocus);
    m_pSeekRight->show();

    UpdatePlayPauseStatus(false);

    connect(m_pSeekLeft,SIGNAL(clicked()),this,SLOT(OnSeekLeftClicked()));
    connect(m_pPlayPause,SIGNAL(clicked()),this,SLOT(OnPlayPauseClicked()));
    connect(m_pSeekRight,SIGNAL(clicked()),this,SLOT(OnSeekRightClicked()));

    //right area
    m_pRightArea = new QWidget(this);
    m_pRightArea->setGeometry(800-116,75,116,(32+20)*5-20);

    QVBoxLayout *pRightLayout = new QVBoxLayout;
    pRightLayout->setSpacing(20);
    pRightLayout->setMargin(0);

    m_vSoftButtons.clear();

    for (int i = 0; i < RIGHT_BTN_NUM; ++i) {
        pRightLayout->addWidget(m_aSoftBtn + i, 0, Qt::AlignTop);
        m_aSoftBtn[i].setSize(116, 32);
        m_aSoftBtn[i].setTextStyle("border:0px; font:19px; color:rgb(238,238,238)");
        m_aSoftBtn[i].SetPadding(10,0,10,0);
        //set softBtnId
        m_aSoftBtn[i].setId(-1);
        connect(&m_aSoftBtn[i], SIGNAL(clicked(int)), this, SLOT(SoftBtnClickedSlot(int)));
    }

    m_pRightArea->setLayout(pRightLayout);

    //slider bar
    m_pMusicPB = new CSlider(Qt::Horizontal,this);
    m_pMusicPB->setGeometry(0, 397-40-5-2-3, 800, 7);
    m_pMusicPB->setStyleSheet("QSlider{border:none;background:transparent;}"
                              "QSlider::groove:horizontal {"
                              "border-image:url(:/SDLApps/Source/images/progress_bar.png);"
                              "height: 1px;"
                              "margin:  0px 0px;"
                              "}"
                              "QSlider::handle:horizontal"
                              "{"
                              "border:none;"
                              "background-image: url(:/SDLApps/Source/images/pointout.png);"
                              "margin: -3px 0px -3px 0px;"
                              "width: 12px;"
                              "height: 7px;"
                              "}"
                              "QSlider::sub-page:horizontal {  "
                              "background-image: url(:/SDLApps/Source/images/compelete.png);"
                              "height:2px;"
                              "}"
                              );
    m_pMusicPB->setEnabled(false);
    m_pMusicPB->hide();

    //play time
    m_pTimeElapseLab = new QLabel(this);
    m_pTimeElapseLab->setStyleSheet("border:0px;font: 14px;color:rgb(153,153,153)");
    m_pTimeElapseLab->setGeometry(15,387-40-19-7,70,28);
    m_pTimeElapseLab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    m_pTimeRemainLab = new QLabel(this);
    m_pTimeRemainLab->setStyleSheet("border:0px;font: 14px;color:rgb(153,153,153)");
    m_pTimeRemainLab->setGeometry(800-15-70,387-40-19-7,70,28);
    m_pTimeRemainLab->setAlignment(Qt::AlignRight|Qt::AlignHCenter);

    connect(this, SIGNAL(startMediaClock(bool)), SLOT(mediaClockSlots(bool)));

    //top widget
    m_pTopWidget = new TopNavigateWidget(this);
    m_pTopWidget->SetReturnTitle(QString("Sources"));
    m_pTopWidget->ShowBack();
    m_pTopWidget->ShowTitle();
    m_pTopWidget->ShowMenu();
    m_pTopWidget->show();
    connect(m_pTopWidget, SIGNAL(SigMenuClicked()), this, SLOT(BtnMenuClickedSlots()));
    connect(m_pTopWidget, SIGNAL(SigBackClicked()), this, SLOT(BtnBackClickedSlots()));

    //textfield
    m_aShowLine[0].setParent(this);
    m_aShowLine[0].setStyleSheet("border:0px;font: 24px;color:rgb(116,118,126)");
    m_aShowLine[0].setGeometry(80+262+15,100,317,33);
    m_aShowLine[0].show();

    m_aShowLine[1].setParent(this);
    m_aShowLine[1].setStyleSheet("border:0px;font: 26px;color:rgb(116,118,126)");
    m_aShowLine[1].setGeometry(80+262+15,100+33+5,317,36);

    m_aShowLine[2].setParent(this);
    m_aShowLine[2].setStyleSheet("border:0px;font: 30px;color:rgb(238,238,238)");
    m_aShowLine[2].setGeometry(80+262+15,100+33+5+36+1,317,41);

    //play mode
    //TODO: playmode is not supported in current, this may support later
    m_pCircleMode = new QPushButton(this);
    m_pCircleMode->setStyleSheet("QPushButton{border-image:url(:/SDLApps/Source/images/cricle.png);"
                                 "background:transparent;}");
    m_pCircleMode->setGeometry(QRect(80+262+15+46+12,100+33+5+36+1+41+22,46,46));
    m_pCircleMode->setFocusPolicy(Qt::NoFocus);
    m_pCircleMode->hide();

    m_pShuffleMode = new QPushButton(this);
    m_pShuffleMode->setStyleSheet("QPushButton{border-image:url(:/SDLApps/Source/images/random.png);"
                                  "background:transparent;}");
    m_pShuffleMode->setGeometry(QRect(80+262+15,100+33+5+36+1+41+22,46,46));
    m_pShuffleMode->setFocusPolicy(Qt::NoFocus);
    m_pShuffleMode->hide();
}

CMediaShow::~CMediaShow()
{

}

void CMediaShow::SoftBtnClickedSlot(int iSoftBtnID) {
    if (iSoftBtnID >= 0) {
        AppControl->OnSoftButtonClick(iSoftBtnID, BUTTON_SHORT);
    }
}

void CMediaShow::BtnMenuClickedSlots() {
    AppControl->OnShowCommand();
}

void CMediaShow::BtnBackClickedSlots()
{
    INFO("CMediaShow::BtnBackClickedSlots");
    if(SDLApps::Inst()->FromMedia())
    {
        HMIFrameWork::Inst()->AppShow(MEDIA_ID);
    }
    else
    {
          SDLApps::Inst()->GetUIManager()->onAppShow(ID_APPLINK);
    }
}

void CMediaShow::UpdatePlayPauseStatus(bool isPlaying)
{
    m_bPlaying = isPlaying;
    if(m_bPlaying)
    {
        m_pPlayPause->setStyleSheet("QPushButton{border-image:url(:/SDLApps/Source/images/play.png);background:transparent;}");
    }
    else
    {
        m_pPlayPause->setStyleSheet("QPushButton{border-image:url(:/SDLApps/Source/images/stop.png);background:transparent;}");
    }
}

void CMediaShow::SetAppName(QString strName) {
    m_pTopWidget->SetTitle(strName);
}

void CMediaShow::showEvent(QShowEvent *e) {
    Q_UNUSED(e);

    INFO("m_pAlbumCover->start();");
    m_pAlbumCover->start();
    m_pAlbumCover->show();

    for (int i = 0; i < RIGHT_BTN_NUM; ++i) {
        m_aSoftBtn[i].setText("");
    }

    for (int i = 0; i < SHOW_LINE_NUM; ++i) {
        m_aShowLine[i].setText(" ");
    }

    m_pTimeElapseLab->setText(" ");
    m_pTimeRemainLab->setText(" ");

    if (AppControl) {
        SetAppName(AppControl->getAppName().c_str());

        rpcValueInterface &pObj = AppControl->getShowData();
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

        if (jsonParams.isMember("graphic")) {
            QUrl graphicUrl(jsonParams["graphic"]["value"].asString().c_str());
            if (graphicUrl.isEmpty()) {
                m_pAlbumCover->setAlbumCover(QPixmap(""));
            } else {
#if defined(WINCE)
                QString path = QString::fromStdString(ChangeSlash(graphicUrl.path().toLocal8Bit().data()));
#else
                QString path = QString::fromStdString(ChangeSlash(graphicUrl.path().toStdString()));
#endif
                m_pAlbumCover->setAlbumCover(QPixmap(path));
            }
        } else {
            m_pAlbumCover->setAlbumCover(QPixmap(""));
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

        UpdateMediaClockTimer();
    }
}

void CMediaShow::hideEvent(QHideEvent *e)
{
    m_pAlbumCover->stop();
    m_pAlbumCover->hide();
}

void CMediaShow::setSoftButtons(std::vector<SSoftButton> vec_softButtons) {
    int iSize = vec_softButtons.size() > RIGHT_BTN_NUM ? RIGHT_BTN_NUM : vec_softButtons.size();
    for (int i = 0; i < iSize; ++i) {
        m_aSoftBtn[i].initParameter(116, 32, ":/SDLApps/Source/images/right_btn_normal.png", ":/SDLApps/Source/images/right_btn_push.png", "", vec_softButtons[i].str_text.c_str());
        m_aSoftBtn[i].setId(vec_softButtons[i].i_softButtonID);

        if (vec_softButtons[i].b_isHighlighted){
            m_aSoftBtn[i].changeToPressed();
        }
    }

    for (int i = iSize; i < RIGHT_BTN_NUM; ++i) {
        m_aSoftBtn[i].initParameter(116, 32, "", "", "", "");
        m_aSoftBtn[i].setId(-1);
    }
}

void CMediaShow::UpdateMediaClockTimer() {
    rpcValueInterface &jsonObj = AppControl->getMediaClockJson();

    if (jsonObj["params"].isMember("startTime")) {
        m_i_startH = jsonObj["params"]["startTime"]["hours"].asInt();
        m_i_startM = jsonObj["params"]["startTime"]["minutes"].asInt();
        m_i_startS = jsonObj["params"]["startTime"]["seconds"].asInt();
    } else {
        m_i_startH = m_i_startM = m_i_startS = 0;
        emit startMediaClock(false);
        setMediaClock(" ", " ");
        m_pMusicPB->hide();
        return;
    }

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
        if (m_MeidaClockCurrentTime.setHMS(m_i_startH, m_i_startM, m_i_startS)) {
            m_b_countup = true;
            emit startMediaClock(true);
            AppControl->OnSetMediaClockTimerResponse(RESULT_SUCCESS);
        } else {
            emit startMediaClock(false);
            AppControl->OnSetMediaClockTimerResponse(RESULT_DATA_NOT_AVAILABLE);
        }
    } else if (jsonObj["params"]["updateMode"].asString() == "COUNTDOWN") {
        if (m_MeidaClockCurrentTime.setHMS(m_i_startH, m_i_startM, m_i_startS)) {
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
    
    UpdatePlayPauseStatus(isStart);
}

void CMediaShow::OnSeekLeftClicked()
{
    AppControl->OnSoftButtonClick(CMD_PREV, BUTTON_SHORT, "SEEKLEFT");
}

void CMediaShow::OnPlayPauseClicked()
{
    if(m_bPlaying)
    {
        AppControl->OnSoftButtonClick(CMD_PAUSE, BUTTON_SHORT, "OK");
    }
    else
    {
        AppControl->OnSoftButtonClick(CMD_START, BUTTON_SHORT, "OK");
    }
}

void CMediaShow::OnSeekRightClicked()
{
    AppControl->OnSoftButtonClick(CMD_NEXT, BUTTON_SHORT, "SEEKRIGHT");
}

void CMediaShow::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);
    if (m_b_countup) {
        m_MeidaClockCurrentTime = m_MeidaClockCurrentTime.addSecs(1);
    } else {
        m_MeidaClockCurrentTime = m_MeidaClockCurrentTime.addSecs(-1);
    }
    
    if (-1 == m_i_endH && -1 == m_i_endM && -1 == m_i_endS) {
        setMediaClock(m_MeidaClockCurrentTime.toString("HH:mm:ss"), "");
        return;
    }
    
    m_pMusicPB->setValue(m_MeidaClockCurrentTime.hour() * 3600 +
                         m_MeidaClockCurrentTime.minute() * 60 +
                         m_MeidaClockCurrentTime.second());
    m_pMusicPB->update();
    
    if (m_MeidaClockCurrentTime.hour() == m_i_endH
            && m_MeidaClockCurrentTime.minute() == m_i_endM
            && m_MeidaClockCurrentTime.second() == m_i_endS) {
        UpdatePlayPauseStatus(false);
        this->killTimer(m_timerId);
    }
    
    int iRemain = m_MediaClockEndTime.secsTo(m_MeidaClockCurrentTime);
    iRemain = 0 - iRemain;
    int iHour = iRemain / 3600;
    iRemain = iRemain % 3600;
    int iMinute = iRemain / 60;
    int iSecond = iRemain % 60;
    QTime timeRemain;
    timeRemain.setHMS(iHour, iMinute, iSecond);
    
    setMediaClock(m_MeidaClockCurrentTime.toString("HH:mm:ss"), "-" + timeRemain.toString("HH:mm:ss"));
}

void CMediaShow::setMediaClock(QString strElapseTime, QString strRemainTime) {
    AppBase::SetEdlidedText(m_pTimeElapseLab, strElapseTime, width() * 0.3);
    AppBase::SetEdlidedText(m_pTimeRemainLab, strRemainTime, width() * 0.3);
}
