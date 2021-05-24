#include"general.h"

typedef struct{
    KeysType keys[MAX_NUM_OF_KEY];
    int next;
}SLCell;

typedef struct{
    SLCell r[MAX_SPACE];//0号不用
    int keynum;
    int recnum;
}SLList;

typedef int ArrType[RADIX];

/**
 * @brief 获取当前关键字所处于的位置
 * 
 * @param key 关键字
 * @return int 在权重中的位置
 */
int ord(KeysType key){
    return key;
}

/**
 * @brief 算法10.15 将静态链表中的第i个关键字有序排列
 * 
 * @param l 静态链表
 * @param i 关键字位数
 * @param f 子表开始项
 * @param e 子表结束项
 */
void distribute(SLList &l,int i ,ArrType &f,ArrType &e){
    for (int j=0;j<RADIX;j++){
        f[j]=0;
    }
    for (int p=l.r[0].next;p;p=l.r[p].next){
        int j=ord(l.r[p].keys[i]);
        if (!f[j]){
            f[j]=p;
        }else{
            l.r[e[j]].next=p;
        }
        e[j]=p;
    }
}

/**
 * @brief 算法10.16 将各个子表按照第i个关键字链接为一个链表
 * 
 * @param l 静态链表
 * @param i 关键字位数
 * @param f 子表开始项
 * @param e 子表结束项
 */
void collect(SLList &l,int i,ArrType f,ArrType e){
    int j=0;
    for (;!f[j];j++){}//按照0-9的顺序，所以后继只要自增就可以了
    l.r[0].next=f[j];
    int t=e[j];
    while (j<RADIX){
        for (j++;j<RADIX&&!f[j];j++){}
        if (j<RADIX&&f[j]){
            l.r[t].next=f[j];
            t=e[j];
        }
    }
    l.r[t].next=0;
}

/**
 * @brief 算法10.17 基数排序
 * 
 * @param l 静态链表
 */
void radixSort(SLList &l){
    ArrType f,e;
    for (int i=l.keynum-1;i>=0;i--){
        distribute(l,i,f,e);
        collect(l,i,f,e);
    }
}

/**
 * @brief 初始化一个静态链表
 * 
 * @param l 静态链表
 */
void initSLList(SLList &l){
    l.keynum=5;
    l.recnum=20;
    for (int i=1;i<=20;i++){
        l.r[i-1].next=i;
        for (int j=0;j<5;j++){
            l.r[i].keys[j]=rand()%10;
        }
    }
    l.r[20].next=0;
}

/**
 * @brief 打印静态链表
 * 
 * @param l 静态链表
 */
void printSLList(SLList l){
    printf("the list is:\n");
    for (int p=l.r[0].next;p;p=l.r[p].next){
        for (int j=0;j<5;j++){
            printf("%d",l.r[p].keys[j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    SLList l;
    initSLList(l);
    printSLList(l);
    printf("before\n");
    radixSort(l);
    printf("after\n");
    printSLList(l);
    return 0;
}