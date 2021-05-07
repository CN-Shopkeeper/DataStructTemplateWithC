#include "general.h"

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
    if (!l.elem) exit(OVERFOLLOW);
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
        if (!newBase) exit(OVERFOLLOW);
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
        return EQUARE;
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
        exit(OVERFOLLOW);
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