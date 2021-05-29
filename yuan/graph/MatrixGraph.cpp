// @Time    :   2021/05/28 22:34:24
// @FileName:   MatrixGraph.cpp
// @Author  :   yuan
// @Software:   VSCode

#include"general.h"

/**
 *
 * 邻接矩阵表示法
 */
typedef struct ArcCell{
    VRType adj;//顶点关系类型 对无权图用0或1表示是否相邻，带权图表示权值类型
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct{
    VertexType vex[MAX_VERTEX_NUM];//顶点向量
    AdjMatrix arcs;//邻接矩阵
    int vexnum,arcnum;//图的当前顶点数和弧数
    GraphKind kind;//图的种类标志
}MGraph;

Status createDG(MGraph &g);
Status createDN(MGraph &g);
Status createUDG(MGraph &g);
Status createUDN(MGraph &g);
int locateVex(MGraph g,VertexType v);
void printMatrixGraph(MGraph g);
void DFS(MGraph g,int v);
void DFSTraverse(MGraph g,Status(*visit)(int v));
int firstAdjVex(MGraph g,int v);
int nextAdjVex(MGraph g,int v,int w);

/**
 *
 * 算法7.1
 * 采用邻接矩阵表示法构造图G
 */
Status createGraph(MGraph &g){
    cout<<"输入图的类型:"<<endl;
    scanf("%d",&g.kind);
    switch(g.kind){
        case DG:cout<<"创建一个有向图:"<<endl;
            return createDG(g);break;
        case DN:cout<<"创建一个有向网:"<<endl;
            return createDN(g);break;
        case UDG:cout<<"创建一个无向图:"<<endl;
            return createUDG(g);break;
        case UDN:cout<<"创建一个无向网:"<<endl;
            return createUDN(g);break;
        default:cout<<"类型错误!"<<endl;
            return ERROR;
    }
}

/**
 *
 * 采用数组表示法构造无向网
 */
Status createUDN(MGraph &g){
    cout<<"input vexnum:\t";
    cin>>g.vexnum;
    cout<<"input arcnum:\t";
    cin>>g.arcnum;
    cout<<"input vexs:\t";
    for(int i=0;i<g.vexnum;i++)cin>>g.vex[i];//构造顶点向量
    //初始化
    for(int i=0;i<g.vexnum;i++){
        for(int j=0;j<g.vexnum;j++){
            g.arcs[i][j].adj=INFINITY;
        }
    }
    //构造邻接矩阵
    for(int k=0;k<g.arcnum;k++){
        cout<<"input Vertex v1 & v2 & weight:\t";
        VertexType v1,v2;
        VRType w;
        cin>>v1>>v2>>w;
        int i=locateVex(g,v1);
        int j=locateVex(g,v2);
        g.arcs[i][j].adj=w;
        g.arcs[j][i]=g.arcs[i][j];
    }
    return OK;
}
int locateVex(MGraph g,VertexType v){
    for(int i=0;i<g.vexnum;i++){
        if(g.vex[i]==v)return i;
    }
    return -1;
}
Status createUDG(MGraph &g){
    cout<<"暂未实现！\n";
    return ERROR;
}
Status createDG(MGraph &g){
    cout<<"暂未实现！\n";
    return ERROR;
}
Status createDN(MGraph &g){
    cout<<"暂未实现！\n";
    return ERROR;
}

void printMatrixGraph(MGraph g){
    //输出表格行head
    cout<<'\t';
    for(int i=0;i<g.vexnum;i++){
        cout<<g.vex[i]<<'\t';
    }
    cout<<endl;
    //内容
    for(int i=0;i<g.vexnum;i++){
        cout<<g.vex[i]<<'\t';
        for(int j=0;j<g.vexnum;j++){
            if(g.arcs[i][j].adj==INFINITY)cout<<-1<<'\t';
            else printf("%d\t",g.arcs[i][j].adj);
        }
        cout<<endl;
    }
}

/**
 *
 * 算法7.4
 * 深度优先遍历
 */
bool visited[MAX_VERTEX_NUM];
Status(*VisitFunc)(int v);
void DFSTraverse(MGraph g,Status(*visit)(int v)){
    VisitFunc=visit;
    for(int v=0;v<g.vexnum;v++)visited[v]=FALSE;
    //防止非连通图遗漏结点！！！！！！
    for(int v=0;v<g.vexnum;v++){
        if(!visited[v])DFS(g,v);
    }
}
void DFS(MGraph g,int v){
    if(!VisitFunc(v))return;
    else visited[v]=TRUE;
    for(int w=firstAdjVex(g,v);w>=0;w=nextAdjVex(g,v,w)){
        if(!visited[w])DFS(g,w);//对v的尚未访问的邻接顶点w递归调用DFS
    }
}
int firstAdjVex(MGraph g,int v){
    //返回v的第一个邻接顶点
    for(int i=0;i<g.vexnum;i++){
        int weight=g.arcs[v][i].adj;
        if(weight!=-1&&weight!=INFINITY)return i;
    }
    return -1;
}
int nextAdjVex(MGraph g,int v,int w){
    //返回v相对于w的下一个邻接顶点，若w是v的最后一个邻接顶点则返回空
    for(int i=w;i<g.vexnum;i++){
        int weight = g.arcs[v][i].adj;
        if(weight!=-1&&weight!=INFINITY)return i;
    }
    return -1;
}

/**
 * 
 * 算法7.6
 * 广度优先搜索
 * 类似于树的层序遍历
 * 使用辅助队列和访问标志数组
 */
void BFSTraverse(MGraph g,Status(*visit)(int v)){
    for(int v=0;v<g.vexnum;v++)visited[v]=FALSE;
    queue<int> q;
    for(int v=0;v<g.vexnum;v++){//考虑图的连通性
        if(!visited[v]){
            if(!visit(v))return;
            else visited[v]=TRUE;
            q.push(v);
            while(!q.empty()){
                int u=q.front();
                q.pop();
                for(int w=firstAdjVex(g,u);w>=0;w=nextAdjVex(g,u,w)){
                    if(!visited[w]){
                        if(!visit(w))return;
                        else visited[w]=TRUE;
                        q.push(w);
                    }
                }
            }
        }
    }
}

Status visitG(int v){
    cout<<v<<'\t';
    return OK;
}
int main(){
    MGraph g;
    if(createGraph(g))
    {
        cout<<"当前图的矩阵表示为(-1表示不相邻)：\n";
        printMatrixGraph(g);//INFINITY
        cout<<"DFS result:\n";
        DFSTraverse(g,visitG);
        cout<<"done!"<<endl;
    }
    return 0;
}