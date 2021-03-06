#ifndef INTERFACE_H
#define INTERFACE_H
#include <string>
#include <vector>
#include <map>
#include <list>
using namespace std;

#define interface struct
#define C_CXX_UNUSED(x) (void)x;


enum eAppStatus{
    AppStatus_Inactive,
    AppStatus_Active
};

enum eViewStatus{
    eviewStatus_Init,
    eViewStatus_Inactive,
    eViewStatus_Active
};
enum eAppType{
    AppType_App,
    AppType_Decorators
};


enum eGstPlayerStatus{
    eGstPlayer_NULL,
    eGstPlayer_Ready,
    eGstPlayer_Playing,
    eGstPlayer_Finish,
    eGstPlayer_Paused,
    eGstPlayer_Stop,
    eGstPlayer_Error
};

interface IAppManager{
    virtual void AppShow(string appId,string viewId) = 0;
    virtual void AppBack() = 0;
    virtual void Notify(string appId,map<string,string> parameter) = 0;
    virtual void Reply(string appId,map<string,string> parameter) = 0;
};

interface IApp{
    virtual void onAppShow(string appId,string viewId) = 0;
    virtual void onAppHide() = 0;
    virtual void onNotify(string appId,map<string,string> parameter) = 0;
    virtual void onReply(string appId,map<string,string> parameter) = 0;
};

interface IViewFactory{
    virtual void* CreateProduct(int viewId) = 0;
};

interface IView{
    virtual void setView(void* view) = 0;
    virtual int getViewId() = 0;
    virtual void viewAction(int state) = 0;
};


interface IGstPlayerMessage
{
   virtual  void OnGstPlayerStatus(eGstPlayerStatus status) = 0;
};
#endif // INTERFACE_H
