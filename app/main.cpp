#include <pthread.h>
#include "AppList.h"
#include "SDLConnector.h"
#include "sdl_export.h"
#include "sdk_export.h"

AppList *g_appList = NULL;

#ifdef SDL_SUPPORT_LIB
void* SDLStartThread(void *arg)
{
#ifdef ANDROID
	// 手动拷贝配置文件assets config msctts 到CONFIG_DIR
#endif
	char  sdlconfig[50] = {0};
#ifdef ANDROID
	sprintf(sdlconfig,"%s/smartDeviceLink.ini",CONFIG_DIR);
#else
	sprintf(sdlconfig,"smartDeviceLink.ini");
#endif
	char* argv[2] = {"smartDeviceLinkCore",sdlconfig};
	sdl_start(2,argv);
	while (true) {
#ifdef WIN32
		Sleep(100000);
#else
		sleep(100);
#endif
	}
	return NULL;
}

void initSDL()
{
	pthread_t  sdlthread;
	pthread_create(&sdlthread,NULL,SDLStartThread,NULL);
}
#endif

AppListInterface* HMISDK_Init(UIInterface* pUI)
{
	g_appList = new AppList;
	if(!g_appList){
		printf("AppList allocate failed!\n");
		return NULL;
	}

	g_appList->setUIManager(pUI);

#ifdef SDL_SUPPORT_LIB
	initSDL();
#endif

	ToSDL->ConnectToSDL(g_appList);
	return g_appList;
}

void HMISDK_UnInit()
{
	if(g_appList)
		delete g_appList;
}