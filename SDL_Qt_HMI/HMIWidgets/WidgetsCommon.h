#ifndef WIDGETSCOMMON
#define WIDGETSCOMMON

extern bool g_bButtonPressed;
extern bool g_bSliderPressed;
extern bool g_bListWidgetPressed;

//#define USE_DLTLOG

#ifdef USE_DLTLOG
#define Log INFO
#else
#include <QDebug>
#define Log qDebug
#endif

#endif // WIDGETSCOMMON

