#include "AlertViewTest.h"

using namespace test;
using namespace hmi_sdk;
using namespace rpc_test;


AlertViewTest::AlertViewTest()
{
}


void AlertViewTest::SetUpTestCase()
{

}


void AlertViewTest::TearDownTestCase()
{

}


void AlertViewTest::SetUp()
{
}


void AlertViewTest::TearDown()
{

}

TEST_F(AlertViewTest,OnSoftBtnClicked_Normal_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnAlertResponse(RESULT_SUCCESS)).Times(AtLeast(1));
    EXPECT_CALL(appDataMock,OnSoftButtonClick(100,RESULT_SUCCESS,_)).Times(AtLeast(1));

    AlertView alertView(&appListMock);
    alertView.OnSoftBtnClicked(100);

}

TEST_F(AlertViewTest,OnSoftBtnClicked_NoId_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnAlertResponse(RESULT_SUCCESS)).Times(AtLeast(1));
    EXPECT_CALL(appDataMock,OnSoftButtonClick(_,_,_)).Times(AtLeast(0));

    AlertView alertView(&appListMock);
    alertView.OnSoftBtnClicked(-1);

}

TEST_F(AlertViewTest,OnSoftBtnClicked_sendNotification_SUCCESS)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appDataMock.DelegateOnSoftButtonClick();
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnAlertResponse(RESULT_SUCCESS)).Times(AtLeast(1));
    EXPECT_CALL(appDataMock,OnSoftButtonClick(100,RESULT_SUCCESS,_)).Times(AtLeast(1));

    AlertView alertView(&appListMock);
    alertView.OnSoftBtnClicked(100);

}

TEST_F(AlertViewTest,OnTimeOut)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnAlertResponse(RESULT_SUCCESS)).Times(AtLeast(1));

    AlertView alertView(&appListMock);
    alertView.OnTimeOut();

}


TEST_F(AlertViewTest,OnAlertResponse_Success)
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


    AlertView alertView(&appListMock);
    alertView.OnSoftBtnClicked(0);
    alertView.OnSoftBtnClicked(-1);
    alertView.OnTimeOut();
}

TEST_F(AlertViewTest,getAlertJson_Success)
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

    Json::Value AlertObj;
    Json::Value params;

    Json::Value alertStrings;
    Json::Value ele1;
    Json::Value ele2;
    Json::Value ele3;

    Json::Value softButtons;
    Json::Value btnEle1;
    Json::Value btnEle2;
    btnEle1["isHighlighted"] = false;
    btnEle1["softButtonID"] = 5500;
    btnEle1["systemAction"] = "STEAL_FOCUS";
    btnEle1["text"] = "ReRoute";
    btnEle1["type"] = "TEXT";

    btnEle2["isHighlighted"] = false;
    btnEle2["softButtonID"] = 5501;
    btnEle2["systemAction"] = "DEFAULT_ACTION";
    btnEle2["text"] = "Close";
    btnEle2["type"] = "TEXT";
    softButtons.append(btnEle1);
    softButtons.append(btnEle2);

    AlertObj["method"] = "UI.Alert";
    params["appID"] = 3;
    params["alertType"] = "BOTH";
    params["duration"] = 5000;
    params["progressIndicator"] = true;
    params["softButtons"] = softButtons;
    ele1["fieldName"] = "alertText1";
    ele1["fieldText"] = "Alert Line 1";
    ele2["fieldName"] = "alertText2";
    ele2["fieldText"] = "Alert Line 2";
    ele3["fieldName"] = "alertText3";
    ele3["fieldText"] = "Alert Line 3";

    alertStrings.append(ele1);
    alertStrings.append(ele2);
    alertStrings.append(ele3);
    params["alertStrings"] = alertStrings;

    AlertObj["id"] = 64;
    AlertObj["jsonrpc"] = "2.0";
    AlertObj["params"] = params;

    appListMock.DelegateOnRequest(AlertObj);
    EXPECT_CALL(appListMock,onRequest(AlertObj)).Times(AtLeast(1));
    EXPECT_EQ(ID_APPLINK,appListMock.getActiveApp()->getCurUI());
    appListMock.onRequest(AlertObj);
    EXPECT_EQ(ID_ALERT,appListMock.getActiveApp()->getCurUI());

    EXPECT_EQ("UI.Alert",appListMock.getActiveApp()->getAlertJson()["method"].asString());
    EXPECT_EQ(3,appListMock.getActiveApp()->getAlertJson()["params"]["alertStrings"].size());

//    AlertView *alertView = new AlertView(&appListMock);
//    alertView->show();
}
