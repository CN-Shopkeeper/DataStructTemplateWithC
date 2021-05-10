#include"general.h"
#include<stack>
using namespace std;

/**
 * @brief 二叉树
 * 
 */
typedef struct BiTNode{
    TElemType data;
    BiTNode * lchild,*rchild;
}BiTNode,*BiTree;


/**
 * @brief 算法6.1 递归先序遍历二叉树
 * 
 * @param t 需要遍历的二叉树
 * @param visit 对遍历节点操作的函数
 * @return Status 返回结果
 */
Status preOrderTraverse(BiTree t,Status(*visit)(TElemType e)){
    if (t){
        if(visit(t->data)){
            if(preOrderTraverse(t->lchild,visit)){
                if(preOrderTraverse(t->rchild,visit)){
                    return OK;
                }
            }
        }
        return ERROR;
    }else{
        return OK;
    }
}

/**
 * @brief 算法6.2 非递归中序遍历二叉树
 * 
 * @param t 需要遍历的二叉树
 * @param visit 对遍历节点操作的函数
 * @return Status 返回结果
 */
Status inOrderTraverse_1(BiTree t,Status(*visit)(TElemType e)){
    printf("\n非递归中序遍历二叉树\n");
    stack<BiTree> s;//为了方便实现，用stl的stack来实现栈
    BiTree p;
    while (!s.empty()){
        s.pop();
    }
    s.push(t);
    while(!s.empty()){
        while (p=s.top()){
            s.push(p->lchild);
        }
        s.pop();
        if(!s.empty()){
            p=s.top();
            s.pop();
            if(!visit(p->data)){
                return ERROR;
            }
            s.push(p->rchild);
        }
    }
    return OK;
}

/**
 * @brief 算法6.3 非递中序归遍历二叉树
 * 
 * @param t 需要遍历的二叉树
 * @param visit 对遍历节点操作的函数
 * @return Status 返回结果
 */
Status inOrderTraverse_2(BiTree t,Status(*visit)(TElemType e)){
    printf("\n非递中序归遍历二叉树:\n");
    stack<BiTree> s;//为了方便实现，用stl的stack来实现栈
    BiTree p=t;
    while (p||!s.empty()){
        if (p){
            s.push(p);
            p=p->lchild;
        }else{
            p=s.top();
            s.pop();
            if (!visit(p->data)){
                return ERROR;
            }
            p=p->rchild;
        }
    }
    return OK;
}

/**
 * @brief 非递归后序遍历二叉树
 * 
 * @param t 需要遍历的二叉树
 * @param visit 对遍历节点操作的函数
 * @return Status 返回结果
 */
Status postOrderTraverse(BiTree t,Status(*visit)(TElemType e)){
    printf("\n非递归后序遍历二叉树:\n");
    stack<BiTree> src;
    stack<TElemType> res;
    src.push(t);
    while(!src.empty()){
        BiTree p=src.top();
        src.pop();
        res.push(p->data);
        if(p->lchild){
            src.push(p->lchild);
        }
        if(p->rchild){
            src.push(p->rchild);
        }
    }
    while (!res.empty()){
        printElement(res.top());
        res.pop();
    }
    return OK;
}

/**
 * @brief 算法6.4 先序遍历的顺序构造一棵二叉树
 * 
 * @param bt 需要构造的二叉树的根节点索引
 * @return Status 返回结果
 */
Status createBiTree(BiTree &bt){
    int d;
    scanf("%d",&d);
    if(d==-1){
        bt=NULL;
    }else{
        if(!(bt=(BiTree)malloc(sizeof(BiTNode)))){
            exit(OVERFLOW);
        }
        bt->data=d;
        createBiTree(bt->lchild);
        createBiTree(bt->rchild);
    }
    return OK;
}

int main(){
    BiTree bt;
    printf("按照先序遍历的顺序构造该二叉树：\n");
    createBiTree(bt);
    printf("\n先序递归遍历：\n");
    preOrderTraverse(bt,printElement);
    inOrderTraverse_1(bt,printElement);
    inOrderTraverse_2(bt,printElement);
    postOrderTraverse(bt,printElement);
    return 0;
}