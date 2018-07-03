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
