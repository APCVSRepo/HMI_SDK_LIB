#ifndef GEN3UI_MOCKMODULE_H
#define GEN3UI_MOCKMODULE_H
#include "app_list.h"
#include "app_data.h"
#include "hmi_ui.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"


using namespace std;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Invoke;


namespace test {
    namespace hmi_sdk {
        namespace rpc_test {

            class AppDataMock;

            class AppListMock:public  IMessageInterface, public AppListInterface
            {
            public:
                AppListMock(){}
                ~AppListMock(){}
                //IMessageInterface
                MOCK_METHOD1(onRequest,Result(Json::Value));
                MOCK_METHOD1(onNotification,void(Json::Value));
                MOCK_METHOD1(onResult,void(Json::Value));
                MOCK_METHOD2(onRawData,void(void *p, int iLength));
                MOCK_METHOD1(onError,void(std::string error));

                //AppListInterface
                MOCK_METHOD1(OnAppActivated,void(int appID));
                MOCK_METHOD0(OnAppExit,void());
                MOCK_METHOD0(ShowPreviousUI,void());
                MOCK_METHOD0(OnShowDeviceList,void());
                MOCK_METHOD0(getActiveApp,AppDataInterface*());
                MOCK_METHOD1(setUIManager,void(UIInterface *pUI));
                MOCK_METHOD2(getAppList,void(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames));
                MOCK_METHOD3(getAppList,void(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames, std::vector<std::string> &vIconPath));
                MOCK_METHOD4(getAppList,void(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames, std::vector<std::string> &vIconPath, std::vector<std::string> &vAppTypes));
                MOCK_METHOD1(OnDeviceSelect,void(const std::string id));
                MOCK_METHOD1(getDeviceList,void(std::vector<DeviceData> &vDevice));
                MOCK_METHOD0(OnStartDeviceDiscovery,void());
                MOCK_METHOD1(appUnregistered,void(int appId));

                void DelegateGetActiveApp(){
                    ON_CALL(*this,getActiveApp()).WillByDefault(Invoke(&applist_,&AppList::getActiveApp));
                }

                void DelegateOnStartDeviceDiscovery(){
                    ON_CALL(*this,OnStartDeviceDiscovery()).WillByDefault(Invoke(&applist_,&AppList::OnStartDeviceDiscovery));
                }
                void DelegateOnShowDeviceList(){
                    ON_CALL(*this,OnShowDeviceList()).WillByDefault(Invoke(&applist_,&AppList::OnShowDeviceList));
                }

                void DelegateSetUIManager(UIInterface *pUI){
                    ON_CALL(*this,setUIManager(pUI)).WillByDefault(Invoke(&applist_,&AppList::setUIManager));
                }

                void DelegateOnRequest(Json::Value &data){
                    ON_CALL(*this,onRequest(data)).WillByDefault(Invoke(&applist_,&AppList::onRequest));
                }

                void DelegateOnDeviceSelect(const std::string id){
                    ON_CALL(*this,OnDeviceSelect(id)).WillByDefault(Invoke(&applist_,&AppList::OnDeviceSelect));
                }

                void DelegateGetAppList(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames, std::vector<std::string> &vIconPath){
                    ON_CALL(*this,getAppList(vAppIDs,vAppNames,vIconPath)).WillByDefault(Invoke(&applist_,static_cast<void (AppList::*)(std::vector<int> &, std::vector<std::string> &, std::vector<std::string> &) >(&AppList::getAppList)));
                }

                AppList &DelegateGetAppList(){
                    return applist_;
                }

            private:
                AppList applist_;
            };

            class AppDataMock:public AppDataInterface
            {
            public:
                AppDataMock(){

                }
                ~AppDataMock(){}
                MOCK_METHOD0(getShowData,Json::Value&());
                MOCK_METHOD0(getAlertJson,Json::Value&());
                MOCK_METHOD0(getSlider,Json::Value&());
                MOCK_METHOD0(getScrollableMsgJson,Json::Value&());
                MOCK_METHOD0(getAudioPassThruJson,Json::Value&());
                MOCK_METHOD0(getInteractionJson,Json::Value&());
                MOCK_METHOD0(getMediaClockJson,Json::Value&());
                MOCK_METHOD0(getCommandList,std::vector<SMenuCommand>());
                MOCK_METHOD1(getCommandList,std::vector<SMenuCommand>(int subMenuID));
                MOCK_METHOD0(getUrlString,std::string());
                MOCK_METHOD0(getAppName,std::string());
                MOCK_METHOD0(getAppIconFile,std::string());
                MOCK_METHOD0(getCurUI,int());
                MOCK_METHOD0(OnShowCommand,void());
                MOCK_METHOD3(OnSoftButtonClick,void(int sbID, int mode, std::string strName));
                MOCK_METHOD1(OnCommandClick,void(int cmdID));
                MOCK_METHOD1(OnAlertResponse,void(int reason));
                MOCK_METHOD1(OnScrollMessageResponse,void(int reason));
                MOCK_METHOD2(OnSliderResponse,void(int code, int sliderPosition));
                MOCK_METHOD1(OnTTSSpeek,void(int code));
                MOCK_METHOD1(OnPerformAudioPassThru,void(int code));
                MOCK_METHOD3(OnPerformInteraction,void(int code, int choiceID, bool bVR));
                MOCK_METHOD1(OnSetMediaClockTimerResponse,void(int code));
                MOCK_METHOD3(OnVideoScreenTouch,void(TOUCH_TYPE touch, int x, int y));
                MOCK_METHOD0(GetActiveTemplate,std::string());
                MOCK_METHOD0(getAppID,int());

                void DelegateOnSoftButtonClick(){
                    ON_CALL(*this,OnSoftButtonClick(_,_,_)).WillByDefault(Invoke(&appdata_,&AppData::OnSoftButtonClick));

                }
                void DelegateOnPerformInteraction(int code, int choiceID){
                    ON_CALL(*this,OnPerformInteraction(code,choiceID,_)).WillByDefault(Invoke(&appdata_,&AppData::OnPerformInteraction));
                }

                void DelegateOnCommandClick( int cmdID){
                    ON_CALL(*this,OnCommandClick(cmdID)).WillByDefault(Invoke(&appdata_,&AppData::OnCommandClick));
                }

            private:
                AppData appdata_;
            };

            class ChannelMock:public Channel
            {
            public:
                ChannelMock():Channel(999,"MOCK")
                  ,channel_(Channel(600,"UI"))
                {
                }
                ~ChannelMock(){}
                MOCK_METHOD2(onReceiveData,void(void *, int));
                MOCK_METHOD0(getChannelName,std::string());
                MOCK_METHOD2(setSocketManager,void(ISocketManager *pManager, void *pHandle));
                MOCK_METHOD0(onOpen,void());


                MOCK_METHOD4(sendError,void(int resultCode, int id, std::string method, std::string message));

                MOCK_METHOD1(onRequest,void(Json::Value &));
                MOCK_METHOD1(onNotification,void(Json::Value &));
                MOCK_METHOD1(onResult,void(Json::Value &));
                MOCK_METHOD2(onRawData,void(void *p, int iLength));
                MOCK_METHOD1(onError,void(std::string error));
                MOCK_METHOD1(sendJson,void(Json::Value &data));
                MOCK_METHOD2(sendError,void(int id, Json::Value &error));
                MOCK_METHOD2(sendResult,void(int id, Json::Value &result));

                MOCK_METHOD3(sendRequest,void(int id, const std::string mothod, const Json::Value &params));
                MOCK_METHOD2(sendNotification,void(const std::string mothod, const Json::Value &params));
                MOCK_METHOD0(onRegistered,void());
                MOCK_METHOD0(onUnregistered,void());
                MOCK_METHOD3(setStaticResult,void(std::string attri, std::string ref, Json::Value value));
                MOCK_METHOD3(sendResult,void(int id, std::string ref, Result code));
                MOCK_METHOD4(sendError,void(int id, std::string ref, std::string message, Result code));



                void DelegateOnReceiveData(void *data, int len){Channel::onReceiveData(data,len);}
                std::string DelegateGetChannelName(){return Channel::getChannelName();}
                void DelegateonOpen(){ Channel::onOpen();}
                void DelegateSendError(int resultCode, int id, std::string method, std::string message){ Channel::sendError(resultCode,id, method,message);}

                void DelegateOnRequest(Json::Value & data){ Channel::onRequest(data);}
                void DelegateSendRequest(int id, std::string ref, Result code){ Channel::sendResult(id,ref, code);}
                void DelegateSendRequest(int id, Json::Value &result){ Channel::sendResult(id,result);}

                void DelegateSetStaticResult(std::string attri, std::string ref, Json::Value value){ Channel::setStaticResult(attri,ref, value);}

            public:
                UI UI_;
                Channel channel_;
            };

            class UIInterfaceMock: public UIInterface
            {
             public:

                UIInterfaceMock(){}
                MOCK_METHOD1(onRecvDataSteam,void (Json::Value jsonObj));
                MOCK_METHOD0(onAppActive,void());
                MOCK_METHOD0(onAppStop,void());
                MOCK_METHOD1(onAppShow,void(int type));
                MOCK_METHOD1(onAppRegister,void(int appId));
                MOCK_METHOD1(onAppUnregister,void(int appId));
                MOCK_METHOD0(onVideoStreamStart,void());
                MOCK_METHOD0(onVideoStreamStop,void());
                MOCK_METHOD0(OnEndAudioPassThru,void());
                MOCK_METHOD2(tsSpeak,void(int VRID, std::string strText));
                MOCK_METHOD0(ShowDeviceList,void());
                MOCK_METHOD1(SetSDLStatus,void(bool bConnect));
                MOCK_METHOD1(SetAppListInterface,void(AppListInterface *pList));
                MOCK_METHOD0(initAppHMI,void());
                MOCK_METHOD1(FindTemplate,bool(std::string name));

            };
        }
    }
}
#endif // GEN3UI_MOCKMODULE_H
