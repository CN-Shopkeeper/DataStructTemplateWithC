#include<general.h>

typedef struct PTNode{
    TElemType data;
    int parent;
}PTNode;

typedef struct{
    PTNode nodes[MAX_TREE_SIZE];
    int r,n;
}PTree;

typedef PTree MFSet;

/**
 * @brief 算法6.8 查找根祖先函数
 * 
 * @param s 并查集
 * @param i 要查找的节点的下标（从0开始）
 * @return int 根祖先的下标
 */
int find_mfSet(MFSet s,int i){
    if(i<0||i>=s.n){
        printf("查找位置错误\n");
        return ERROR;
    }
    while (s.nodes[i].parent>=0){//教材中是>0，是因为所有节点从下标1开始排列
        i=s.nodes[i].parent;
    }
    return i;
}

/**
 * @brief 算法6.11 查找根节点时压缩路径
 * 
 * @param s 并查集
 * @param i 要查找的节点的下标（从0开始）
 * @return int 根祖先的下标
 */
int fix_mfSet(MFSet &s,int i){
    if(i<0||i>=s.n){
        printf("查找位置错误\n");
        return ERROR;
    }
    // int j;
    // for (j=i;s.nodes[j].parent>=0;j=s.nodes[j].parent);//找到根节点
    // //修改所有路径上的节点的双亲
    // for (int k=i;k!=j;){
    //     int t=s.nodes[k].parent;
    //     s.nodes[k].parent=j;
    //     k=t;
    // }

    //递归写法
    return s.nodes[i].parent>=0?s.nodes[i].parent=fix_mfSet(s,s.nodes[i].parent):i;
}

/**
 * @brief 算法6.9 合并函数
 * 
 * @param s 并查集
 * @param i 第一个要合并的函数 
 * @param j 第二个要合并的函数
 * @return Status 返回结果
 */
Status merge_mfSet(MFSet &s,int i,int j){
    if(i<0||i>=s.n||j<0||j>=s.n){
        printf("合并位置错误\n");
        return ERROR;
    }
    s.nodes[fix_mfSet(s,i)].parent=j;//教材中没有使用find函数，这会导致树的深度增加；并且在使用路径压缩时也需要这样写。
    return OK;
}

/**
 * @brief 算法6.10 合并时小深度的合并到大深度的
 * 
 * @param s 并查集
 * @param i 第一个要合并的函数 
 * @param j 第二个要合并的函数
 * @return Status 返回结果
 */
Status mix_mfSet(MFSet &s,int i,int j){
    if(i<0||i>=s.n||j<0||j>=s.n){
        printf("合并位置错误\n");
        return ERROR;
    }
    int pi=fix_mfSet(s,i),pj=fix_mfSet(s,j);//同上，只有根节点才会存储节点数
    if(s.nodes[pi].parent>s.nodes[pj].parent){
        s.nodes[pj].parent+=s.nodes[pi].parent;
        s.nodes[pi].parent=pj;
    }else{
        s.nodes[pi].parent+=s.nodes[pj].parent;
        s.nodes[pj].parent=pi;
    }
    return OK;
}

int main(){
    MFSet s;
    s.n=20;
    for (int i=0;i<s.n;i++){
        s.nodes[i].parent=-1;
    }
    printf("常规合并\n");
    merge_mfSet(s,0,1);
    merge_mfSet(s,2,3);
    printf("0号节点的根是:%d\n",fix_mfSet(s,0));
    printf("1号节点的根是:%d\n",fix_mfSet(s,1));
    printf("2号节点的根是:%d\n",fix_mfSet(s,2));
    printf("3号节点的根是:%d\n",fix_mfSet(s,3));
    mix_mfSet(s,10,11);
    mix_mfSet(s,12,10);
    printf("小深度合并\n");
    printf("10号节点的根是:%d\n",fix_mfSet(s,10));
    printf("11号节点的根是:%d\n",fix_mfSet(s,11));
    printf("12号节点的根是:%d\n",fix_mfSet(s,12));
    return 0;
}