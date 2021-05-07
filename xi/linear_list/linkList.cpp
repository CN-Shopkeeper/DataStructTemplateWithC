#include "general.h"

typedef struct LNode
{
    ElemType data;
    LNode * next;
}LNode,*LinkList;

/**
 * @brief 算法2.8 获取链表的第i个元素
 * 
 * @param l 传入的链表
 * @param i 需要查找的元素的下标（从0开始）
 * @param e 找到的元素存放的位置
 * @return Status 
 */
Status getElem_L(LinkList l,int i,ElemType &e){
    LNode * p=l->next;
    int j=0;
    while(p&&j<i){
        p=p->next;
        j++;
    }
    if (!p||j>i){
        printf("不存在第i个元素！\n");
        return ERROR;
    }
    e=p->data;
    return OK;
}

/**
 * @brief 算法2.9 向链表中插入一个元素
 * 
 * @param l 要插入的链表
 * @param i 要插入的位置（从0开始）
 * @param e 要插入的元素
 * @return Status 返回结果
 */
Status listInsert_L(LinkList &l,int i,ElemType e){
    LNode * p=l;//i=0就是在头指针后面插入
    int j=0;
    while (p&&j<i){
        p=p->next;
        j++;
    }
    if (!p||j>i-1){
        printf("不存在第i个元素！\n ");
        return ERROR;
    }
    LNode * s=(LinkList) malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return OK;
}