#include "DialNumberTest.h"

using namespace test;
using namespace hmi_sdk;
using namespace rpc_test;


CDialNumberTest::CDialNumberTest()
{

}

void CDialNumberTest::SetUpTestCase()
{

}

void CDialNumberTest::TearDownTestCase()
{

}

void CDialNumberTest::SetUp()
{

}

void CDialNumberTest::TearDown()
{

}

TEST_F(CDialNumberTest,OnDialNumberCall_Normal_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnDialNumber(0)).Times(AtLeast(1));

    CDialNumber dialNumber(&appListMock);
    dialNumber.OnDialNumberCall();
}

TEST_F(CDialNumberTest,OnDialNumberCancel_Normal_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnDialNumber(5)).Times(AtLeast(1));

    CDialNumber dialNumber(&appListMock);
    dialNumber.OnDialNumberCancel();
}

TEST_F(CDialNumberTest,dialNumberJson_Normal_Success)
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

    Json::Value dialNumberObj;
    Json::Value params;
    dialNumberObj["method"] = "BasicCommunication.DialNumber";
    dialNumberObj["jsonrpc"] = "2.0";
    dialNumberObj["id"] = 65;
    params["appID"] = 3;
    params["number"] = "8675309";
    dialNumberObj["params"] = params;
    appListMock.DelegateOnRequest(dialNumberObj);
    EXPECT_CALL(appListMock,onRequest(dialNumberObj)).Times(AtLeast(1));
    appListMock.onRequest(dialNumberObj);

    EXPECT_EQ(3,appListMock.getActiveApp()->getDialNumberJson()["params"]["appID"].asInt());
    EXPECT_EQ("8675309",appListMock.getActiveApp()->getDialNumberJson()["params"]["number"].asString());

}
