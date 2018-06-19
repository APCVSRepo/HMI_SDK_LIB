#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QString>

#define CONST_ZERO                  0

#define  SCREEN_H                   800 // mainwindow heigt
#define  SCREEN_W                   480 // mainwindow width

#define APP_BT_W                    120
#define APP_BT_H                    151

#define APP_ICON_W                  120
#define APP_ICON_H                  120

#define COLUMN_SPACE                22
#define ROW_SPACE                   10

#define OFFSET_POS_X                127
#define OFFSET_POS_Y                83

#define QUICK_APP_BT_W              120//64
#define QUICK_APP_BT_H              64

#define QUICK_APP_BT_EDIT_W         30
#define QUICK_APP_BT_EDIT_H         30

#define QUICK_APP_BT_PUSH_W         64
#define QUICK_APP_BT_PUSH_H         64

#define QUICK_APP_ICON_W            44
#define QUICK_APP_ICON_H            44

#define QUICK_COLUMN_SPACE          0
#define QUICK_ROW_SPACE             40

#define QUICK_OFFSET_POS_X          30 //48
#define QUICK_OFFSET_POS_Y          32

#define HOME_PAGE_OFFSET_POS_X      80


#define PHONE_NAME "Phone"
#define SETTINGS_NAME "Setting"
#define MEDIA_NAME "Media"
#define HVAC_NAME "HVAC"
#define WEATHER_NAME "Weather"
#define SDLAPPS_NAME "Application"
#define MESSAGE_NAME "Message"
#define NAV_NAME "Nav"

#define HOME_ID "HOME"
#define QUICKLANUCH_ID "QUICKLANUCH"
#define STATUSBAR_ID "STATUSBAR"
#define POPUP_ID "POPUP"
#define PROMPT_ID "PROMPT"
#define PHONE_ID "PHONE"
#define SETTINGS_ID "SETTING"
#define MEDIA_ID "MEDIA"
#define HVAC_ID "HVAC"
#define WEATHER_ID "WEATHER"
#define SDLAPPS_ID "APPLICATION"
#define MESSAGE_ID "MESSAGE"
#define NAV_ID "NAV"
#define VR_ID "VR"

struct AppInfo
{
    QString AppType;
    QString AppIconPath;
    QString AppName;
    QString AppBgPathNormal;
    QString AppBgPathPush;
    QString AppEditPath;
};

//enum eAppType{

//   eNONE_TYPE = 0,
//   ePHONE_TYPE,
//   eSETTINGS_TYPE,
//   eMEDIA_TYPE,
//   eHVAC_TYPE,
//   eWEATHER_TYPE,
//   eAPPS_TYPE,
//   eMESSAGE_TYPE,
//   eNAV_TYPE,

//};

//enum eAppId{
//    eAppId_Home,
//    eAppId_Apps,
//    eAppId_HVAC,
//    eAppId_Media,
//    eAppId_Message,
//    eAppId_Nav,
//    eAppId_Phone,
//    eAppId_Settings,
//    eAppId_Weather

//};
#endif // APPCONFIG_H
