#include "GraphicSoftButtonShowTest.h"

using namespace test;
using namespace hmi_sdk;
using namespace rpc_test;


CGraphicSoftButtonShowTest::CGraphicSoftButtonShowTest()
{
}

void CGraphicSoftButtonShowTest::SetUpTestCase()
{

}

void CGraphicSoftButtonShowTest::TearDownTestCase()
{

}

void CGraphicSoftButtonShowTest::SetUp()
{

}

void CGraphicSoftButtonShowTest::TearDown()
{

}


TEST_F(CGraphicSoftButtonShowTest,SoftBtnClickedSlot_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnSoftButtonClick(1,BUTTON_SHORT,"")).Times(AtLeast(1));

    CGraphicSoftButtonShow cGraphicSoftButtonShow(&appListMock);
    cGraphicSoftButtonShow.SoftBtnClickedSlot(1);

}

TEST_F(CGraphicSoftButtonShowTest,BtnMenuClickedSlots_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnShowCommand()).Times(AtLeast(1));

    CGraphicSoftButtonShow cGraphicSoftButtonShow(&appListMock);
    cGraphicSoftButtonShow.BtnMenuClickedSlots();

}

TEST_F(CGraphicSoftButtonShowTest,getShowData_Success)
{
    AppListMock appListMock;
    UIInterfaceMock uiManagerMock;

    Json::Value obj;
    Json::Value appList_;
    Json::Value eleArr_;
    Json::Value element1;
    Json::Value element2;

    element1["appName"] = "MEDIA";
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
    EXPECT_EQ("MEDIA",appListMock.getActiveApp()->getAppName());

    Json::Value ShowObj;
    Json::Value params;
    Json::Value graphic;
    ShowObj["method"] = "UI.Show";
    ShowObj["jsonrpc"] = "2.0";
    ShowObj["id"] = 65;
    params["showStrings"] = "test getScrollableMsgJson_Success!";
    //params["softButtons"] = "Cancle";
    params["appID"] = 3;
    graphic["value"] = "";
    //params["graphic"]= graphic;
    ShowObj["params"] = params;
    appListMock.DelegateOnRequest(ShowObj);
    EXPECT_CALL(appListMock,onRequest(ShowObj)).Times(AtLeast(1));
    appListMock.onRequest(ShowObj);

    EXPECT_EQ(3,appListMock.getActiveApp()->getShowData()["params"]["appID"].asInt());
//    CGraphicSoftButtonShow *cGraphicSoftButtonShow = new CGraphicSoftButtonShow(&appListMock);
//    cGraphicSoftButtonShow->show();
}


