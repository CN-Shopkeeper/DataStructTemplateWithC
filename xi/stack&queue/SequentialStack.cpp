#include"general.h"

/**
 * @brief 栈
 * 
 */
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

Status initStack(SqStack &s);
Status destroyStack(SqStack &s);
Status clearStack(SqStack &s);
bool stackEmpty(SqStack s);
int stackLength(SqStack s);
Status getTop(SqStack s,SElemType &e);
Status push(SqStack &s,SElemType e);
Status pop(SqStack &s,SElemType &e);
Status stackTraverse(SqStack s,Status(*visit)(SElemType e));

/**
 * @brief 初始化一个栈
 * 
 * @param s 栈索引
 * @return Status 操作结果
 */
Status initStack(SqStack &s){
    s.base=(SElemType *)malloc(sizeof(SElemType)*STACK_INIT_SIZE);
    if(!s.base){
        printf("栈存储分配失败\n");
        exit(OVERFLOW);
    }
    s.top=s.base;
    s.stacksize=STACK_INIT_SIZE;
    return OK;
}

/**
 * @brief 摧毁一个栈
 * 
 * @param s 栈索引
 * @return Status 操作结果
 */
Status destroyStack(SqStack &s){
    free(s.base);
    s.base=NULL;
    s.top=NULL;
    s.stacksize=0;
    //如果栈是动态分配空间的，需要调用free来释放s
    //free(&s);
    return OK;
}

/**
 * @brief 清空一个栈
 * 
 * @param s 栈索引
 * @return Status 操作结果
 */
Status clearStack(SqStack &s){
    s.top=s.base;
    s.stacksize=0;
    return OK;
}

/**
 * @brief 判断一个栈是否为空
 * 
 * @param s 栈索引
 * @return true 栈为空
 * @return false 栈不为空
 */
bool stackEmpty(SqStack s){
    return s.base==s.top;
}

/**
 * @brief 获取栈的长度
 * 
 * @param s 栈索引
 * @return int 栈长度
 */
int stackLength(SqStack s){
    return s.top-s.base;
}

/**
 * @brief 获取栈顶元素
 * 
 * @param s 栈索引
 * @param e 栈顶元素索引
 * @return Status 操作结果
 */
Status getTop(SqStack s,SElemType &e){
    if(stackEmpty(s)){
        return ERROR;
    }
    e=*(s.top-1);
    return OK;
}

/**
 * @brief 向栈顶压入一个元素
 * 
 * @param s 栈索引
 * @param e 压入的元素
 * @return Status 操作结果
 */
Status push(SqStack &s,SElemType e){
    if (!s.base){
        printf("栈异常\n");
        return ERROR;
    }
    if (s.top-s.base>=s.stacksize){
        s.base=(SElemType *)realloc(s.base,(s.stacksize+STACKINCREMENT)*sizeof(SElemType));
        if (!s.base){
            printf("栈空间追加失败！\n");
            exit(OVERFLOW);
        }
    }
    *(s.top++)=e;
    return OK;
}

/**
 * @brief 从栈顶弹出一个元素
 * 
 * @param s 栈索引
 * @param e 弹出元素的索引
 * @return Status 操作结果
 */
Status pop(SqStack &s,SElemType &e){
    if (!s.base||stackEmpty(s)){
        printf("栈不存在或为空\n");
        return ERROR;
    }
    e=*(--s.top);
    return OK;
}

/**
 * @brief 从栈底遍历元素
 * 
 * @param s 栈索引
 * @param visit 遍历函数
 * @return Status 操作结果
 */
Status stackTraverse(SqStack s,Status(*visit)(SElemType e)){
    if (!s.base){
        printf("栈异常\n");
        return ERROR;
    }
    SElemType *p=s.base;
    while (p!=s.top){
        if(!printSElement(*p++)){
            return ERROR;
        }
    }
    return OK;
}

int main(){
    SqStack s;
    initStack(s);
    printf("初始化后，");
    if (stackEmpty(s)){
        printf("栈为空\n");
    }else{
        printf("栈不为空\n");
    }
    for (int i=0;i<10;i++){
        printf("向栈中压入%d\n",i);
        push(s,i);
    }
    printf("栈的长度为：%d\n",stackLength(s));
    SElemType e;
    pop(s,e);
    printf("弹出栈顶元素：%d\n",e);
    destroyStack(s);
    return 0;
}