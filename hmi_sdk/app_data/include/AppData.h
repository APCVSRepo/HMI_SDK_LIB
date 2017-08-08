#ifndef APPDATA_H_
#define APPDATA_H_

#include "SDLConnector.h"
#include "AppDataInterface.h"
#include "UIInterface.h"

class AppData : public AppDataInterface
{
public:
    AppData();

    void setUIManager(UIInterface *pcallBack);

    Json::Value& getShowData();
	Json::Value& getAlertJson();
	Json::Value& getSlider();
	Json::Value& getScrollableMsgJson();
	Json::Value& getAudioPassThruJson();
	Json::Value& getInteractionJson();
	Json::Value& getMediaClockJson();
	std::vector<SMenuCommand> getCommandList();
    std::vector<SMenuCommand> getCommandList(int subMenuID);
	std::string getUrlString();
    std::string getAppName();
    std::string getAppIconFile();

    int getCurUI();

    void OnShowCommand();
    void OnSoftButtonClick(int sbID, int mode,std::string strName = "");
    void OnCommandClick(int cmdID);
    void OnAlertResponse(int reason);
    void OnScrollMessageResponse(int reason);
    void OnSliderResponse( int code, int sliderPosition);
    void OnTTSSpeek(int code);
    void OnPerformAudioPassThru(int code);
    void OnPerformInteraction(int code, int choiceID, bool bVR = false);

    void OnSetMediaClockTimerResponse(int iCode);

    void OnVideoScreenTouch(TOUCH_TYPE touch,int x,int y);

    Result recvFromServer(Json::Value);

    // 增加一个退出app的指令
    void addExitAppCommand();

    // bInApp: just show the UI of the app, or could bjump to the applist.
    bool ShowPreviousUI(bool bInApp = true);

private:
    UIInterface *m_pUIManager;
    std::vector<int> m_vecUIStack;
    void ShowUI(int);

    Json::Value m_JsonShow;
    std::vector <SMenuCommand > m_MenuCommands;

    Json::Value m_JsonAlert;
    Json::Value m_JsonSlider;
    Json::Value m_JsonScrollableMessage;
    Json::Value m_JsonAudioPassThru;
    Json::Value m_JsonInteraction;
    Json::Value m_JsonMediaClock;
    Json::Value m_JsonTtsSpeak;

    void addCommand(Json::Value jsonObj);
    void addSubMenu(Json::Value jsonObj);
    void delCommand(Json::Value jsonObj);
    void delSubMenu(Json::Value jsonObj);
    void alert(Json::Value jsonObj);
    void slider(Json::Value jsonObj);
    void scrollableMessage(Json::Value jsonObj);
    void performAudioPassThru(Json::Value jsonObj);
    void performInteraction(Json::Value jsonObj);
    void systemRequest(Json::Value jsonObj);
    void tsSpeak(Json::Value jsonObj);

    Json::Value m_JsonVideoStream;
    void videoStreamStart(Json::Value jsonObj);
    void videoStreamStop(Json::Value jsonObj);

public:
    std::string m_strAppIconFilePath;
    int m_iAppID;
    std::string m_szAppName;
};

#endif // APPDATA_H_
