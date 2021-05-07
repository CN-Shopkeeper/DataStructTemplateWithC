#include"sqlist.cpp"

int main(){
    SqList a,b;
    initList_Sq(a);
    initList_Sq(b);
    for (int i = 0; i < 10; i++)
    {
        listInsert_Sq(a,i,4*i);
        listInsert_Sq(b,i,10+3*i);
    }
    printList_Sq(a);
    printList_Sq(b);
    // ElemType t=99;
    // listInsert_Sq(a,10,t);
    // listDelete_Sq(b,10,t);
    // printList_Sq(a);
    // printList_Sq(b);
    // union_Sq(a,b);
    // printList_Sq(a);
    SqList c;
    mergeList_Sq(a,b,c);
    printList_Sq(c);
    return 0;
}