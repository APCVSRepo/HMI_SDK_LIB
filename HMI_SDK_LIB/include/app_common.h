/**
* @file			app_common
* @brief		公共的枚举及宏定义
* @author		fanqiang
* @date			2017-6-21
* @version		A001
* @copyright	ford
*/

#ifndef APPCOMMON_H
#define APPCOMMON_H

namespace hmisdk {

#define DEFAULT_TEMPLATE "MEDIA"
#define DEFAULT_TEMPLATE_PROPERTY "this is media template"

#define DEFAULT_DEFAULT_TEMPLATE "DEFAULT"
#define DEFAULT_DEFAULT_TEMPLATE_PROPERTY "this is default template"

#define MEDIA_TEMPLATE "MEDIA"
#define MEDIA_TEMPLATE_PROPERTY "this is media template"


#define LARGE_GRAPHIC_WITH_SOFTBUTTONS "LARGE_GRAPHIC_WITH_SOFTBUTTONS"
#define LARGE_GRAPHIC_WITH_SOFTBUTTONS_PROPERTY "this is large graphic with softbuttons template"

#define NON_MEDIA "NON-MEDIA"
#define NON_MEDIA_PROPERTY "this is non media template"

#define GRAPHIC_WITH_TEXT "GRAPHIC_WITH_TEXT"
#define GRAPHIC_WITH_TEXT_PROPERTY "this is graphic with text template"

#define TEXT_WITH_GRAPHIC "TEXT_WITH_GRAPHIC"
#define TEXT_WITH_GRAPHIC_PROPERTY "this is text with graphic template"

#define TILES_ONLY "TILES_ONLY"
#define TILES_ONLY_PROPERTY "this is tiles only template"

#define GRAPHIC_WITH_TILES "GRAPHIC_WITH_TILES"
#define GRAPHIC_WITH_TILES_PROPERTY "this is graphic with tiles template"

#define TILES_WITH_GRAPHIC "TILES_WITH_GRAPHIC"
#define TILES_WITH_GRAPHIC_PROPERTY "this is tiles with graphic template"


#define GRAPHIC_WITH_TEXT_AND_SOFTBUTTONS "GRAPHIC_WITH_TEXT_AND_SOFTBUTTONS"
#define GRAPHIC_WITH_TEXT_AND_SOFTBUTTONS_PROPERTY "this is graphic with text and softbuttons template"

#define TEXT_AND_SOFTBUTTONS_WITH_GRAPHIC "TEXT_AND_SOFTBUTTONS_WITH_GRAPHIC"
#define TEXT_AND_SOFTBUTTONS_WITH_GRAPHIC_PROPERTY "this is text and softbuttons  with graphic template"

#define GRAPHIC_WITH_TEXTBUTTONS "GRAPHIC_WITH_TEXTBUTTONS"
#define GRAPHIC_WITH_TEXTBUTTONS_PROPERTY "this is graphic with textbuttons template"

#define DOUBLE_GRAPHIC_WITH_SOFTBUTTONS "DOUBLE_GRAPHIC_WITH_SOFTBUTTONS"
#define DOUBLE_GRAPHIC_WITH_SOFTBUTTONS_PROPERTY "this is double graphic with softbuttons template"

#define TEXTBUTTONS_WITH_GRAPHIC "TEXTBUTTONS_WITH_GRAPHIC"
#define TEXTBUTTONS_WITH_GRAPHIC_PROPERTY "this is textbuttons with graphic template"

#define TEXTBUTTONS_ONLY "TEXTBUTTONS_ONLY"
#define TEXTBUTTONS_ONLY_PROPERTY "this is textbuttons only template"

#define LARGE_GRAPHIC_ONLY "LARGE_GRAPHIC_ONLY"
#define LARGE_GRAPHIC_ONLY_PROPERTY "this is large graphic only template"

#define ONSCREEN_PRESETS "ONSCREEN_PRESETS"
#define ONSCREEN_PRESETS_PROPERTY "this is onscreen presets template"

enum MenuCmdId {
  CMDID_MENU_FM = 101,
  CMDID_MENU_TEL,
  CMDID_MENU_MSG,
  CMDID_MENU_CD,
  CMDID_MENU_LIST
};


/**  画面ID枚举类型*/
enum ShowType {
  ID_APPLINK = 0,	///<  App列表
  ID_DEVICEVIEW,	///<  设备列表
  ID_CHOICESET,	///<  ChoiceSet画面
  ID_COMMAND,	///<  菜单画面
  ID_SHOW,	///<  Show画面
  ID_ALERT,	///<  Alert画面
  ID_AUDIOPASSTHRU,	///<  录音画面
  ID_CHOICESETVR,	///<  保留
  ID_SCROLLMSG,	///<  ScrollMessage画面
  ID_SLIDER,	///<  Slider画面
  ID_NOTIFY,	///<  保留
  ID_MEDIACLOCK,	///<  MediaClockTimer画面
  ID_VIDEOSTREAM,	///<  VideoStream画面
  ID_MAIN,	///<  Main画面
  ID_DIALNUMBER,	///<  拨打电话画面
  ID_UI_MAX
};


#define MIN_APP_BASE  ID_APPLINK
#define MAX_APP_BASE  (ID_SHOW+1)
#define MIN_POP_BASE  ID_ALERT
#define MAX_POP_BASE  (ID_APP_MAX)
enum VRID {
  ID_DEFAULT = 0,
  ID_CANCEL,
  ID_HELP,
  ID_EXIT,
  ID_SWITCHAPP
};

typedef enum {
  ID_CHN_BUTTON = 0,
  ID_CHN_TTS,
  ID_CHN_VR,
  ID_CHN_BASE,
  ID_CHN_UI,
  ID_CHN_VEHICLE,
  ID_CHN_NAVI,
  ID_CHN_MAX
} ID_CHN_TYPE;

/**  执行结果枚举类型*/
enum RESULT_CODE {
  RESULT_SUCCESS = 0,
  RESULT_UNSUPPORTED_REQUEST = 1,
  RESULT_UNSUPPORTED_RESOURCE = 2,
  RESULT_DISALLOWED = 3,
  RESULT_REJECTED = 4,
  RESULT_ABORTED = 5,
  RESULT_IGNORED = 6,
  RESULT_RETRY = 7,
  RESULT_IN_USE = 8,
  RESULT_DATA_NOT_AVAILABLE = 9,
  RESULT_TIMED_OUT = 10,
  RESULT_INVALID_DATA = 11,
  RESULT_CHAR_LIMIT_EXCEEDED = 12,
  RESULT_INVALID_ID = 13,
  RESULT_DUPLICATE_NAME = 14,
  RESULT_APPLICATION_NOT_REGISTERED = 15,
  RESULT_WRONG_LANGUAGE = 16,
  RESULT_OUT_OF_MEMORY = 17,
  RESULT_TOO_MANY_PENDING_REQUESTS = 18,
  RESULT_NO_APPS_REGISTERED = 19,
  RESULT_NO_DEVICES_CONNECTED = 20,
  RESULT_WARNINGS = 21,
  RESULT_GENERIC_ERROR = 22,
  RESULT_USER_DISALLOWED = 23,
  RESULT_USER_WAIT//user added
};

typedef RESULT_CODE  Result;

enum RPC_TYPE {
  RPC_Show = 0,
  RPC_Alert,
  RPC_ScrollMessage,
  RPC_Slider,
  RPC_PerformAudioPassthru,
  RPC_PerformInteraction,
  RPC_StartStream,
  RPC_StopStream,
  RPC_SetMediaClockTimer,
  RPC_MAX
};

}

#endif // APPCOMMON_H

