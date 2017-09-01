#ifndef CONFIG_H
#define CONFIG_H
#include <global_first.h>
enum
{
    W800_H480=0,
    W1024_H600=1
};

extern int ui_res_width;
extern int ui_res_height;
extern float ui_menu_udmargin;//menu up and down ratio:up height=ui_res_width*ui_menu_udmargin
extern int ui_content_ud;
extern int ui_content_lr;
extern int ui_content_width;
extern int ui_content_height;
extern int ui_content_left;
extern int  ui_content_right;
extern int ui_leftMenu_SizeW;
extern int ui_leftMenu_SizeH;
extern int ui_leftMenu_Width;
extern int ui_aler_width;
extern int ui_aler_height;
extern int ui_showScroll_height;
extern int ui_commandScroll_height;
extern int ui_item_width;
extern int ui_item_height;
extern int ui_btn_width;
extern int ui_btn_height;
extern int ui_list_width;
extern int ui_list_height;

extern int ui_app_width;
extern int ui_app_height;
class UIConfig
{
public:

    static void loadResolution(int res_w,int res_h);
};




#endif // CONFIG_H
