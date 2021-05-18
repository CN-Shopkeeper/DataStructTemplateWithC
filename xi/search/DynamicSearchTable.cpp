#include"BinaryTree.h"

/**
 * @brief 算法9.5 在二叉排序树中查找关键字
 * 
 * @param t 二叉排序树的根节点
 * @param key 关键字
 * @param f 当前树的父节点
 * @param p 返回的指针引用
 * @return true 查找成功
 * @return false 查找失败
 */
bool searchBST(BiTree t,KeyType key,BiTree f,BiTree &p){
    if (!t){//查找不成功
        p=f;
        return false;
    }else if(EQ(key,t->data)){
        p=t;
        return true;
    }else if (LT(key,t->data)){
        return searchBST(t->lchild,key,t,p);
    }else{
        return searchBST(t->rchild,key,t,p);
    }
}

/**
 * @brief 算法9.6 当查找失败时插入元素
 * 
 * @param t 二叉排序树
 * @param k 关键字
 * @return true 插入成功
 * @return false 插入失败
 */
bool insertBST(BiTree &t,KeyType k){
    BiTree p;
    if (!searchBST(t,k,NULL,p)){
        BiTree s=(BiTree)malloc(sizeof(BiTNode));
        s->data=k;
        s->lchild=s->rchild=NULL;
        if (!p){
            t=s;
        }else{
            if (k<p->data){
                p->lchild=s;
            }else{
                p->rchild=s;
            }
        }
        return true;
    }else{
        return false;
    }
}

/**
 * @brief 算法9.8 删除节点
 * 
 * @param p 要删除的节点（不需要引用）
 * @param f 该节点的父亲
 * @return true 删除成功
 * @return false 删除失败
 */
bool _delete(BiTree p,BiTree f){
    if (!p->rchild){
        if (f->lchild==p){
            f->lchild=p->lchild;
        }else{
            f->rchild=p->lchild;
        }
        free(p);
    }else if(!p->lchild){
        if (f->lchild==p){
            f->lchild=p->rchild;
        }else{
            f->rchild=p->rchild;
        }
        free(p);
    }else{
        //找p的前驱
        BiTree q=p->lchild;
        BiTree qf=p;
        while (q->rchild){
            qf=p;
            q=q->rchild;
        }
        p->data=q->data;
        if (qf!=p){
            qf->rchild=q->lchild;
        }else{
            p->lchild=q->rchild;
        }
        free(p);
    }
    return true;
}

/**
 * @brief 算法9.7 删除树中某一节点
 * 
 * @param t 当前根节点
 * @param f 根节点的父亲
 * @param k 要删除的元素
 * @return true 删除成功
 * @return false 删除失败
 */
bool deleteBST(BiTree &t,BiTree f,KeyType k){
    if (!t){
        return false;
    }else{
        if (EQ(t->data,k)){
            return _delete(t,f);
        }else if (LT(k,t->data)){
            return deleteBST(t->lchild,t,k);
        }else{
            return deleteBST(t->rchild,t,k);
        }
    }
}

int main(){
    BiTree t=NULL;//一定要初始化为NULL
    for (int i=1;i<=10;i++){
        if (insertBST(t,i)){
            printf("插入了%d\n",i);
        }else{
            printf("插入失败\n");
        }
    }
    if (insertBST(t,3)){
        printf("插入了3\n");
    }else{
        printf("插入3失败\n");
    }
    if (deleteBST(t,NULL,3)){
        printf("删除了3\n");
    }else{
        printf("删除3失败\n");
    }
    if (deleteBST(t,NULL,3)){
        printf("删除了3\n");
    }else{
        printf("删除3失败\n");
    }
    return 0;
}