#ifndef GLOBAL_FIRST
#define GLOBAL_FIRST

#ifdef WINCE
# if _WIN32_WCE > 0x600
#  include <stdlib.h>
# endif
# include <winsock2.h>
#endif

#include <stdarg.h>
#ifdef ANDROID
#include <android/log.h>
#define  LOGI(...)  //__android_log_print(ANDROID_LOG_INFO,"SDL",__VA_ARGS__)
#define  LOGD(...)  //__android_log_print(ANDROID_LOG_DEBUG,"SDL",__VA_ARGS__)
#define  LOGE(...)  //__android_log_print(ANDROID_LOG_ERROR,"SDL",__VA_ARGS__)
#define  CONFIG_DIR   "/sdcard/sdlconfig"

#else
#define  LOGI(...)  //{printf(__VA_ARGS__);printf(" %s():%d\n",__FUNCTION__,__LINE__);fflush(stdout);}while(0)
#define  LOGD(...)  {printf(__VA_ARGS__);printf(" %s():%d\n",__FUNCTION__,__LINE__);fflush(stdout);}while(0)
#define  LOGE(...)  //{printf(__VA_ARGS__);printf(" %s():%d\n",__FUNCTION__,__LINE__);fflush(stderr);}while(0)
#endif

#endif
