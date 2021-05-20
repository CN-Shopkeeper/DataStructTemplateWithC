// @Time    :   2021/05/20 21:29:25
// @FileName:   CircularQueue.cpp
// @Author  :   yuan
// @Software:   VSCode
#include"general.h"

//循环队列
typedef struct{
    QElemType *base;
    int front;
    int rear;
}SqQueue;

Status initQueue(SqQueue &q){
    q.base =(QElemType*)malloc(MAXQSIZE*sizeof(QElemType));
    if(!q.base)exit(OVERFLOW);
    q.front=q.rear=0;
    return OK;
}

int queueLength(SqQueue q){
    // return q.rear-q.front;
    //错！注意是循环队列循环队列！！
    return (q.rear-q.front+MAXQSIZE)% MAXQSIZE;
}

Status enQueue(SqQueue &q,QElemType e){
    if((q.rear+1)% MAXQSIZE ==q.front)return ERROR;
    q.base[q.rear]=e;
    // q.rear++;
    q.rear=(q.rear+1)%MAXQSIZE;
    return OK;
}

Status deQueue(SqQueue &q,QElemType &e){
    if(q.front==q.rear)return ERROR;
    q.rear=(q.rear-1+MAXQSIZE) % MAXQSIZE;
    return OK;
}