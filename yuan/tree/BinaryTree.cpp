// @Time    :   2021/05/21 15:16:48
// @FileName:   BinaryTree.cpp
// @Author  :   yuan
// @Software:   VSCode

#include"general.h"

typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

//构造二叉链表表示的二叉树
Status createBiTree(BiTree &t){
    //先序创建，t指向根结点
    char c;
    cout<<"enter tnode:\n";
    cin>>c;
    if(c==0)t=NULL;
    else{
        t=(BiTree)malloc(sizeof(BiTNode));
        if(!t)exit(OVERFLOW);
        createBiTree(t->lchild);
        createBiTree(t->rchild);
    }
    return OK;
}

//递归方式
//先序遍历二叉树
Status preOrderTraverse(BiTree t,Status(*visit)(TElemType e)){
    if(t){
        if(!visit(t->data))return ERROR;
        preOrderTraverse(t->lchild,visit);
        preOrderTraverse(t->rchild,visit);
    }
    return OK;
}
//非递归方式
Status preOrderTraverseN(BiTree,Status(*visit)(TElemType e)){

}

//中序遍历二叉树
//递归方式
Status inOrderTraverse(BiTree t,Status(*visit)(TElemType e)){
    if(t){
        inOrderTraverse(t->lchild,visit);
        if(!visit(t->data))return ERROR;
        inOrderTraverse(t->rchild,visit);
    }
    return OK;
}
//-------------------------------------------------非递归方式----------------------------------------------------
Status inOrderTraverseN1(BiTree t,Status(*visit)(TElemType e)){
    stack<BiTree> s;
    s.push(t);
    while(!s.empty()){
        BiTree p;
        while((p=s.top())!=NULL)s.push(p->lchild);
        s.pop();//把NULL弹出栈
        if(!s.empty()){
            p=s.top();
            s.pop();
            if(!visit(p->data))return ERROR;
            s.push(p->rchild);
        }
    }
    return OK;
}
//-------------------------------------------------非递归方式----------------------------------------------------
Status inOrderTraverseN2(BiTree t,Status(*visit)(TElemType e)){
    stack<BiTree> s;
    BiTree p=t;
    while(p||!s.empty()){
        if(p){
            s.push(p);
            p=p->lchild;
        }else{
            p=s.top();
            if(!visit(p->data))return ERROR;
            p=p->rchild;
        }
    }
    return OK;
}

//后序遍历二叉树
Status postOrderTraverse(BiTree t,Status(*visit)(TElemType e)){
    if(t){
        postOrderTraverse(t->lchild,visit);
        postOrderTraverse(t->rchild,visit);
        if(!visit(t->data))return ERROR;
    }
    return OK;
}

//层序遍历二叉树
Status levelOrderTraverse(BiTree t,Status(*visit)(TElemType e)){
    //借助队列？

}

//判断两棵二叉树是否相等
Status equal(BiTree t1,BiTree t2){

}

//求二叉树的深度
int depth(BiTree t){

}

//求二叉树中位于先序序列的第k个结点的值
BiTree countK(BiTree t,int &k){

}
Status locK(BiTree t,int k,TElemType &e){

}

//删除二叉树所有以x为根的子树且释放空间
void delSubTree(BiTree &t){

}

void delTree(BiTree &t,TElemType x){

}