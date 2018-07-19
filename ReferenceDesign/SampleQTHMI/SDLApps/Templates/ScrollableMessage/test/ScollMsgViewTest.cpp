#include "ScollMsgViewTest.h"

using namespace test;
using namespace hmi_sdk;
using namespace rpc_test;


CScollMsgViewTest::CScollMsgViewTest()
{
}

void CScollMsgViewTest::SetUpTestCase()
{

}

void CScollMsgViewTest::TearDownTestCase()
{

}

void CScollMsgViewTest::SetUp()
{

}

void CScollMsgViewTest::TearDown()
{

}


TEST_F(CScollMsgViewTest,getAppName_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
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


}


TEST_F(CScollMsgViewTest,getScrollableMsgJson_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
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

    Json::Value scrollMessageObj;
    Json::Value params;
    scrollMessageObj["method"] = "UI.ScrollableMessage";
    scrollMessageObj["jsonrpc"] = "2.0";
    scrollMessageObj["id"] = -1;
    params["timeout"] = 3000;
    params["messageText"] = "test getScrollableMsgJson_Success!";
    params["appID"] = 3;
    scrollMessageObj["params"] = params;
    appListMock.DelegateOnRequest(scrollMessageObj);
    EXPECT_CALL(appListMock,onRequest(scrollMessageObj)).Times(AtLeast(1));
    appListMock.onRequest(scrollMessageObj);

    EXPECT_EQ(3000,appListMock.getActiveApp()->getScrollableMsgJson()["params"]["timeout"].asInt());

}

TEST_F(CScollMsgViewTest,OnTimeOutSlot_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnScrollMessageResponse(RESULT_SUCCESS)).Times(AtLeast(1));


    CScollMsgView cScollMsgView(&appListMock);
    cScollMsgView.OnTimeOutSlot();

}

TEST_F(CScollMsgViewTest,OnReturnBtnClicked_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnScrollMessageResponse(RESULT_ABORTED)).Times(AtLeast(1));

    CScollMsgView cScollMsgView(&appListMock);
    cScollMsgView.OnReturnBtnClicked();

}

TEST_F(CScollMsgViewTest,OnSoftBtnClicked_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnScrollMessageResponse(RESULT_ABORTED)).Times(AtLeast(1));

    CScollMsgView cScollMsgView(&appListMock);
    cScollMsgView.OnSoftBtnClicked(1);

    EXPECT_CALL(appDataMock,OnSoftButtonClick(2,BUTTON_SHORT,"")).Times(AtLeast(1));
    cScollMsgView.OnSoftBtnClicked(2);

}



TEST_F(CScollMsgViewTest,OnScrollMessageResponse_Success)
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

    Json::Value scrollMessageObj;
    Json::Value params;
    scrollMessageObj["method"] = "UI.ScrollableMessage";
    scrollMessageObj["jsonrpc"] = "2.0";
    scrollMessageObj["id"] = 65;
    params["timeout"] = 3000;
    params["messageText"] = "test getScrollableMsgJson_Success!";
    params["appID"] = 3;
    scrollMessageObj["params"] = params;
    appListMock.DelegateOnRequest(scrollMessageObj);
    EXPECT_CALL(appListMock,onRequest(scrollMessageObj)).Times(AtLeast(1));
    appListMock.onRequest(scrollMessageObj);

    EXPECT_EQ(3000,appListMock.getActiveApp()->getScrollableMsgJson()["params"]["timeout"].asInt());
    EXPECT_NE(-1,appListMock.getActiveApp()->getScrollableMsgJson()["params"]["id"].asInt());

    CScollMsgView cScollMsgView(&appListMock);
    cScollMsgView.OnSoftBtnClicked(1);
}


TEST_F(CScollMsgViewTest,OnSoftButtonClick_Success)
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

    Json::Value scrollMessageObj;
    Json::Value params;
    scrollMessageObj["method"] = "UI.ScrollableMessage";
    scrollMessageObj["jsonrpc"] = "2.0";
    scrollMessageObj["id"] = 65;
    params["timeout"] = 3000;
    params["messageText"] = "test getScrollableMsgJson_Success!";
    params["appID"] = 3;
    scrollMessageObj["params"] = params;
    appListMock.DelegateOnRequest(scrollMessageObj);
    EXPECT_CALL(appListMock,onRequest(scrollMessageObj)).Times(AtLeast(1));
    appListMock.onRequest(scrollMessageObj);

    EXPECT_EQ(3000,appListMock.getActiveApp()->getScrollableMsgJson()["params"]["timeout"].asInt());
    EXPECT_NE(-1,appListMock.getActiveApp()->getScrollableMsgJson()["params"]["id"].asInt());

    CScollMsgView cScollMsgView(&appListMock);
    cScollMsgView.OnSoftBtnClicked(2);
}
