#include"LinearList.h"

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


int main(){
    SqList l;
    initList_Sq(l);
    for (int i=0;i<10;i++){
        listInsert_Sq(l,i,10-i);
    }
    printList_Sq(l);
    insertSort(l);
    printList_Sq(l);
    return 0;
}