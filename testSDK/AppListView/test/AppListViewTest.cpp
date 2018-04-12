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

TEST_F(CAppListViewTest,onChildAppSelected)
{
    AppListMock appListMock;

    EXPECT_CALL(appListMock,OnStartDeviceDiscovery()).Times(AtLeast(1));
    EXPECT_CALL(appListMock,OnShowDeviceList()).Times(AtLeast(1));

    CAppListView cAppListView(&appListMock);
    cAppListView.onChildAppSelected(-1);
}
