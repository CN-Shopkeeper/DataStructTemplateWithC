/**
 * @file BalanceTree.cpp
 * @author Shopkeeper
 * @brief B-树，简单实现了一下，但是没有验证写的对不对（太复杂了，脑壳疼）
 * @version 0.1
 * @date 2021-05-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include"general.h"

#define m 3
typedef struct BTNode{
    int keynum;
    struct BTNode *parent;
    KeyType key[m+1];//0不使用，m号用于插入时的冗余
    struct BTNode *ptr[m+1];//m用于插入时的冗余
    // Record *recptr[m+1];
}BTNode,*BTree;

typedef struct Result{
    BTNode *pt;//找到的节点
    int i;//在节点中的关键字
    int tag;//查找结果
    Result(BTNode *pt,int i,int tag):pt(pt),i(i),tag(tag){}
}Result;

/**
 * @brief 从p中寻找i。如果i<=p.keynum&&k==p.key[i]，则查找到关键字；否则i是下一层的儿子节点（和书上不同）
 * 
 * @param p 
 * @param k 
 * @return int 
 */
int search(BTree p,KeyType k){
    int i=1;
    for (;i<=p->keynum;i++){
        if (p->key[i]>k){
            return i-1;//儿子指针
        }else if(p->key[i]==k){
            return i;
        }
    }
    return i;
}

Result searchBTree(BTree t,KeyType k){
    BTree p=t;
    BTree q=NULL;
    bool found=false;
    int i=0;
    while (p&&!found){
        i=search(p,k);
        if (i>0&&p->key[i]==k){
            found=true;
        }else{
            q=p;
            p=p->ptr[i];
        }
    }
    if (found){
        return Result(p,i,1);
    }else{
        return Result(q,i,0);
    }
}

void insert(BTree &t,int i,KeyType x,BTree ap){
    for (int j=t->keynum;j>i;j--){
        t->key[j+1]=t->key[j];
        t->ptr[j+1]=t->ptr[j];
    }
    t->key[i+1]=x;
    t->ptr[i+1]=ap;
    t->keynum++;
}

void split(BTree q,int s,BTree &ap){
    //每次都得新生成一个ap
    ap=(BTree)malloc(sizeof(BTNode));
    for (int i=s+1;i<=m;i++){
        ap->key[i-s]=q->key[i];
    }
    for (int i=s;i<=m;i++){
        ap->ptr[i-s]=q->ptr[i];
    }
    q->keynum=s;
    ap->keynum=m-s;
}

/**
 * @brief 
 * 
 * @param t 
 * @param k 
 * @param q 
 * @param i 应该是searchBTree返回结果中的i
 * @return Status 
 */
Status insertBTree(BTree &t,KeyType k,BTree q,int i){
    KeyType x=k;
    BTree ap=NULL;
    bool finished=false;
    while(q&&!finished){
        insert(q,i,x,ap);
        if (q->keynum<m){
            finished=true;
        }else{
            int s=ceil(m/2);
            split(q,s,ap);
            x=q->key[s];//ap理应在q的右边，即如果要在p的双亲插入x的位置
            q=q->parent;
            if (q){
                i=search(q,x);
            }
        }
    }
    if (!finished){
        BTree nt=(BTree)malloc(sizeof(BTNode));
        nt->keynum=1;
        nt->key[1]=x;
        nt->ptr[0]=t;
        nt->ptr[1]=ap;
        t=nt;
    }
    return OK;
}


Status deleteBTree(BTree &t,KeyType k,BTree q,int i){
    if (q->ptr[0]){//如果不是最下层，找到右边子树的最小节点并替换之
        BTree p=q->ptr[i];
        BTree fp=q;
        while (p){
            fp=p;
            p=p->ptr[0];
        }
        q->key[i]=fp->key[1];
        return deleteBTree(t,fp->key[1],fp,1);//删除这个被替换的节点
    }else{
        if (q->keynum>=ceil(m/2)||q->parent==NULL){//如果是根节点或者关键字数目不小于ceil(m/2)
            for (int j=i;j<q->keynum;j++){
                q->key[j]=q->key[j+1];
                q->ptr[j]=q->ptr[j+1];//ptr可以不修改，因为都是null
            }
            q->keynum--;
            return OK;
        }else { //q->keynum==ceil(m/2)-1
            int k=0;//k为q在父节点中的位置
            BTree fq=q->parent;
            for (;k<=fq->keynum;k++){
                if (fq->ptr[k]==q){
                    break;
                }
            }
            if (k>0||k<fq->keynum){//此条件为真，肯定会有兄弟
                if (k>0&&fq->ptr[k-1]->keynum>=ceil(m/2)){//左兄弟有多余节点
                    BTree ls=fq->ptr[k-1];
                    int lskey=ls->key[ls->keynum];//需要上移的关键字节点
                    ls->keynum--;
                    int fqkey=fq->key[k];//需要下移的关键字节点
                    fq->key[k]=lskey;
                    //将fqkey插入到q中，fqkey肯定小于所有的q->key，插入到下标1中
                    for (int j=i;j>1;j--){
                        q->key[j]=q->key[j-1];
                    }
                    q->key[1]=fqkey;
                    return OK;
                }else if (k<fq->keynum&&fq->ptr[k+1]->keynum>=ceil(m/2)){//右兄弟有多余节点
                    //同上
                    BTree rs=fq->ptr[k+1];
                    int rskey=rs->key[1];
                    for (int j=1;j<rs->keynum;j++){
                        rs->key[j]=rs->key[j+1];
                    }
                    rs->keynum--;
                    int fqkey=fq->key[k+1];
                    fq->key[k+1]=rskey;
                    for (int j=i;j<q->keynum;j++){
                        q->key[j]=q->key[j+1];
                    }
                    q->key[q->keynum]=fqkey;
                    return OK;
                }else{//左右兄弟都没有空余节点
                    bool finished=false;
                    while (q&&finished){//当处理完成或者q已经是根节点时
                        if (k>0){//有左兄弟
                            //先将父节点的元素插入到自己中，再把自己合并到左兄弟中
                            int fqkey=fq->key[k];
                            //删除这个父节点元素
                            for (int j=k;j<fq->keynum;j++){
                                fq->key[j]=fq->key[j+1];
                                fq->ptr[j]=fq->ptr[j+1];
                            }
                            fq->keynum--;
                            if (fq->keynum>=ceil(m/2)-1){
                                finished=true;
                            }
                            //将父节点元素插入到q中
                            for (int j=i;j>1;j--){
                                q->key[j]=q->key[j-1];
                            }
                            q->key[1]=fqkey;
                            //合并到左兄弟中
                            BTree ls=fq->ptr[k-1];
                            for (int j=ls->keynum+1;j<=ls->keynum+q->keynum;j++){
                                ls->key[j]=q->key[j-ls->keynum];
                                ls->ptr[j]=NULL;
                            }
                            ls->keynum=ls->keynum+q->keynum;
                            free(q);
                        }else{//有右兄弟
                            //同上
                            int fqkey=fq->key[k+1];
                            for (int j=k+1;j<fq->keynum;j++){
                                fq->key[j]=fq->key[j+1];
                                fq->ptr[j]=fq->ptr[j+1];
                            }
                            fq->keynum--;
                            if (fq->keynum>=ceil(m/2)-1){
                                finished=true;
                            }
                            for (int j=i;j<q->keynum;j++){
                                q->key[j]=q->key[j+1];
                            }
                            q->key[q->keynum]=fqkey;
                            BTree rs=fq->ptr[k+1];
                            //这里可以将右兄弟合并到q，再将q赋值给有兄弟
                            for (int j=q->keynum+1;j<=rs->keynum+q->keynum;j++){
                                q->key[j]=rs->key[j-q->keynum];
                                q->ptr[j]=NULL;
                            }
                            q->keynum=rs->keynum+q->keynum;
                            free(rs);
                            fq->ptr[k+1]=q;
                        }
                        q=fq;
                        fq=fq->parent;
                    }
                    return OK;
                }
            }else{
                return ERROR;
            }
        }
        
    }
}