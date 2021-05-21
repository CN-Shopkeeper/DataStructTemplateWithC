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
    e=q.base[q.rear-1];
    q.rear=(q.rear-1+MAXQSIZE) % MAXQSIZE;
    return OK;
}

//测试输出结果
void print(SqQueue q){
    for(int i=q.front;i<q.rear;i++){
        cout<<q.base[i]<<'\t';
    }
    cout<<endl;
}

//test
int main(){
    SqQueue q;
    initQueue(q);
    for(int i=1;i<5;i++){
        enQueue(q,i);
    }
    cout<<"队列元素如下："<<queueLength(q)<<endl;
    print(q);
    QElemType e;
    cout<<"删除一个元素：\t";
    deQueue(q,e);
    cout<<e<<endl;
    cout<<"现在的队列:"<<queueLength(q)<<endl;
    print(q);
    return 0;
}