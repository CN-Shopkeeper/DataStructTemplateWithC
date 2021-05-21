#include"general.h"
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

/**
 * @date 2021年5月18日l
 * @brief 算法2.8 获取第i个元素的值
 */
Status GetElem_L(LinkList l,int i,ElemType &e){
    LNode * p=l->next;
    int j=1;
    while (p&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i)return ERROR;
    e = p->data;
    return OK;
}
/**
 * @brief 算法2.9 在第i个位置插入元素e
 */
Status ListInsert_L(LinkList &l,int i,ElemType e){
    int j=1;
    LNode * p=l->next;
    while(p&&j<i-1){
        p=p->next;
        j++;
    }
    if(!p||j>i-1)return ERROR;
    LinkList n = (LinkList)malloc(sizeof(LNode));
    n->data = e;
    n->next = p->next;
    p->next = n;
    return OK;
}
/**
 * @brief 算法2.10 删除第i个元素
 */
Status ListDelete_L(LinkList &l,int i,ElemType &e){
    int j=1;
    LNode * p=l->next;
    while(p&&j<i-1){
        p=p->next;
        j++;
    }
    if(!p->next||j>i-1)return ERROR;
    LNode *q;
    q=p->next;
    e=q->data;
    p->next = q->next;
    free(q);
    return OK;
}
/**
 * @brief 算法2.11 逆序位输入n个元素的值，建立带表头结点的单链线性表l
 */
void CreateList_L(LinkList &l,int n){
    ElemType e;
    l=(LinkList)malloc(sizeof(LNode));
    l->next = NULL;
    for(int i=0;i<n;i++){
        LNode * p=(LinkList)malloc(sizeof(LNode));
        scanf("%d",&e);
        p->data = e;
        p->next = l->next;
        l->next = p;
    }
}

/**
 * @brief 算法2.12 la lb非递减，合并到lc，保持非递减，不需要保留la和lb
 * @param la
 * @param lb
 * @param lc
 */
void MergeList(LinkList &la,LinkList &lb,LinkList &lc){
    //-------------------------------------------------没写出来哦，主要是因为想保留la和lb-------------------------------------------
    lc=la;
    LNode *a=la->next,*b=lb->next,*c=lc;
    while(a && b){
        if(a->data <= b->data){
            c->next=a;
            c=a;//移动指针
            a=a->next;
        }else{
            c->next=b;
            c=b;
            b=b->next;
        }
    }
    c->next=a?a:b;//插入剩余段-----------------------------------实在是太妙啦
    free(lb);
}
void print(LinkList l){
    LNode * p=l->next;
    while(p){
        cout<<p->data<<endl;
        p=p->next;
    }
}

//测试
int main(){
    LinkList la,lb,lc;
    printf("enter 10 elements for la:\n");
    CreateList_L(la,10);
    printf("enter 3 elements for la:\n");
    CreateList_L(lb,3);
    ListInsert_L(lb,2,3);
    cout<<"lb after insert"<<endl;
    print(lb);
    ElemType e;
    ListDelete_L(la,2,e);
    cout<<"la after delete"<<endl;
    print(la);
    MergeList(la,lb,lc);
    cout<<"lc"<<endl;
    print(lc);
    return OK;
}