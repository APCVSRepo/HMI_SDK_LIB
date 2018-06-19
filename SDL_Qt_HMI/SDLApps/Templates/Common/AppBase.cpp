#include "AppBase.h"
#include <QMouseEvent>

std::string ChangeSlash(std::string strSrc) {
#if defined(WIN32) || defined(WINCE)
    char *pTemp = new char[strSrc.size() + 1];
    strcpy(pTemp, strSrc.c_str());
    for (int i = 0; i != strSrc.size(); ++i) {
        if (pTemp[i] == '\\') {
            pTemp[i] = '/';
        }
    }
    strSrc = pTemp;
    delete []pTemp;
#endif
    return strSrc;
}

AppBase::AppBase(AppListInterface *pList, QWidget *parent)
    : QWidget(parent) {
    const int ui_app_width = SCREEN_WIDTH;
    const int ui_app_height = SCREEN_HEIGHT;
    setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    setGeometry(0, 0, ui_app_width, ui_app_height);
    setBkgImage("");
    m_pList = pList;
}

AppBase::~AppBase() {

}

void AppBase::setBkgImage(const char *img) {
    //Widget增加背景图片时，这句一定要。
    setAutoFillBackground(true);
    QPixmap pixmap(img);
    QPixmap fitpixmap = pixmap.scaled(width(), height(),
                                      Qt::IgnoreAspectRatio,
                                      Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(fitpixmap));
    setPalette(palette);
}

// Bug #9671
void AppBase::SetEdlidedText(QLabel *pLabel, QString strText, int iWidth, Qt::AlignmentFlag alignMode) {
    QFontMetrics qfm(pLabel->font());
    pLabel->setText(qfm.elidedText(strText, Qt::ElideRight, iWidth));
    // Bug #9671
    pLabel->setAlignment(alignMode);
}

void AppBase::SetEdlidedText(QLineEdit *pEdit, QString strText, int iWidth) {
    QFontMetrics qfm(pEdit->font());
    pEdit->setText(qfm.elidedText(strText, Qt::ElideRight, iWidth));
}
