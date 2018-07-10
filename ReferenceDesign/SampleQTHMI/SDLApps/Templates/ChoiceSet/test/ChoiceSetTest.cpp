#include "ChoiceSetTest.h"

using namespace test;
using namespace hmi_sdk;
using namespace rpc_test;

CChoiceSetTest::CChoiceSetTest()
{
}

void CChoiceSetTest::SetUpTestCase()
{

}

void CChoiceSetTest::TearDownTestCase()
{

}

void CChoiceSetTest::SetUp()
{

}

void CChoiceSetTest::TearDown()
{

}

TEST_F(CChoiceSetTest,OnVRPerformInteraction_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();
    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnPerformInteraction(PERFORMINTERACTION_TIMEOUT, 0, true));
    EXPECT_CALL(appDataMock,OnPerformInteraction(PERFORMINTERACTION_TIMEOUT, 0, false));


    CChoiceSet choiceSet(&appListMock);
    choiceSet.OnTimeOut();
}

TEST_F(CChoiceSetTest,OnPerformInteraction_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();
    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnPerformInteraction(PERFORMINTERACTION_TIMEOUT, 0, true));
    EXPECT_CALL(appDataMock,OnPerformInteraction(PERFORMINTERACTION_TIMEOUT, 0, false));


    CChoiceSet choiceSet(&appListMock);
    choiceSet.OnTimeOut();
}

TEST_F(CChoiceSetTest,OnPerformInteraction_OnListItemClicked_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();
    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnPerformInteraction(PERFORMINTERACTION_CHOICE, 0, _)).Times(AtLeast(1));

    CChoiceSet choiceSet(&appListMock);
    choiceSet.OnListItemClicked(0);
}

TEST_F(CChoiceSetTest,OnPerformInteraction_OnChoiceVRClicked_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();
    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnPerformInteraction(PERFORMINTERACTION_TIMEOUT, 0, _)).Times(AtLeast(1));

    CChoiceSet choiceSet(&appListMock);
    choiceSet.OnChoiceVRClicked();
}

TEST_F(CChoiceSetTest,OnPerformInteraction_OnReturnBtnClicked_Success)
{
    AppListMock appListMock;
    AppDataMock appDataMock;
    appListMock.DelegateGetActiveApp();
    EXPECT_CALL(appListMock,getActiveApp()).WillRepeatedly(Return(&appDataMock));
    EXPECT_CALL(appDataMock,OnPerformInteraction(RESULT_ABORTED, 0, _)).Times(AtLeast(1));

    CChoiceSet choiceSet(&appListMock);
    choiceSet.OnReturnBtnClicked();
}


TEST_F(CChoiceSetTest,getInteractionJson_Success)
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

    Json::Value InteractionObj;
    Json::Value choiceSet;
    Json::Value params;
    Json::Value initialText;

    initialText["fieldName"] = "initialInteractionText";
    initialText["fieldText"] = "1111111";

    for (int i = 0; i< 10;++i)
    {
        Json::Value choiceSetEle;
        choiceSetEle["choiceID"] = i+1;
        choiceSetEle["menuName"] =  QString(("MenuName" + QString::number(i+1))).toStdString();
        choiceSet.append(choiceSetEle);
    }


    params["appID"] = 3;
    params["choiceSet"] = choiceSet;
    params["initialText"] = initialText;
    InteractionObj["method"] = "UI.PerformInteraction";
    InteractionObj["id"] = 127;
    InteractionObj["jsonrpc"] = "2.0";
    InteractionObj["params"] = params;

    appListMock.DelegateOnRequest(InteractionObj);
    EXPECT_CALL(appListMock,onRequest(InteractionObj)).Times(AtLeast(1));
    appListMock.onRequest(InteractionObj);

    EXPECT_EQ(3,appListMock.getActiveApp()->getInteractionJson()["Choiceset"]["params"]["appID"].asInt());

//    CChoiceSet* cChoiceSet = new CChoiceSet(&appListMock);
//    cChoiceSet->show();
}

