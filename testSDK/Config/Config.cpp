#include "Config.h"

int ui_res_width;
int ui_res_height;
float ui_menu_udmargin;//menu up and down ratio:up height=ui_res_width*ui_menu_udmargin
int ui_content_ud;
int ui_content_lr;

int ui_content_width;
int ui_content_height;
int ui_content_left;
int  ui_content_right;

int ui_app_width;
int ui_app_height;

int ui_leftMenu_SizeH;
int ui_leftMenu_SizeW;
int ui_leftMenu_Width;

int ui_aler_width;
int ui_aler_height;

int ui_showScroll_height;
int ui_commandScroll_height;

int ui_item_width;
int ui_item_height;

int ui_btn_width;
int ui_btn_height;

int ui_list_width;
int ui_list_height;
void UIConfig::loadResolution(int res_w,int res_h)
{
    ui_res_width=res_w;//主界面宽
    ui_res_height=res_h;//主界面高
    ui_menu_udmargin=1/6.0;//menu up and down ratio:up height=ui_res_width*ui_menu_udmargin
    ui_content_ud=ui_res_height*ui_menu_udmargin;//中间功能界面的上下边距
    ui_content_lr=15;//中间功能界面的左右边距
    ui_content_left=45;//
    ui_content_right=15;
    ui_content_height=ui_res_height-2*ui_content_ud;
    ui_leftMenu_SizeH=(ui_content_height-4)/6.0;
    ui_leftMenu_Width=ui_leftMenu_SizeH+15;
    ui_leftMenu_SizeW=ui_leftMenu_Width*3/4.0-2;

    ui_content_width=ui_res_width-ui_content_lr*2-ui_leftMenu_Width;
    ui_app_width=ui_content_width-ui_content_right-ui_content_left;
    ui_app_height=ui_content_height-10;

    ui_aler_width=ui_res_width*(1.0/6.0);
    ui_aler_height=ui_res_height*(1.0/8.0);
    ui_showScroll_height=ui_res_height*(1.0/4.0);
    ui_commandScroll_height=ui_res_height*(5.0/12.0);
    ui_item_width=ui_app_width*(3.0/4.0);
    ui_item_height=ui_app_height*(1.0/5.0);
    ui_btn_width=(ui_app_width-30)/4;
    ui_btn_height=ui_app_height*0.18;

    ui_list_width=ui_app_width*2.0/3.0;
    ui_list_height=ui_app_height*1.0/4.0;
}
