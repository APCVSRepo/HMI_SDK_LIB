#include "SDLVFactory.h"
#include "SDLApps/UI/SDLAppsView.h"
#include "SDLApps/app/SDLApps.h"
#include "SDLApps/Gen3UIManager.h"
#include <QDialog>
#include "HMIFrameWork/HMIFrameWork.h"
SDLVFactory::SDLVFactory()
{
}
SDLVFactory * SDLVFactory::m_pInst = NULL;

SDLVFactory *SDLVFactory::Inst()
{
    if(m_pInst == NULL)
    {
        m_pInst = new SDLVFactory;
    }
    return m_pInst;
}

void *SDLVFactory::CreateProduct(int viewId)
{
    QWidget* mainwin = reinterpret_cast<QWidget*>(SDLApps::Inst()-> getMain());
    switch (viewId) {
    case SDLApps::eViewId_SDL_Main:
    {

           CGen3UIManager *g_pUIManager  = new CGen3UIManager;
            QTimer::singleShot(500, g_pUIManager, SLOT(loadsdk()));

            QDialog diaStart(mainwin);
          #ifdef ANDROID
            diaStart.setGeometry(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height() - 30);
          #else
            diaStart.setGeometry(0, 0, 800, 480);
          #endif
            diaStart.setStyleSheet("border-image:url(:/images/Screen.png);");
            QObject::connect(g_pUIManager, SIGNAL(finishLoadSDK()), &diaStart, SLOT(accept()));

            // 启动画面，等待HMISDK初始化完成

            diaStart.setWindowFlags(Qt::FramelessWindowHint);
            diaStart.exec();


            if(g_pUIManager->getSDLAppsView())
            {
                g_pUIManager->getSDLAppsView()->hide();
                SDLApps::Inst()->setMain(reinterpret_cast<void*>(g_pUIManager->getSDLAppsView()));
                HMIFrameWork::Inst()->RegisterApp(dynamic_cast<App*> (SDLApps::Inst()));
               // g_pUIManager.onAppShow(ID_MAIN);
                g_pUIManager->onAppShow(ID_APPLINK);
                g_pUIManager->onAppShow(ID_CHOICESET);
                (g_pUIManager->getSDLAppsView())->setView(dynamic_cast<QWidget*>(g_pUIManager->getSDLAppsView()));
                return  dynamic_cast<CView*>(g_pUIManager->getSDLAppsView());
            }
            return NULL;
    }
    default:
        return NULL;
    }
}
