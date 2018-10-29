#include "AudioPassThruTest.h"

using namespace test;
using namespace hmi_sdk;
using namespace rpc_test;


CAudioPassThruTest::CAudioPassThruTest()
{

}

void CAudioPassThruTest::SetUpTestCase()
{

}

void CAudioPassThruTest::TearDownTestCase()
{

}

void CAudioPassThruTest::SetUp()
{

}

void CAudioPassThruTest::TearDown()
{

}

TEST_F(CAudioPassThruTest,OnAudioPassThruFinish_Normal_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnPerformAudioPassThru(0)).Times(AtLeast(1));

    CAudioPassThru audioPassThru(&appListMock);
    audioPassThru.OnAudioPassThruFinish();
}

TEST_F(CAudioPassThruTest,OnAudioPassThruCancel_Normal_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnPerformAudioPassThru(5)).Times(AtLeast(1));

    CAudioPassThru audioPassThru(&appListMock);
    audioPassThru.OnAudioPassThruCancel();
}

TEST_F(CAudioPassThruTest,OnAudioPassThruTimeOut_Normal_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();

    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnPerformAudioPassThru(5)).Times(AtLeast(1));

    CAudioPassThru audioPassThru(&appListMock);
    audioPassThru.OnAudioPassThruTimeOut();
}
