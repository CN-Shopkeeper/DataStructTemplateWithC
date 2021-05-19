#include"MatrixGraph.cpp"
/**
 * @brief prim算法用到的数据结构
 * 
 */
struct{
    VertexType adjVex;
    VRType lowCost;
}closedge[MAX_VERTEX_NUM];

struct AdjVex{
    VertexType v1,v2;
    VRType adj;
    AdjVex(VertexType v1, VertexType v2,VRType adj):v1(v1),v2(v2),adj(adj){}
    bool operator<(const AdjVex & a)const{
        return adj>a.adj;
    }
};

//简单实现一个并查集
int father[MAX_VERTEX_NUM];
//并查集的查找函数
int findFather(int i){
    return father[i]==i?i:father[i]=findFather(father[i]);
}
//并查集的合并函数
void merge(int x,int y){
    int fx=findFather(x);
    int fy=findFather(y);
    father[fx]=fy;
}

/**
 * @brief 算法7.9 prim算法求最小生成树
 * 
 * @param g 无向网
 * @param u 开始节点名称
 */
void prim(MGraph g,VertexType u){
    int k=locateVex(g,u);
    for (int j=0;j<g.vexNum;j++){
        if (j!=k){
            closedge[j].adjVex=u;
            closedge[j].lowCost=g.arcs[k][j].adj;
        }
    }
    closedge[k].lowCost=0;
    for (int i=1;i<g.vexNum;i++){
        int mincost=INFINITY;
        for (int j=0;j<g.vexNum;j++){
            if (closedge[j].lowCost!=0&&closedge[j].lowCost<mincost){
                mincost=closedge[j].lowCost;
                k=j;
            }
        }
        closedge[k].lowCost=0;
        printf("从%d到%d\n",closedge[k].adjVex,g.vexs[k]);
        for (int j=0;j<g.vexNum;j++){
            if (g.arcs[k][j].adj<closedge[j].lowCost){
                closedge[j].adjVex=g.vexs[k];
                closedge[j].lowCost=g.arcs[k][j].adj;
            }
        }
    }
}

/**
 * @brief kruskal算法
 * 
 * @param g 图
 */
void kruskal(MGraph g){
    priority_queue<AdjVex> q;
    for (int i=0;i<g.vexNum;i++){
        //初始化并查集父节点都是自己
        father[i]=i;
    }
    for (int i=0;i<g.vexNum;i++){
        for (int j=0;j<i;j++){
            if (g.arcs[i][j].adj!=INFINITY){
                q.push(AdjVex(g.vexs[i],g.vexs[j],g.arcs[i][j].adj));
            }
        }
    }
    while (!q.empty()){
        AdjVex now=q.top();
        q.pop();
        int f1=findFather(now.v1);
        int f2=findFather(now.v2);
        if (f1!=f2){
            printf("从%d到%d\n",now.v1,now.v2);
            merge(f1,f2);
        }
    }
}

int main(){
    MGraph g;
    printf("请构造一个无向网！\n");
    createGraph(g);
    printf("\nprim\n");
    prim(g,g.vexs[0]);
    printf("\nkruskal\n");
    kruskal(g);
    printf("pk");
    return 0;
}

/*
prim算法和kruskal算法的测试用例（图7.16）
3
6
10
1 2 3 4 5 6
1 2 6
1 3 1
1 4 5
2 3 5
2 5 3
3 4 5
3 5 6
3 6 4
4 6 2
5 6 6
*/