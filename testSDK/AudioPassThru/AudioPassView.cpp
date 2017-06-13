#include "AudioPassView.h"

CAudioPassView::CAudioPassView(AppListInterface * pList, QWidget *parent) : QWidget(parent)
{
    if (parent) {
        setGeometry(0,0,parent->width(),parent->height());
    }
    m_pList = pList;

    setAutoFillBackground(true);
    QPixmap pixmap(":/images/choicevr_back.png");
    pixmap = pixmap.scaled(width(),height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    setPalette(palette);
}
