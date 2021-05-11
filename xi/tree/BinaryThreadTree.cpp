#include"general.h"

/**
 * @brief 子节点的标记类型
 * 
 */
enum PointerTag {Link=1,Thread=2};

/**
 * @brief 线索化二叉树
 * 
 */
typedef struct BiThrNode{
    TElemType data;
    BiThrNode * lchild,*rchild;
    PointerTag lTag,rTag;
}BiThrNode,* BiThrTree;

/**
 * @brief 算法6.5 中序遍历线索化后的二叉树（非递归）
 * 
 * @param t 线索化二叉树的头节点
 * @param visit 访问函数
 * @return Status 返回结果
 */
Status inOrderTraverse(BiThrTree t,Status(*visit)(TElemType e)){
    BiThrTree p=t;
    p=p->lchild;//左孩子是根节点
    while (p!=t){
        while (p->lTag==Link){
            p=p->lchild;
        }
        if (!visit(p->data)){
            return ERROR;
        }
        while (p->rTag==Thread&&p->rchild!=t){//教材中忘记判断p的下一个右线索是否是头节点
            p=p->rchild;
            if (!visit(p->data)){
                return ERROR;
            }
        }
        p=p->rchild;
    }
    return OK;    
}

/**
 * @brief 算法6.7 线索化某一个节点
 * 
 * @param p 当前需要线索化的节点
 * @param pre 当前节点的前驱
 * @return Status 返回结果
 */
Status inThreading(BiThrTree p,BiThrTree &pre){
    if(p){
        inThreading(p->lchild,pre);
        if(!p->lchild){
            p->lTag=Thread;
            p->lchild=pre;
        }else{//教材上没有将这里标注
            p->lTag=Link;
        }
        if(!pre->rchild){
            pre->rTag=Thread;
            pre->rchild=p;
        }else{
            pre->rTag=Link;
        }
        pre=p;
        inThreading(p->rchild,pre);
    }
    return OK;
}

/**
 * @brief 算法6.6 中序线索化一棵二叉树
 * 
 * @param thrt 线索化后的头节点
 * @param t 二叉树的根节点
 * @return Status 返回结果
 */
Status inOrderThreading(BiThrTree &thrt,BiThrTree t){
    if(!(thrt=(BiThrTree)malloc(sizeof(BiThrNode)))){
        exit(OVERFLOW);
    }
    thrt->lTag=Link;
    thrt->rTag=Thread;
    thrt->rchild=thrt;
    if (!t){
        thrt->lchild=thrt;
    }else{
        thrt->lchild=t;
        BiThrTree pre=thrt;
        inThreading(t,pre);
        //此时pre是树最后一个访问的节点
        pre->rTag=Thread;
        pre->rchild=thrt;
        thrt->rchild=pre;
    }
    return OK;
}

/**
 * @brief 改编自算法6.4 先序遍历的顺序构造一棵二叉树
 * 
 * @param bt 二叉树的根节点
 * @return Status 返回结果
 */
Status createBiTree(BiThrTree &bt){
    int d;
    scanf("%d",&d);
    if(d==-1){
        bt=NULL;
    }else{
        if(!(bt=(BiThrTree)malloc(sizeof(BiThrNode)))){
            exit(OVERFLOW);
        }
        bt->data=d;
        createBiTree(bt->lchild);
        createBiTree(bt->rchild);
    }
    return OK;
}

int main(){
    BiThrTree bt;
    BiThrTree thrt;
    printf("按照先序遍历的顺序构造该二叉树：\n");
    createBiTree(bt);
    printf("中序线索化二叉树并打印：\n");
    inOrderThreading(thrt,bt);
    inOrderTraverse(thrt,printTElement);
    return 0;
}