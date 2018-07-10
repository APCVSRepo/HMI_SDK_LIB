#include "MediaShowTest.h"

using namespace test;
using namespace hmi_sdk;
using namespace rpc_test;


CMediaShowTest::CMediaShowTest()
{
}

void CMediaShowTest::SetUpTestCase()
{

}

void CMediaShowTest::TearDownTestCase()
{

}

void CMediaShowTest::SetUp()
{

}

void CMediaShowTest::TearDown()
{

}


TEST_F(CMediaShowTest,OnSoftButtonClick_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnSoftButtonClick(1,BUTTON_SHORT,"")).Times(AtLeast(1));

    CMediaShow cMediaShow(&appListMock);
    cMediaShow.SoftBtnClickedSlot(1);
}

TEST_F(CMediaShowTest,OnShowCommand_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnShowCommand()).Times(AtLeast(1));

    CMediaShow cMediaShow(&appListMock);
    cMediaShow.BtnMenuClickedSlots();

}



TEST_F(CMediaShowTest,getMediaClockJson_Success)
{
    AppListMock appListMock;
    UIInterfaceMock uiManagerMock;

    Json::Value obj;
    Json::Value appList_;
    Json::Value eleArr_;
    Json::Value element1;
    Json::Value element2;

    element1["appName"] = "Music1";
    element1["appID"] = 3;
    element1["icon"] = "";

    element2["appName"] = "Music2";
    element2["appID"] = 4;
    element2["icon"] = "";

    eleArr_.append(element1);
    eleArr_.append(element2);

    appList_["applications"] = eleArr_;

    obj["id"] = 64;
    obj["jsonrpc"] = "2.0";
    obj["method"] = "BasicCommunication.UpdateAppList";
    obj["params"] = appList_;


    appListMock.DelegateOnRequest(obj);
    appListMock.DelegateSetUIManager(&uiManagerMock);
    EXPECT_CALL(appListMock,onRequest(obj)).Times(AtLeast(1));
    EXPECT_CALL(appListMock,setUIManager(&uiManagerMock));
    EXPECT_CALL(uiManagerMock,onAppShow(ID_APPLINK)).Times(AtLeast(1));

    appListMock.setUIManager(&uiManagerMock);
    appListMock.onRequest(obj);

    appListMock.DelegateGetActiveApp();
    EXPECT_CALL(appListMock,getActiveApp());
    EXPECT_FALSE(appListMock.getActiveApp());

    Json::Value appObj;
    Json::Value appId;

    appObj["method"] = "BasicCommunication.ActivateApp";
    appId["appID"] = 3;

    appObj["id"] = 64;
    appObj["jsonrpc"] = "2.0";
    appObj["params"] = appId;

    appListMock.DelegateOnRequest(appObj);
    EXPECT_CALL(appListMock,onRequest(appObj)).Times(AtLeast(1));
    appListMock.onRequest(appObj);

    EXPECT_CALL(appListMock,getActiveApp()).Times(AtLeast(1));
    EXPECT_TRUE(appListMock.getActiveApp());
    EXPECT_EQ("Music1",appListMock.getActiveApp()->getAppName());

    Json::Value mediaClockObj;
    Json::Value params;
    Json::Value startTime;
    Json::Value endTime;
    mediaClockObj["method"] = "UI.SetMediaClockTimer";
    mediaClockObj["jsonrpc"] = "2.0";
    mediaClockObj["id"] = 65;
    params["updateMode"] = "COUNTUP";
    params["appID"] = 3;
    startTime["hours"] = 0;
    startTime["minutes"] = 0;
    startTime["seconds"] = 0;
    endTime["hours"] = 0;
    endTime["minutes"] = 3;
    endTime["seconds"] = 1;
    params["startTime"]= startTime;
    params["endTime"]= endTime;
    mediaClockObj["params"] = params;
    appListMock.DelegateOnRequest(mediaClockObj);
    EXPECT_CALL(appListMock,onRequest(mediaClockObj)).Times(AtLeast(1));
    appListMock.onRequest(mediaClockObj);

    EXPECT_EQ("COUNTUP",appListMock.getActiveApp()->getMediaClockJson()["params"]["updateMode"].asString());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["hours"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["minutes"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["seconds"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["hours"].asInt());
    EXPECT_EQ(3,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["minutes"].asInt());
    EXPECT_EQ(1,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["seconds"].asInt());

}



TEST_F(CMediaShowTest,OnSetMediaClockTimerResponse_COUNTUP_Success)
{
    AppListMock appListMock;
    UIInterfaceMock uiManagerMock;

    Json::Value obj;
    Json::Value appList_;
    Json::Value eleArr_;
    Json::Value element1;
    Json::Value element2;

    element1["appName"] = "Music1";
    element1["appID"] = 3;
    element1["icon"] = "";

    element2["appName"] = "Music2";
    element2["appID"] = 4;
    element2["icon"] = "";

    eleArr_.append(element1);
    eleArr_.append(element2);

    appList_["applications"] = eleArr_;

    obj["id"] = 64;
    obj["jsonrpc"] = "2.0";
    obj["method"] = "BasicCommunication.UpdateAppList";
    obj["params"] = appList_;


    appListMock.DelegateOnRequest(obj);
    appListMock.DelegateSetUIManager(&uiManagerMock);
    EXPECT_CALL(appListMock,onRequest(obj)).Times(AtLeast(1));
    EXPECT_CALL(appListMock,setUIManager(&uiManagerMock));
    EXPECT_CALL(uiManagerMock,onAppShow(ID_APPLINK)).Times(AtLeast(1));

    appListMock.setUIManager(&uiManagerMock);
    appListMock.onRequest(obj);

    appListMock.DelegateGetActiveApp();
    EXPECT_CALL(appListMock,getActiveApp());
    EXPECT_FALSE(appListMock.getActiveApp());

    Json::Value appObj;
    Json::Value appId;

    appObj["method"] = "BasicCommunication.ActivateApp";
    appId["appID"] = 3;

    appObj["id"] = 64;
    appObj["jsonrpc"] = "2.0";
    appObj["params"] = appId;

    appListMock.DelegateOnRequest(appObj);
    EXPECT_CALL(appListMock,onRequest(appObj)).Times(AtLeast(1));
    appListMock.onRequest(appObj);

    EXPECT_CALL(appListMock,getActiveApp()).Times(AtLeast(1));
    EXPECT_TRUE(appListMock.getActiveApp());
    EXPECT_EQ("Music1",appListMock.getActiveApp()->getAppName());

    Json::Value mediaClockObj;
    Json::Value params;
    Json::Value startTime;
    Json::Value endTime;
    mediaClockObj["method"] = "UI.SetMediaClockTimer";
    mediaClockObj["jsonrpc"] = "2.0";
    mediaClockObj["id"] = 65;
    params["updateMode"] = "COUNTUP";
    params["appID"] = 3;
    startTime["hours"] = 0;
    startTime["minutes"] = 0;
    startTime["seconds"] = 0;
    endTime["hours"] = 0;
    endTime["minutes"] = 3;
    endTime["seconds"] = 1;
    params["startTime"]= startTime;
    params["endTime"]= endTime;
    mediaClockObj["params"] = params;

    appListMock.DelegateOnRequest(mediaClockObj);
    EXPECT_CALL(appListMock,onRequest(mediaClockObj)).Times(AtLeast(1));
    appListMock.onRequest(mediaClockObj);

    EXPECT_EQ("COUNTUP",appListMock.getActiveApp()->getMediaClockJson()["params"]["updateMode"].asString());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["hours"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["minutes"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["seconds"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["hours"].asInt());
    EXPECT_EQ(3,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["minutes"].asInt());
    EXPECT_EQ(1,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["seconds"].asInt());

    CMediaShow cMediaShow(&appListMock);
    cMediaShow.UpdateMediaClockTimer();
}


TEST_F(CMediaShowTest,OnSetMediaClockTimerResponse_COUNTDOWN_Success)
{
    AppListMock appListMock;
    UIInterfaceMock uiManagerMock;

    Json::Value obj;
    Json::Value appList_;
    Json::Value eleArr_;
    Json::Value element1;
    Json::Value element2;

    element1["appName"] = "Music1";
    element1["appID"] = 3;
    element1["icon"] = "";

    element2["appName"] = "Music2";
    element2["appID"] = 4;
    element2["icon"] = "";

    eleArr_.append(element1);
    eleArr_.append(element2);

    appList_["applications"] = eleArr_;

    obj["id"] = 64;
    obj["jsonrpc"] = "2.0";
    obj["method"] = "BasicCommunication.UpdateAppList";
    obj["params"] = appList_;


    appListMock.DelegateOnRequest(obj);
    appListMock.DelegateSetUIManager(&uiManagerMock);
    EXPECT_CALL(appListMock,onRequest(obj)).Times(AtLeast(1));
    EXPECT_CALL(appListMock,setUIManager(&uiManagerMock));
    EXPECT_CALL(uiManagerMock,onAppShow(ID_APPLINK)).Times(AtLeast(1));

    appListMock.setUIManager(&uiManagerMock);
    appListMock.onRequest(obj);

    appListMock.DelegateGetActiveApp();
    EXPECT_CALL(appListMock,getActiveApp());
    EXPECT_FALSE(appListMock.getActiveApp());

    Json::Value appObj;
    Json::Value appId;

    appObj["method"] = "BasicCommunication.ActivateApp";
    appId["appID"] = 3;

    appObj["id"] = 64;
    appObj["jsonrpc"] = "2.0";
    appObj["params"] = appId;

    appListMock.DelegateOnRequest(appObj);
    EXPECT_CALL(appListMock,onRequest(appObj)).Times(AtLeast(1));
    appListMock.onRequest(appObj);

    EXPECT_CALL(appListMock,getActiveApp()).Times(AtLeast(1));
    EXPECT_TRUE(appListMock.getActiveApp());
    EXPECT_EQ("Music1",appListMock.getActiveApp()->getAppName());

    Json::Value mediaClockObj;
    Json::Value params;
    Json::Value startTime;
    Json::Value endTime;
    mediaClockObj["method"] = "UI.SetMediaClockTimer";
    mediaClockObj["jsonrpc"] = "2.0";
    mediaClockObj["id"] = 65;
    params["updateMode"] = "COUNTDOWN";
    params["appID"] = 3;
    startTime["hours"] = 0;
    startTime["minutes"] = 0;
    startTime["seconds"] = 0;
    endTime["hours"] = 0;
    endTime["minutes"] = 3;
    endTime["seconds"] = 1;
    params["startTime"]= startTime;
    params["endTime"]= endTime;
    mediaClockObj["params"] = params;

    appListMock.DelegateOnRequest(mediaClockObj);
    EXPECT_CALL(appListMock,onRequest(mediaClockObj)).Times(AtLeast(1));
    appListMock.onRequest(mediaClockObj);

    EXPECT_EQ("COUNTDOWN",appListMock.getActiveApp()->getMediaClockJson()["params"]["updateMode"].asString());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["hours"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["minutes"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["seconds"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["hours"].asInt());
    EXPECT_EQ(3,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["minutes"].asInt());
    EXPECT_EQ(1,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["seconds"].asInt());

    CMediaShow cMediaShow(&appListMock);
    cMediaShow.UpdateMediaClockTimer();
}



TEST_F(CMediaShowTest,OnSetMediaClockTimerResponse_PAUSE_Success)
{
    AppListMock appListMock;
    UIInterfaceMock uiManagerMock;

    Json::Value obj;
    Json::Value appList_;
    Json::Value eleArr_;
    Json::Value element1;
    Json::Value element2;

    element1["appName"] = "Music1";
    element1["appID"] = 3;
    element1["icon"] = "";

    element2["appName"] = "Music2";
    element2["appID"] = 4;
    element2["icon"] = "";

    eleArr_.append(element1);
    eleArr_.append(element2);

    appList_["applications"] = eleArr_;

    obj["id"] = 64;
    obj["jsonrpc"] = "2.0";
    obj["method"] = "BasicCommunication.UpdateAppList";
    obj["params"] = appList_;


    appListMock.DelegateOnRequest(obj);
    appListMock.DelegateSetUIManager(&uiManagerMock);
    EXPECT_CALL(appListMock,onRequest(obj)).Times(AtLeast(1));
    EXPECT_CALL(appListMock,setUIManager(&uiManagerMock));
    EXPECT_CALL(uiManagerMock,onAppShow(ID_APPLINK)).Times(AtLeast(1));

    appListMock.setUIManager(&uiManagerMock);
    appListMock.onRequest(obj);

    appListMock.DelegateGetActiveApp();
    EXPECT_CALL(appListMock,getActiveApp());
    EXPECT_FALSE(appListMock.getActiveApp());

    Json::Value appObj;
    Json::Value appId;

    appObj["method"] = "BasicCommunication.ActivateApp";
    appId["appID"] = 3;

    appObj["id"] = 64;
    appObj["jsonrpc"] = "2.0";
    appObj["params"] = appId;

    appListMock.DelegateOnRequest(appObj);
    EXPECT_CALL(appListMock,onRequest(appObj)).Times(AtLeast(1));
    appListMock.onRequest(appObj);

    EXPECT_CALL(appListMock,getActiveApp()).Times(AtLeast(1));
    EXPECT_TRUE(appListMock.getActiveApp());
    EXPECT_EQ("Music1",appListMock.getActiveApp()->getAppName());

    Json::Value mediaClockObj;
    Json::Value params;
    Json::Value startTime;
    Json::Value endTime;
    mediaClockObj["method"] = "UI.SetMediaClockTimer";
    mediaClockObj["jsonrpc"] = "2.0";
    mediaClockObj["id"] = 65;
    params["updateMode"] = "PAUSE";
    params["appID"] = 3;
    startTime["hours"] = 0;
    startTime["minutes"] = 0;
    startTime["seconds"] = 0;
    endTime["hours"] = 0;
    endTime["minutes"] = 3;
    endTime["seconds"] = 1;
    params["startTime"]= startTime;
    params["endTime"]= endTime;
    mediaClockObj["params"] = params;

    appListMock.DelegateOnRequest(mediaClockObj);
    EXPECT_CALL(appListMock,onRequest(mediaClockObj)).Times(AtLeast(1));
    appListMock.onRequest(mediaClockObj);

    EXPECT_EQ("PAUSE",appListMock.getActiveApp()->getMediaClockJson()["params"]["updateMode"].asString());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["hours"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["minutes"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["seconds"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["hours"].asInt());
    EXPECT_EQ(3,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["minutes"].asInt());
    EXPECT_EQ(1,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["seconds"].asInt());

    CMediaShow cMediaShow(&appListMock);
    cMediaShow.UpdateMediaClockTimer();
}



TEST_F(CMediaShowTest,OnSetMediaClockTimerResponse_RESUME_Success)
{
    AppListMock appListMock;
    UIInterfaceMock uiManagerMock;

    Json::Value obj;
    Json::Value appList_;
    Json::Value eleArr_;
    Json::Value element1;
    Json::Value element2;

    element1["appName"] = "Music1";
    element1["appID"] = 3;
    element1["icon"] = "";

    element2["appName"] = "Music2";
    element2["appID"] = 4;
    element2["icon"] = "";

    eleArr_.append(element1);
    eleArr_.append(element2);

    appList_["applications"] = eleArr_;

    obj["id"] = 64;
    obj["jsonrpc"] = "2.0";
    obj["method"] = "BasicCommunication.UpdateAppList";
    obj["params"] = appList_;


    appListMock.DelegateOnRequest(obj);
    appListMock.DelegateSetUIManager(&uiManagerMock);
    EXPECT_CALL(appListMock,onRequest(obj)).Times(AtLeast(1));
    EXPECT_CALL(appListMock,setUIManager(&uiManagerMock));
    EXPECT_CALL(uiManagerMock,onAppShow(ID_APPLINK)).Times(AtLeast(1));

    appListMock.setUIManager(&uiManagerMock);
    appListMock.onRequest(obj);

    appListMock.DelegateGetActiveApp();
    EXPECT_CALL(appListMock,getActiveApp());
    EXPECT_FALSE(appListMock.getActiveApp());

    Json::Value appObj;
    Json::Value appId;

    appObj["method"] = "BasicCommunication.ActivateApp";
    appId["appID"] = 3;

    appObj["id"] = 64;
    appObj["jsonrpc"] = "2.0";
    appObj["params"] = appId;

    appListMock.DelegateOnRequest(appObj);
    EXPECT_CALL(appListMock,onRequest(appObj)).Times(AtLeast(1));
    appListMock.onRequest(appObj);

    EXPECT_CALL(appListMock,getActiveApp()).Times(AtLeast(1));
    EXPECT_TRUE(appListMock.getActiveApp());
    EXPECT_EQ("Music1",appListMock.getActiveApp()->getAppName());

    Json::Value mediaClockObj;
    Json::Value params;
    Json::Value startTime;
    Json::Value endTime;
    mediaClockObj["method"] = "UI.SetMediaClockTimer";
    mediaClockObj["jsonrpc"] = "2.0";
    mediaClockObj["id"] = 65;
    params["updateMode"] = "RESUME";
    params["appID"] = 3;
    startTime["hours"] = 0;
    startTime["minutes"] = 0;
    startTime["seconds"] = 0;
    endTime["hours"] = 0;
    endTime["minutes"] = 3;
    endTime["seconds"] = 1;
    params["startTime"]= startTime;
    params["endTime"]= endTime;
    mediaClockObj["params"] = params;

    appListMock.DelegateOnRequest(mediaClockObj);
    EXPECT_CALL(appListMock,onRequest(mediaClockObj)).Times(AtLeast(1));
    appListMock.onRequest(mediaClockObj);

    EXPECT_EQ("RESUME",appListMock.getActiveApp()->getMediaClockJson()["params"]["updateMode"].asString());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["hours"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["minutes"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["seconds"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["hours"].asInt());
    EXPECT_EQ(3,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["minutes"].asInt());
    EXPECT_EQ(1,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["seconds"].asInt());

    CMediaShow cMediaShow(&appListMock);
    cMediaShow.UpdateMediaClockTimer();
}


TEST_F(CMediaShowTest,OnSetMediaClockTimerResponse_CLEAR_Success)
{
    AppListMock appListMock;
    UIInterfaceMock uiManagerMock;

    Json::Value obj;
    Json::Value appList_;
    Json::Value eleArr_;
    Json::Value element1;
    Json::Value element2;

    element1["appName"] = "Music1";
    element1["appID"] = 3;
    element1["icon"] = "";

    element2["appName"] = "Music2";
    element2["appID"] = 4;
    element2["icon"] = "";

    eleArr_.append(element1);
    eleArr_.append(element2);

    appList_["applications"] = eleArr_;

    obj["id"] = 64;
    obj["jsonrpc"] = "2.0";
    obj["method"] = "BasicCommunication.UpdateAppList";
    obj["params"] = appList_;


    appListMock.DelegateOnRequest(obj);
    appListMock.DelegateSetUIManager(&uiManagerMock);
    EXPECT_CALL(appListMock,onRequest(obj)).Times(AtLeast(1));
    EXPECT_CALL(appListMock,setUIManager(&uiManagerMock));
    EXPECT_CALL(uiManagerMock,onAppShow(ID_APPLINK)).Times(AtLeast(1));

    appListMock.setUIManager(&uiManagerMock);
    appListMock.onRequest(obj);

    appListMock.DelegateGetActiveApp();
    EXPECT_CALL(appListMock,getActiveApp());
    EXPECT_FALSE(appListMock.getActiveApp());

    Json::Value appObj;
    Json::Value appId;

    appObj["method"] = "BasicCommunication.ActivateApp";
    appId["appID"] = 3;

    appObj["id"] = 64;
    appObj["jsonrpc"] = "2.0";
    appObj["params"] = appId;

    appListMock.DelegateOnRequest(appObj);
    EXPECT_CALL(appListMock,onRequest(appObj)).Times(AtLeast(1));
    appListMock.onRequest(appObj);

    EXPECT_CALL(appListMock,getActiveApp()).Times(AtLeast(1));
    EXPECT_TRUE(appListMock.getActiveApp());
    EXPECT_EQ("Music1",appListMock.getActiveApp()->getAppName());

    Json::Value mediaClockObj;
    Json::Value params;
    Json::Value startTime;
    Json::Value endTime;
    mediaClockObj["method"] = "UI.SetMediaClockTimer";
    mediaClockObj["jsonrpc"] = "2.0";
    mediaClockObj["id"] = 65;
    params["updateMode"] = "CLEAR";
    params["appID"] = 3;
    startTime["hours"] = 0;
    startTime["minutes"] = 0;
    startTime["seconds"] = 0;
    endTime["hours"] = 0;
    endTime["minutes"] = 3;
    endTime["seconds"] = 1;
    params["startTime"]= startTime;
    params["endTime"]= endTime;
    mediaClockObj["params"] = params;

    appListMock.DelegateOnRequest(mediaClockObj);
    EXPECT_CALL(appListMock,onRequest(mediaClockObj)).Times(AtLeast(1));
    appListMock.onRequest(mediaClockObj);

    EXPECT_EQ("CLEAR",appListMock.getActiveApp()->getMediaClockJson()["params"]["updateMode"].asString());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["hours"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["minutes"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["startTime"]["seconds"].asInt());
    EXPECT_EQ(0,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["hours"].asInt());
    EXPECT_EQ(3,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["minutes"].asInt());
    EXPECT_EQ(1,appListMock.getActiveApp()->getMediaClockJson()["params"]["endTime"]["seconds"].asInt());

    CMediaShow cMediaShow(&appListMock);
    cMediaShow.UpdateMediaClockTimer();
}

