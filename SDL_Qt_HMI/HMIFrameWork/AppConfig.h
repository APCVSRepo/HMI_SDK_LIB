#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QString>
#define  SCREEN_H                   720 // mainwindow heigt
#define  SCREEN_W                   1280 // mainwindow width
#define  APP_ICON_W                 117
#define  APP_ICON_H                 114

#define  COLUMN_SPACE               170
#define  ROW_SPACE                  158
#define  MULTI_BT_SIZE              142

#define APP_DEL_ICON_W              20
#define APP_DEL_ICON_H              20
#define MOVE_OFFSET_POS_X           71
#define MOVE_OFFSET_POS_Y           71
#define SCREEN_MAX_W                800
#define REGION_VALUE_W              50
#define MOVE_BG_SIZE                142
#define APP_BT_W                    142
#define APP_BT_H                    142

#define PHONE_NAME "Phone"
#define SETTINGS_NAME "Settings"
#define MEDIA_NAME "Media"
#define HVAC_NAME "HVAC"
#define WEATHER_NAME "Weather"
#define SDLAPPS_NAME "SDLApps"
#define MESSAGE_NAME "Message"
#define NAV_NAME "Nav"

#define HOME_ID "HOME"
#define QUICKLANUCH_ID "QUICKLANUCH"
#define PHONE_ID "PHONE"
#define SETTINGS_ID "SETTINGS"
#define MEDIA_ID "MEDIA"
#define HVAC_ID "HVAC"
#define WEATHER_ID "WEATHER"
#define SDLAPPS_ID "SDLAPPS"
#define MESSAGE_ID "MESSAGE"
#define NAV_ID "NAV"

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
