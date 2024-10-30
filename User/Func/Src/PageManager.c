
#include "PageManager.h"

PageStack_t PageStack;

// ջ��ʼ������
static void page_stack_init(PageStack_t* stack)
{
    stack->top = 0;

}


// ��ջ
static uint8_t page_stack_push(PageStack_t* stack, Page_t* page)
{
    if (stack->top >= MAX_DEPTH) return -1; // ջ��������-1,��Ϊ���ص����޷������ݣ����Խ��ܵ��ķ���ֵ��0xFF
    stack->pages[stack->top++] = page;
    return 0;

}

// ��ջ
static uint8_t page_stack_pop(PageStack_t* stack)
{
    if (stack->top <= 0) return -1;
    stack->pages[--stack->top]->deinit();
    return 0;
}

// �ж�ջ�Ƿ�Ϊ��
static uint8_t page_stack_is_empty(const PageStack_t* stack) {
    return stack->top == 0;
}

// ��ȡջ��ҳ���ָ��
static Page_t* get_top_page(PageStack_t* stack)
{
    
    if (stack->top == 0)  // ���ջ�Ƿ�Ϊ��
    {
        return NULL; // ���ջΪ�գ�����NULL
    }    
   
    return stack->pages[stack->top - 1]; // ����ջ��ҳ���ָ��
    
}

/**
 * ��ȡ��ǰҳ�棨ջ��ҳ�棩��ָ�롣
 *
 * @param NULL
 * @return ���ص�ǰҳ���ָ�룬���ջΪ���򷵻�NULL��
 */
Page_t* Page_Get_NowPage(void) {
    return get_top_page(&PageStack);
}

/**
 * back to previous page  �����ϸ�ҳ��
 *
 * @param NULL
 * @return NULL
 */
void Page_Back(void) {
	if (page_stack_is_empty(&PageStack)) {
        // ջΪ��ʱ����Ӧ����
        return;
    }

    // ������ǰҳ��
    page_stack_pop(&PageStack);

    // �жϳ�ջ��ջ�Ƿ�Ϊ��
    if (page_stack_is_empty(&PageStack)) 
    {
        // ���ջΪ�գ���ջ���л���MenuPage
//        page_stack_push(&PageStack, &Page_Home);
//        page_stack_push(&PageStack, &Page_Menu);
//        Page_Menu.init();
//        lv_scr_load_anim(*Page_Menu.page_obj, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0, true);
    } 
    else 
    {
        // �л�����һ��ҳ��
        Page_t *previous_page = PageStack.pages[PageStack.top - 1];
        previous_page->init();
        lv_scr_load_anim(*previous_page->page_obj, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0, true);
    }
}

/**
 * back to bottom page home page
 *
 * @param NULL
 * @return NULL
 */
void Page_Back_Bottom(void) {

    if (page_stack_is_empty(&PageStack)) {
        // ջΪ��ʱ����Ӧ����
        return;
    }

    // ������ջ�׵�����ҳ��
    while(PageStack.top > 1)
    {
        page_stack_pop(&PageStack);
    }
        
    PageStack.pages[PageStack.top - 1]->init(); // ��ʼ����ҳ��
    lv_scr_load_anim(*PageStack.pages[PageStack.top - 1]->page_obj, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0, true); // ���ز�Ӧ�ö���
}

/**
 * Load a new page to stack top
 *
 * @param newPage Page_t a new page
 * @return NULL
 */
void Page_Load(Page_t *newPage) {
	// ����ջ�Ƿ�����
    if (PageStack.top >= MAX_DEPTH - 1) {
        // ��������ջ��
        return;
    }

    // �����ջ�ǿգ�����ʼ����ǰҳ��
    // �µ�ҳ�͵�ǰ��ҳ����ͬһ���ģ������Ȱѵ�ǰ��ҳ��ɾ�������ڼ����µ�ҳ�浽��ǰλ��
    if (PageStack.top > 0) {
        PageStack.pages[PageStack.top - 1]->deinit();
    }

    // ����ҳ�������ջ
    page_stack_push(&PageStack, newPage);
    newPage->init(); // ��ʼ����ҳ��
    lv_scr_load_anim(*newPage->page_obj, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0, true); // ���ز�Ӧ�ö���
}

/**
 * initialize the page manager & start home page
 *
 * @param NULL
 * @return NULL
 */
void Pages_init(void) {
    page_stack_init(&PageStack);
//    page_stack_push(&PageStack, &Page_Home);
//    Page_Home.init();
//    lv_disp_load_scr(*Page_Home.page_obj);
}






