#ifndef _PAGE_STACK_H_
#define _PAGE_STACK_H_

#include "ui.h"

// ҳ��ջ���
#define MAX_DEPTH 6


// ҳ��ṹ��
typedef struct {
    void (*init)(void);      // ��ʼ������ָ��    ����ͨ������ָ����ú���
    void (*deinit)(void);    // ɾ������ָ��      ����ͨ������ָ����ú���
    lv_obj_t **page_obj;     // ����ָ�룬ָ�� lv_obj_t * ����
} Page_t;

// ҳ���ջ�ṹ��
typedef struct {
    Page_t* pages[MAX_DEPTH];   
    uint8_t top;             // ��¼ջ��
} PageStack_t;


extern PageStack_t PageStack;


Page_t* Page_Get_NowPage(void);
void Page_Back(void);
void Page_Back_Bottom(void);
void Page_Load(Page_t *newPage);
void Pages_init(void);



#endif


