#include"general.h"

typedef struct QNode{
    QElemType data;
    QNode *next;
}QNode,*QueuePtr;

typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

Status initQueue(LinkQueue &q);
Status destroyQueue(LinkQueue &q);
Status clearQueue(LinkQueue &q);
bool queueEmpty(LinkQueue q);
int queueLength(LinkQueue q);
Status getHead(LinkQueue q,QElemType &e);
Status enQueue(LinkQueue &q,QElemType e);
Status deQueue(LinkQueue &q,QElemType &e);
Status queueTraverse(LinkQueue q,Status(*visit)(QElemType e));

Status initQueue(LinkQueue &q){
    q.front=q.rear=(QueuePtr)malloc(sizeof(QNode));
    if (!q.front){
        printf("初始化队列失败！\n");
        exit(OVERFLOW);
    }
    q.front->next=NULL;
    return OK;
}
Status destroyQueue(LinkQueue &q){
    while(q.front){
        QueuePtr p=q.front;
        q.front=p->next;
        free(p);
    }
    return OK;
}

Status clearQueue(LinkQueue &q){
    QueuePtr p=q.front->next;
    while(p){
        QueuePtr t=p;
        p=p->next;
        free(t);
    }
    q.rear=q.front;
    q.front->next=NULL;
    return OK;
}

bool queueEmpty(LinkQueue q){
    return q.front==q.rear;
}

int queueLength(LinkQueue q){
    int len=0;
    QueuePtr p=q.front->next;
    while(p){
        len++;
        p=p->next;
    }
    return len;
}

Status getHead(LinkQueue q,QElemType &e){
    e=q.front->next->data;
    return OK;    
}

Status enQueue(LinkQueue &q,QElemType e){
    QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
    if (!p){
        printf("存储分配失败！\n");
        exit(OVERFLOW);
    }
    p->data=e;
    p->next=NULL;
    q.rear->next=p;
    q.rear=p;
    return OK;
}

Status deQueue(LinkQueue &q,QElemType &e){
    if (q.front==q.rear){
        printf("队列为空！\n");
        return ERROR;
    }
    QueuePtr p=q.front->next;
    q.front->next=p->next;
    if(q.rear==p){//如果删除的是最后一个元素
        q.rear=q.front;
    }
    free(p);
    return OK;
}

Status queueTraverse(LinkQueue q,Status(*visit)(QElemType e)){
    QueuePtr p=q.front->next;
    while (p){
        if (!visit((p++)->data)){
            return ERROR;
        }
    }
    return OK;
}

int main(){
    LinkQueue q;
    initQueue(q);
    printf("初始化队列，长度为：%d\n",queueLength(q));
    if(queueEmpty(q)){
        printf("队列为空！\n");
    }else{
        printf("队列不为空！\n"); 
    }
    for (int i=0;i<10;i++){
        printf("队尾插入%d\n",i);
        enQueue(q,i);
    }
    printf("此时队列长度:%d\n",queueLength(q));
    if(queueEmpty(q)){
        printf("队列为空！\n");
    }else{
        printf("队列不为空！\n"); 
    }
    QElemType e;
    deQueue(q,e);
    printf("弹出队首元素：%d\n",e);
    getHead(q,e);
    printf("此时的队首元素是：%d\n",e);
    clearQueue(q);
    printf("清空队列，此时队列长度:%d\n",queueLength(q));
    return 0;
}