#include "CustomButton.h"
#include <QUrl>

std::string ChangeSlash(std::string strSrc)
{
#if defined(WIN32) || defined(WINCE)
    char *pTemp = new char[strSrc.size()+1];
    strcpy(pTemp,strSrc.c_str());
    for (int i = 0;i != strSrc.size();++i) {
        if (pTemp[i] == '\\') {
            pTemp[i] = '/';
        }
    }
    strSrc = pTemp;
    delete []pTemp;
#endif
    return strSrc;
}


CCustomButton::CCustomButton(QWidget *parent) : QWidget(parent),
    m_point(0,0),m_iOldState(-1),m_iId(0)
{
    m_pMainLayout = new QHBoxLayout(this);
    m_pLeftIconLab = new QLabel;
    m_pTextLab = new QLabel;
    m_pRightIconLab = new QLabel;

    m_pMainLayout->addWidget(m_pLeftIconLab);
    m_pMainLayout->addWidget(m_pTextLab,1);
    m_pMainLayout->addWidget(m_pRightIconLab);
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->setContentsMargins(0,0,0,0);

    m_pLeftIconLab->setStyleSheet("max-width:0px;max-height:0px");
    m_pRightIconLab->setStyleSheet("max-width:0px;max-height:0px");

    m_pCheckHoverTimer = new QTimer(this);
}

CCustomButton::~CCustomButton()
{
    delete m_pMainLayout;
    delete m_pLeftIconLab;
    delete m_pTextLab;
    delete m_pRightIconLab;
}

void CCustomButton::SetTextStyle(std::string strQtStyle)
{
    m_pTextLab->setStyleSheet(strQtStyle.c_str());
}

void CCustomButton::SetText(std::string strText,int iAlign)
{    
    m_Text = strText;
    QFontMetrics qfm(m_pTextLab->font());
    QString strTemp(qfm.elidedText(strText.c_str(),Qt::ElideRight,width()));
    m_pTextLab->setText(strTemp);
    m_pTextLab->setAlignment((Qt::Alignment)iAlign);
    m_pTextLab->setAttribute(Qt::WA_TranslucentBackground,true);
}

std::string CCustomButton::Text()
{
    return m_Text;
}

void CCustomButton::SetPadding(int iPadding)
{
    m_pMainLayout->setContentsMargins(iPadding,iPadding,iPadding,iPadding);
}

void CCustomButton::SetPadding(int iLeft,int iTop,int iRight,int iBottom)
{
    m_pMainLayout->setContentsMargins(iLeft,iTop,iRight,iBottom);
}

void CCustomButton::SetSize(int iWidth, int iHeight)
{
    setMinimumSize(iWidth,iHeight);
    setMaximumSize(iWidth,iHeight);
}

void CCustomButton::SetBackPicPath(std::string strNormalPic,std::string strPressPic,std::string strHoverPic)
{
    m_strNormalPicPath = strNormalPic;
    m_strPressPicPath = strPressPic;
    m_strHoverPicPath = strHoverPic;
    if (!strHoverPic.empty()) {
        m_pCheckHoverTimer->start(100);
        connect(m_pCheckHoverTimer,SIGNAL(timeout()),this,SLOT(CheckHoverSlot()));
    } else {
        m_pCheckHoverTimer->stop();
        disconnect(m_pCheckHoverTimer,SIGNAL(timeout()),this,SLOT(CheckHoverSlot()));
    }
}

void CCustomButton::SetBackImage(int iState)
{
    if (m_iOldState != iState) {
        m_iOldState = iState;
        QPixmap *pPixmap = NULL;
        if (iState == BTN_STAT_NORMAL) {
            pPixmap = new QPixmap(m_strNormalPicPath.c_str());
        } else if (iState == BTN_STAT_PRESSED) {
            pPixmap = new QPixmap(m_strPressPicPath.c_str());
        } else if (iState == BTN_STAT_HOVER) {
            pPixmap = new QPixmap(m_strHoverPicPath.c_str());
        } else {
            return;
        }

        if (!pPixmap->isNull()) {
            setAutoFillBackground(true);
            QPalette palette;
            palette.setBrush(QPalette::Background, QBrush(pPixmap->scaled(width(),height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
            setPalette(palette);
        }

        delete pPixmap;
    }
}

void CCustomButton::Init(int iWidth,int iHeight,std::string strtext,std::string strNormalPic,std::string strPressPic,std::string strHoverPic)
{
    SetSize(iWidth,iHeight);
    SetBackPicPath(strNormalPic,strPressPic,strHoverPic);
    SetBackImage(BTN_STAT_NORMAL);
    SetText(strtext);
}

void CCustomButton::SetLeftIcon(std::string strIcon)
{
    if (strIcon.empty()) {
        m_pLeftIconLab->setMinimumWidth(0);
        m_pLeftIconLab->setStyleSheet("max-width:0px;max-height:0px");
    } else {
        m_pLeftIconLab->setMinimumWidth(height());
#if defined(WINCE)
        QString strTemp = QString("background:transparent;border:transparent;padding:%1px;image:url(%2)").arg(height()*0.15).arg(ChangeSlash(QUrl(strIcon.c_str()).path().toLocal8Bit().data()).c_str());
#else
        QString strTemp = QString("background:transparent;border:transparent;padding:%1px;image:url(%2)").arg(height()*0.15).arg(ChangeSlash(QUrl(strIcon.c_str()).path().toStdString()).c_str());
#endif
        m_pLeftIconLab->setStyleSheet(strTemp);
    }
}

void CCustomButton::SetRightIcon(std::string strIcon)
{
    if (strIcon.empty()) {
        m_pRightIconLab->setStyleSheet("max-width:0px;max-height:0px");
    } else {
        m_pRightIconLab->setMinimumWidth(height());
#if defined(WINCE)
        QString strTemp = QString("background:transparent;border:transparent;padding:%1px;image:url(%2)").arg(height()*0.15).arg(ChangeSlash(QUrl(strIcon.c_str()).path().toLocal8Bit().data()).c_str());
#else
        QString strTemp = QString("background:transparent;border:transparent;padding:%1px;image:url(%2)").arg(height()*0.15).arg(ChangeSlash(QUrl(strIcon.c_str()).path().toStdString()).c_str());
#endif
        m_pRightIconLab->setStyleSheet(strTemp);
    }
}

void CCustomButton::mousePressEvent(QMouseEvent *event)
{
    m_point = event->pos();
    SetBackImage(BTN_STAT_PRESSED);
    m_pressedTime.start();
}

void CCustomButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button()== Qt::LeftButton) {
        SetBackImage(BTN_STAT_NORMAL);
        if (event->pos() == m_point) {
            if (m_pressedTime.elapsed() > 2000) {
                emit ClickedLong();
                emit ClickedLong(m_iId);
            } else {
                emit Clicked();
                emit Clicked(m_iId);
                emit Clicked(m_iId,m_strCustomName);
            }
            m_point = QPoint(0,0);
        }
    }
}

void CCustomButton::SetId(int iId)
{
    m_iId = iId;
}

void CCustomButton::SetCustomName(std::string strName)
{
    m_strCustomName = strName;
}

void CCustomButton::CheckHoverSlot()
{
    if (!QRect(0,0,width(),height()).contains(mapFromGlobal(QCursor::pos()))) {
        SetBackImage(BTN_STAT_NORMAL);
    } else {
        SetBackImage(BTN_STAT_HOVER);
    }
}
