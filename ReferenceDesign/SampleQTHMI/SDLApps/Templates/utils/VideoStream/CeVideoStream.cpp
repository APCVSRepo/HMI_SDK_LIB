#include "CeVideoStream.h"
#include "main.h"
#include "SDLApps/Templates/Common/AppBase.h"
#include "SDLApps/UI/SDLAppsView.h"
#include "HMIFrameWork/HMIFrameWork.h"
#include "HMIFrameWork/log_interface.h"
#include "SDLApps/app/SDLApps.h"

CeVideoStream::CeVideoStream(AppListInterface *pList, QWidget *parent)
    :QWidget(parent)
    ,videoWidth(SCREEN_WIDTH)
    ,videoHeight(SCREEN_HEIGHT)
    ,m_pList(pList)
    ,m_pBackground(NULL)
    ,m_pTopWidget(NULL)
{
    setWindowFlags(Qt::FramelessWindowHint);
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }

#ifdef SDL_CALL_BACK
    sdl_set_videostream_callback(callBack_send_data);
#endif

    m_pVideoArea = new QWidget(this);
    m_pVideoArea->setGeometry(40, 70, this->width()-40, this->height()-70);

    //top widget
    m_pTopWidget = new TopNavigateWidget(this);
    m_pTopWidget->SetReturnTitle(QString(""));
    m_pTopWidget->ShowBack();
//    m_pTopWidget->ShowMenu();
    m_pTopWidget->show();
    connect(m_pTopWidget, SIGNAL(SigMenuClicked()), this, SLOT(OnClickedMenuBtn()));
    connect(m_pTopWidget, SIGNAL(SigBackClicked()), this, SLOT(OnClickedBackBtn()));
}

CeVideoStream::~CeVideoStream() {
}

void CeVideoStream::startStream() {
#ifdef OS_LINUX
    SDLAppsView *pMain = (SDLAppsView *)this->parentWidget();
    if (pMain) {
        pMain->HideAllComponent();
    }
#ifdef ARCH_X86
    m_player.open("./storage/video_stream_pipe", "ximagesink", false, m_pVideoArea->winId());
#elif ARCH_ARMHF
    m_player.open("./storage/video_stream_pipe", "rkximagesink", false, m_pVideoArea->winId());
#endif
    m_player.play();
#endif
}

void CeVideoStream::stopStream() {
#ifdef OS_LINUX
    SDLAppsView *pMain = (SDLAppsView *)this->parentWidget();
    if (pMain) {
        pMain->ShowAllComponent();
        pMain->ShowMenuBar();
    }
#endif
}

#ifdef SDL_CALL_BACK
#define TMP_BUF_LEN 100
static uchar m_tmpBuf[TMP_BUF_LEN + 2048] = {0};
static int offset = 0;
void CeVideoStream::callBack_send_data(const char *data, int size) {
    static bool bb = false;
    if (!bb) {
        bb = true;
    }
}
#endif

void CeVideoStream::onRawData(void *p, int iLength) {
    static bool bb = false;
    if (!bb) {
        bb = true;
    }
#ifdef TEST_FILE
    fwrite(p, iLength, 1, fp);
#endif
}

void CeVideoStream::OnClickedMenuBtn() {
#ifdef OS_LINUX
    stopStream();
#endif
    AppControl->OnShowCommand();
}

void CeVideoStream::OnClickedBackBtn()
{
    INFO("CeVideoStream::OnClickedBackBtn");
    if(SDLApps::Inst()->FromNavi())
    {
        HMIFrameWork::Inst()->AppShow(NAV_ID);
        m_pList->OnAppExit();
    }
    else
    {
        m_pList->OnAppExit();
    }
}

void CeVideoStream::mousePressEvent(QMouseEvent *e) {
    int x = e->x();
    int y = e->y();
    x = x * videoWidth / width();
    y = y * videoHeight / height();
    AppControl->OnVideoScreenTouch(TOUCH_START, x, y);
    m_ClickStatus = true;
}

void CeVideoStream::mouseMoveEvent(QMouseEvent *e) {
    int x = e->x();
    int y = e->y();
    x = x * videoWidth / width();
    y = y * videoHeight / height();

    AppControl->OnVideoScreenTouch(TOUCH_MOVE, x, y);
    m_ClickStatus = false;
}

#define ZOOMINBTNID 3
#define ZOOMOUTBTNID 4

void CeVideoStream::mouseReleaseEvent(QMouseEvent *e) {
    int x = e->x();
    int y = e->y();
    x = x * videoWidth / width();
    y = y * videoHeight / height();

    AppControl->OnVideoScreenTouch(TOUCH_END, x, y);
#ifdef OS_LINUX
    if (m_ClickStatus) {
        SDLAppsView *pMain = (SDLAppsView *)this->parentWidget();
        pMain->ShowMenuBar();
    }
#endif
}
