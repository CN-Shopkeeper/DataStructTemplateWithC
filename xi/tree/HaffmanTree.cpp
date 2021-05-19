#include"general.h"

/**
 * @brief Huffman树
 * 
 */
typedef struct HTNode{
    unsigned int weight;
    unsigned int parent,lchild,rchild;
    HTNode(int weight,int parent,int lchild,int rchild):weight(weight),parent(parent),lchild(lchild),rchild(rchild){}
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;

/**
 * @brief 从已经生成的树中选取最小的两棵树
 * 
 * @param ht Huffman森林
 * @param i 森林截止位置
 * @param s1 第一棵树索引
 * @param s2 第二棵树索引
 */
void select(HuffmanTree ht,int i,int &s1,int &s2){
    int min=0x3f3f3f;
    for (int j=1;j<=i;j++){
        if (ht[j].weight<min){
            min=ht[j].weight;
            s1=j;
        }
    }
    min=0x3f3f3f;
    for (int j=1;j<=i;j++){
        if (j==s1){
            continue;
        }
        if (ht[j].weight<min){
            min=ht[j].weight;
            s2=j;
        }
    }
}

/**
 * @brief 算法 6.12 从叶子到根生成哈夫曼编码
 * 
 * @param ht 哈夫曼树
 * @param hc 哈夫曼编码索引
 * @param n 符号数
 */
void leafToRoot(HuffmanTree ht,HuffmanCode &hc,int n){
    //从叶子到根
    printf("从叶子到根\n");
    hc=(HuffmanCode)malloc((n+1)*sizeof(char*));//n+1是因为下标0不使用
    char *cd =(char *)malloc(n*sizeof(char));//最差情况下，n个字符需要用n-1位二进制位表示，最后一位是'\0'
    cd[n-1]='\0';
    for (int i=1;i<=n;i++){
        int start=n-1;
        int c=i;
        while (ht[c].parent!=0){
            if (ht[ht[c].parent].lchild==c){//如果是左孩子就标记为'0'
                cd[--start]='0';
            }else{
                cd[--start]='1';
            }
            c=ht[c].parent;
        }
        hc[i]=(char *)malloc((n-start)*sizeof(char));
        strcpy(hc[i],&cd[start]);
    }
    free(cd);
}

/**
 * @brief 算法6.13 从根到叶子生成哈夫曼编码
 * 
 * @param ht 哈夫曼树
 * @param hc 哈夫曼编码索引
 * @param n 符号数
 */
void rootToLeaf(HuffmanTree ht,HuffmanCode &hc,int n){
    //从根到叶子
    //无栈是指不用宽搜、无递归是指不用深搜
    //这种写法是复用了weight值模拟深搜，在搜索的过程中记录路径。默认每次都访问左儿子。
    //如果访问过了左儿子就将weight标记为1。
    //如果weight为1，此时访问右儿子，并标记为2
    //如果weight为2，说明左右节点均已经访问完，回到父节点
    printf("从根到叶子\n");
    hc=(HuffmanCode)malloc((n+1)*sizeof(char*));
    char *cd =(char *)malloc(n*sizeof(char));
    int p=2*n-1;//p是根节点
    int cdLen=0;
    for (int i=1;i<=2*n+1;i++){
        ht[i].weight=0;
    }
    while(p){//当p==0时说明已经从根节点前往头节点了
        if (ht[p].weight==0){//搜索左子树
            if (ht[p].lchild!=0){//如果没到叶子就记录路径
                ht[p].weight=1;//哈夫曼树是严格二叉树，有左孩子就一定有右孩子,因此调整weight的赋值位置
                p=ht[p].lchild;//搜索左孩子
                cd[cdLen++]='0';
            }else{//哈夫曼树是严格二叉树，有左孩子就一定有右孩子。因此这个elif的判断可以不用加
                ht[p].weight=2;
                cd[cdLen]='\0';
                hc[p]=(char*)malloc((cdLen+1)*sizeof(char));
                strcpy(hc[p],cd);
            }
        }else if(ht[p].weight==1){
            ht[p].weight=2;
            p=ht[p].rchild;
            cd[cdLen++]='1';
        }else{
            ht[p].weight=0;//这里可以不用修改，树中无回路，不会有其它路径再次访问到这个点了
            p=ht[p].parent;
            cdLen--;
        }
    }
}

/**
 * @brief 算法 6.12 生成哈夫曼树与哈夫曼编码
 * 
 * @param ht 哈夫曼树索引
 * @param hc 哈夫曼编码索引
 * @param w 权重数组
 * @param n 编码个数
 */
void huffmanCoding(HuffmanTree &ht,HuffmanCode &hc,int *w,int n){
    if(n<=1){
        return;
    }
    int m=2*n-1;//严格二叉树，有n个树叶就一共有2*n-1个节点
    ht=(HuffmanTree)malloc(sizeof(HTNode)*(m+1));//0号节点不用，用于表示根节点或无子节点
    for (int i=1;i<=n;i++){
        *(ht+i)=HTNode(w[i-1],0,0,0);
    }
    for (int i=n+1;i<=m;i++){
        *(ht+i)=HTNode(0,0,0,0);
    }
    for (int i=n+1;i<=m;i++){
        int s1,s2;
        select(ht,i-1,s1,s2);
        ht[s1].parent=i;
        ht[s2].parent=i;
        ht[i].lchild=s1;
        ht[i].rchild=s2;
        ht[i].weight=ht[s1].weight+ht[s2].weight;
        //这里一定要覆盖掉s1和s2的weight
        ht[s1].weight=0x3f3f3f;
        ht[s2].weight=0x3f3f3f;
    }
    leafToRoot(ht,hc,n);
    // rootToLeaf(ht,hc,n);
}

int main(){
    HuffmanTree ht;
    HuffmanCode hc;
    int weight[10]={1,2,3,4,5,6,7,8,9,10};
    huffmanCoding(ht,hc,weight,10);
    for (int i=1;i<=10;i++){
        printf("%s\n",hc[i]);
    }
    return 0;
}

/*
    从叶子到根
    01110
    01111
    0110
    1110
    1111
    010
    100
    101
    110
    00
*/
//huffman树相同，结果显然应该是一样的
/*
    从根到叶子
    01110
    01111
    0110
    1110
    1111
    010
    100
    101
    110
    00
*/
