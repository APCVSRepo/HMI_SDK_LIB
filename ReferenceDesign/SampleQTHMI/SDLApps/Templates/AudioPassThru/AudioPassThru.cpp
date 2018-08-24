#include "AudioPassThru.h"
#include "HMIFrameWork/log_interface.h"

CAudioPassThru::CAudioPassThru(AppListInterface *pList, QWidget *parent)
    : QWidget(parent)
    , m_pList(pList)
{
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }
}

void CAudioPassThru::showEvent(QShowEvent *)
{
    INFO("CAudioPassThru show nothing; Show popup view instead.");
}
