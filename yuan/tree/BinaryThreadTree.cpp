// @Time    :   2021/05/24 22:01:55
// @FileName:   BinaryThreadTree.cpp
// @Author  :   yuan
// @Software:   VSCode

#include"general.h"

/**
 *
 * 线索二叉树
 * 不同遍历顺序下前驱后继不同
 * 数据结构
 * lchild   LTag    data    RTag    rchild
 * LTag 0:lchild指示左孩子  1:lchild指示前驱
 * RTag 0:rchild指示右孩子  1:rchild指示后继
 * 
 * 来源：利用n+1个空链域存储前驱后继信息
 */

typedef enum PointerTag{Link,Thread};   //link==0:指针 thread==1:线索
typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode *lchild,*rchild;
    PointerTag ltag,rtag;
}BiThrNode,*BiThrTree;

Status inOrderTraverse_Thr(BiThrTree t,Status(*visit)(TElemType)){
    //中序遍历二叉线索树t的非递归算法，对每个元素调用visit
    BiThrTree p=t->lchild;//左孩子是根节点
    while(p!=t){
        while(p->ltag==Link)p=p->lchild;//最最左孩子
        if(!visit(p->data))return ERROR;
        while(p->rtag==Thread&&p->rchild!=t){
            p=p->rchild;
            if(!visit(p->data))return ERROR;
        }
        p=p->rchild;
    }//有前驱后继，故不需要使用栈
    return OK;
}



//将二叉树t中序线索化，thrt指向头结点
//实质是在遍历过程中修改空指针

void inThreading(BiThrTree p,BiThrTree &pre){//pre前面要加&
    if(p){
        inThreading(p->lchild,pre);
        if(!p->lchild){//前驱线索
            p->ltag=Thread;
            p->lchild=pre;
        }else{
            p->ltag=Link;
        }
        if(!pre->rchild){//后继线索
            pre->rtag=Thread;
            pre->rchild=p;
        }else{
            pre->rtag=Link;
        }
        pre=p;
        inThreading(p->rchild,pre);
    }
}
Status inOrderThreading(BiThrTree &thrt,BiThrTree t){
    if(!(thrt=(BiThrTree)malloc(sizeof(BiThrNode))))exit(OVERFLOW);
    thrt->ltag = Link;
    thrt->rtag = Thread;
    thrt->rchild=thrt;
    if(!t)thrt->lchild=thrt;//若二叉树空，则左指针回指
    else{
        thrt->lchild=t;
        BiThrTree pre = thrt;
        inThreading(t,pre);
        //pre已经更新为树中最后一个访问的结点
        pre->rchild=thrt;
        pre->rtag=Thread;
        thrt->rchild=pre;
    }
    return OK;
}

//先序构造一棵二叉树
Status createBiThrTree(BiThrTree &t){
    int n;
    cin>>n;
    if(n==-1)t=NULL;
    else{
        if(!(t=(BiThrTree)malloc(sizeof(BiThrNode))))exit(OVERFLOW);
        t->data=n;
        createBiThrTree(t->lchild);
        createBiThrTree(t->rchild);
    }
    return OK;
}

int main(){
    BiThrTree t,thrt;
    cout<<"先序创建二叉树(-1表示NULL)：\n";
    createBiThrTree(t);
    cout<<"中序线索化结果：\n";
    inOrderThreading(thrt,t);//中序线索化
    inOrderTraverse_Thr(thrt,printTElement);
    return 0;
}