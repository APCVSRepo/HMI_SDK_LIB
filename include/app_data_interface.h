/**
* @file			app_data_interface.h  
* @brief		手机端App数据接口
* @author		fanqiang
* @date			2017-6-21 
* @version		A001 
* @copyright	ford                                                              
*/

#ifndef APPDATAINTERFACE_H
#define APPDATAINTERFACE_H

#include "rpc_value_interface.h"
#include <string.h>
#include <vector>
#include "global_first.h"
#include "app_common.h"
#include "protocol_defines.h"

/**  菜单命令项信息*/  
typedef struct command{
    int i_appID;	///<  App ID
    int i_cmdID;	///<  cmd ID
    int i_menuID;	///<  菜单 ID
    std::string str_menuName;	///<  菜单名
    int i_parentID;	///<  父菜单 ID
    int i_position;	///<  菜单命令项所在的位置
    unsigned char i_ImageType;	///<  菜单命令项图标类型
    std::string str_ImagePath;	///<  菜单命令项图标路径

    command()
    {
        i_appID = 0;
        i_cmdID = 0;
        i_menuID = 0;
        str_menuName.clear();
        i_parentID = 0;
        i_position = 0;
        i_ImageType = 0;
        str_ImagePath.clear();
    }
}SMenuCommand;

class AppDataInterface
{
public:
	/** 
	 * 获取Show画面需要的rpc数据
	 * @return		rpcValueInterface&
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual rpcValueInterface& getShowData() = 0;

	/** 
	 * 获取Alert画面需要的rpc数据
	 * @return		rpcValueInterface&
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual rpcValueInterface& getAlertJson() = 0;

	/** 
	 * 获取Slider画面需要的rpc数据
	 * @return		rpcValueInterface&
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual rpcValueInterface& getSlider() = 0;

	/** 
	 * 获取ScrollableMessage画面需要的rpc数据
	 * @return		rpcValueInterface&
	 * @ref			
	 * @see			
	 * @note		
	 */  
	virtual rpcValueInterface& getScrollableMsgJson() = 0;

	/** 
	 * 获取AudioPassThru画面需要的rpc数据
	 * @return		rpcValueInterface&
	 * @ref			
	 * @see			
	 * @note		
	 */  
	virtual rpcValueInterface& getAudioPassThruJson() = 0;

	/** 
	 * 获取ChoiceSet画面需要的rpc数据
	 * @return		rpcValueInterface&
	 * @ref			
	 * @see			
	 * @note		
	 */  
	virtual rpcValueInterface& getInteractionJson() = 0;

	/** 
	 * 获取MediaShow画面需要的rpc数据
	 * @return		rpcValueInterface&
	 * @ref			
	 * @see			
	 * @note		Show画面在media模式时，可通过SetMediaClockTimer rpc请求设置媒体播放进度栏
	 */  
	virtual rpcValueInterface& getMediaClockJson() = 0;

	/** 
	 * 获取所有菜单命令项数据
	 * @return		std::vector<SMenuCommand>
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual std::vector<SMenuCommand> getCommandList() = 0;

	/** 
	 * 获取指定菜单下所有菜单命令项数据
	 * @param[in]	subMenuID		菜单标识
	 * @return		std::vector<SMenuCommand>
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual std::vector<SMenuCommand> getCommandList(int subMenuID) = 0;

	/** 
	 * 获取VideoStream数据源地址
	 * @return		std::string		视频流url源地址
	 * @ref			
	 * @see			
	 * @note		保留
	 */ 
	virtual std::string getUrlString() = 0;

	/** 
	 * 获取当前手机端App名称
	 * @return		std::string		当前手机端App名称
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual std::string getAppName() = 0;

	/** 
	 * 获取当前手机端App图标存放路径
	 * @return		std::string		当前手机端App图标存放路径
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual std::string getAppIconFile() = 0;

	/** 
	 * 获取当前手机端App显示画面的ID
	 * @return		int		当前手机端App显示画面的ID
	 * @ref			
	 * @see			app_common.h ShowType枚举值定义 
	 * @note		
	 */ 
	virtual int getCurUI() = 0;

	/** 
	 * 请求展示当前App菜单列表画面
	 * @return		无
	 * @ref			
	 * @see			app_common.h ShowType枚举值定义 
	 * @note		会调用显示ID_COMMAND画面
	 */ 
	virtual void OnShowCommand() = 0;

	/** 
	 * 软按钮点击通知
	 * @param[in]	sbID		软按钮ID
	 * @param[in]	mode		点击模式
	 * @param[in]	strName		软按钮名称
	 * @return		无
	 * @ref			
	 * @see			protocol_defines.h BUTTON_SHORT BUTTON_LONG
	 * @note		用户点击画面软按钮时，调用SDK该函数将通知传递给手机端App
	 */ 
	virtual void OnSoftButtonClick(int sbID, int mode,std::string strName = "") = 0;

	/** 
	 * 菜单命令项点击通知
	 * @param[in]	cmdID		菜单命令项ID
	 * @return		无
	 * @ref			
	 * @see			
	 * @note		用户在菜单命令画面点击菜单命令项时，调用SDK该函数将通知传递给手机端App
	 */ 
	virtual void OnCommandClick(int cmdID) = 0;

	/** 
	 * Alert画面执行的结果通知
	 * @param[in]	reason		执行结果，参照RESULT_CODE
	 * @return		无
	 * @ref			
	 * @see			app_common.h RESULT_CODE
	 * @note		将Alert画面执行的结果通知给SDK，然后回到前一画面
	 */ 
	virtual void OnAlertResponse(int reason) = 0;

	/** 
	 * ScrollMessage画面执行的结果通知
	 * @param[in]	reason		执行结果，参照RESULT_CODE
	 * @return		无
	 * @ref			
	 * @see			app_common.h RESULT_CODE
	 * @note		将ScrollMessage画面执行的结果通知给SDK，然后回到前一画面
	 */ 
	virtual void OnScrollMessageResponse(int reason) = 0;

	/** 
	 * Slider画面执行的结果通知
	 * @param[in]	reason		执行结果，参照RESULT_CODE
	 * @return		无
	 * @ref			
	 * @see			app_common.h RESULT_CODE
	 * @note		将Slider画面执行的结果通知给SDK，然后回到前一画面
	 */ 
	virtual void OnSliderResponse( int code, int sliderPosition) = 0;

	/** 
	 * TTSSpeek执行的结果通知
	 * @param[in]	code		执行结果
	 * @return		无
	 * @ref			
	 * @see			protocol_defines.h
	 * @note		将TTSSpeek执行的结果通知给SDK，该函数保留
	 */ 
	virtual void OnTTSSpeek(int code) = 0;

	/** 
	 * 录音执行的结果通知
	 * @param[in]	code		执行结果
	 * @return		无
	 * @ref			
	 * @see			protocol_defines.h
	 * @note		将录音执行的结果通知给SDK，该函数保留
	 */ 
	virtual void OnPerformAudioPassThru(int code) = 0;

	/** 
	 * ChoiceSet执行的结果通知
	 * @param[in]	code		执行结果
	 * @return		无
	 * @ref			
	 * @see			protocol_defines.h
	 * @note		将ChoiceSet执行的结果通知给SDK，该函数保留
	 */ 
	virtual void OnPerformInteraction(int code, int choiceID, bool bVR = false) = 0;

	/** 
	 * SetMediaClockTimer执行的结果通知
	 * @param[in]	code		执行结果，参照RESULT_CODE
	 * @return		无
	 * @ref			
	 * @see			app_common.h RESULT_CODE
	 * @note		将SetMediaClockTimer执行的结果通知给SDK
	 */ 
	virtual void OnSetMediaClockTimerResponse(int iCode) = 0;

	/** 
	 * VideoStream画面点击移动操作通知
	 * @param[in]	touch		软按钮ID
	 * @param[in]	x		鼠标操作的屏幕坐标x轴位置
	 * @param[in]	y		鼠标操作的屏幕坐标y轴位置
	 * @return		无
	 * @ref			
	 * @see			protocol_defines.h TOUCH_TYPE
	 * @note		VideoStream画面点击移动操作时通知SDK，调用SDK该函数将通知传递给手机端App
	 */ 
	virtual void OnVideoScreenTouch(TOUCH_TYPE touch,int x,int y) = 0;
};

#endif // APPDATAINTERFACE_H
