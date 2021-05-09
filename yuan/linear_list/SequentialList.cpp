#include"general.h"

/**
 * @brief 线性表
 */


typedef struct{
    ElemType * elem;
    int length;//当前长度
    int listsize;//总容量
}SqList;

/**
 * @brief 构造一个空线性表
 * @param l
 * @return Status
 */
Status InitList_Sq(SqList &l){
    l.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!l.elem)exit(OVERFLOW);
    l.length=0;
    l.listsize=LIST_INIT_SIZE;
    return OK;
}
/**
 * @brief 算法2.4 在顺序线性表l中第i个位置之前插入新的元素e
 * @param l
 * @param i
 * @param e
 * @return Status
 */
Status ListInsert_Sq(SqList &l,int i,ElemType e){
    if(i<1||i>l.length+1)return ERROR;
    ElemType* newbase;
    if(l.listsize<=l.length){//若空间不足
        newbase = (ElemType*)realloc(l.elem,(LIST_INIT_SIZE+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)exit(OVERFLOW);
        l.elem = newbase;
        l.listsize = LIST_INIT_SIZE + LISTINCREMENT;
    }
    //空间足够，开始插入操作
    ElemType *p,*q;
    q = &(l.elem[i-1]);
    for(p=&(l.elem[l.length-1]);p>=q;--p)*(p+1)=*(p);
    *q=e;
    ++l.length;
    return OK;
}


/**
 * @brief 算法2.5 在顺序线性表l中删除第i个元素，并用e返回其值
 * @param l
 * @param i
 * @param e
 * @return Status
 */
Status ListDelete_Sq(SqList &l,int i,ElemType &e){
    if(i<1||i>l.length)return ERROR;
    ElemType *p,*q;
    q = &(l.elem[i-1]);
    e= *q;
    for(p=q;p<&(l.elem[l.length-1]);p++)*p=*(p+1);
    --l.length;
    return OK;
}

/**
 * @brief 测试
 */
int main(){
    SqList l;
    InitList_Sq(l);
    for(int i=0;i<5;i++){
        ListInsert_Sq(l,i,i);//第三个参数不太规范
    }
    ElemType e;
    ListDelete_Sq(l,1,e);
    printf("%d\n",e);
    for(int i=0;i<l.length;i++)printf("%d\t",l.elem[i]);
    return 0;
}