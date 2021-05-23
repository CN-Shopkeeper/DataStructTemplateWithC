#include"LinearList.h"

/**
 * @brief 算法10.12 将数组进行归并（和书上不一样）
 * 
 * @param s 线性表
 * @param x 起始位置
 * @param y 中间位置
 * @param z 结束位置
 */
void merge(SqList &s,int x,int y,int z){
    int i=x,j=y+1,index=0;
    int *t=new int[z-x+1];
    for (;i<=y&&j<=z;){
        if (s.elem[i]<=s.elem[j]){//这里需要时小于号
            t[index++]=s.elem[i++];
        }else{
            t[index++]=s.elem[j++];
        }
    }
    if (i<=y){
        for (;i<=y;){
            t[index++]=s.elem[i++];
        }
    }
    if (j<=z){
        for (;j<=z;){
            t[index++]=s.elem[j++];
        }
    }
    for (int k=0;k<z-x+1;k++){
        s.elem[x+k]=t[k];
    }
}

/**
 * @brief 算法10.13 归并排序
 * 
 * @param sr 线性表
 * @param s 起始位置
 * @param t 结束位置
 */
void mSort(SqList &sr,int s,int t){
    if (s!=t){
        int mid=(s+t)/2;
        mSort(sr,s,mid);
        mSort(sr,mid+1,t);
        merge(sr,s,mid,t);
    }
}

int main(){
    SqList s,t;
    initList_Sq(s);
    for (int i=0;i<10;i++){
        listInsert_Sq(s,i,10-i);
    }
    printList_Sq(s);
    mSort(s,0,s.length-1);
    printList_Sq(s);
}