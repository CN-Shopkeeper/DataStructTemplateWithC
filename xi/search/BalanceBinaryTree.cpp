#include"general.h"

typedef struct BSTNode{
    ElemType data;
    int bf;
    BSTNode * lchild,*rchild;
}BSTNode,*BSTree;

/**
 * @brief 递归先序遍历二叉树
 * 
 * @param t 需要遍历的二叉树
 * @param visit 对遍历节点操作的函数
 * @return Status 返回结果
 */
Status preOrderTraverse(BSTree t,Status(*visit)(TElemType e)){
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
 * @brief 算法9.9 对二叉树进行右旋处理
 * 
 * @param p 需要右旋的二叉树根节点
 */
void r_route(BSTree &p){
    BSTree lc=p->lchild;
    p->lchild=lc->rchild;
    lc->rchild=p;
    p=lc;
}

/**
 * @brief 算法9.10 对二叉树进行左旋处理
 * 
 * @param p 需要左旋的二叉树根节点
 */
void l_route(BSTree &p){
    BSTree rc=p->rchild;
    p->rchild=rc->lchild;
    rc->lchild=p;
    p=rc;
}

/**
 * @brief 算法9.12 左平衡旋转
 * 
 * @param t 二叉树
 */
void leftBalance(BSTree &t){
    BSTree lc=t->lchild;
    BSTree rd=lc->rchild;
    switch (lc->bf){
        case LH:
            /**
             * @brief 单右旋转
             * 
             */
            t->bf=lc->bf=EH;
            r_route(t);
            break;
        case RH:
            /**
             * @brief 先左后右双向旋转
             * lc的右子树要高一点
             * rd变成根节点，rd左子树为lc，右子树为t
             * lc左子树为lc->lchild，lc右子树为rd->lchild
             * t左子树为lc->rchild，右子树为t->rchild
             * 
             */
            switch (rd->bf){
                case LH:
                    t->bf=RH;//rd的右子树变成t的左子树；因为LH所以rd的右子树要矮一点，即t的左子树要矮一点
                    lc->bf=EH;//rd的左子树变成lc的右子树，即lc的左子树高了一点，能和右子树相同
                    break;
                case EH:
                    t->bf=lc->bf=EH;//rd的右子树和左子树同高，rd的右子树比LH中的高一点，即t的左子树也高一点，能够和t的右子树同高
                    break;
                case RH:
                    t->bf=EH;
                    lc->bf=LH;//和LH的情况相反
                    break;
                default:
                    break;
            }
            rd->bf=EH;
            l_route(t->lchild);
            r_route(t);
            break;
        default:
            //不会出现EH的情况
            break;
    }
}

/**
 * @brief 右平衡旋转
 * 
 * @param t 二叉树
 */
void rightBalance(BSTree &t){
    BSTree rc=t->rchild;
    BSTree ld=rc->lchild;
    switch (rc->bf){
        case RH:
            /**
             * @brief 单左旋转
             * 
             */
            t->bf=rc->bf=EH;
            l_route(t);
            break;
        case LH:
            /**
             * @brief 先右后左双向旋转
             * rc的左子树要高一点
             * ld变成根节点，ld左子树为t，右子树为rc
             * t左子树为t->lchild，右子树为ld->lchild
             * rc左子树为ld->rchild，右子树为rc->rchild
             * 
             */
            switch (ld->bf){
                case LH:
                    rc->bf=RH;
                    t->bf=EH;
                    break;
                case EH:
                    t->bf=rc->bf=EH;
                    break;
                case RH:
                    rc->bf=EH;
                    t->bf=LH;
                    break;
                default:
                    break;
            }
            ld->bf=EH;
            r_route(t->rchild);
            l_route(t);
            break;
        default:
            //不会出现EH的情况
            break;
    }
}

/**
 * @brief 算法9.11 向二叉树中插入一个节点并保持平衡
 * 
 * @param t 二叉树
 * @param e 插入的元素
 * @param taller 是否在插入后变高
 * @return true 插入成功
 * @return false 插入失败
 */
bool insertAVL(BSTree &t,ElemType e,bool &taller){
    if (!t){
        t=(BSTree)malloc(sizeof(BSTNode));
        t->data=e;
        t->lchild=t->rchild=NULL;
        t->bf=EH;
        taller=true;
    }else{
        if (EQ(e,t->data)){
            taller=false;
            return false;
        }
        if (LT(e,t->data)){
            if (!insertAVL(t->lchild,e,taller)){
                return false;
            }
            //在左边插入后这棵树变高了
            if (taller){
                //递归调用保证只有最近的一层会做平衡
                switch (t->bf){
                    case LH:
                        //在左边插入且左边高
                        leftBalance(t);
                        //平衡后树高不变
                        taller=false;
                        break;
                    case EH:
                        t->bf=LH;
                        taller=true;
                        break;
                    case RH:
                        t->bf=EH;
                        taller=false;
                        break;
                    default:
                        break;
                }
            }
        }else{
            if (!insertAVL(t->rchild,e,taller)){
                return false;
            }
            if (taller){
                switch (t->bf){
                    case LH:
                        t->bf=EH;
                        taller=false;
                        break;
                    case EH:
                        t->bf=RH;
                        taller=true;
                        break;
                    case RH:
                        rightBalance(t);
                        taller=false;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return true;
}

int main(){
    BSTree t=NULL;
    for (int i=0;i<10;i++){
        bool taller=false;
        printf("插入%d\n",i);
        insertAVL(t,i,taller);
    }
    preOrderTraverse(t,printTElement);
    /*
        结果为：
                        3
                1             7
             0    2       5     8
                        4   6     9
    */
    return 0;
}