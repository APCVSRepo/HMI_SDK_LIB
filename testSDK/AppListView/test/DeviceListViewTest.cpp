#include "DeviceListViewTest.h"

using namespace test;
using namespace hmi_sdk;
using namespace rpc_test;

CDeviceListViewTest::CDeviceListViewTest()
{
}

void CDeviceListViewTest::SetUpTestCase()
{

}

void CDeviceListViewTest::TearDownTestCase()
{

}

void CDeviceListViewTest::SetUp()
{

}

void CDeviceListViewTest::TearDown()
{

}

TEST_F(CDeviceListViewTest,onDeviceSelected_NotReturn)
{
    AppListMock appListMock;
    EXPECT_CALL(appListMock,OnDeviceSelect("test")).Times(AtLeast(1));
    EXPECT_CALL(appListMock,ShowPreviousUI()).Times(AtLeast(1));

    CDeviceListView cDeviceListView(&appListMock);
    cDeviceListView.onDeviceSelected("test");
}

TEST_F(CDeviceListViewTest,onDeviceSelected_Return)
{
    AppListMock appListMock;
    EXPECT_CALL(appListMock,OnDeviceSelect("return")).Times(AtLeast(0));
    EXPECT_CALL(appListMock,ShowPreviousUI()).Times(AtLeast(1));

    CDeviceListView cDeviceListView(&appListMock);
    cDeviceListView.onDeviceSelected("return");
}

/*


{
  "id" : 64,
  "jsonrpc" : "2.0",
  "method" : "BasicCommunication.UpdateDeviceList",
  "params" :
  {
    "deviceList" :
    [
      {
        "name" : "Jerry`s Phone",
        "id" : 3
      },

      {
        "name" : "XT910",
        "id" : 4
      }
    ]
  }
}


*/

TEST_F(CDeviceListViewTest,onDeviceSelected_UpdateDeviceList)
{
    //onRequest
    AppListMock appListMock;
    UIInterfaceMock uiInterfaceMock;

    Json::Value obj;
    Json::Value deviceList_;
    Json::Value eleArr_;
    Json::Value element1;
    Json::Value element2;

    element1["name"] = "Jerry's Phone";
    element1["id"] = 3;

    element2["name"] = "XT910";
    element2["id"] = 4;

    eleArr_.append(element1);
    eleArr_.append(element2);

    deviceList_["deviceList"] = eleArr_;

    obj["id"] = 64;
    obj["jsonrpc"] = "2.0";
    obj["method"] = "BasicCommunication.UpdateDeviceList";
    obj["params"] = deviceList_;


    appListMock.DelegateOnRequest(obj);
    appListMock.DelegateOnDeviceSelect("3");
    appListMock.DelegateSetUIManager(&uiInterfaceMock);
    EXPECT_CALL(appListMock,OnDeviceSelect("3")).Times(AtLeast(0));
    EXPECT_CALL(appListMock,ShowPreviousUI()).Times(AtLeast(1));
    EXPECT_CALL(appListMock,onRequest(obj)).Times(AtLeast(1));
    EXPECT_CALL(appListMock,setUIManager(&uiInterfaceMock)).Times(AtLeast(1));
    EXPECT_CALL(uiInterfaceMock,ShowDeviceList()).Times(AtLeast(1));

    appListMock.setUIManager(&uiInterfaceMock);

    appListMock.onRequest(obj);
    CDeviceListView cDeviceListView(&appListMock);
    cDeviceListView.onDeviceSelected("3");
}

