#include"general.h"

typedef struct HTNode{
    unsigned int weight;
    unsigned int parent,lchild,rchild;
    HTNode(int weight,int parent,int lchild,int rchild):weight(weight),parent(parent),lchild(lchild),rchild(rchild){}
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;

void huffmanCoding(HuffmanTree &ht,HuffmanCode &hc,int *w,int n){
    if(n<=1){
        return;
    }
    int m=2*n-1;//严格二叉树，有n个树叶就一共有2*n-1个节点
    ht=(HuffmanTree)malloc(sizeof(HTNode)*(m+1));//0号节点不用
    int i=1;
    for (HuffmanTree p=ht+1;i<=n;){

    }
}