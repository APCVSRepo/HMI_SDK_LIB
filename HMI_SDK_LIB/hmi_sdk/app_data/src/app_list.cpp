/**
* @file			app_list
* @brief		AppListInterface接口实现类，实现手机端App数据控制，保存所有手机端App数据列表（参见AppDataInterface说明），作为UI部分控制指定App的总入口，对于公用部分的RPC请求也会在此处理，指定App的处理将会继续传递到下一层AppDataInterface中进行
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#include "app_list.h"
#include "global_first.h"

namespace hmisdk {

extern std::string string_To_UTF8(const std::string &str);
extern bool IsTextUTF8(char *str, unsigned long long length);

std::string ChangeSlash(std::string strSrc) {
#if defined(WIN32) || defined(WINCE)
  char *pTemp = new char[strSrc.size() + 1];
  strcpy(pTemp, strSrc.c_str());
  for (int i = 0; i != strSrc.size(); ++i) {
    if (pTemp[i] == '\\') {
      pTemp[i] = '/';
    }
  }
  strSrc = pTemp;
  delete []pTemp;
#endif
  return strSrc;
}

int CharToHex(char c) {
  if (c > 0x2f && c < 0x3a) {
    return c - 0x30;
  } else if (c > 0x40 && c < 0x47) {
    return c - 0x41 + 10;
  } else if (c > 0x60 && c < 0x67) {
    return c - 0x61 + 10;
  } else {
    //error
    return 0;
  }
}

int atoi_hex(std::string str) {
  int ret = 0;

  for (int i = 0; i != str.size(); ++i) {
    ret = ret << 4;
    ret += CharToHex(str[i]);
  }

  return ret;
}

const std::string ConvertPathOfURL(const std::string &path) {
  const std::string reserved_symbols = "!#$&'()*+,:;=?@[] ";
  std::string converted_path("");
  const char key = '%';
  char symbols_id[3] = {0, 0, 0};
  char symbols;

  size_t pos = path.find_first_of(key);
  size_t last_pos = 0;

  while (pos != std::string::npos) {
    converted_path += path.substr(last_pos, pos - last_pos);
    ++pos;

    // Bug #9556
    path.copy(symbols_id, 2, pos);
    symbols = static_cast<char>(atoi_hex(symbols_id));
    if (reserved_symbols.find_first_of(symbols) != std::string::npos) {
      converted_path += symbols;
      last_pos = pos + 2;
      pos = path.find_first_of(key, last_pos);
    } else {
      LOGE("---atoi error symbols\n");
      break;
    }
  }

  converted_path += path.substr(last_pos, path.size() - last_pos);

  return converted_path;
}

AppList::AppList() {
  m_pCurApp = NULL;
}

AppList::~AppList() {
  int i;
  for (i = 0; i < m_AppDatas.size(); ++i) {
    delete m_AppDatas[i];
  }
}

void AppList::setUIManager(UIInterface *pUIManager) {
  m_pUIManager = pUIManager;
  if (m_pCurApp)
    m_pCurApp->setUIManager(pUIManager);
}

void AppList::OnShowDeviceList() {
  m_pUIManager->onAppShow(ID_DEVICEVIEW);
}

void AppList::ShowPreviousUI() {
  if (m_pCurApp) {
    if (m_pCurApp->ShowPreviousUI(false))
      return;
  }
  m_pUIManager->onAppShow(ID_APPLINK);
}

void AppList::OnStartDeviceDiscovery() {
  ToSDL->OnStartDeviceDiscovery();
}

void AppList::OnDeviceChosen(const std::string name, const std::string id) {
  ToSDL->OnDeviceChosen(name, id);
}

void AppList::OnFindApplications(std::string name, std::string id) {
  ToSDL->OnFindApplications(name, id);
}

void AppList::getDeviceList(std::vector<DeviceData> &vDevice) {
  vDevice = m_DeviceList;
}

void AppList::OnDeviceSelect(const std::string id) {
  DeviceData data;
  bool bFind = false;
  for (int i = 0; i < m_DeviceList.size(); ++i) {
    if (id == m_DeviceList[i].id) {
      data = m_DeviceList[i];
      bFind = true;
      break;
    }
  }

  if (bFind) {
    ToSDL->OnDeviceChosen(data.name, data.id);
    ToSDL->OnFindApplications(data.name, data.id);
  }
}

AppDataInterface *AppList::getActiveApp() {
  AppDataInterface *ptemp = m_pCurApp;
  return ptemp;
}

Result AppList::onRequest(Json::Value jsonObj) {
  return recvFromServer(jsonObj);
}

void AppList::onNotification(Json::Value jsonObj) {
  if (jsonObj.isMember("method") && jsonObj["method"].asString() != "BasicCommunication.SDLLog") {
    recvFromServer(jsonObj);
  }
}

void AppList::onResult(Json::Value jsonObj) {
  recvFromServer(jsonObj);
}

void AppList::onRawData(void *, int) {
}

void AppList::onError(std::string) {
}

Result AppList::recvFromServer(Json::Value jsonObj) {
  if (jsonObj.isMember("method")) {
    std::string str_method = jsonObj["method"].asString();

    if (str_method == "BasicCommunication.OnAppRegistered") {
      newAppRegistered(jsonObj);
      // 防止在其他App画面弹回到App列表画面
      if (m_pCurApp == NULL) {
        m_pUIManager->onAppShow(ID_APPLINK);
      }
    } else if (str_method == "BasicCommunication.UpdateAppList") {
      updateAppList(jsonObj);
      // 防止在其他App画面弹回到App列表画面，强制图标更新
      if (m_pCurApp == NULL || ID_APPLINK == m_pUIManager->GetCurViewId()) {
        m_pUIManager->onAppShow(ID_APPLINK);
      }
    } else if (str_method == "BasicCommunication.OnAppUnregistered") {
      int appID = jsonObj["params"]["appID"].asInt();
      m_pUIManager->onAppUnregister(appID);
    } else if (str_method == "VR.VRExitApp") {
      m_pUIManager->tsSpeak(ID_EXIT, "退出" + m_pCurApp->m_szAppName);
      m_pUIManager->onAppShow(ID_APPLINK);
    } else if (str_method == "Navigation.StopStream") {
      m_pUIManager->onVideoStreamStop();
      ShowPreviousUI();
    } else if (str_method == "VR.VRSwitchApp") {
//            {
//               "jsonrpc" : "2.0",
//               "method" : "VR.VRSwitchApp",
//               "params" : {
//                  "appID" : 18467,
//                  "appVRName" : "百度 "
//               }
//            }
      std::string strAppVRName = jsonObj["params"]["appVRName"].asString();
      if (!IsTextUTF8((char *)strAppVRName.data(), strAppVRName.size()))
        strAppVRName = string_To_UTF8(strAppVRName);

      m_pUIManager->tsSpeak(ID_SWITCHAPP, strAppVRName);

      int iNewID = jsonObj["params"]["appID"].asInt();
      if (m_pCurApp->m_iAppID != iNewID) {
        std::vector <AppData *>::iterator i;
        for (i = m_AppDatas.begin(); i != m_AppDatas.end(); ++i) {
          if (iNewID == (*i)->m_iAppID) {
            m_pCurApp = *i;
            m_pUIManager->onAppShow(m_pCurApp->getCurUI());
            break;
          }
        }
      }
    } else if (str_method == "UI.SetAppIcon") {
      int iAppId = jsonObj["params"]["appID"].asInt();
      std::vector <AppData *>::iterator Iter = m_AppDatas.begin();

      while (Iter != m_AppDatas.end()) {
        if (iAppId == (*Iter)->m_iAppID) {
          (*Iter)->m_strAppIconFilePath = ChangeSlash(
                                            ConvertPathOfURL(jsonObj["params"]["syncFileName"]["value"].asString()));

          if (m_pCurApp == NULL) {
            m_pUIManager->onAppShow(ID_APPLINK);
          }
          //m_pUIManager->onAppShow(m_pCurApp->getCurUI());
          break;
        }
        ++Iter;
      }
    } else if (str_method == "UI.EndAudioPassThru") {
      ToSDL->OnVRCancelRecord();
      m_pUIManager->OnEndAudioPassThru();
      return RESULT_SUCCESS;
    } else if (str_method == "BasicCommunication.UpdateDeviceList") {
      // add by fanqiang
      updateDeiveList(jsonObj);
      m_pUIManager->ShowDeviceList();
    } else if (str_method == "BasicCommunication.ActivateApp") {
      int iAppID = jsonObj["params"]["appID"].asInt();
      AppData *pData;
      int i;
      for (i = 0; i < m_AppDatas.size(); ++i) {
        pData = m_AppDatas[i];
        if (pData->m_iAppID == iAppID)
          break;
      }

      if (i >= m_AppDatas.size()) {
        return RESULT_SUCCESS;
      }

      // 设置当前活动App
      if (m_pCurApp != NULL && m_pCurApp->m_iAppID != iAppID)
        ToSDL->OnAppOut(m_pCurApp->m_iAppID);
      m_pCurApp = pData;
    }  else if (str_method == "UI.SetDisplayLayout") {
      int iAppId = jsonObj["params"]["appID"].asInt();
      std::string name = jsonObj["params"]["displayLayout"].asString();
      bool bFind = m_pUIManager->FindTemplate(name);
      if (!bFind)
        return RESULT_UNSUPPORTED_RESOURCE;

      std::vector <AppData *>::iterator Iter = m_AppDatas.begin();
      AppData* pData = NULL;
      while (Iter != m_AppDatas.end()) {
        if (iAppId == (*Iter)->m_iAppID) {
          pData = (*Iter);
          pData->SetActiveTemplate(name);
          LOGD("change template to %s\n", name.c_str());
          break;
        }
        ++Iter;
      }

      // 强制刷新当前画面
      if (pData && pData == m_pCurApp && ID_APPLINK != pData->getCurUI())
        m_pUIManager->onAppShow(pData->getCurUI());
    } else {
      if (jsonObj["params"].isMember("appID")) {
        int iAppId = jsonObj["params"]["appID"].asInt();
        std::vector <AppData *>::iterator Iter = m_AppDatas.begin();

        while (Iter != m_AppDatas.end()) {
          if (iAppId == (*Iter)->m_iAppID) {
            return (*Iter)->recvFromServer(jsonObj);
          }
          ++Iter;
        }
      } else {
        if (m_pCurApp) {
          LOGD("#####%s rpc request no appid, goto current app\n", str_method.c_str());
          return m_pCurApp->recvFromServer(jsonObj);
        } else {
          LOGD("#####%s rpc request no appid, no current app\n", str_method.c_str());
          return RESULT_APPLICATION_NOT_REGISTERED;
        }
      }
    }
    return  RESULT_SUCCESS;
  }
  return  RESULT_SUCCESS;
}


//{
//   "jsonrpc" : "2.0",
//   "method" : "BasicCommunication.OnAppRegistered",
//   "params" : {
//      "application" : {
//         "appID" : 846930886,
//         "appName" : "Sina Weibo",
//         "appType" : [ "NAVIGATION" ],
//         "deviceName" : "10.27.0.132",
//         "hmiDisplayLanguageDesired" : "EN-US",
//         "icon" : "",
//         "isMediaApplication" : true,
//         "ngnMediaScreenAppName" : "Sina "
//      },
//      "vrSynonyms" : [ "Sina Weibo" ]
//   }
//}
//{
//   "jsonrpc" : "2.0",
//   "method" : "BasicCommunication.OnAppRegistered",
//   "params" : {
//      "application" : {
//         "appID" : 783368690,
//         "appName" : "SyncProxyTester",
//         "appType" : [
//            "DEFAULT",
//            "COMMUNICATION",
//            "MEDIA",
//            "MESSAGING",
//            "NAVIGATION",
//            "INFORMATION",
//            "SOCIAL",
//            "BACKGROUND_PROCESS",
//            "TESTING",
//            "SYSTEM"
//         ],
//         "deviceName" : "10.27.0.132",
//         "hmiDisplayLanguageDesired" : "EN-US",
//         "icon" : "",
//         "isMediaApplication" : true,
//         "ngnMediaScreenAppName" : "SPT"
//      },
//      "resumeVrGrammars" : true,
//      "ttsName" : [
//         {
//            "text" : "TTS Name 1",
//            "type" : "TEXT"
//         },
//         {
//            "text" : "Tester",
//            "type" : "TEXT"
//         }
//      ],
//      "vrSynonyms" : [ "SPT", "Tester" ]
//   }
//}
void AppList::newAppRegistered(Json::Value jsonObj) {
  AppData *pData = new AppData();
  pData->setUIManager(m_pUIManager);
  pData->m_iAppID = jsonObj["params"]["application"]["appID"].asInt();
  pData->m_szAppName = jsonObj["params"]["application"]["appName"].asString();
  pData->m_szAppType = jsonObj["params"]["application"]["appType"][0].asString();
  pData->addExitAppCommand();
  if (jsonObj["params"]["application"].isMember("icon") && !jsonObj["params"]["application"]["icon"].asString().empty())
    pData->m_strAppIconFilePath = ChangeSlash(ConvertPathOfURL(jsonObj["params"]["application"]["icon"].asString()));

  std::vector <AppData *>::iterator i;
  for (i = m_AppDatas.begin(); i != m_AppDatas.end(); ++i) {
    AppData *pOne = *i;
    if (pOne->m_iAppID == pData->m_iAppID) {
      delete pData;
      return;
      /*
            m_AppDatas.erase(i);
            if (m_pCurApp == pOne)
              m_pCurApp = pData;
            delete pOne;
            break;*/
    }
  }

  m_AppDatas.push_back(pData);
  m_pUIManager->onAppRegister(pData->m_iAppID);
}

void AppList::updateAppList(Json::Value jsonObj) {
  int size = jsonObj["params"]["applications"].size();

  if (size <= 0)
    return;

  for (int i = 0; i < size; i++) {
    AppData *pData = new AppData();
    pData->setUIManager(m_pUIManager);
    pData->m_iAppID = jsonObj["params"]["applications"][i]["appID"].asInt();
    pData->m_szAppName = jsonObj["params"]["applications"][i]["appName"].asString();
    pData->m_szAppType = jsonObj["params"]["applications"][i]["appType"][0].asString();
    if (jsonObj["params"]["applications"][i].isMember("icon"))
      pData->m_strAppIconFilePath = ChangeSlash(ConvertPathOfURL(jsonObj["params"]["applications"][i]["icon"].asString()));
    pData->addExitAppCommand();

    std::vector <AppData *>::const_iterator it;
    bool bFind = false;
    for (it = m_AppDatas.begin(); it != m_AppDatas.end(); ++it) {
      AppData *pOne = *it;
      if (pOne->m_iAppID == pData->m_iAppID) {
        if (!pData->m_strAppIconFilePath.empty()) {
          // 更新图标
          pOne->m_strAppIconFilePath = pData->m_strAppIconFilePath;
        }
        bFind = true;
        break;
        /*
        		  if (pData->m_strAppIconFilePath == "")
        			  pData->m_strAppIconFilePath = pOne->m_strAppIconFilePath;
                m_AppDatas.erase(it);
                if(m_pCurApp == pOne)
                  m_pCurApp = pData;
                delete pOne;
                break;*/
      }
    }

    if (bFind) {
      delete pData;
      continue;
    }

    m_AppDatas.push_back(pData);
  }
}

void AppList::OnAppActivated(int iAppID) {
  AppData *pData;
  int i;
  for (i = 0; i < m_AppDatas.size(); ++i) {
    pData = m_AppDatas[i];
    if (pData->m_iAppID == iAppID)
      break;
  }

  if (i >= m_AppDatas.size()) {
    return;
  }

  if (m_pCurApp != NULL && m_pCurApp->m_iAppID != iAppID)
    ToSDL->OnAppOut(m_pCurApp->m_iAppID);
  m_pCurApp = pData;
  ToSDL->OnAppActivated(iAppID);
  int curScene = m_pCurApp->getCurUI();
  
  if (ID_APPLINK != curScene) {
    if (ID_COMMAND == curScene)
      // 防止画面点不进去或者停留在菜单画面(测试发现从菜单退出应用后再次进入不应该停留在菜单画面，这样体验不好)
      m_pCurApp->ShowPreviousUI();
    else
      // 强制刷新当前画面
      m_pUIManager->onAppShow(curScene);
  } else {
    // 第一次启动App，此处逻辑根据需求来定，一般在收到UI.Show后才显示App画面，但有时App依赖网络但网络不好时，一直不发送Show请求，造成App点击进不去的假象
    // m_pUIManager->onAppShow(ID_SHOW);
  }

  m_pUIManager->onAppActive();
}

void AppList::OnAppExit() {
  ToSDL->OnAppExit(m_pCurApp->m_iAppID);
  m_pCurApp = NULL;
  m_pUIManager->onAppShow(ID_APPLINK);
  m_pUIManager->onAppStop();
}

void AppList::getAppList(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames, std::vector<std::string> &vIconPath) {
  for (int i = 0; i < m_AppDatas.size(); ++i) {
    vAppIDs.push_back(m_AppDatas[i]->m_iAppID);
    vAppNames.push_back(m_AppDatas[i]->m_szAppName);
    vIconPath.push_back(m_AppDatas[i]->m_strAppIconFilePath);
  }
}

void AppList::getAppList(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames, std::vector<std::string> &vIconPath, std::vector<std::string> &vAppTypes)
{
    for (int i = 0; i < m_AppDatas.size(); ++i) {
      vAppIDs.push_back(m_AppDatas[i]->m_iAppID);
      vAppNames.push_back(m_AppDatas[i]->m_szAppName);
      vIconPath.push_back(m_AppDatas[i]->m_strAppIconFilePath);
      vAppTypes.push_back(m_AppDatas[i]->m_szAppType);
    }
}

void AppList::getAppList(std::vector<int> &vAppIDs, std::vector<std::string> &vAppNames) {
  for (int i = 0; i < m_AppDatas.size(); ++i) {
    vAppIDs.push_back(m_AppDatas[i]->m_iAppID);
    vAppNames.push_back(m_AppDatas[i]->m_szAppName);
  }
}

void AppList::appUnregistered(int appId) {
  std::vector <AppData *>::iterator appdata_iter;
  for (appdata_iter = m_AppDatas.begin(); appdata_iter != m_AppDatas.end(); ++appdata_iter) {
    if (appId == (*appdata_iter)->m_iAppID) {
      if (m_pCurApp) {
        if (m_pCurApp->m_iAppID == appId) {
          m_pCurApp = NULL;
          //m_pUIManager->onVideoStreamStop();
        }
      }
      delete *appdata_iter;
      m_AppDatas.erase(appdata_iter);
      break;
    }
  }

  m_pUIManager->onAppShow(ID_APPLINK);
}

void AppList::updateDeiveList(Json::Value jsonObj) {
  m_DeviceList.clear();
  int size = jsonObj["params"]["deviceList"].size();
  for (int i = 0; i < size; i++) {
    DeviceData data;
    Json::Value device = jsonObj["params"]["deviceList"][i];
    data.name = device["name"].asString();
    data.id = device["id"].asString();
    m_DeviceList.push_back(data);
  }
}

}
