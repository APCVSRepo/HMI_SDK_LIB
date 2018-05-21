#ifndef SCOLLMSGVIEW_H
#define SCOLLMSGVIEW_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include "SDLApps/Templates/Common/Button.h"
#include "SDLApps/Templates/Common/CustomButton.h"
#include "SDLApps/Templates/Common/AppBase.h"

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

  AppListInterface *m_pList;

  QTimer *m_pTimer;
  CCustomButton *m_pReturnBtn;
  QLabel *m_pAppNameLab;
  QTextEdit *m_pText;
  CButton m_aSoftBtn[6];
  QLabel m_aSplit[5];
  QLabel *m_pShadowLab;
  std::vector <SSoftButton> m_vSoftButtons;
};

#endif // SCOLLMSGVIEW_H
