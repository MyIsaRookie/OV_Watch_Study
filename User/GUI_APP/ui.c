

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


// ����һ����������Ļ����
void Test_study_obj(void)
{
    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    
    // ���ö���Ĵ�С
    lv_obj_set_width(obj, 100); // ���ÿ��

    lv_obj_set_height(obj, 100);// ���ø߶�
    
}

// ����һ������
void Test_study_swtich(void)
{
    lv_obj_t * sw = lv_switch_create(lv_scr_act());
    lv_obj_center(sw);
    
//    lv_obj_add_state(sw, LV_STATE_CHECKED | LV_STATE_DISABLED);

}



 //����һ����ѡ��
void Test_study_checkbox(void)
{
    lv_obj_t * cb = lv_checkbox_create(lv_scr_act());
   
    lv_obj_set_style_bg_opa(cb, LV_OPA_50, LV_PART_MAIN);// ������ʽ������͸����
    lv_obj_set_style_bg_color(cb, lv_color_hex(0xc43e1c), LV_PART_MAIN);// ������ʽ��������ɫ
    
    // �޸Ĺ�ѡ��ͱ�ǩ֮��ļ��
    lv_obj_set_style_pad_column(cb, 50, 0);
    
    // �޸Ĺ�ѡ�򲿷֣�����ѡʱ�ı���  0xFF00FF��ɫ
    lv_obj_set_style_bg_color(cb, lv_color_hex(0xFF00FF), LV_PART_INDICATOR);

    // �޸Ĺ�ѡ�򲿷֣���ѡʱ�ı�����ɫ   0xDC143C��ɫ
    lv_obj_set_style_bg_color(cb, lv_color_hex(0xDC143C), LV_PART_INDICATOR | LV_STATE_CHECKED);    
    
    lv_obj_center(cb);// ����

}















