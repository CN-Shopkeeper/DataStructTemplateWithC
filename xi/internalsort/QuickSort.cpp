#include"LinearList.h"

/**
 * @brief 算法10.6 一趟快速排序
 * 
 * @param l 线性表
 * @param low 下界
 * @param high 上界
 * @return int 结束位置
 */
int partition(SqList &l, int low, int high){
    l.elem[l.length]=l.elem[low];
    int key=l.elem[low];
    while (low<high){
        while(low<high&&l.elem[high]>=key){
            high--;
        }
        l.elem[low]=l.elem[high];
        while (low<high&&l.elem[low]<=key){
            low++;
        }
        l.elem[high]=l.elem[low];
    }
    l.elem[low]=key;
    return low;
}

/**
 * @brief 算法10.7 快速排序
 * 
 * @param l 线性表
 * @param low 下界
 * @param high 上界
 */
void quickSort(SqList &l,int low,int high){
    if (low<high){
        int pos=partition(l,low,high);
        quickSort(l,low,pos-1);
        quickSort(l,pos+1,high);
    }
}

int main(){
    SqList l;
    initList_Sq(l);
    for (int i=0;i<10;i++){
        listInsert_Sq(l,i,10-i);
    }
    printList_Sq(l);
    quickSort(l,0,l.length-1);
    printList_Sq(l);
    return 0;
}