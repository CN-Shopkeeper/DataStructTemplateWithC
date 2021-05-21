#include"LinearList.h"


typedef struct{
    SlinkList rec;
    int length;
}SLinkListType;

/**
 * @brief 算法10.1 直接插入排序
 * 
 * @param l 线性表
 */
void insertSort(SqList &l){
    for (int i=l.length-1;i>0;i--){
        if (l.elem[i]<l.elem[i-1]){
            l.elem[l.length]=l.elem[i-1];
            l.elem[i-1]=l.elem[i];
            int j=i+1;
            for (;l.elem[j]<l.elem[l.length];j++){
                l.elem[j-1]=l.elem[j];
            }
            l.elem[j-1]=l.elem[l.length];
        }
    }
}

/**
 * @brief 算法10.2 二分插入
 * 
 * @param l 线性表
 */
void bInsertSort(SqList &l){
    for (int i=1;i<l.length;i++){
        l.elem[l.length]=l.elem[i];
        int low =0,high=i-1;
        while(low<=high){
            int mid=(low+high)/2;
            if (l.elem[l.length]<l.elem[mid]){
                high=mid-1;
            }else{
                low=mid+1;
            }
        }
        for (int j=i-1;j>=high+1;j--){
            l.elem[j+1]=l.elem[j];
        }
        l.elem[high+1]=l.elem[l.length];
    }
}

/**
 * @brief 为一个静态链表的元素进行排序（按照指针访问）
 * 
 * @param l 静态链表
 */
void slInsertSort(SLinkListType &l){
    l.rec[0].data=0x3f3f3f3f;
    l.rec[0].cur=1;
    l.rec[1].cur=0;
    for (int i=2;i<=l.length;i++){
        int index=l.rec[0].cur;
        int pre=0;
        while (index!=0&&l.rec[i].data>l.rec[index].data){
            pre=index;
            index=l.rec[index].cur;
        }
        l.rec[pre].cur=i;
        l.rec[i].cur=index;
    }
}

/**
 * @brief 算法10.3 将上述的排序后的静态链表元素按照下标非递减排列（随机访问）
 * 
 * @param sl 静态链表
 */
void arrange(SLinkListType &sl){
    int p=sl.rec[0].cur;
    for (int i=1;i<sl.length;i++){
        while (p<i){
            p=sl.rec[p].cur;//正常情况下不会遇到这种情况，当p的位置的元素在交换前是下一个要插入的元素，且其在之前的操作中已经被交换位置了才会用到
        }
        int q=sl.rec[p].cur;
        if (p!=i){
            component t=sl.rec[p];
            sl.rec[p]=sl.rec[i];
            sl.rec[i]=t;
            sl.rec[i].cur=p;//记录这个位置的元素被交换到哪个位置了，防止之后要用它时找不到了。
        }
        p=q;
    }
}

/**
 * @brief 算法10.4 一趟希尔排序
 * 
 * @param l 线性表
 * @param dk 间隔
 */
void shellInsert(SqList &l,int dk){
    for (int i=l.length-dk-1;i>=0;i--){
        if (l.elem[i]>l.elem[i+dk]){
            l.elem[l.length]=l.elem[i];
            l.elem[i]=l.elem[i+dk];
            int j=i+dk;
            for (;j<l.length&&l.elem[j]<l.elem[l.length];j+=dk){
                l.elem[j-dk]=l.elem[j];
            }
            l.elem[j-dk]=l.elem[l.length];
        }
    }
}

/**
 * @brief 算法10.5 希尔排序
 * 
 * @param l 线性表
 */
void shellSort(SqList &l){
    for (int i=l.length/2;i>=1;i=ceil(log2(i))){
        shellInsert(l,i);
    }
}

int main(){
    SqList l;
    initList_Sq(l);
    for (int i=0;i<10;i++){
        listInsert_Sq(l,i,10-i);
    }
    printList_Sq(l);
    // insertSort(l);
    bInsertSort(l);
    printList_Sq(l);

    SLinkListType sl;
    sl.length=10;
    int tail=0;
    SlinkList space;
    createList_SL(sl.rec);
    initSpace_SL(space);
    for (int i=0;i<10;i++){
        insertList_SL(sl.rec,space,tail,10-i);
    }
    printList_SL(sl.rec);
    slInsertSort(sl);
    arrange(sl);
    for (int i=1;i<=sl.length;i++){
        printf("%d ",sl.rec[i].data);
    }
    printf("\n");
    SqList ll;
    initList_Sq(ll);
    for (int i=0;i<10;i++){
        listInsert_Sq(ll,i,10-i);
    }
    printList_Sq(ll);
    shellSort(ll);
    printList_Sq(ll);
    return 0;
}