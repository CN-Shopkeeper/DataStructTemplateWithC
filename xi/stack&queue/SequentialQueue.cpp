#include"general.h"

/**
 * @brief 循环队列
 * 
 */
typedef struct{
    QElemType *base;
    int front;
    int rear;
}SqQueue;

Status initQueue(SqQueue &q);
Status destroyQueue(SqQueue &q);
Status clearQueue(SqQueue &q);
bool queueEmpty(SqQueue q);
int queueLength(SqQueue q);
Status getHead(SqQueue q,QElemType &e);
Status enQueue(SqQueue &q,QElemType e);
Status deQueue(SqQueue &q,QElemType &e);

/**
 * @brief 初始化队列
 * 
 * @param q 队列的引用
 * @return Status 操作结果
 */
Status initQueue(SqQueue &q){
    q.base=(QElemType*)malloc(MAXQSIZE*sizeof(QElemType));
    if (!q.base){
        printf("存储分配失败！\n");
        exit(OVERFLOW);
    }
    q.front=q.rear=0;
    return OK;
}

/**
 * @brief 摧毁队列
 * 
 * @param q 队列引用
 * @return Status 操作结果
 */
Status destroyQueue(SqQueue &q){
    free(q.base);
    q.front=q.rear=0;
    return OK;
}

/**
 * @brief 清空队列
 * 
 * @param q 队列引用
 * @return Status 操作结果
 */
Status clearQueue(SqQueue &q){
    q.rear=q.front;
    return OK;
}

/**
 * @brief 判断队列是否为空
 * 
 * @param q 队列引用
 * @return true 队列为空
 * @return false 队列不为空
 */
bool queueEmpty(SqQueue q){
    return q.front==q.rear;
}

/**
 * @brief 获取队列长度
 * 
 * @param q 队列引用
 * @return int 队列长度
 */
int queueLength(SqQueue q){
    return (q.rear-q.front+MAXQSIZE)%MAXQSIZE;
}

/**
 * @brief 获取队列队首元素
 * 
 * @param q 队列引用
 * @param e 队首元素引用
 * @return Status 操作结果
 */
Status getHead(SqQueue q,QElemType &e){
    if (!q.base||queueEmpty(q)){
        printf("队列为空或不存在！\n");
        return ERROR;
    }
    e=q.base[q.front];
    return OK;
}

/**
 * @brief 插入元素
 * 
 * @param q 队列引用
 * @param e 要插入的元素的引用
 * @return Status 操作结果
 */
Status enQueue(SqQueue &q,QElemType e){
    if ((q.rear+1)%MAXQSIZE==q.front){
        printf("队列已满\n");
        return ERROR;
    }
    q.base[q.rear]=e;
    q.rear=(q.rear+1)%MAXQSIZE;
    return OK;
}

/**
 * @brief 弹出队首元素
 * 
 * @param q 队列引用
 * @param e 弹出元素的引用
 * @return Status 操作结果
 */
Status deQueue(SqQueue &q,QElemType &e){
    if (queueEmpty(q)){
        printf("队列为空！\n");
        return ERROR;
    }
    e=q.base[q.front];
    q.front=(q.front+1)%MAXQSIZE;
    return OK;
}

int main(){
    SqQueue q;
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

    printf("\n\n测试插入过多元素\n");
    for (int i=0;i<MAXQSIZE;i++){
        enQueue(q,i);
    }
    return 0;
}