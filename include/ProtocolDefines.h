#ifndef __PROTOCOL_DEFINES_H__
#define __PROTOCOL_DEFINES_H__

/**@name    Alert画面执行状态
* @{
*/
#define ALERT_TIMEOUT                   0	///<超时
#define ALERT_CLICK_SOFTBUTTON          1	///<点击软按钮
#define ALERT_ABORTED                   2	///<中断
/** @}*/

/**@name    ScrollMessage画面执行状态
* @{
*/
#define SCROLLMESSAGE_TIMEOUT           0	///<超时
#define SCROLLMESSAGE_CLICK_SOFTBUTTON  1	///<点击软按钮
#define SCROLLMESSAGE_REJECTED          2	///<拒绝
/** @}*/

/**@name    按钮按下模式
* @{
*/
#define BUTTON_SHORT                    0	///<短按
#define BUTTON_LONG                     1	///<长按
/** @}*/

/**@name    ChoiceSet画面执行状态
* @{
*/
#define PERFORMINTERACTION_TIMEOUT      10	///<超时
#define PERFORMINTERACTION_CHOICE       0	///<选择VR命令
/** @}*/

/**@name    Slider画面执行状态
* @{
*/
#define SLIDER_OK                       0	///<执行成功
#define SLIDER_TIMEOUT                  10	///<超时
#define SLIDER_ABORTED                  5	///<中断
/** @}*/

/**@name    录音画面执行状态
* @{
*/
#define PERFORMAUDIOPASSTHRU_TIMEOUT    0
#define PERFORMAUDIOPASSTHRU_RETYP      7
#define PERFORMAUDIOPASSTHRU_DONE       0
#define PERFORMAUDIOPASSTHRU_CANCEL     5
/** @}*/

/**@name    TTS执行状态
* @{
*/
#define SPEEK_OK                        0
#define SPEEK_INTERRUPTED               5
/** @}*/

/**  屏幕操作枚举类型*/  
typedef enum
{
    TOUCH_START,	///<  按下 
    TOUCH_MOVE,	///<  移动 
    TOUCH_END	///<  弹起 
}TOUCH_TYPE;

#endif
