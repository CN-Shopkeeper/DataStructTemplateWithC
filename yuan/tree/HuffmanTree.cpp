// @Time    :   2021/05/26 22:01:25
// @FileName:   HuffmanTree.cpp
// @Author  :   yuan
// @Software:   VSCode
#include"general.h"

/**
 * n个叶子结点的HuffmanTree有2n-1个结点，可以用2n-1的一维数组存放
 */

typedef struct{
    unsigned int weight;
    unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;//动态分配数组存储赫夫曼树

typedef char**HuffmanCode;//动态分配数组存储赫夫曼编码表

void select(HuffmanTree ht,int n,int &s1,int&s2);

//从叶子到根逆向求每个字符的赫夫曼编码
void leafToRoot(HuffmanTree ht,HuffmanCode &hc,int n){
    hc=(HuffmanCode)malloc(sizeof(char*)*(n+1));
    char * cd=(char*)malloc(n*sizeof(char));
    cd[n-1]='\0';//结束符
    int i;
    for(i=1;i<=n;i++){//对n个叶子结点求赫夫曼编码
        int start=n-1;
        for(int c=i,f=ht[i].parent;  f!=0;   c=f,f=ht[f].parent){
            if(ht[f].lchild==c)cd[--start]='0';
            else cd[--start]='1';
        }
        hc[i]=(char*)malloc((n-start)*sizeof(char));
        strcpy(hc[i],&cd[start]);
    }
    free(cd);
}

//从根到叶子正向求每个字符的赫夫曼编码
//无栈非递归遍历赫夫曼树
void rootToLeaf(HuffmanTree ht,HuffmanCode &hc,int n){
    hc=(HuffmanCode)malloc((n+1)*sizeof(char*));
    char * cd=(char*)malloc(n*sizeof(char));
    int m=2*n-1,p=m,cdlen=0;
    for(int i=1;i<=m;i++)ht[i].weight=0;
    while(p){
        if(ht[p].weight==0){
            ht[p].weight=1;
            if(ht[p].lchild!=0){
                p=ht[p].lchild;
                cd[cdlen++]='0';
            }else if(ht[p].rchild==0){
                hc[p]=(char*)malloc((cdlen+1)*sizeof(char));
                cd[cdlen]='\0';
                strcpy(hc[p],cd);
            }
        }else if(ht[p].weight==1){
            ht[p].weight=2;
            if(ht[p].rchild!=0){
                p=ht[p].rchild;
                cd[cdlen++]='1';
            }
        }else{
            ht[p].weight=0;
            p=ht[p].parent;
            --cdlen;
        }
    }
    free(cd);
}

//求赫夫曼编码
void HuffmanCoding(HuffmanTree &ht,HuffmanCode &hc,unsigned int *w,int n){
    //w存放n个字符的权值，构造赫夫曼树ht，并求出n个字符的赫夫曼编码hc
    if(n<1)return;
    int m=2*n-1;
    ht=(HuffmanTree)malloc(sizeof(HTNode)*(m+1));//0号单元未用
    if(!ht)exit(OVERFLOW);
    //初始化
    HuffmanTree p;
    int i;
    for(i=1,p=ht;i<=n;++i,++p,++w){
        *p={*w,0,0,0};//前n个点作为叶子结点，权值为weight
    }
    for(;i<=m;++i,++p){
        *p={0,0,0,0};//n+1~m个点作为非叶子结点，权值为0
    }
    for(i=n+1;i<=m;++i){
        //在ht[1..i-1]选择parent为0且weight最小的两个结点，其序号分别为s1,s2
        int s1,s2;
        select(ht,i-1,s1,s2);
        ht[s1].parent=i;
        ht[s2].parent=i;
        ht[i].lchild=s1;
        ht[i].rchild=s2;
        ht[i].weight=ht[s1].weight+ht[s2].weight;
    }
    leafToRoot(ht,hc,n);
}

void select(HuffmanTree ht,int n,int &s1,int &s2){
    //从1~n选择weight最小且parent为0的两个结点
    if(n<1)return;
    int min=ht[1].weight;
    for(int i=1;i<=n;i++){
        if(ht[i].weight<min){
            min=ht[i].weight;
            s1=i;
        }
    }
    min=ht[1].weight;
    for(int i=1;i<=n;i++){
        if(i==s1)continue;
        if(ht[i].weight<min){
            min=ht[i].weight;
            s2=i;
        }
    }
}
