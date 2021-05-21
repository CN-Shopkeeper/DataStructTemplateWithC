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
    int c;
    cout<<"enter tnode:\n";
    cin>>c;
    if(c==0)t=NULL;//非常不规范！！！！！！！！！！！！
    else{
        t=(BiTree)malloc(sizeof(BiTNode));
        if(!t)exit(OVERFLOW);
        t->data=c;
        createBiTree(t->lchild);
        createBiTree(t->rchild);
    }
    return OK;
}

//递归方式
//先序遍历二叉树 根左右
Status preOrderTraverse(BiTree t,Status(*visit)(TElemType e)){
    if(t){
        if(!visit(t->data))return ERROR;
        preOrderTraverse(t->lchild,visit);
        preOrderTraverse(t->rchild,visit);
    }
    return OK;
}
//非递归方式
Status preOrderTraverseN(BiTree t,Status(*visit)(TElemType e)){
    stack<BiTree> s;
    if(t==NULL)return ERROR;
    s.push(t);
    while(!s.empty()){
        BiTree now=s.top();
        s.pop();
        if(now){
            if(!visit(now->data))return ERROR;
            if(now->rchild!=NULL)s.push(now->rchild);
            if(now->lchild!=NULL)s.push(now->lchild);
        }
    }
    return OK;
}

//中序遍历二叉树 左根右
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
//非递归方式
Status postOrderTraverseN(BiTree t,Status(*visit)(TElemType e)){
    stack<BiTree> s;
    BiTree p;
    if(t==NULL)return ERROR;
    s.push(t);
    while(!s.empty()){
        p=s.top();
        while(p){
            s.push(p->lchild);
            p=p->lchild;
        }
        s.pop();//弹出多余的NULL
        p=s.top();
        if(p->rchild)s.push(p->rchild);
        else{
            if(!visit(p->data))return ERROR;
            s.pop();//处理完就弹出
        }
        return OK;
    }
}

//层序遍历二叉树
Status levelOrderTraverse(BiTree t,Status(*visit)(TElemType e)){
    //借助队列
    queue<BiTree> q;
    BiTree p;
    if(t==NULL)return ERROR;
    q.push(t);
    while(!q.empty()){
        p=q.front();
        if(p->lchild)q.push(p->lchild);
        if(p->rchild)q.push(p->rchild);
        if(!visit(p->data))return ERROR;
        q.pop();
    }
    return OK;
}

//判断两棵二叉树是否相等
//递归方式
Status equalTree(BiTree t1,BiTree t2){
    if(t1==NULL&&t2==NULL)return OK;
    else if(t1==NULL ||t2==NULL)return ERROR;
    else{
        if(t1->data==t2->data){
            if( equalTree(t1->lchild,t2->lchild)&&equalTree(t1->rchild,t2->rchild))return OK;
            else return ERROR;
        }
    }
    return ERROR;
}
//非递归方式
Status equalTreeN1(BiTree t1,BiTree t2){
    if(t1==NULL&&t2==NULL)return OK;
    else if(t1==NULL ||t2==NULL)return ERROR;
    else{
        queue<BiTree> q1,q2;
        BiTree n1,n2;
        q1.push(t1);
        q2.push(t2);
        while((!q1.empty())&&(!q2.empty())){
            n1=q1.front();n2=q2.front();
            if(n1->data!=n2->data)return ERROR;
            if(n1->lchild)q1.push(n1->lchild);if(n1->rchild)q1.push(n1->rchild);
            if(n2->lchild)q2.push(n2->lchild);if(n2->rchild)q2.push(n2->rchild);
            q1.pop();q2.pop();
        }
        return OK;
    }
    return ERROR;
}
//非递归方式
//借助visit函数，任意序列遍历两个二叉树，将结点收集到一个数组里，再访问数组进行判定

//求二叉树的深度
//递归
int depth(BiTree t){
    if(t){
        return depth(t->lchild)>depth(t->rchild)?depth(t->lchild)+1:depth(t->rchild)+1;
    }else return 0;
}

//求二叉树中位于先序序列的第k个结点的值:    根左右
//非递归
BiTree countK(BiTree t,int &k){
    stack<BiTree> s;
    BiTree p;
    int count = 0;
    if(!t)return NULL;
    s.push(t);
    while(!s.empty()){
        p=s.top();
        s.pop();
        count++;
        if(count==k)return p;
        if(p->rchild)s.push(p->rchild);
        if(p->lchild)s.push(p->lchild);
    }
    return NULL;
}


//删除二叉树所有以x为根的子树且释放空间
void delSubTree(BiTree &t){
    if(t){
        delSubTree(t->lchild);
        delSubTree(t->rchild);
        free(t);
    }
}

void delTree(BiTree &t,TElemType x){
    if(t){
        if(t->data==x){
        delSubTree(t);
        t=NULL;//重要！！
        }
        else{
            if(t->lchild)delTree(t->lchild,x);
            if(t->rchild)delTree(t->rchild,x);
        }
    }
}

//test
int main(){
    BiTree t;
    createBiTree(t);
    int k=3;
    BiTree p=countK(t,k);
    cout<<"countK k=3:\t"<<p->data<<endl;
    return 0;
}