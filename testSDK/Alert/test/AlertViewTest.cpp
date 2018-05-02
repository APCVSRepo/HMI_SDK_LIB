#include "AlertViewTest.h"
#include "global_first.h"

using namespace test;
using namespace hmi_sdk;
using namespace rpc_test;


AlertViewTest::AlertViewTest()
{
}


void AlertViewTest::SetUpTestCase()
{

}


void AlertViewTest::TearDownTestCase()
{

}


void AlertViewTest::SetUp()
{

}


void AlertViewTest::TearDown()
{

}

TEST_F(AlertViewTest,OnSoftBtnClicked_Normal)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnAlertResponse(RESULT_SUCCESS)).Times(AtLeast(1));
    EXPECT_CALL(appDataMock,OnSoftButtonClick(100,RESULT_SUCCESS,_)).Times(AtLeast(1));

    AlertView alertView(&appListMock);
    alertView.OnSoftBtnClicked(100);

}

TEST_F(AlertViewTest,OnSoftBtnClicked_NoId)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnAlertResponse(RESULT_SUCCESS)).Times(AtLeast(1));
    EXPECT_CALL(appDataMock,OnSoftButtonClick(_,_,_)).Times(AtLeast(0));

    AlertView alertView(&appListMock);
    alertView.OnSoftBtnClicked(-1);

}

TEST_F(AlertViewTest,OnSoftBtnClicked_sendNotification)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appDataMock.DelegateOnSoftButtonClick();
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnAlertResponse(RESULT_SUCCESS)).Times(AtLeast(1));
    EXPECT_CALL(appDataMock,OnSoftButtonClick(100,RESULT_SUCCESS,_)).Times(AtLeast(1));

    AlertView alertView(&appListMock);
    alertView.OnSoftBtnClicked(100);



}

TEST_F(AlertViewTest,OnTimeOut)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnAlertResponse(RESULT_SUCCESS)).Times(AtLeast(1));

    AlertView alertView(&appListMock);
    alertView.OnTimeOut();

}
