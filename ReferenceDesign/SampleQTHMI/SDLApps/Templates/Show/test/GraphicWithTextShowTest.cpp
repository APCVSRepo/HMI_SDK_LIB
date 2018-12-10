#include "GraphicWithTextShowTest.h"

using namespace test;
using namespace hmi_sdk;
using namespace rpc_test;


CGraphicWithTextShowTest::CGraphicWithTextShowTest()
{
}

void CGraphicWithTextShowTest::SetUpTestCase()
{

}

void CGraphicWithTextShowTest::TearDownTestCase()
{

}

void CGraphicWithTextShowTest::SetUp()
{

}

void CGraphicWithTextShowTest::TearDown()
{

}

TEST_F(CGraphicWithTextShowTest,OnShowCommand_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnShowCommand()).Times(AtLeast(1));

    CGraphicWithTextShow cGraphicWithTextShow(&appListMock);
    cGraphicWithTextShow.BtnMenuClickedSlots();

}
/*

"params" : {
      "alignment" : "CENTERED",
      "appID" : 2078235495,
      "customPresets" : [ "GEN0", "GEN1", "GEN2", "GEN3", "GEN4", "GEN5" ],
      "graphic" : {
         "imageType" : "DYNAMIC",
         "value" : "/home/linux/D/sdl/SDL_MASTER/build/bin/storage/584421907_bc511c722e968e631dc0c3f7620408aa7ffd7bb9e5dd79e9b2d812d781f15512/icon.png"
      },
      "showStrings" : [
         {
            "fieldName" : "mainField1",
            "fieldText" : "Show Line 1"
         },
         {
            "fieldName" : "mainField2",
            "fieldText" : "Show Line 2"
         },
         {
            "fieldName" : "mainField3",
            "fieldText" : "Show Line 3"
         },
         {
            "fieldName" : "mainField4",
            "fieldText" : "Show Line 4"
         },
         {
            "fieldName" : "statusBar",
            "fieldText" : "status bar"
         }
      ]
   }



*/
TEST_F(CGraphicWithTextShowTest,getShowData_Success)
{
    AppListMock appListMock;
    UIInterfaceMock uiManagerMock;

    Json::Value obj;
    Json::Value appList_;
    Json::Value eleArr_;
    Json::Value element1;
    Json::Value element2;

    element1["appName"] = "TEST1";
    element1["appID"] = 3;
    element1["icon"] = "";

    element2["appName"] = "TEST2";
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
    EXPECT_EQ("TEST1",appListMock.getActiveApp()->getAppName());

    Json::Value ShowObj;
    Json::Value params;
    Json::Value stringsArr;
    Json::Value stringsEL1;
    Json::Value stringsEL2;
    Json::Value stringsEL3;
    ShowObj["method"] = "UI.Show";
    ShowObj["jsonrpc"] = "2.0";
    ShowObj["id"] = 65;
    stringsEL1["fieldName"] = "mainField1";
    stringsEL1["fieldText"] = "Show Line 1";

    stringsEL2["fieldName"] = "mainField2";
    stringsEL2["fieldText"] = "Show Line 2";

    stringsEL3["fieldName"] = "mainField3";
    stringsEL3["fieldText"] = "Show Line 3";

    stringsArr.append(stringsEL1);
    stringsArr.append(stringsEL2);
    stringsArr.append(stringsEL3);
    params["showStrings"] = stringsArr;
    params["appID"] = 3;
    params["alignment"] = "CENTERED";
    appListMock.DelegateOnRequest(ShowObj);
    EXPECT_CALL(appListMock,onRequest(ShowObj)).Times(AtLeast(1));
    appListMock.onRequest(ShowObj);

    EXPECT_EQ(3,appListMock.getActiveApp()->getShowData()["params"]["appID"].asInt());

    rpcValueInterface &pObj = appListMock.getActiveApp()->getShowData();

    EXPECT_FALSE(pObj.isNull());

//    CGraphicWithTextShow cGraphicWithTextShow(&appListMock);
//    cGraphicWithTextShow.show();

}



