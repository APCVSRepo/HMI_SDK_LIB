#include "AppData.h"

std::string string_To_UTF8(const std::string & str)
{
#ifdef WIN32
    int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

    wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
    ZeroMemory(pwBuf, nwLen * 2 + 2);

    ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

    int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

    char * pBuf = new char[nLen + 1];
    ZeroMemory(pBuf, nLen + 1);

    ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

    std::string retStr(pBuf);

    delete []pwBuf;
    delete []pBuf;

    pwBuf = NULL;
    pBuf  = NULL;

    return retStr;
#else
    return str;
#endif
}
bool IsTextUTF8(char* str, unsigned long long length)
{
#ifdef WIN32
    DWORD nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节
    UCHAR chr;
    BOOL bAllAscii = TRUE; //如果全部都是ASCII, 说明不是UTF-8
    for (int i = 0; i<length; ++i) {
        chr = *(str+i);
        if ( (chr&0x80) != 0 ) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx
            bAllAscii = FALSE;
        //如果不是ASCII码,应该是多字节符,计算字节数
        if (nBytes == 0) {
            if (chr >= 0x80) {
                if (chr >= 0xFC && chr <= 0xFD)
                    nBytes = 6;
                else if (chr >= 0xF8)
                    nBytes = 5;
                else if (chr >= 0xF0)
                    nBytes = 4;
                else if (chr >= 0xE0)
                    nBytes = 3;
                else if (chr >= 0xC0)
                    nBytes = 2;
                else
                    return FALSE;

                nBytes--;
            }
        } else {
            //多字节符的非首字节,应为 10xxxxxx
            if ( (chr&0xC0) != 0x80 )
                return FALSE;

            nBytes--;
        }
    }
    if ( nBytes > 0 ) //违返规则
        return FALSE;
    if ( bAllAscii ) //如果全部都是ASCII, 说明不是UTF-8
        return FALSE;
    return true;
#else
    return true;
#endif
}


AppData::AppData()
{
}

void AppData::setUIManager(UIInterface *pUIManager)
{
    m_pUIManager = pUIManager;
}

Result AppData::recvFromServer(Json::Value jsonObj)
{
    int appID = jsonObj["params"]["appID"].asInt();
    if (m_iAppID != appID)
        return RESULT_APPLICATION_NOT_REGISTERED;

    if (jsonObj.isMember("method")) {
        std::string str_method = jsonObj["method"].asString();

        if (str_method == "UI.Show") {
            m_json_show = jsonObj;
            ShowUI(ID_SHOW);
        }else if (str_method == "UI.SubscribeButton") {
        }else if (str_method == "UI.AddCommand") {
            addCommand(jsonObj);
        }else if (str_method == "UI.AddSubMenu") {
            addSubMenu(jsonObj);
        }else if (str_method == "UI.DeleteCommand") {
            delCommand(jsonObj);
        }else if (str_method == "UI.DeleteSubMenu") {
            delSubMenu(jsonObj);
        }else if (str_method == "UI.Alert") {
            if (m_json_alert.isMember("id")) {
                if (m_json_alert["id"].asInt()!=-1)
                    return RESULT_TOO_MANY_PENDING_REQUESTS;
            }
            alert(jsonObj);
            ShowUI(ID_ALERT);
            return RESULT_USER_WAIT;
        }else if (str_method == "UI.ScrollableMessage") {
            if (m_json_scrollableMessage.isMember("id")) {
                if (m_json_scrollableMessage["id"].asInt()!=-1)
                    return RESULT_TOO_MANY_PENDING_REQUESTS;
            }
            scrollableMessage(jsonObj);
            ShowUI(ID_SCROLLMSG);
            return RESULT_USER_WAIT;
        }else if (str_method == "UI.Slider") {
            slider(jsonObj);
            ShowUI(ID_SLIDER);
            return RESULT_USER_WAIT;
        }else if (str_method == "UI.PerformAudioPassThru") {
            performAudioPassThru(jsonObj);
//            ShowUI(ID_AUDIOPASSTHRU);
            ToSDL->OnVRStartRecord();
            return RESULT_USER_WAIT;
        }else if (str_method == "VR.PerformInteraction") {
            m_json_interaction["ChoicesetVR"]=jsonObj;
            Json::Value initialPrompt = jsonObj["params"]["initialPrompt"];
            std::string txt = initialPrompt[0]["text"].asString();
            if (!IsTextUTF8((char *)txt.data(),txt.size()))
                txt = string_To_UTF8(txt);
            m_pUIManager->tsSpeak(ID_DEFAULT, txt);
            //ShowUI(ID_CHOICESETVR);
            return RESULT_USER_WAIT;
        }else if (str_method == "UI.PerformInteraction") {
            m_json_interaction["Choiceset"]=jsonObj;
            ShowUI(ID_CHOICESET);
            return RESULT_USER_WAIT;
        }else if (str_method == "Navigation.StartStream") {
            videoStreamStart(jsonObj);
            m_pUIManager->onVideoStreamStart();
            ShowUI(ID_VIDEOSTREAM);
        }else if (str_method == "UI.SetMediaClockTimer") {
            m_json_mediaclock = jsonObj;
            ShowUI(ID_MEDIACLOCK);
            return RESULT_USER_WAIT;
        }else if (str_method == "VR.VRStatus") {
            if ("SUCCESS" == jsonObj["params"]["status"].asString()) {

            }else if ("FAIL" == jsonObj["params"]["status"].asString()) {
                m_pUIManager->tsSpeak(ID_DEFAULT, "识别失败");
            }else if ("TIME_OVER" == jsonObj["params"]["status"].asString()) {
                m_pUIManager->tsSpeak(ID_DEFAULT, "识别超时");
            }
        }else if (str_method == "VR.VRCancel") {
            m_pUIManager->tsSpeak(ID_CANCEL,"程序取消中");
        }else if (str_method == "VR.VRCommandHelp") {
//            {
//               "jsonrpc" : "2.0",
//               "method" : "VR.VRCommandHelp",
//               "params" : {
//                  "vrContent" : "新浪帮助 "
//               }
//            }
            std::string strVrContent = jsonObj["params"]["vrContent"].asString();

            if (!IsTextUTF8((char *)strVrContent.data(),strVrContent.size()))
                strVrContent = string_To_UTF8(strVrContent);

            m_pUIManager->tsSpeak(ID_DEFAULT, strVrContent);
        }else if (str_method == "VR.VRCommandTTS") {
            for (int i = 0; i < jsonObj["params"]["vrCommands"].size(); ++i) {
                m_pUIManager->tsSpeak(ID_HELP, jsonObj["params"]["vrCommands"][i].asString());
            }
        }else if (str_method == "VR.VRResult") {
//            {
//               "jsonrpc" : "2.0",
//               "method" : "VR.VRResult",
//               "params" : {
//                  "cmdID" : 2,
//                  "vrName" : "新浪 "
//               }
//            }
            std::string strVRName = jsonObj["params"]["vrName"].asString();
            if (!IsTextUTF8((char *)strVRName.data(),strVRName.size()))
                strVRName = string_To_UTF8(strVRName);

            m_pUIManager->tsSpeak(ID_CANCEL, strVRName);
            ToSDL->OnVRCommand(m_iAppID, jsonObj["params"]["cmdID"].asInt());
        }else if (str_method == "TTS.Speak") {
            tsSpeak(jsonObj);
            Json::Value ttsSpeeks = jsonObj["params"]["ttsChunks"];
            int size = ttsSpeeks.size();
            for (int i=0;i<size;++i) {
                std::string speek = ttsSpeeks[i]["text"].asString();
                //if (ttsSpeeks[i]["type"].asString()!="TEXT")
                //    continue;
                if (!IsTextUTF8((char *)speek.data(),speek.size()))
                    speek = string_To_UTF8(speek);
                m_pUIManager->tsSpeak(ID_DEFAULT, speek);
            }
        }
    }
    return RESULT_SUCCESS;
}

int AppData::getCurUI()
{
    int iSize = m_vecUIStack.size();
    if (iSize > 0)
        return m_vecUIStack[iSize - 1];
    return ID_MAIN;
}

void AppData::OnShowCommand()
{
    ShowUI(ID_COMMAND);
}

//////////////////////////////////////////
void AppData::OnMenuBtnClick(std::string btnText)
{
    if ("FMButton" == btnText)
        ToSDL->OnCommandClick(m_iAppID, 101);
    else if ("TelButton" == btnText)
        ToSDL->OnCommandClick(m_iAppID, 102);
    else if ("MsgButton" == btnText)
        ToSDL->OnCommandClick(m_iAppID, 103);
    else if ("CDButton" == btnText)
        ToSDL->OnCommandClick(m_iAppID, 104);
    else if ("ListButton" == btnText) {
//        SDLConnector::getSDLConnectore()->OnCommandClick(m_i_currentAppID, 105);
    }

}

void AppData::OnVRStartRecord()
{
    ToSDL->OnVRStartRecord();
    ShowUI(ID_AUDIOPASSTHRU);
}

void AppData::OnVRCancelRecord()
{
    ToSDL->OnVRCancelRecord();
}

void AppData::OnSoftButtonClick(int sbID, int mode,std::string strName)
{
    ToSDL->OnSoftButtonClick(sbID, mode,strName);
}

void AppData::OnCommandClick(int cmdID)
{
    if (cmdID > 0) {
        ToSDL->OnCommandClick(m_iAppID, cmdID);
    }
    ShowPreviousUI();
}

void AppData::OnAlertResponse(int reason)
{
    if (m_json_alert["id"].asInt() != -1) {
        ToSDL->OnAlertResponse(m_json_alert["id"].asInt(), reason);
        m_json_alert["id"] = -1;
        ShowPreviousUI();
    }
}

void AppData::OnScrollMessageResponse(int reason)
{
    if (m_json_scrollableMessage["id"].asInt() != -1) {
        ToSDL->OnScrollMessageResponse(m_json_scrollableMessage["id"].asInt(), reason);
        m_json_scrollableMessage["id"] = -1;
        ShowPreviousUI();
    }
}

void AppData::OnSliderResponse( int code, int sliderPosition)
{
    ToSDL->OnSliderResponse(code, m_json_slider["id"].asInt(), sliderPosition);
    ShowPreviousUI();
}

void AppData::OnSetMediaClockTimerResponse(int iCode)
{
    ToSDL->OnSetMediaClockTimerResponse(iCode, m_json_mediaclock["id"].asInt());
}

void AppData::OnTTSSpeek(int code)
{
    ToSDL->OnTTSSpeek(m_json_tsSpeak["id"].asInt(), code);
}

void AppData::OnPerformAudioPassThru(int code)
{
    if (m_json_audioPassThru == Json::Value::null)
        return;

    ToSDL->OnPerformAudioPassThru(m_iAppID, m_json_audioPassThru["id"].asInt(), code);
    ToSDL->OnVRCancelRecord();
    ShowPreviousUI();
}

void AppData::OnPerformInteraction(int code, int choiceID,bool bVR)
{
    Json::Value jsonChoice=m_json_interaction["Choiceset"];
    Json::Value jsonChoiceVR;
    bool isVrMode=m_json_interaction.isMember("ChoicesetVR");
    if (isVrMode)
        jsonChoiceVR =m_json_interaction["ChoicesetVR"];
    /*
    int choiceID=0;
    if (jsonChoice.isMember("choiceSet")) {
        choiceID=jsonChoice["choiceSet"][row]["choiceID"].asInt();
    }
    */

    /*
    if (isVrMode) {
        if (code==RESULT_TIMED_OUT) {
            if (jsonChoiceVR.isMember("timeoutPrompt")) {
                std::string speak=jsonChoiceVR["timeoutPrompt"][0]["text"].asString();
                if (!IsTextUTF8((char *)speak.data(),speak.size()))
                    speak = string_To_UTF8(speak);
                m_pUIManager->tsSpeak(ID_DEFAULT,speak);
            }
        }
        else{
            if (jsonChoiceVR.isMember("helpPrompt")) {
                std::string speak=jsonChoiceVR["helpPrompt"][row]["text"].asString();
                if (!IsTextUTF8((char *)speak.data(),speak.size()))
                    speak = string_To_UTF8(speak);
                m_pUIManager->tsSpeak(ID_DEFAULT,speak);
            }
        }
    }
    */
    if(bVR)
    {
        ToSDL->OnVRPerformInteraction(code, jsonChoiceVR["id"].asInt(), choiceID);
    }
    else
    {
        ToSDL->OnPerformInteraction(code, jsonChoice["id"].asInt(), choiceID);
        ShowPreviousUI();
    }
}

void AppData::OnMediaClock(int code)
{
    int id = m_json_mediaclock["id"].asInt();
    ToSDL->OnMediaClockResponse(id,code);
}


//////////////////////////////////


Json::Value AppData::getShowData()
{
   return m_json_show;
}
std::vector<SMenuCommand> AppData::getCommandList()
{
    static std::vector<SMenuCommand> retVec;
    retVec.clear();
    for (std::vector <SMenuCommand>::iterator iterator = m_vec_scommand.begin(); iterator != m_vec_scommand.end(); iterator++) {
        if (0 == (*iterator).i_parentID) {
            retVec.push_back(*iterator);
        }
    }
    //需要排序

    SMenuCommand tmp;
    for (int i = 0; i < retVec.size(); ++i)
        for (int j = 0; j < retVec.size() - i - 1; j++) {
            if (retVec.at(j).i_position > retVec.at(j+1).i_position) {
                tmp = retVec.at(j);
                retVec.at(j) = retVec.at(j+1);
                retVec.at(j+1) = tmp;
            }
        }

    return retVec;
}
std::vector<SMenuCommand> AppData::getCommandList(int subMenuID)
{
    static std::vector<SMenuCommand> retVec;
    retVec.clear();
    std::vector <SMenuCommand>::const_iterator  iterator;
    for (iterator = m_vec_scommand.begin(); iterator != m_vec_scommand.end(); iterator++) {
        if (subMenuID == (*iterator).i_parentID) {
            retVec.push_back(*iterator);
        }
    }
    //需要排序
    SMenuCommand tmp;
    for (int i = 0; i < retVec.size(); ++i) {
        for (int j = 0; j < retVec.size() - i - 1; j++) {
            if (retVec.at(j).i_position > retVec.at(j+1).i_position) {
                tmp = retVec.at(j);
                retVec.at(j) = retVec.at(j+1);
                retVec.at(j+1) = tmp;
            }
        }
    }

    return retVec;
}
Json::Value AppData::getAlertJson()
{
    return m_json_alert;
}
Json::Value AppData::getSlider()
{
    return m_json_slider;
}
Json::Value AppData::getScrollableMsgJson()
{
    return m_json_scrollableMessage;
}
Json::Value AppData::getAudioPassThruJson()
{
    return m_json_audioPassThru;
}
Json::Value AppData::getInteractionJson()
{
    return m_json_interaction;
}

Json::Value AppData::getMediaClockJson()
{
    return m_json_mediaclock;
}

void AppData::ShowUI(int iUIType)
{
    if (iUIType != ID_MEDIACLOCK)
        m_vecUIStack.push_back(iUIType);

    m_pUIManager->onAppShow(iUIType);
}

bool AppData::ShowPreviousUI(bool bInApp)
{
    int iSize = m_vecUIStack.size();
    if (iSize > 0)
        m_vecUIStack.pop_back();

    if (iSize > 1) {
        m_pUIManager->onAppShow(m_vecUIStack[iSize - 2]);
        return true;
    }

    if (!bInApp)
        return false;

    ShowUI(ID_MAIN);
    return true;
}


//    {
//       "id" : 48,
//       "jsonrpc" : "2.0",
//       "method" : "UI.Show",
//       "params" : {
//          "alignment" : "CENTERED",
//          "appID" : 846930886,
//          "customPresets" : [ "GEN0", "GEN1", "GEN2", "GEN3", "GEN4", "GEN5" ],
//          "showStrings" : [
//             {
//                "fieldName" : "mainField1",
//                "fieldText" : "Show Line 1"
//             },
//             {
//                "fieldName" : "mainField2",
//                "fieldText" : "Show Line 2"
//             },
//             {
//                "fieldName" : "mainField3",
//                "fieldText" : "Show Line 3"
//             },
//             {
//                "fieldName" : "mainField4",
//                "fieldText" : "Show Line 4"
//             },
//             {
//                "fieldName" : "mediaClock",
//                "fieldText" : "12:34"
//             },
//             {
//                "fieldName" : "mediaTrack",
//                "fieldText" : "Media Track"
//             },
//             {
//                "fieldName" : "statusBar",
//                "fieldText" : "status bar"
//             }
//          ]
//       }
//    }

//    {
//       "id" : 42,
//       "jsonrpc" : "2.0",
//       "method" : "UI.AddCommand",
//       "params" : {
//          "appID" : 846930886,
//          "cmdID" : 101,
//          "menuParams" : {
//             "menuName" : "Policies Test",
//             "parentID" : 0
//          }
//       }
//    }
//    {
//       "id" : 46,
//       "jsonrpc" : "2.0",
//       "method" : "UI.AddCommand",
//       "params" : {
//          "appID" : 846930886,
//          "cmdID" : 4,
//          "menuParams" : {
//             "menuName" : "Item To4",
//             "parentID" : 0,
//             "position" : 1000
//          }
//       }
//    }
//    {
//       "id" : 50,
//       "jsonrpc" : "2.0",
//       "method" : "UI.AddCommand",
//       "params" : {
//          "appID" : 846930886,
//          "cmdID" : 5,
//          "menuParams" : {
//             "menuName" : "Menucommandjjj",
//             "parentID" : 1000,
//             "position" : 1000
//          }
//       }
//    }
void AppData::addCommand(Json::Value jsonObj)
{
    SMenuCommand tmpCommand;

    if (jsonObj["params"].isMember("appID"))
        tmpCommand.i_appID = jsonObj["params"]["appID"].asInt();
    if (jsonObj["params"].isMember("cmdID"))
        tmpCommand.i_cmdID = jsonObj["params"]["cmdID"].asInt();
    if (jsonObj["params"]["menuParams"].isMember("menuName"))
        tmpCommand.str_menuName = jsonObj["params"]["menuParams"]["menuName"].asString();
    if (jsonObj["params"]["menuParams"].isMember("parentID"))
        tmpCommand.i_parentID = jsonObj["params"]["menuParams"]["parentID"].asInt();
    if (jsonObj["params"]["menuParams"].isMember("position"))
        tmpCommand.i_position = jsonObj["params"]["menuParams"]["position"].asInt();

    if(jsonObj["params"].isMember("cmdIcon"))
    {
        if(jsonObj["params"]["cmdIcon"]["imageType"].asString() == "DYNAMIC")
        {
            tmpCommand.i_ImageType = 2;
        }
        else if(jsonObj["params"]["cmdIcon"]["imageType"].asString() == "STATIC")
        {
            tmpCommand.i_ImageType = 1;
        }

        tmpCommand.str_ImagePath = jsonObj["params"]["cmdIcon"]["value"].asString();
    }

    m_vec_scommand.push_back(tmpCommand);

}

void AppData::addExitAppCommand()
{
    SMenuCommand tmpCommand;
    tmpCommand.i_appID = m_iAppID;
    tmpCommand.i_cmdID = 101;
    std::string strMenuName = "Exit " + m_szAppName;
    tmpCommand.str_menuName = strMenuName;
    tmpCommand.i_parentID = 0;
    tmpCommand.i_position = 0;

    m_vec_scommand.push_back(tmpCommand);
}

//    {
//       "id" : 49,
//       "jsonrpc" : "2.0",
//       "method" : "UI.AddSubMenu",
//       "params" : {
//          "appID" : 846930886,
//          "menuID" : 1000,
//          "menuParams" : {
//             "menuName" : "SubmenuName",
//             "position" : 1000
//          }
//       }
//    }
void AppData::addSubMenu(Json::Value jsonObj)
{
    SMenuCommand tmpCommand;

    if (jsonObj["params"].isMember("appID"))
        tmpCommand.i_appID = jsonObj["params"]["appID"].asInt();
    if (jsonObj["params"].isMember("menuID"))
        tmpCommand.i_menuID = jsonObj["params"]["menuID"].asInt();
    if (jsonObj["params"]["menuParams"].isMember("menuName"))
        tmpCommand.str_menuName = jsonObj["params"]["menuParams"]["menuName"].asString();
    if (jsonObj["params"]["menuParams"].isMember("position"))
        tmpCommand.i_position = jsonObj["params"]["menuParams"]["position"].asInt();

    m_vec_scommand.push_back(tmpCommand);
}

//{
//   "id" : 41,
//   "jsonrpc" : "2.0",
//   "method" : "UI.DeleteCommand",
//   "params" : {
//      "appID" : 846930886,
//      "cmdID" : 28
//   }
//}
void AppData::delCommand(Json::Value jsonObj)
{
    int cmdID = jsonObj["params"]["cmdID"].asInt();
    for (int i = 0; i < m_vec_scommand.size(); ++i) {
        if (cmdID == m_vec_scommand.at(i).i_cmdID) {
            m_vec_scommand.erase(m_vec_scommand.begin()+i);
        }
    }
}
//{
//   "id" : 43,
//   "jsonrpc" : "2.0",
//   "method" : "UI.DeleteSubMenu",
//   "params" : {
//      "appID" : 846930886,
//      "menuID" : 52
//   }
//}
void AppData::delSubMenu(Json::Value jsonObj)
{
    int menuID = jsonObj["params"]["menuID"].asInt();
    for (int i = 0; i < m_vec_scommand.size(); ++i) {
        if (menuID == m_vec_scommand.at(i).i_menuID) {
            m_vec_scommand.erase(m_vec_scommand.begin()+i);
        }
    }
}



//{
//   "id" : 44,
//   "jsonrpc" : "2.0",
//   "method" : "UI.Alert",
//   "params" : {
//      "alertStrings" : [
//         {
//            "fieldName" : "alertText1",
//            "fieldText" : "Alert Line 1"
//         },
//         {
//            "fieldName" : "alertText2",
//            "fieldText" : "Alert Line 2"
//         },
//         {
//            "fieldName" : "alertText3",
//            "fieldText" : "Alert Line 3"
//         }
//      ],
//      "alertType" : "BOTH",
//      "appID" : 846930886,
//      "duration" : 5000,
//      "progressIndicator" : true,
//      "softButtons" : [
//         {
//            "isHighlighted" : false,
//            "softButtonID" : 5500,
//            "systemAction" : "STEAL_FOCUS",
//            "text" : "ReRoute",
//            "type" : "TEXT"
//         },
//         {
//            "isHighlighted" : false,
//            "softButtonID" : 5501,
//            "systemAction" : "DEFAULT_ACTION",
//            "text" : "Close",
//            "type" : "TEXT"
//         }
//      ]
//   }
//}
//{
//   "id" : 65,
//   "jsonrpc" : "2.0",
//   "method" : "UI.Alert",
//   "params" : {
//      "alertStrings" : [
//         {
//            "fieldName" : "alertText1",
//            "fieldText" : "alertText1"
//         },
//         {
//            "fieldName" : "alertText2",
//            "fieldText" : "alertText2"
//         },
//         {
//            "fieldName" : "alertText3",
//            "fieldText" : "alertText3"
//         }
//      ],
//      "alertType" : "BOTH",
//      "appID" : 846930886,
//      "duration" : 5000,
//      "softButtons" : [
//         {
//            "isHighlighted" : false,
//            "softButtonID" : 1,
//            "systemAction" : "DEFAULT_ACTION",
//            "text" : "Softbutton1",
//            "type" : "TEXT"
//         },
//         {
//            "isHighlighted" : false,
//            "softButtonID" : 2,
//            "systemAction" : "DEFAULT_ACTION",
//            "text" : "Softbutton2",
//            "type" : "TEXT"
//         },
//         {
//            "isHighlighted" : false,
//            "softButtonID" : 3,
//            "systemAction" : "DEFAULT_ACTION",
//            "text" : "Softbutton3",
//            "type" : "TEXT"
//         },
//         {
//            "isHighlighted" : false,
//            "softButtonID" : 4,
//            "systemAction" : "DEFAULT_ACTION",
//            "text" : "Softbutton4",
//            "type" : "TEXT"
//         }
//      ]
//   }
//}
void AppData::alert(Json::Value jsonObj)
{
    m_json_alert = jsonObj;
}

void AppData::tsSpeak(Json::Value jsonObj)
{
    m_json_tsSpeak = jsonObj;
}


//{
//   "id" : 421,
//   "jsonrpc" : "2.0",
//   "method" : "UI.Slider",
//   "params" : {
//      "appID" : 1365180540,
//      "numTicks" : 2,
//      "position" : 1,
//      "sliderFooter" : [ "1", "2" ],
//      "sliderHeader" : "Slider Header",
//      "timeout" : 5000
//   }
//}
void AppData::slider(Json::Value jsonObj)
{
    m_json_slider = jsonObj;
}

//{
//   "id" : 47,
//   "jsonrpc" : "2.0",
//   "method" : "UI.ScrollableMessage",
//   "params" : {
//      "appID" : 846930886,
//      "messageText" : {
//         "fieldName" : "scrollableMessageBody",
//         "fieldText" : "This is where long text can go for a scrollable message"
//      },
//      "timeout" : 30000
//   }
//}
//{
//   "id" : 111,
//   "jsonrpc" : "2.0",
//   "method" : "UI.ScrollableMessage",
//   "params" : {
//      "appID" : 1714636915,
//      "messageText" : {
//         "fieldName" : "scrollableMessageBody",
//         "fieldText" : "21231"
//      },
//      "softButtons" : [
//         {
//            "isHighlighted" : false,
//            "softButtonID" : 1,
//            "systemAction" : "DEFAULT_ACTION",
//            "text" : "Softbutton1",
//            "type" : "TEXT"
//         },
//         {
//            "isHighlighted" : false,
//            "softButtonID" : 2,
//            "systemAction" : "DEFAULT_ACTION",
//            "text" : "Softbutton2",
//            "type" : "TEXT"
//         },
//         {
//            "isHighlighted" : false,
//            "softButtonID" : 3,
//            "systemAction" : "DEFAULT_ACTION",
//            "text" : "Softbutton3",
//            "type" : "TEXT"
//         },
//         {
//            "isHighlighted" : false,
//            "softButtonID" : 4,
//            "systemAction" : "DEFAULT_ACTION",
//            "text" : "Softbutton4",
//            "type" : "TEXT"
//         }
//      ],
//      "timeout" : 30000
//   }
//}
void AppData::scrollableMessage(Json::Value jsonObj)
{
    m_json_scrollableMessage = jsonObj;
}



//{
//   "id" : 49,
//   "jsonrpc" : "2.0",
//   "method" : "UI.PerformAudioPassThru",
//   "params" : {
//      "appID" : 846930886,
//      "audioPassThruDisplayTexts" : [
//         {
//            "fieldName" : "audioPassThruDisplayText1",
//            "fieldText" : "AudioPassThru Display Text 1"
//         },
//         {
//            "fieldName" : "audioPassThruDisplayText2",
//            "fieldText" : "AudioPassThru Display Text 2"
//         }
//      ],
//      "audioType" : "PCM",
//      "bitsPerSample" : "8_BIT",
//      "maxDuration" : 10000,
//      "muteAudio" : true,
//      "samplingRate" : "8KHZ"
//   }
//}
void AppData::performAudioPassThru(Json::Value jsonObj)
{
    m_json_audioPassThru = jsonObj;
}



//{
//   "id" : 52,
//   "jsonrpc" : "2.0",
//   "method" : "BasicCommunication.SystemRequest",
//   "params" : {
//      "appID" : "8675308",
//      "fileName" : "/tmp/fs/mp/images/ivsu_cache/SYNC",
//      "requestType" : "HTTP"
//   }
//}
void AppData::systemRequest(Json::Value jsonObj)
{
}



//+++++recvFromServer+++++
//{
//   "id" : 218,
//   "jsonrpc" : "2.0",
//   "method" : "VR.PerformInteraction",
//   "params" : {
//      "grammarID" : [ 491705403 ],
//      "helpPrompt" : [
//         {
//            "text" : "VrCommand1,"
//         },
//         {
//            "text" : "VrCommand2,"
//         },
//         {
//            "text" : "VrCommand3,"
//         },
//         {
//            "text" : "VrCommand4,"
//         },
//         {
//            "text" : "VrCommand5,"
//         },
//         {
//            "text" : "VrCommand6,"
//         },
//         {
//            "text" : "VrCommand7,"
//         },
//         {
//            "text" : "VrCommand8,"
//         },
//         {
//            "text" : "VrCommand9,"
//         },
//         {
//            "text" : "VrCommand10,"
//         }
//      ],
//      "initialPrompt" : [
//         {
//            "text" : "1",
//            "type" : "TEXT"
//         }
//      ],
//      "timeout" : 10000,
//      "timeoutPrompt" : [
//         {
//            "text" : "VrCommand1,"
//         },
//         {
//            "text" : "VrCommand2,"
//         },
//         {
//            "text" : "VrCommand3,"
//         },
//         {
//            "text" : "VrCommand4,"
//         },
//         {
//            "text" : "VrCommand5,"
//         },
//         {
//            "text" : "VrCommand6,"
//         },
//         {
//            "text" : "VrCommand7,"
//         },
//         {
//            "text" : "VrCommand8,"
//         },
//         {
//            "text" : "VrCommand9,"
//         },
//         {
//            "text" : "VrCommand10,"
//         }
//      ]
//   }
//}

//---------
//+++++recvFromServer+++++
//{
//   "id" : 219,
//   "jsonrpc" : "2.0",
//   "method" : "UI.PerformInteraction",
//   "params" : {
//      "appID" : 137806862,
//      "choiceSet" : [
//         {
//            "choiceID" : 1,
//            "menuName" : "MenuName1"
//         },
//         {
//            "choiceID" : 2,
//            "menuName" : "MenuName2"
//         },
//         {
//            "choiceID" : 3,
//            "menuName" : "MenuName3"
//         },
//         {
//            "choiceID" : 4,
//            "menuName" : "MenuName4"
//         },
//         {
//            "choiceID" : 5,
//            "menuName" : "MenuName5"
//         },
//         {
//            "choiceID" : 6,
//            "menuName" : "MenuName6"
//         },
//         {
//            "choiceID" : 7,
//            "menuName" : "MenuName7"
//         },
//         {
//            "choiceID" : 8,
//            "menuName" : "MenuName8"
//         },
//         {
//            "choiceID" : 9,
//            "menuName" : "MenuName9"
//         },
//         {
//            "choiceID" : 10,
//            "menuName" : "MenuName10"
//         }
//      ],
//      "initialText" : {
//         "fieldName" : "initialInteractionText",
//         "fieldText" : "Ghhb"
//      },
//      "timeout" : 10000,
//      "vrHelp" : [
//         {
//            "position" : 1,
//            "text" : "VrCommand1"
//         },
//         {
//            "position" : 2,
//            "text" : "VrCommand2"
//         },
//         {
//            "position" : 3,
//            "text" : "VrCommand3"
//         },
//         {
//            "position" : 4,
//            "text" : "VrCommand4"
//         },
//         {
//            "position" : 5,
//            "text" : "VrCommand5"
//         },
//         {
//            "position" : 6,
//            "text" : "VrCommand6"
//         },
//         {
//            "position" : 7,
//            "text" : "VrCommand7"
//         },
//         {
//            "position" : 8,
//            "text" : "VrCommand8"
//         },
//         {
//            "position" : 9,
//            "text" : "VrCommand9"
//         },
//         {
//            "position" : 10,
//            "text" : "VrCommand10"
//         }
//      ],
//      "vrHelpTitle" : "Ghhb"
//   }
//}
//{
//   "id" : 125,
//   "jsonrpc" : "2.0",
//   "method" : "UI.PerformInteraction",
//   "params" : {
//      "appID" : 1025202362,
//      "choiceSet" : [
//         {
//            "choiceID" : 1,
//            "menuName" : "MenuName1"
//         },
//         {
//            "choiceID" : 2,
//            "menuName" : "MenuName2"
//         },
//         {
//            "choiceID" : 3,
//            "menuName" : "MenuName3"
//         },
//         {
//            "choiceID" : 4,
//            "menuName" : "MenuName4"
//         },
//         {
//            "choiceID" : 5,
//            "menuName" : "MenuName5"
//         },
//         {
//            "choiceID" : 6,
//            "menuName" : "MenuName6"
//         },
//         {
//            "choiceID" : 7,
//            "menuName" : "MenuName7"
//         },
//         {
//            "choiceID" : 8,
//            "menuName" : "MenuName8"
//         },
//         {
//            "choiceID" : 9,
//            "menuName" : "MenuName9"
//         },
//         {
//            "choiceID" : 10,
//            "menuName" : "MenuName10"
//         }
//      ],
//      "initialText" : {
//         "fieldName" : "initialInteractionText",
//         "fieldText" : "Llllll"
//      },
//      "timeout" : 10000
//   }
//}
//{
//   "id" : 127,
//   "jsonrpc" : "2.0",
//   "method" : "UI.PerformInteraction",
//   "params" : {
//      "appID" : 1025202362,
//      "timeout" : 10000,
//      "vrHelp" : [
//         {
//            "position" : 1,
//            "text" : "VrCommand1"
//         },
//         {
//            "position" : 2,
//            "text" : "VrCommand2"
//         },
//         {
//            "position" : 3,
//            "text" : "VrCommand3"
//         },
//         {
//            "position" : 4,
//            "text" : "VrCommand4"
//         },
//         {
//            "position" : 5,
//            "text" : "VrCommand5"
//         },
//         {
//            "position" : 6,
//            "text" : "VrCommand6"
//         },
//         {
//            "position" : 7,
//            "text" : "VrCommand7"
//         },
//         {
//            "position" : 8,
//            "text" : "VrCommand8"
//         },
//         {
//            "position" : 9,
//            "text" : "VrCommand9"
//         },
//         {
//            "position" : 10,
//            "text" : "VrCommand10"
//         }
//      ],
//      "vrHelpTitle" : "Gggff"
//   }
//}
void AppData::performInteraction(Json::Value jsonObj)
{
    m_json_interaction = jsonObj;
}



//{
//   "id" : 32,
//   "jsonrpc" : "2.0",
//   "method" : "Navigation.StartStream",
//   "params" : {
//      "appID" : 846930886,
//      "url" : "http://127.0.0.1:5050"
//   }
//}
void  AppData::videoStreamStart(Json::Value jsonObj)
{
    m_videoStreamJson = jsonObj;
}
std::string AppData::getUrlString()
{
    return m_videoStreamJson["params"]["url"].asString();
}

//{
//   "id" : 33,
//   "jsonrpc" : "2.0",
//   "method" : "Navigation.StopStream",
//   "params" : {
//      "appID" : 846930886
//   }
//}
void AppData::videoStreamStop(Json::Value jsonObj)
{

}

/////////////////////////////VR
//{
//   "jsonrpc" : "2.0",
//   "method" : "VR.VRStatus",
//   "params" : {
//      "status" : "TIME_OVER" //SUCCESS //FAIL
//   }
//}

//{
//   "jsonrpc" : "2.0",
//   "method" : "VR.VRCancel",
//   "params" : {}
//}

//{
//   "jsonrpc" : "2.0",
//   "method" : "VR.VRStatus",
//   "params" : {
//      "status" : "SUCCESS"
//   }
//}

std::string AppData::getAppIconFile()
{
    return m_strAppIconFilePath;
}

std::string AppData::getAppName()
{
    return m_szAppName;
}

void AppData::OnVideoScreenTouch(TOUCH_TYPE touch,int x,int y)
{
    ToSDL->OnVideoScreenTouch(touch,x,y);
}
