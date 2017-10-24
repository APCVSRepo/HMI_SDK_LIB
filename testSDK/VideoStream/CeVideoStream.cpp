#include "CeVideoStream.h"
#include "main.h"
#include "Common/AppBase.h"
#include "MainWindow/MainWindow.h"

CeVideoStream::CeVideoStream(AppListInterface * pList, QWidget *parent) : QWidget(parent)
  ,videoWidth(SCREEN_WIDTH),videoHeight(SCREEN_HEIGHT)
{
    setWindowFlags(Qt::FramelessWindowHint);
    if (parent) {
#ifdef ARCH_X86
        setGeometry(80, 0, parent->width() - 90, parent->height() - 80);
#elif ARCH_ARMHF
        setGeometry(80, 0, parent->width() - 90, parent->height() - 90);
#endif
    }

#ifdef SDL_CALL_BACK
    sdl_set_videostream_callback(callBack_send_data);
#endif

    m_pList = pList;

    m_ucCurrentImageIndex[0] = 0;
    m_ucCurrentImageIndex[1] = 2;

    m_pBtnImage[0] = new QImage(":/images/ZoomInBtnNormal.png");
    m_pBtnImage[1] = new QImage(":/images/ZoomInBtnPress.png");
    m_pBtnImage[2] = new QImage(":/images/ZoomOutBtnNormal.png");
    m_pBtnImage[3] = new QImage(":/images/ZoomOutBtnPress.png");

    m_pMenuBtn = new CButton(this);
    m_pZoomInBtn = new CButton(this);
    m_pZoomOutBtn = new CButton(this);


    int iBtnHeight = 40;
    int iBtnWidth = 60;

    m_pZoomInBtn->setGeometry(QRect(20,height()*0.3-10,iBtnWidth,iBtnHeight));
    m_pZoomInBtn->initParameter(iBtnWidth,iBtnHeight,
                                ":/images/ZoomInBtnNormal.png",
                                ":/images/ZoomInBtnPress.png","","");

    m_pZoomOutBtn->setGeometry(QRect(20,height()*0.3+iBtnHeight+10,iBtnWidth,iBtnHeight));
    m_pZoomOutBtn->initParameter(iBtnWidth,iBtnHeight,
                                 ":/images/ZoomOutBtnNormal.png",
                                 ":/images/ZoomOutBtnPress.png","","");

    m_pMenuBtn->setGeometry(QRect(20,height()*0.8,iBtnWidth,iBtnHeight));
    m_pMenuBtn->initParameter(iBtnWidth,iBtnHeight,
                              ":/images/BtnNormal.png",
                              ":/images/BtnPress.png","","Menu");
    m_pMenuBtn->setTextStyle("border:0px;font: 20px \"Liberation Serif\";color:rgb(0,0,0)");

    m_pZoomInBtn->setParent(parent);
    m_pZoomOutBtn->setParent(parent);
    m_pMenuBtn->setParent(parent);

    m_pZoomInBtn->hide();
    m_pZoomOutBtn->hide();
    m_pMenuBtn->hide();

    connect(m_pZoomInBtn,SIGNAL(clicked()),this,SLOT(OnClickedZoomInBtn()));
    connect(m_pZoomOutBtn,SIGNAL(clicked()),this,SLOT(OnClickedZoomOutBtn()));
    connect(m_pMenuBtn,SIGNAL(clicked()),this,SLOT(OnClickedMenuBtn()));

    m_pTimeLab = new QLabel(this);
    m_pTimeLab->setGeometry(QRect(width()*0.8,height()*0.02,width()*0.2,height()*0.1));
    m_pTimeLab->setAlignment(Qt::AlignCenter);
    m_pTimeLab->setStyleSheet("font: 55 30pt \"Liberation Serif\";color:rgb(0,0,0);background:transparent;border: 0px");
    m_pTimeLab->setText(QTime::currentTime().toString("HH:mm:ss"));

    m_pTimer = new QTimer(this);
    m_pTimer->start(1000);
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(onUpdateTime()));

#ifdef OS_LINUX
    m_MenuTimer.setInterval(5000);
    connect(&m_MenuTimer,SIGNAL(timeout()),this,SLOT(onMenuShowTimeout()));
#endif
}

CeVideoStream::~CeVideoStream()
{
}

void CeVideoStream::startStream()
{
#ifdef OS_LINUX
    MainWindow* pMain = (MainWindow*)this->parentWidget();
    if (pMain) {
        pMain->HideAllComponent();
    }
#ifdef ARCH_X86
    m_player.open("./storage/video_stream_pipe", "ximagesink", false, this->winId());
#elif ARCH_ARMHF
    m_player.open("./storage/video_stream_pipe", "rkximagesink", false, this->winId());
#endif
    m_player.play();
    m_pZoomInBtn->show();
    m_pZoomOutBtn->show();
    m_pMenuBtn->show();
    m_MenuTimer.start();
#endif
}

void CeVideoStream::stopStream()
{
#ifdef OS_LINUX
    MainWindow* pMain = (MainWindow*)this->parentWidget();
    //m_player.stop();
    m_pZoomInBtn->hide();
    m_pZoomOutBtn->hide();
    m_pMenuBtn->hide();
    if (m_MenuTimer.isActive()) {
        m_MenuTimer.stop();
    }
    if (pMain) {
        pMain->ShowAllComponent();
        pMain->ShowMenuBar();
    }
#endif
}

#ifdef OS_LINUX
void CeVideoStream::onMenuShowTimeout() {
    m_MenuTimer.stop();
    MainWindow* pMain = (MainWindow*)this->parentWidget();
    m_pZoomInBtn->hide();
    m_pZoomOutBtn->hide();
    m_pMenuBtn->hide();
    pMain->HideMenuBar();
    setGeometry(0, 0, parentWidget()->width(), parentWidget()->height());
}
#endif

#ifdef SDL_CALL_BACK
#define TMP_BUF_LEN 100
static uchar m_tmpBuf[TMP_BUF_LEN + 2048] = {0};
static int offset = 0;
void CeVideoStream::callBack_send_data(const char *data, int size)
{
    static bool bb = false;
    if(!bb){
        bb = true;
    }
}
#endif

void CeVideoStream::onRawData(void *p, int iLength)
{
    static bool bb = false;
    if(!bb){
        bb = true;
    }
#ifdef TEST_FILE
    fwrite(p,iLength,1,fp);
#endif
}

void CeVideoStream::OnClickedMenuBtn()
{
#ifdef OS_LINUX
    stopStream();
#endif
    m_pList->getActiveApp()->OnShowCommand();
}

void CeVideoStream::mousePressEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();
    x = x*videoWidth/width();
    y = y*videoHeight/height();
    m_pList->getActiveApp()->OnVideoScreenTouch(TOUCH_START,x,y);
#ifdef OS_LINUX
    m_MenuTimer.start();
    MainWindow* pMain = (MainWindow*)this->parentWidget();
    m_pZoomInBtn->show();
    m_pZoomOutBtn->show();
    m_pMenuBtn->show();
    pMain->ShowMenuBar();
#ifdef ARCH_X86
    setGeometry(80, 0, parentWidget()->width() - 90, parentWidget()->height() - 80);
#elif ARCH_ARMHF
    setGeometry(80, 0, parentWidget()->width() - 90, parentWidget()->height() - 90);
#endif
#endif
}

void CeVideoStream::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();
    x = x*videoWidth/width();
    y = y*videoHeight/height();

    m_pList->getActiveApp()->OnVideoScreenTouch(TOUCH_MOVE,x,y);
}

#define ZOOMINBTNID 3
#define ZOOMOUTBTNID 4

void CeVideoStream::mouseReleaseEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();
    x = x*videoWidth/width();
    y = y*videoHeight/height();

    m_pList->getActiveApp()->OnVideoScreenTouch(TOUCH_END,x,y);
}
