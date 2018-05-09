#ifndef MEDIASHOW_H
#define MEDIASHOW_H

#include <QLabel>
#include <QProgressBar>
#include "SDLApps/Common/AppBase.h"
#include "SDLApps/Common/Button.h"
#include "SDLApps/Common/CustomButton.h"


class CMediaShow : public QWidget {
  Q_OBJECT
 public:
  explicit CMediaShow(AppListInterface *pList, QWidget *parent = 0);
  //~CMediaShow();

  void SetAppName(QString strName);

  void UpdateMediaClockTimer();
 protected:
  virtual void showEvent(QShowEvent *e);

  void timerEvent(QTimerEvent *e);
 signals:
  void startMediaClock(bool isStart);
 public slots:
  void SoftBtnClickedSlot(int iSoftBtnID);
  void SoftBtnClickedSlot(int iSoftBtnID, std::string strName);

  void BtnMenuClickedSlots();
  void mediaClockSlots(bool);
 private:
  void SetPlayBtnID(bool bPlay);
  void setMediaClock(QString strElapseTime, QString strRemainTime);
  void setSoftButtons(std::vector<SSoftButton> vec_softButtons);

  AppListInterface *m_pList;

  CCustomButton *m_pSourceBtn;
  QLabel *m_pAppNameLab;
  CCustomButton *m_pMenuBtn;
  QLabel *m_pTimeElapseLab;
  QLabel *m_pTimeRemainLab;
  QProgressBar *m_pMusicPB;
  QLabel m_aShowLine[5];
  QLabel *m_pMusicPicLab;
  CButton m_aSoftBtn[9];
  QHBoxLayout *m_pBtnLayout;
  QLabel m_aSplit[5];
  QLabel *m_pShadowLab;

  //timer
  int m_timerId;
  QTime nowMeidaClockTime;
  QTime m_MediaClockEndTime;
  int m_i_startH;
  int m_i_startM;
  int m_i_startS;
  int m_i_endH;
  int m_i_endM;
  int m_i_endS;
  bool m_b_countup;

  // softbutton容器
  std::vector <SSoftButton> m_vSoftButtons;
};

#endif // MEDIASHOW_H
