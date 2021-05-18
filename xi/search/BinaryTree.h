#include"general.h"
/**
 * @brief 二叉树
 * 
 */
typedef struct BiTNode{
    KeyType data;
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
 * @brief 树中的visit函数
 * 
 * @param e 树中要访问的元素
 * @return Status 操作结果
 */
Status print(TElemType e){
    printf("%c ",e);
    return OK;
}
