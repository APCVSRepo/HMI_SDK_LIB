#include "AppListViewTest.h"

using namespace test;
using namespace hmi_sdk;
using namespace rpc_test;

CAppListViewTest::CAppListViewTest()
{
}

void CAppListViewTest::SetUpTestCase()
{

}

void CAppListViewTest::TearDownTestCase()
{

}

void CAppListViewTest::SetUp()
{

}

void CAppListViewTest::TearDown()
{

}

TEST_F(CAppListViewTest,onChildAppSelected_NegativeOne_SUCCESS)
{
    AppListMock appListMock;

    EXPECT_CALL(appListMock,OnStartDeviceDiscovery()).Times(AtLeast(1));
    EXPECT_CALL(appListMock,OnShowDeviceList()).Times(AtLeast(1));

    CAppListView cAppListView(&appListMock);
    cAppListView.onChildAppSelected(-1);
}

TEST_F(CAppListViewTest,onChildAppSelected_NegativeTwo_SUCCESS)
{
    AppListMock appListMock;

    EXPECT_CALL(appListMock,OnStartDeviceDiscovery()).Times(AtLeast(0));
    EXPECT_CALL(appListMock,OnShowDeviceList()).Times(AtLeast(0));

    CAppListView cAppListView(&appListMock);
    cAppListView.onChildAppSelected(-2);
}

TEST_F(CAppListViewTest,onChildAppSelected_Hundred_SUCCESS)
{
    AppListMock appListMock;

    EXPECT_CALL(appListMock,OnAppActivated(100)).Times(AtLeast(1));

    CAppListView cAppListView(&appListMock);
    cAppListView.onChildAppSelected(100);
}

//BasicCommunication.OnStartDeviceDiscovery
TEST_F(CAppListViewTest,onChildAppSelected_sendNotification_SUCCESS)
{
    AppListMock appListMock;
    appListMock.DelegateOnStartDeviceDiscovery();
    EXPECT_CALL(appListMock,OnStartDeviceDiscovery()).Times(AtLeast(1));
    EXPECT_CALL(appListMock,OnShowDeviceList()).Times(AtLeast(0));

    CAppListView cAppListView(&appListMock);
    cAppListView.onChildAppSelected(-1);
}

TEST_F(CAppListViewTest,onChildAppSelected_onAppShow_DEVICEVIEW)
{
    AppListMock appListMock;
    AppList appList;
    UIInterfaceMock uiInterfaceMock;

    ON_CALL(appListMock,OnShowDeviceList()).WillByDefault(Invoke(&appList,&AppList::OnShowDeviceList));
    ON_CALL(appListMock,setUIManager(&uiInterfaceMock)).WillByDefault(Invoke(&appList,&AppList::setUIManager));

    EXPECT_CALL(appListMock,OnShowDeviceList()).Times(AtLeast(1));
    EXPECT_CALL(appListMock,OnStartDeviceDiscovery()).Times(AtLeast(1));
    EXPECT_CALL(appListMock,setUIManager(_)).Times(AtLeast(1));
    EXPECT_CALL(uiInterfaceMock,onAppShow(ID_DEVICEVIEW)).Times(AtLeast(1));

    appListMock.setUIManager(&uiInterfaceMock);

    CAppListView cAppListView(&appListMock);
    cAppListView.onChildAppSelected(-1);
}


TEST_F(CAppListViewTest,getAppList_Success)
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


    std::vector<int> vAppIDs;
    std::vector<std::string> vAppNames;
    std::vector<std::string> vIconPath;
    appListMock.DelegateGetAppList(vAppIDs,vAppNames,vIconPath);
    EXPECT_CALL(appListMock,getAppList(_,_,_)).Times(AtLeast(1));
    appListMock.getAppList(vAppIDs,vAppNames,vIconPath);
    EXPECT_EQ(2,vAppIDs.size());
    EXPECT_EQ(3,vAppIDs.at(0));
    EXPECT_EQ(4,vAppIDs.at(1));

    EXPECT_EQ("Music1",vAppNames.at(0));
    EXPECT_EQ("Music2",vAppNames.at(1));

}
