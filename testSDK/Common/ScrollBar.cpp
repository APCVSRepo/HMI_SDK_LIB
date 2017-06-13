#include "ScrollBar.h"

ScrollBar::ScrollBar(QWidget *parent):QScrollBar(parent)
{
    this->setStyleSheet(ScrollBar::cssString());

//QScrollBar::up-arrow:vertical{ subcontrol-origin: margin; \
//background-image:url(:/images/uparrow.png);\
//height:13px;}\
//QScrollBar::down-arrow:vertical{ background-image:url(:/images/downarrow.png); }
}

ScrollBar::~ScrollBar()
{

}

QString ScrollBar::cssString()
{
    return QString::fromUtf8("\
                             QScrollBar::vertical {\
                                background:rgb(63,70,87);\
                                border:0px solid grey;\
                                width: 30px;\
                                margin:30px 0px 30px 0px;\
                             }\
                             QScrollBar::handle:vertical {\
                                background: rgb(108,113,125);\
                                border: 1px solid grey;\
                                border-radius:0px;\
                                min-height: 20px;\
                                width:30px;\
                                border-image: url(:images/downarrow.png);\
                            }\
                            QScrollBar::add-line:vertical {\
                                height: 31px;\
                                subcontrol-origin:margin;\
                            }\
                            QScrollBar::sub-line:vertical {\
                                height: 31px;\
                                subcontrol-origin:margin;\
                            }\
                            QScrollBar::up-arrow:vertical {\
                               subcontrol-origin: margin; \
                               border-image: url(:images/uparrow.png);\
                            }\
                            QScrollBar::down-arrow:vertical { \
                               subcontrol-origin: margin; \
                               border-image: url(:images/downarrow.png);\
                            }\
                            QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\
                               background: none;\
                               border:0,0,0,0;\
                            }\
                            QScrollArea {\
                               border:0,0,0,0;\
                               background:rgb(63,70,87);\
                            }\
                  ");
}

void ScrollBar::init(int h)
{
   this->setOrientation(Qt::Vertical);
   this->setFixedHeight(h);
}

void ScrollBar::flushScroll(int page,int currentNo, int totalNum)
{
    this->setPageStep(page);
    this->setRange(0,totalNum-1);
    this->setValue(currentNo-1);
}


