/**
* @file			main
* @brief		hmi_sdk主入口，实现动态库导出函数，负责hmi_sdk初始化及与sdl的连接创建等
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef OS_WIN32
#include <unistd.h>
#endif
#include <pthread.h>
#include "app_list.h"
#include "sdl_connector.h"
#include "sdl_export.h"
#include "sdk_export.h"

AppList *g_appList = NULL;

#ifdef SDL_SUPPORT_LIB
void *SDLStartThread(void *arg) {
#ifdef ANDROID
  // 手动拷贝配置文件assets config msctts 到CONFIG_DIR
#endif
  char  sdlconfig[50] = {0};
#ifdef ANDROID
  sprintf(sdlconfig, "%s/smartDeviceLink.ini", CONFIG_DIR);
#else
  sprintf(sdlconfig, "smartDeviceLink.ini");
#endif
  char *argv[2] = {"smartDeviceLinkCore", sdlconfig};
  sdl_start(2, argv);
  while (true) {
#ifdef WIN32
    Sleep(100000);
#else
    sleep(100);
#endif
  }
  return NULL;
}

void initSDL() {
  pthread_t  sdlthread;
  pthread_create(&sdlthread, NULL, SDLStartThread, NULL);
}
#endif

AppListInterface *InitHmiSdk(UIInterface *pUI) {
  g_appList = new AppList;
  if (!g_appList) {
    printf("AppList allocate failed!\n");
    return NULL;
  }

  g_appList->setUIManager(pUI);

  pUI->SetAppListInterface(g_appList);
  pUI->initAppHMI();

#ifdef SDL_SUPPORT_LIB
  initSDL();
#endif

  ToSDL->ConnectToSDL(g_appList);
  return g_appList;
}

void UnInitHmiSdk() {
  if (g_appList)
    delete g_appList;
}