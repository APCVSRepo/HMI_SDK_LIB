#ifndef MEDIASHOW_H
#define MEDIASHOW_H

#include <QLabel>
#include "SDLApps/Templates/Common/AppBase.h"
#include "SDLApps/Templates/Common/Button.h"
#include "HMIWidgets/AlbumCoverWidget.h"
#include "HMIWidgets/CPushButton.h"
#include "HMIWidgets/CSlider.h"
#include "HMIWidgets/TopNavigateWidget.h"

using namespace hmisdk;

#define RIGHT_BTN_NUM 5
#define SHOW_LINE_NUM 3

class CMediaShow : public QWidget {
    Q_OBJECT

public:
    explicit CMediaShow(AppListInterface *pList, QWidget *parent = 0);
    ~CMediaShow();

    void UpdateMediaClockTimer();
    void SetAppName(QString strName);

    // QWidget interface
protected:
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);

    // QObject interface
protected:
    void timerEvent(QTimerEvent *e);

signals:
    void startMediaClock(bool isStart);

public slots:
    void mediaClockSlots(bool);

    void OnSeekLeftClicked();
    void OnPlayPauseClicked();
    void OnSeekRightClicked();

    void BtnMenuClickedSlots();
    void BtnBackClickedSlots();

    void SoftBtnClickedSlot(int iSoftBtnID);

private:
    void UpdatePlayPauseStatus(bool isPlaying);
    void setSoftButtons(std::vector<SSoftButton> vec_softButtons);
    void setMediaClock(QString strElapseTime, QString strRemainTime);

private:
    AppListInterface *m_pList;

    //timer
    int m_timerId;
    QTime m_MeidaClockCurrentTime;    //TODO: QTime can only display 24 hours, we need use other widget
    QTime m_MediaClockEndTime;
    int m_i_startH;
    int m_i_startM;
    int m_i_startS;
    int m_i_endH;
    int m_i_endM;
    int m_i_endS;
    bool m_b_countup;

    QLabel *m_pTimeElapseLab;
    QLabel *m_pTimeRemainLab;

    CSlider *m_pMusicPB;

    //background
    QLabel *m_pBackground;
    QLabel *m_pBottomBackground;

    //album
    AlbumCoverWidget *m_pAlbumCover;

    //playpause
    CPushButton *m_pSeekLeft;
    CPushButton *m_pPlayPause;
    CPushButton *m_pSeekRight;
    bool m_bPlaying;   //true:playing, false:pause

    //right softbutton
    QWidget *m_pRightArea;
    std::vector <SSoftButton> m_vSoftButtons;
    CButton m_aSoftBtn[RIGHT_BTN_NUM];

    //navigate item
    TopNavigateWidget *m_pTopWidget;

    //textfield
    QLabel m_aShowLine[SHOW_LINE_NUM];

    //play mode
    QPushButton *m_pCircleMode;
    QPushButton *m_pShuffleMode;
};

#endif // MEDIASHOW_H
