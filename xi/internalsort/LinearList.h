#include"general.h"

/**
 * @brief 线性表
 * 
 */
typedef struct {
    ElemType *elem;
    int length;
    int listsize;
}SqList;

/**
 * @brief 输出一个线性表的所有元素
 * 
 * @param l 要输出的线性表
 */
void printList_Sq(SqList &l){
    printf("SqList length is:%d\n",l.length);
    for (size_t i = 0; i < l.length; i++)
    {
        printf("%d ",l.elem[i]);
    }
    printf("\n");
}
/**
 * @brief 算法2.3 初始化一个线性表
 * 
 * @param l 需要生成的线性表
 * @return Status 返回结果
 */
Status initList_Sq(SqList &l){
    l.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if (!l.elem) exit(OVERFLOW);
    l.length=0;
    l.listsize=LIST_INIT_SIZE;
    return OK;
}


/**
 * @brief 算法2.4 向线性表中插入一个数据
 * 
 * @param l 需要插入的线性表
 * @param i 需要插入的位置（从0开始）
 * @param e 需要插入的元素
 * @return Status 返回结果
 */
Status listInsert_Sq(SqList &l,int i,ElemType e){
    if (i<0||i>l.length) { //越界
        printf("下标越界！\n");
        return ERROR;
    }
    if (l.length>l.listsize) //当前分配空间已满
    {
        ElemType * newBase=(ElemType *)realloc(l.elem,(l.listsize+LISTINCREMENT)*sizeof(ElemType));
        if (!newBase) exit(OVERFLOW);
        l.elem=newBase;
    }
    ElemType* q=&(l.elem[i]);
    for (ElemType*  p = &(l.elem[l.length-1]); p >= q; p--)
    {
        *(p+1)=*p;
    }
    *q=e;
    ++l.length;
    return OK;
}

/**
 * @brief 算法2.5 从线性表中删除一个数据
 * 
 * @param l 需要删除元素的线性表
 * @param i 需要删除的位置（从0开始）
 * @param e 需要删除的元素
 * @return Status 返回结果
 */
Status listDelete_Sq(SqList &l,int i,ElemType &e){
    if (i<0||i>=l.length) { //越界
        printf("下标越界！\n");
        return ERROR;
    }
    ElemType * p=&(l.elem[i]);
    e=*p;
    ElemType * q=l.elem+l.length-1;
    for (++p;p<=q;++p){
        *(p-1)=*p;
    }
    --l.length;
    return OK;
}

/**
 * @brief 算法2.6 查询线性表中是否有某一个元素
 * 
 * @param l 目标线性表
 * @param e 要查找的元素
 * @param compare 两元素之间的比较函数
 * @return int 若存在则返回第一个元素的下表，否则返回-1
 */
int locateElem_Sq(SqList &l,ElemType e,Status(* compare)(ElemType,ElemType)){
    int i=0;
    ElemType *p =l.elem;
    while (i<l.length&&!(*compare)(e,*p++)){
        i++;
    }
    if (i<l.length) return i;
    else return -1;
}

/**
 * @brief 算法2.6 要用到的比较函数
 * 
 * @param x 第一个元素
 * @param y 第二个元素
 * @return Status 0相等；-1小于；1大于
 */
Status compare_ElemType(ElemType x,ElemType y){
    if (x>y){
        return GREATER;
    }else if(x==y){
        return EQUAL;
    }else{
        return LESSER;
    }
}

/**
 * @brief 算法2.1 求两个线性表的并集
 * 
 * @param a 第一个线性表
 * @param b 第二个线性表
 */
void union_Sq(SqList &a,SqList b){
    int lena=a.length;
    int lenb=b.length;
    int e;
    for (int i=0;i<lenb;i++){
        e=b.elem[i];
        if (!locateElem_Sq(a,e,compare_ElemType)){
            listInsert_Sq(a,a.length,e);
        }
    }
}

/**
 * @brief 算法2.7 对两线性表进行归并排序
 * 
 * @param a 第一个线性表
 * @param b 第二个线性表
 * @param c 结果线性表
 */
void mergeList_Sq(SqList a,SqList b,SqList &c){
    ElemType * pa=a.elem;
    ElemType * pb=b.elem;
    c.listsize=c.length=a.length+b.length;
    ElemType * pc=c.elem=(ElemType *) malloc(c.listsize*sizeof(ElemType));
    if (!pc) {
        printf("内存分配失败！\n ");
        exit(OVERFLOW);
    }
    ElemType * pa_last=a.elem+a.length-1;
    ElemType * pb_last=b.elem+b.length-1;
    while (pa<=pa_last&&pb<=pb_last) {
        if (*pa<=*pb) {
            *pc++=*pa++;
        }else{
            *pc++=*pb++;
        }
    }
    while (pa<=pa_last){
        *pc++=*pa++;
    }
    while (pb<=pb_last) {
        *pc++=*pb++;
    }
}

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
        return OVERFLOW;
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