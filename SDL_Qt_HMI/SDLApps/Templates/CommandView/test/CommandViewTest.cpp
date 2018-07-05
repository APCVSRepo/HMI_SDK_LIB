#include "CommandViewTest.h"

using namespace test;
using namespace hmi_sdk;
using namespace rpc_test;


CCommandViewTest::CCommandViewTest()
{
}

void CCommandViewTest::SetUpTestCase()
{

}

void CCommandViewTest::TearDownTestCase()
{

}

void CCommandViewTest::SetUp()
{

}

void CCommandViewTest::TearDown()
{

}


TEST_F(CCommandViewTest,OnCommandClick_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnCommandClick(-1));
    CCommandView commandView(&appListMock);
    commandView.OnReturnBtnClicked();
}


TEST_F(CCommandViewTest,updateAppList_Success)
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
}

TEST_F(CCommandViewTest,ActivateApp_Success)
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

    EXPECT_CALL(appListMock,getActiveApp());
    EXPECT_TRUE(appListMock.getActiveApp());
}


TEST_F(CCommandViewTest,ShowPreviousUI_Success)
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
    EXPECT_EQ(NULL,appListMock.getActiveApp());

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

    EXPECT_CALL(appListMock,getActiveApp());
    EXPECT_TRUE(appListMock.getActiveApp());

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnCommandClick(-1));
    CCommandView commandView(&appListMock);
    commandView.OnReturnBtnClicked();

}


TEST_F(CCommandViewTest,getCommandList_Success)
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

    Json::Value addSubMenuObj;
    Json::Value appInfo;
    Json::Value menuParams;
    addSubMenuObj["method"] = "UI.AddSubMenu";
    appInfo["appID"] = 3;
    appInfo ["menuID"] = 1;

    menuParams["menuName"] = "Musci3";
    menuParams["position"] = 1;

    appInfo["menuParams"] = menuParams;
    addSubMenuObj["id"] = 64;
    addSubMenuObj["jsonrpc"] = "2.0";
    addSubMenuObj["params"] = appInfo;

    appListMock.DelegateOnRequest(addSubMenuObj);
    EXPECT_CALL(appListMock,onRequest(addSubMenuObj)).Times(AtLeast(1));
    appListMock.onRequest(addSubMenuObj);

    EXPECT_NE(0,appListMock.getActiveApp()->getCommandList().size());

//    CCommandView* cCommandView= new CCommandView(&appListMock);
//    cCommandView->show();
}


