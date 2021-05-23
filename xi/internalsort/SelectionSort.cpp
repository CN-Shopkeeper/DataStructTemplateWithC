#include "LinearList.h"

typedef SqList HeapType;

/**
 * @brief 算法10.9 选择排序
 * 
 * @param l 线性表
 */
void selectSort(SqList &l){
    for (int i=0;i<l.length-1;i++){
        int min=l.elem[i];
        int pos;
        for (int j=i+1;j<l.length;j++){
            if (min>l.elem[j]){
                min=l.elem[j];
                pos=j;
            }
        }
        int t=l.elem[i];
        l.elem[i]=l.elem[pos];
        l.elem[pos]=t;
    }
}

/**
 * @brief 算法10.10 将除了s之外，别的都符合大顶堆的定义的线性表调整为大顶堆
 * 从s开始向下，找到s这个元素应该处于的位置（保证大顶堆）
 * 
 * @param h 线性表（堆）
 * @param s 开始位置
 * @param m 结束位置
 */
void heapAdjust(HeapType &h,int s,int m){
    int rc=h.elem[s];
    for (int i=2*s;i<=m;i=i*2){
        if (i<m&&h.elem[i]<h.elem[i+1]){
            i++;//右孩子更大
        }
        if (rc>=h.elem[i]){
            break;//如果两个孩子都小于rc，则过程结束
        }
        h.elem[s]=h.elem[i];//否则大孩子变成父节点，并从大孩子那里继续选择
        s=i;
    }
    h.elem[s]=rc;
}

/**
 * @brief 算法10.11 堆排序
 * 
 * @param h 线性表（堆）
 */
void heapSort(HeapType &h){
    //这个循环是为了将线性表构造为大顶堆
    //意思是从最后一个有孩子的节点开始构造大顶堆（因为heapAdjust必须保证除了头节点以外其它必须符合大顶堆要求）
    for (int i=h.length/2;i>=0;i--){
        heapAdjust(h,i,h.length-1);
    }
    //这个循环是将每一次大顶堆的头部，逆序放到线性表中，这样线性表就是升序
    for (int i=h.length-1;i>0;i--){
        int t=h.elem[i];
        h.elem[i]=h.elem[0];
        h.elem[0]=t;
        heapAdjust(h,0,i-1);
    }
}

int main(){
    SqList l;
    HeapType h;
    initList_Sq(l);
    initList_Sq(h);
    for (int i=0;i<=10;i++){
        listInsert_Sq(l,i,10-i);
        listInsert_Sq(h,i,10-i);
    }
    selectSort(l);
    heapSort(h);
    printList_Sq(l);
    printList_Sq(h);
    return 0;
}