#include"general.h"

/**
 * @brief 双链表
 * 
 */
typedef struct DuLNode{
    ElemType data;
    DuLNode *prior;
    DuLNode *next;
}DuLNode,*DuLinkList;

/**
 * @brief 打印双链表内容
 * 
 * @param l 要打印的双链表
 */
void printList_DuL(DuLinkList l){
    printf("the list is:\n");
    while (l->next){
        l=l->next;
        printf("%d ",l->data);
    }
    printf("\n");
}

/**
 * @brief 创建一个只包含头节点的双链表
 * 
 * @param l 头节点的索引
 */
void createList_DuL(DuLinkList &l){
    l=(DuLinkList)malloc(sizeof(DuLNode));
    l->next=NULL;
    l->prior=NULL;
}

/**
 * @brief 获取链表中第i个元素的前一个节点的指针
 * 注意这里和教材上有所区别，教材上是直接获取那个节点的指针，但是显然是做不到的（算法2.18中要先获取一个指针再插入这个节点，这是不可能实现的）
 * 
 * @param l 要寻找的链表
 * @param i 要寻找的位置
 * @return DuLinkList 要寻找的节点的前一个节点的指针
 */
DuLinkList getElemP_DuL(DuLinkList l,int i){
    int j=0;
    while (l->next&&j<i){
        j++;
        l=l->next;
    }
    if (!l||j>i){
        printf("查找位置错误！\n");
        return NULL;
    }
    return l;
}

/**
 * @brief 算法2.18 向双链表中的特定位置插入一个元素
 * 
 * @param l 
 * @param i 
 * @param e 
 * @return Status 
 */
Status listInsert_DuL(DuLinkList &l,int i,ElemType e){
    DuLinkList p,s;
    if (!(p=getElemP_DuL(l,i))){
        return ERROR;
    }
    if(!(s=(DuLinkList)malloc(sizeof(DuLNode)))){
        printf("新建节点失败！\n");
        return ERROR;
    }
    s->data=e;
    s->prior=p;
    s->next=p->next;
    if (p->next){//注意，这里一定要判断是否为NULL，课本上没有判断
      p->next->prior=s;  
    }
    p->next=s;
    return OK;
}

Status listDelete_DuL(DuLinkList &l,int i,ElemType &e){
    DuLinkList p=getElemP_DuL(l,i);
    p=p->next;
    if (!p){
        printf("删除位置有误！\n");
        return ERROR;
    }
    e=p->data;
    p->prior->next=p->next;
    if (p->next){
        p->next->prior=p->prior;
    }
    free(p);
    return OK;
}


int main(){
    DuLinkList l;
    createList_DuL(l);
    ElemType e;
    listDelete_DuL(l,0,e);
    for (int i=0;i<10;i++){
        listInsert_DuL(l,i,3*i+2);
    }
    printList_DuL(l);
    int position=2;
    listDelete_DuL(l,position,e);
    printf("删除了第%d个元素（从0开始），这个元素是%d\n",position,e);
    printList_DuL(l);
    return 0;
}