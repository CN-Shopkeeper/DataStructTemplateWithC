#include"general.h"

typedef TElemType SqBiTree[MAX_TREE_SIZE];

SqBiTree bt;

void printTree_Sq(SqBiTree bt,int depth){
    int maxN=pow(2,depth);
    int interval=maxN*2;
    int nowF=1;
    printf("the tree is:\n");
    for (size_t i = 1; i < maxN; i++){
        if (i==pow(2,nowF)){
            interval/=2;
            printf("\n");
            nowF++;
        }
        if (bt[i]){
           printf("%*d%*c",interval,bt[i],interval,0);
        }else{
            printf("%*c",interval*2,0);
        }
    }
    
}

void createTree_Sq(SqBiTree &bt,int &n,int &depth){
    int a,b,d=0;
    printf("输入该树的结点个数:\n");
    scanf("%d",&n);
    memset(bt,0,sizeof(bt));
    printf("请输入节点的满二叉树位置与内容值（用空格来间隔）\n");
    for(int i=0;i<n;i++){
        scanf("%d%d",&a,&b);
        bt[a]=b;
        d=(int)floor(log2(a))+1;
        depth=depth>d?depth:d;
    }
}

int main(){
    SqBiTree bt;
    int n=0,depth=0;
    createTree_Sq(bt,n,depth);
    printTree_Sq(bt,depth);
    return 0;
}