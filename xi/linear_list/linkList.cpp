#include"general.h"

typedef struct LNode
{
    ElemType data;
    LNode * next;
}LNode,*LinkList;

void printList_L(LinkList l){
    printf("link list is:\n");
    while (l->next){
        l=l->next;
        printf("%d ",l->data);
    }
    printf("\n ");    
}

/**
 * @brief 算法2.8 获取链表的第i个元素
 * 
 * @param l 传入的链表
 * @param i 需要查找的元素的下标（从0开始，不包括头节点）
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
 * @param i 要插入的位置（从0开始，不包括头节点）
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
    if (!p||j>i){
        printf("不存在第i个元素！\n ");
        return ERROR;
    }
    LNode * s=(LinkList) malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return OK;
}

/**
 * @brief 算法2.10 从链表中删除第i个元素
 * 
 * @param l 给定的链表
 * @param i 需要删除的位置（从0开始，不包括头节点）
 * @param e 删除的元素的引用
 * @return Status 返回结果
 */
Status listDelete_L(LinkList &l,int i,ElemType &e){
    LinkList p=l;
    int j=0;
    while (p->next&&j<i){
        p=p->next;
        j++;
    }
    if (!p||j>i){
        printf("删除位置不合理！\n ");
        return ERROR;
    }
    LinkList q=p->next;
    p->next=q->next;
    e=q->data;
    free(q);
    return OK;
}

/**
 * @brief 2.11从链表尾部开始插入节点
 * 
 * @param l 需要插入的链表索引
 * @param n 需要插入的节点数量
 */
void createList_L(LinkList &l,int n){
    l=(LinkList)malloc(sizeof(LNode));
    l->next=NULL;
    while (n--)
    {
        LinkList p=(LinkList)malloc(sizeof(LNode));
        scanf("%d",&p->data);
        p->next=l->next;
        l->next=p;
    }
}

/**
 * @brief 算法2.12 将两个链表合并为一个
 * 
 * @param la 第一个链表
 * @param lb 第二个链表
 * @param lc 结果链表
 */
void mergeList_L(LinkList &la,LinkList &lb,LinkList &lc){
    LinkList pa=la->next;
    LinkList pb=lb->next;
    LinkList pc=lc=la;
    while (pa&&pb)
    {
        if (pa->data>=pb->data){
            pc->next=pb;
            pc=pb;//等价于pc=pc->next
            pb=pb->next;
        }else{
            pc->next=pa;
            pc=pa;
            pa=pa->next;
        }
    }
    pc->next=pa?pa:pb;
    free(lb);
}


int main(){
    LinkList l;
    createList_L(l,0);
    for (size_t i = 0; i < 10; i++)
    {
        listInsert_L(l,i,3*i+1);
    }
    printList_L(l);
    ElemType e;
    getElem_L(l,2,e);
    printf("第2个元素是：%d\n",e);
    listDelete_L(l,7,e);
    printf("删除第7个元素,这个元素是：\n ",e);
    printList_L(l);
    printf("输入要插入的元素个数：\n");
    int n;
    scanf("%d",&n);
    LinkList ll;
    createList_L(ll,n);
    printList_L(ll);
    printf("合并这两个链表\n ");
    LinkList lll;
    createList_L(lll,0);
    mergeList_L(l,ll,lll);
    printList_L(lll);
    return 0;
}