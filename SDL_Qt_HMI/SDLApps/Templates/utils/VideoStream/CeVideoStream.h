#ifndef CEVIDEOSTREAM_H
#define CEVIDEOSTREAM_H

#include <QWidget>
#include <QPainter>
#include <QQueue>
#include <QDebug>
#include <QTimer>

#include "SDLApps/Templates/Common/Button.h"
#include "app_list_interface.h"
#ifdef OS_LINUX
#include "gst_player.h"
#endif

#define TEST_FILE

typedef struct dataPackage {
  uchar buf[1024];
  int len;
} DataS;

class CeVideoStream : public QWidget { //, public IMessageInterface
  Q_OBJECT
 public:
  explicit CeVideoStream(AppListInterface *pList, QWidget *parent = 0);
  ~CeVideoStream();

  void startStream();
  void stopStream();

  void mousePressEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
 public: //IMessageInterface
  Result onRequest(rpcValueInterface &) {return RESULT_SUCCESS;}
  void onNotification(rpcValueInterface &) {}
  void onResult(rpcValueInterface &) {}
  void onRawData(void *p, int iLength);
  void onError(std::string error) {
    Q_UNUSED(error);
  }
 signals:

 public slots:
  void OnClickedMenuBtn();
#ifdef OS_LINUX
  void onMenuShowTimeout();

  void OnClickedZoomInBtn();
  void OnClickedZoomOutBtn();
  void onUpdateTime();
#endif
 private:
  int videoWidth;
  int videoHeight;
  bool m_ClickStatus;

  QRect m_BtnRect[3];
  QImage *m_pBtnImage[4];
  unsigned char m_ucCurrentImageIndex[2];

#ifdef OS_LINUX
  GstPlayer m_player;
  QTimer  m_MenuTimer;
#endif
  CButton *m_pMenuBtn;
  CButton *m_pZoomInBtn;
  CButton *m_pZoomOutBtn;

  QLabel *m_pTimeLab;
  QTimer *m_pTimer;

  AppListInterface *m_pList;

#ifdef SDL_CALL_BACK
  static void callBack_send_data(const char *data, int size);
#endif

#ifdef TEST_FILE
  FILE *fp;
#endif
};

#endif // CEVIDEOSTREAM_H
