#include "SliderViewTest.h"

using namespace test;
using namespace hmi_sdk;
using namespace rpc_test;


CSliderViewTest::CSliderViewTest()
{
}

void CSliderViewTest::SetUpTestCase()
{

}

void CSliderViewTest::TearDownTestCase()
{

}

void CSliderViewTest::SetUp()
{

}

void CSliderViewTest::TearDown()
{

}

TEST_F(CSliderViewTest,OnTimeOut_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnSliderResponse(RESULT_TIMED_OUT,_)).Times(AtLeast(1));

    CSliderView cSliderView(&appListMock);
    cSliderView.OnTimeOut();

}


TEST_F(CSliderViewTest,OnReturnBtnClicked_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnSliderResponse(RESULT_ABORTED,_)).Times(AtLeast(1));

    CSliderView cSliderView(&appListMock);
    cSliderView.OnReturnBtnClicked();

}


TEST_F(CSliderViewTest,OnSliderResponse_Success)
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


    CSliderView cSliderView(&appListMock);

    cSliderView.OnTimeOut();

    cSliderView.OnReturnBtnClicked();

}


TEST_F(CSliderViewTest,getSlider_Success)
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


    Json::Value SliderObj;
    Json::Value params;
    Json::Value sliderFooter;

    SliderObj["method"] = "UI.Slider";
    sliderFooter.append("1");
    sliderFooter.append("2");
    params["appID"] = 3;
    params["numTicks"] = 2;
    params["position"] = 1;
    params["timeout"] = 5000;
    params["sliderHeader"] = "Slider Header";
    params["sliderFooter"] = sliderFooter;
    SliderObj["id"] = 421;
    SliderObj["jsonrpc"] = "2.0";
    SliderObj["params"] = params;
    appListMock.DelegateOnRequest(SliderObj);
    EXPECT_CALL(appListMock,onRequest(SliderObj)).Times(AtLeast(1));
    appListMock.onRequest(SliderObj);

    EXPECT_EQ(3,appListMock.getActiveApp()->getSlider()["params"]["appID"].asInt());
    EXPECT_EQ(2,appListMock.getActiveApp()->getSlider()["params"]["numTicks"].asInt());
    EXPECT_EQ(1,appListMock.getActiveApp()->getSlider()["params"]["position"].asInt());
//    CSliderView *cSliderView = new CSliderView(&appListMock);
//    cSliderView->show();

}
