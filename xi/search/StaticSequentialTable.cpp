#include"general.h"

typedef struct{
    KeyType *elem;
    int length;
}SSTable;

/**
 * @brief 二叉树
 * 
 */
typedef struct BiTNode{
    TElemType data;
    BiTNode * lchild,*rchild;
}BiTNode,*BiTree;

/**
 * @brief 递归先序遍历二叉树
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


/**
 * @brief 由于次优查找树要用到前缀和，所以哨兵最方便设置在下标0处
 * 
 * @param st 
 * @param key 
 * @return int 
 */
int search_Seq(SSTable st,KeyType key){
    st.elem[0]=key;
    int i=st.length;
    for (;!EQ(st.elem[i],key);i--){}
    return i;
}

/**
 * @brief 
 * 
 * @param st 
 * @param key 
 * @return int 
 */
int search_Bin(SSTable st,KeyType key){
    int low=1;
    int high=st.length;
    while (low<=high){//符号为<=
        int mid=(low+high)/2;
        if (EQ(st.elem[mid],key)){
            return mid;
        }else if(LT(st.elem[mid],key)){
            high=mid-1;
        }else{
            low=mid+1;
        }
    }
    return 0;
}

void secondOptimal(BiTree &t,KeyType k[],float sw[],int low,int high){
    int i=low;
    float min=abs(sw[high]-sw[low]);
    float dw=sw[high]+sw[low-1];
    for (int j=low+1;j<=high;j++){
        if (abs(dw-sw[j]-sw[j-1])<min){
            i=j;
            min=abs(dw-sw[j]-sw[j-1]);//dw-sw[j]-sw[j-1]=sw[high]-sw[j]-(sw[j-1]-sw[low-1])
        }
    }
    t=(BiTree)malloc(sizeof(BiTNode));
    t->data=k[i];
    if (i==low){
        t->lchild=NULL;
    }else{
        secondOptimal(t->lchild,k,sw,low,i-1);
    }
    if (i==high){
        t->rchild=NULL;
    }else{
        sw[i]=0;//需要将low-1赋值为0
        secondOptimal(t->rchild,k,sw,i+1,high);
    }
}

Status createSOSTree(BiTree &t,SSTable st,float sw[]){
    if (st.length==0){
        t=NULL;
    }else{
        secondOptimal(t,st.elem,sw,1,st.length);
    }
    return OK;
}

int main(){
    SSTable st;
    st.elem=(KeyType *)malloc(10*sizeof(KeyType));
    st.length=9;
    for (int i=1;i<=st.length;i++){
        st.elem[i]='A'+i-1;
    }
    for (int i=1;i<=st.length;i++){
        printf("%d ",st.elem[i]);
    }
    printf("\n");
    int i9=search_Seq(st,9);
    int i15=search_Bin(st,15);
    int i8=search_Bin(st,8);
    printf("9在数组中的下标是%d\n15在数组中的下标是%d\n8在数组中的下标是%d\n\n\n",i9,i15,i8);

    printf("次优查找树的先序遍历为：\n");
    float sw[10]={0,1,1,2,5,3,4,4,3,5};
    for (int i=1;i<=st.length;i++){
        sw[i]+=sw[i-1];
    }
    BiTree t;
    createSOSTree(t,st,sw);
    preOrderTraverse(t,print);
    return 0;
}