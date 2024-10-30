

#include "lvgl.h"






void ui_init(void)
{
    
    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    //lv_obj_set_size(obj, LV_PCT(20), LV_PCT(10));
    lv_obj_set_size(obj, LV_PCT(40), LV_PCT(20));
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * label = lv_label_create(obj);
    lv_label_set_text_fmt(label, "Hello, LVGL!\nLVGL V%d.%d.%d\nhttps://www.100ask.net", lv_version_major(), lv_version_minor(), lv_version_patch());
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

}


// 创建一个基础的屏幕对象
void Test_study_obj(void)
{
    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    
    // 设置对象的大小
    lv_obj_set_width(obj, 100); // 设置宽度

    lv_obj_set_height(obj, 100);// 设置高度
    
}

// 创建一个开关
void Test_study_swtich(void)
{
    lv_obj_t * sw = lv_switch_create(lv_scr_act());
    lv_obj_center(sw);
    
//    lv_obj_add_state(sw, LV_STATE_CHECKED | LV_STATE_DISABLED);

}



 //创建一个复选框
void Test_study_checkbox(void)
{
    lv_obj_t * cb = lv_checkbox_create(lv_scr_act());
   
    lv_obj_set_style_bg_opa(cb, LV_OPA_50, LV_PART_MAIN);// 设置样式，背景透明度
    lv_obj_set_style_bg_color(cb, lv_color_hex(0xc43e1c), LV_PART_MAIN);// 设置样式，背景颜色
    
    // 修改勾选框和标签之间的间距
    lv_obj_set_style_pad_column(cb, 50, 0);
    
    // 修改勾选框部分，不勾选时的背景  0xFF00FF紫色
    lv_obj_set_style_bg_color(cb, lv_color_hex(0xFF00FF), LV_PART_INDICATOR);

    // 修改勾选框部分，勾选时的背景颜色   0xDC143C红色
    lv_obj_set_style_bg_color(cb, lv_color_hex(0xDC143C), LV_PART_INDICATOR | LV_STATE_CHECKED);    
    
    lv_obj_center(cb);// 居中

}















