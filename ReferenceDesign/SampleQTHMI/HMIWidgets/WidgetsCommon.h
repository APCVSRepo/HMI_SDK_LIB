#ifndef WIDGETSCOMMON
#define WIDGETSCOMMON

extern bool g_bButtonPressed;
extern bool g_bSliderPressed;
extern bool g_bListWidgetPressed;

#define USE_LOG

#ifdef USE_LOG
#include "HMIFrameWork/log_interface.h"
#define Log INFO
#else
#include <QDebug>
#define Log
#endif

#endif // WIDGETSCOMMON

