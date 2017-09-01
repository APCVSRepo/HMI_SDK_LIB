#include "AppBase.h"
#include <QMouseEvent>

AppBase::AppBase(AppListInterface * pList, QWidget *parent)
    : QWidget(parent)
{
    const int ui_app_width = SCREEN_WIDTH;
    const int ui_app_height = SCREEN_HEIGHT;
    setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    setGeometry(0,0,ui_app_width,ui_app_height);
    setBkgImage(":/images/mainbkg.png");
    m_pList = pList;
}

AppBase::~AppBase()
{

}

void AppBase::setBkgImage(const char *img)
{
    setAutoFillBackground(true);    //Widget增加背景图片时，这句一定要。
    QPixmap pixmap(img);
    QPixmap fitpixmap = pixmap.scaled(width(),height(),
                                      Qt::IgnoreAspectRatio,
                                      Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(fitpixmap));
    setPalette(palette);
}

// Bug #9671
void AppBase::SetEdlidedText(QLabel *pLabel,QString strText,int iWidth, Qt::AlignmentFlag alignMode)
{
    QFontMetrics qfm(pLabel->font());
    pLabel->setText(qfm.elidedText(strText,Qt::ElideRight,iWidth));
    // Bug #9671
    pLabel->setAlignment(alignMode);
}

void AppBase::SetEdlidedText(QLineEdit *pEdit,QString strText,int iWidth)
{
    QFontMetrics qfm(pEdit->font());
    pEdit->setText(qfm.elidedText(strText,Qt::ElideRight,iWidth));
}
