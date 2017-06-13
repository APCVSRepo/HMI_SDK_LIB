#include "CeVideoStream.h"
#include "main.h"

CeVideoStream::CeVideoStream(AppListInterface * pList, QWidget *parent) : QWidget(parent)
  ,videoWidth(800),videoHeight(480)
{
    setWindowFlags(Qt::FramelessWindowHint);
    if (parent) {
        setGeometry(0,0,parent->width(),parent->height());
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


    int iBtnHeight = 60;
    int iBtnWidth = 80;

    m_pZoomInBtn->setGeometry(QRect(40,height()*0.5-10,iBtnWidth,iBtnHeight));
    m_pZoomInBtn->initParameter(iBtnWidth,iBtnHeight,
                                ":/images/ZoomInBtnNormal.png",
                                ":/images/ZoomInBtnPress.png","","");

    m_pZoomOutBtn->setGeometry(QRect(40,height()*0.5+iBtnHeight+10,iBtnWidth,iBtnHeight));
    m_pZoomOutBtn->initParameter(iBtnWidth,iBtnHeight,
                                 ":/images/ZoomOutBtnNormal.png",
                                 ":/images/ZoomOutBtnPress.png","","");

    m_pMenuBtn->setGeometry(QRect(40,height()*0.8+10,iBtnWidth,iBtnHeight));
    m_pMenuBtn->initParameter(iBtnWidth,iBtnHeight,
                              ":/images/BtnNormal.png",
                              ":/images/BtnPress.png","","Menu");
    m_pMenuBtn->setTextStyle("border:0px;font: 20px \"Liberation Serif\";color:rgb(0,0,0)");

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
}

CeVideoStream::~CeVideoStream()
{
}

void CeVideoStream::startStream()
{
#ifdef TEST_FILE
    fp = fopen("./VideoFile.mp4", "ab+");
#endif

    show();
}

void CeVideoStream::stopStream()
{
#ifdef TEST_FILE
    fclose(fp);
#endif
}

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
    m_pList->getActiveApp()->OnShowCommand();
}

void CeVideoStream::mousePressEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();
    x = x*videoWidth/width();
    y = y*videoHeight/height();
    m_pList->getActiveApp()->OnVideoScreenTouch(TOUCH_START,x,y);
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
