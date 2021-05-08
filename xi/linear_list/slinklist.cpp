#include"general.h"

/**
 * @brief 静态链表
 * 
 */
typedef struct{
    ElemType data;
    int cur;
}component,SlinkList[MAXSIZE];

void printList_SL(SlinkList l){
    printf("the SLinkList is:\n");
    int i=0;
    while (l[i].cur){
        i=l[i].cur;
        printf("%d ",l[i].data);
    }
    printf("\n");
}

/**
 * @brief 算法2.13 在静态链表中定位一个元素
 * 
 * @param s 需要定位的静态链表
 * @param e 需要查找的元素
 * @return int 元素的位置（从0开始），如果不存在就返回-1
 */
int locateElem_SL(SlinkList s,ElemType e){
    int i=s[0].cur;
    while(i&&s[i].data!=e){
        i=s[i].cur;
    }
    return !i?i:-1;
}

/**
 * @brief 算法2.14 生成一个大小为MAXSIZE的备用链表，用于存储空闲的节点
 * 
 * @param space 空闲链表头节点的引用
 */
void initSpace_SL(SlinkList &space){
    for (int i=0;i<MAXSIZE-1;i++){
        space[i].cur=i+1;
    }
    space[MAXSIZE-1].cur=0;
}

/**
 * @brief 算法2.15 从备用链表中取出一个节点
 * 
 * @param space 备用链表头节点
 * @return int 分配得到的节点下标，如果是0则分配失败
 */
int malloc_SL(SlinkList &space){
    int i=space[0].cur;
    if (i){//i是下一个空闲的节点，若为0则无空闲
        space[0].cur=space[i].cur;
    }
    return i;
}

/**
 * @brief 算法2.16 回收一个节点到备用链表
 * 
 * @param space 备用链表头节点
 * @param k 回收节点的下标
 */
void free_SL(SlinkList &space,int k){
    space[k].cur=space[0].cur;
    space[0].cur=k;
}

/**
 * @brief 创建一个静态链表（实际上只是将其初始化
 * 
 * @param l 静态链表
 */
void createList_SL(SlinkList &l){
    l[0].cur=0;
}

/**
 * @brief 向静态链表尾部插入一个元素
 * 
 * @param l 静态链表首部
 * @param space 备用链表首部
 * @param tail 尾部节点下标
 * @param e 插入元素
 * @return Status 返回操作结果
 */
Status insertList_SL(SlinkList &l,SlinkList &space,int &tail,ElemType e){
    int i=malloc_SL(space);
    if (!i){//教材中这里没有检查是否溢出
        printf("备用链表已经分配完！\n");
        return OVERFOLLOW;
    }
    l[i].data=e;
    l[i].cur=l[tail].cur;
    l[tail].cur=i;
    tail=i;
    return OK;
}

/**
 * @brief 删除下标为k的元素
 * 
 * @param l 静态链表
 * @param space 备用链表
 * @param p k的上一个节点
 * @param k 要删除的元素的下标
 */
void deleteList_SL(SlinkList &l,SlinkList &space,int p,int k){
    l[p].cur=l[k].cur;
    free_SL(space,k);
}


/**
 * @brief 输入两个集合A、B，求(A-B)与(B-A)的并集
 * 
 * @param l 结果链表
 * @param space 备用链表
 * @return Status 返回结果
 */
Status difference(SlinkList &l,SlinkList &space){
    initSpace_SL(space);
    createList_SL(l);
    int s=0;
    int r=s,n,m;
    printf("请输入A和B的元素个数：\n");
    scanf("%d%d",&m,&n);
    for (int j=1,i;j<=m;j++){
        scanf("%d",&i);
        if (insertList_SL(l,space,r,i)!=1){
            return ERROR;
        }
    }
    /**
     * @brief 参数说明
     * b是当前集合B中的数
     * k是我们想要找到的A集合中等于b的节点的下标
     * p是k的前一个节点
     * 
     */
    for (int j=1,i,b,p,k;j<=n;j++){
        scanf("%d",&b);
        p=s;
        k=l[s].cur;
        while(k!=l[r].cur&&l[k].data!=b){
            p=k;k=l[k].cur;
        }
        if(k==l[r].cur){//如果不包含则插入
            insertList_SL(l,space,r,b);
        }else{
            deleteList_SL(l,space,p,k);
            if (r==k){//如果删除的是最后一个节点，需要让r=p
                r=p;
            }
        }
    }
    return OK;
}

int main(){
    SlinkList l;
    SlinkList space;
    int s=0;
    difference(l,space);
    printList_SL(l);
    return 0;
}