#ifndef _PAGE_STACK_H_
#define _PAGE_STACK_H_

#include "ui.h"

// 页面栈深度
#define MAX_DEPTH 6


// 页面结构体
typedef struct {
    void (*init)(void);      // 初始化函数指针    可以通过函数指针调用函数
    void (*deinit)(void);    // 删除函数指针      可以通过函数指针调用函数
    lv_obj_t **page_obj;     // 二级指针，指向 lv_obj_t * 类型
} Page_t;

// 页面堆栈结构体
typedef struct {
    Page_t* pages[MAX_DEPTH];   
    uint8_t top;             // 记录栈顶
} PageStack_t;


extern PageStack_t PageStack;


Page_t* Page_Get_NowPage(void);
void Page_Back(void);
void Page_Back_Bottom(void);
void Page_Load(Page_t *newPage);
void Pages_init(void);



#endif


