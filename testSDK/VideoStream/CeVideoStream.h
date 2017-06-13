#ifndef CEVIDEOSTREAM_H
#define CEVIDEOSTREAM_H

#include <QWidget>

#include <QPainter>
#include <QQueue>
#include <QDebug>
//#include "IMessageInterface.h"

#include "Common/Button.h"
#include "AppListInterface.h"
#include <QTimer>

#define TEST_FILE

typedef struct dataPackage{
    uchar buf[1024];
    int len;
}DataS;

class CeVideoStream : public QWidget//, public IMessageInterface
{
    Q_OBJECT
public:
    explicit CeVideoStream(AppListInterface * pList,QWidget *parent = 0);
    ~CeVideoStream();

    void startStream();
    void stopStream();

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
public: //IMessageInterface
    Result onRequest(rpcValueInterface&) {return RESULT_SUCCESS;}
    void onNotification(rpcValueInterface&) {}
    void onResult(rpcValueInterface&) {}
    void onRawData(void * p, int iLength);
    void onError(std::string error) {}
signals:

public slots:
    void OnClickedMenuBtn();

private:
    int videoWidth;
    int videoHeight;

    QRect m_BtnRect[3];
    QImage *m_pBtnImage[4];
    unsigned char m_ucCurrentImageIndex[2];

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
