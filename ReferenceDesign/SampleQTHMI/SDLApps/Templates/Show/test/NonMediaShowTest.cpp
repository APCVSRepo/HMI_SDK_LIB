#include "NonMediaShowTest.h"

using namespace test;
using namespace hmi_sdk;
using namespace rpc_test;


CNonMediaShowTest::CNonMediaShowTest()
{
}

void CNonMediaShowTest::SetUpTestCase()
{

}

void CNonMediaShowTest::TearDownTestCase()
{

}

void CNonMediaShowTest::SetUp()
{

}

void CNonMediaShowTest::TearDown()
{

}


TEST_F(CNonMediaShowTest,OnSoftButtonClick_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnSoftButtonClick(1,BUTTON_SHORT,"")).Times(AtLeast(1));

    CNonMediaShow cNonMediaShow(&appListMock);
    cNonMediaShow.SoftBtnClickedSlot(1);
}

TEST_F(CNonMediaShowTest,OnShowCommand_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnShowCommand()).Times(AtLeast(1));

    CNonMediaShow cNonMediaShow(&appListMock);
    cNonMediaShow.BtnMenuClickedSlots();

}

TEST_F(CNonMediaShowTest,getShowData_Success)
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

    Json::Value btnsArr;
    Json::Value btnEL1;
    Json::Value btnEL2;
    Json::Value btnEL3;
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

    btnEL1["isHighlighted"] = true;
    btnEL1["softButtonID"] = 1;
    btnEL1["text"] = "btn1";

    btnEL2["isHighlighted"] = true;
    btnEL2["softButtonID"] = 2;
    btnEL2["text"] = "btn2";

    btnEL3["isHighlighted"] = true;
    btnEL3["softButtonID"] = 3;
    btnEL3["text"] = "btn3";

    btnsArr.append(btnEL1);
    btnsArr.append(btnEL2);
    btnsArr.append(btnEL3);

    params["softButtons"] = btnsArr;

    params["appID"] = 3;
    params["alignment"] = "CENTERED";
    appListMock.DelegateOnRequest(ShowObj);
    EXPECT_CALL(appListMock,onRequest(ShowObj)).Times(AtLeast(1));
    appListMock.onRequest(ShowObj);

    EXPECT_EQ(3,appListMock.getActiveApp()->getShowData()["params"]["appID"].asInt());

    rpcValueInterface &pObj = appListMock.getActiveApp()->getShowData();

    EXPECT_FALSE(pObj.isNull());

    CNonMediaShow cNonMediaShow(&appListMock);
    cNonMediaShow.show();

}

