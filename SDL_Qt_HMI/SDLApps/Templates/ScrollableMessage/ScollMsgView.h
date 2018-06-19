#ifndef SCOLLMSGVIEW_H
#define SCOLLMSGVIEW_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QTimer>
#include "SDLApps/Templates/Common/Button.h"
//#include "SDLApps/Templates/Common/CustomButton.h"
#include "SDLApps/Templates/Common/AppBase.h"
#include "HMIWidgets/TopNavigateWidget.h"

#define RIGHT_BTN_NUM 5

class CScollMsgView : public QWidget {
  Q_OBJECT
 public:
  explicit CScollMsgView(AppListInterface *pList, QWidget *parent = 0);
  ~CScollMsgView();

 protected:
  void showEvent(QShowEvent *e);
  void hideEvent(QHideEvent *);
 signals:

 public slots:
  void OnTimeOutSlot();
  void OnReturnBtnClicked();
  void OnSoftBtnClicked(int iBtnId);
 private:
  void SetTimeOut(int iDuration);
  void setSoftButtons(std::vector<SSoftButton> vec_softButtons);


  QTimer *m_pTimer;
//  CCustomButton *m_pReturnBtn;
//  QLabel *m_pAppNameLab;
  QTextEdit *m_pText;
//  CButton m_aSoftBtn[RIGHT_BTN_NUM];
//  QLabel m_aSplit[5];
//  QLabel *m_pShadowLab;
//  std::vector <SSoftButton> m_vSoftButtons;


private:
  AppListInterface *m_pList;

  //right softbutton
  QWidget *m_pRightArea;
  std::vector <SSoftButton> m_vSoftButtons;
  CButton m_aSoftBtn[RIGHT_BTN_NUM];

  //navigate item
  TopNavigateWidget *m_pTopWidget;
};

#endif // SCOLLMSGVIEW_H
