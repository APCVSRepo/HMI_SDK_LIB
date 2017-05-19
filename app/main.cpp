#include <pthread.h>
#include "SDLConnector.h"
#include "sdl_export.h"

int main(int argc, char *argv[])
{
#ifdef SDL_SUPPORT_LIB
    pthread_t  sdlthread;
    pthread_create(&sdlthread,NULL,SDLStartThread,NULL);
#endif
    //replace
    //ToSDL->ConnectToSDL(m_appList);
    return 0;
}
