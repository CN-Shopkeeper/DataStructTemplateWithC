// @Time    :   2021/05/19 22:29:28
// @FileName:   LinkQueue.cpp
// @Author  :   yuan
// @Software:   VSCode

#include"general.h"


typedef struct QNode{
    QElemType data;
    QNode * next;
}QNode,*QueuePtr;
typedef struct {
    QueuePtr front;//队头指针
    QueuePtr rear;//队尾指针
}LinkQueue;

//构造一个空队列
Status initQueue(LinkQueue &q){
    q.front=q.rear=(QNode*)malloc(sizeof(QNode));
    if(!q.rear)exit(OVERFLOW);
    q.front->next=NULL;
    return OK;
}

//销毁队列
Status destroyQueue(LinkQueue &q){
    while(q.front){
        q.rear=q.front->next;
        free(q.front);
        q.front=q.rear;
    }
    return OK;
}

//将Q清空
Status clearQueue(LinkQueue &q){
    //不行不行太简单粗暴了
    // q.front=q.rear;
    // return OK;
    if(q.front==q.rear&&q.front->next==NULL)return OK;//保险起见加一个next的判定，实际上按照书上的判定条件，如果不是循环队列则不需要NULL判定
    QueuePtr d=q.front->next;
    while(d){
        QueuePtr t=d->next;
        free(d);
        d=t;
    }
    q.rear=q.front;
    q.front->next=NULL;
    return OK;
}

//若队列空，返回true，否则false
Status queueEmpty(LinkQueue q){
    return q.front==q.rear;
}

//获取队列元素个数
int queueLength(LinkQueue q){
    int len=0;
    if(q.front==q.rear)return 0;
    QueuePtr ptr=q.front;
    while(ptr!=q.rear){
        len++;
        ptr=ptr->next;
    }
    return len;
}

Status getHead(LinkQueue q,QElemType &e){
    if(q.front==q.rear)return ERROR;
    e=q.front->next->data;
    return OK;
}

//插入元素e为队尾元素
Status enQueue(LinkQueue &q,QElemType e){
    QueuePtr newnode = (QueuePtr)malloc(sizeof(QNode));
    if(!newnode)exit(OVERFLOW);
    newnode->data=e;
    newnode->next=NULL;
    q.rear->next=newnode;
    q.rear=newnode;//更新队尾指针
}

//删除队头元素
Status deQueue(LinkQueue &q,QElemType &e){
    if(q.front==q.rear)return ERROR;
    //注意理清思路，头结点不变，直接删除第二个结点，然后更改指针即可（因为要保证head的data域不存值）
    QueuePtr t=q.front->next;
    e=t->data;
    q.front->next=t->next;
    free(t);
    return OK;
}

//遍历
Status queueTraverse(LinkQueue q,Status(*visit)(QElemType e)){
    if(q.front==q.rear)return ERROR;
    QueuePtr t=q.front->next;
    while(t){//按照NULL来判断是否到队尾了，也可以按照t!=p.rear判断
        if(!visit((t++)->data))return ERROR;//-----------------------------注意这里可以用t++
    }
    return OK;
}

