// @Time    :   2021/05/29 11:55:00
// @FileName:   AdjacentListGraph.cpp
// @Author  :   yuan
// @Software:   VSCode
#include"general.h"
/**
 * 
 * 图的邻接表表示法
 * 链式存储结构
 * 表结点： adjvex  nextarc (info)
 * 头结点： data    firstarc
 */

//表结点--弧信息
typedef struct ArcNode{
    int adjvex; //该弧所指顶点的位置
    struct ArcNode *nextarc;    //指向下一条弧的指针
    //int weight;//记录权值
}ArcNode;

//头结点
typedef struct VNode{
    VertexType data;    //顶点信息
    ArcNode *firstarc;  //指向第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];

//邻接表
typedef struct{
    AdjList vertices;
    int vexnum,arcnum;
    int kind;
}ALGraph;

Status createDG(ALGraph &g);
Status createDN(ALGraph &g);
Status createUDG(ALGraph &g);
Status createUDN(ALGraph &g);
void printAdjListGraph(ALGraph g);
void DFS(ALGraph g,int v);
void DFSTraverse(ALGraph g,Status(*visit)(int v));
int firstAdjVex(ALGraph g,int v);
int nextAdjVex(ALGraph g,int v,int w);

/**
 *
 * 算法7.1
 * 采用邻接矩阵表示法构造图G
 */
Status createGraph(ALGraph &g){
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
 * 采用邻接表表示法构造无向网
 */
Status createDN(ALGraph &g){
    cout<<"input vexnum:\t";
    cin>>g.vexnum;
    cout<<"input arcnum:\t";
    cin>>g.arcnum;
    //初始化头结点
    cout<<"input vex data:"<<endl;
    for(int i=0;i<g.vexnum;i++){
        cin>>g.vertices[i].data;
        g.vertices[i].firstarc=nullptr;
    }
    //初始化邻接表
    for(int k=0;k<g.arcnum;k++){
        cout<<"input Vertex v1->v2:"<<k<<'\t';
        int v1,v2;
        cin>>v1>>v2;
        ArcNode* tmp=(ArcNode*)malloc(sizeof(ArcNode));
        tmp->adjvex=v2;
        tmp->nextarc=nullptr;
        if(g.vertices[v1].firstarc==nullptr){
            g.vertices[v1].firstarc=tmp;
        }else{
            ArcNode * ptr=g.vertices[v1].firstarc;
            while(ptr->nextarc!=nullptr)ptr=ptr->nextarc;
            ptr->nextarc=tmp;
            free(ptr);
        }
        free(tmp);
    }
    cout<<"creation finished.\n";
    return OK;
}
Status createDG(ALGraph &g){
    cout<<"暂未实现！\n";
    return OK;
}
Status createUDG(ALGraph &g){
    cout<<"暂未实现！\n";
    return OK;
}
Status createUDN(ALGraph &g){
    cout<<"暂未实现！\n";
    return OK;
}

void printAdjListGraph(ALGraph g){
    cout<<"该图的邻接表表示如下："<<endl;
    ArcNode * ptr;
    VNode  head;
    for(int i=0;i<g.vexnum;i++){
        head=g.vertices[i];
        cout<<head.data<<'\t';
        ptr=head.firstarc;
        while(ptr!=nullptr){
            cout<<ptr->adjvex<<'\t';
            ptr=ptr->nextarc;
        }
        cout<<endl;
    }
}

/**
 *
 * 深度优先遍历
 */
bool visited[MAX_VERTEX_NUM];
Status(*VisitFunc)(int v);
void DFSTraverse(ALGraph g,Status(*visit)(int v)){
    VisitFunc=visit;
    for(int v=0;v<g.vexnum;v++)visited[v]=FALSE;
    //防止非连通图和入度为0时遗漏结点
    for(int v=0;v<g.vexnum;v++){
        if(!visited[v])DFS(g,v);
    }
}
void DFS(ALGraph g,int v){
    if(!VisitFunc(v))return;
    else visited[v]=TRUE;
    for(int w=firstAdjVex(g,v);w>=0;w=nextAdjVex(g,v,w)){
        if(!visited[w])DFS(g,w);//对v的尚未访问的邻接顶点w递归调用DFS
    }
}
int firstAdjVex(ALGraph g,int v){
    //返回v的第一个邻接顶点
    ArcNode*p=g.vertices[v].firstarc;
    if(p!=nullptr)return p->adjvex;
    else return -1;
}
int nextAdjVex(ALGraph g,int v,int w){
    //返回v相对于w的下一个邻接顶点，若w是v的最后一个邻接顶点则返回空
    ArcNode *p=g.vertices[v].firstarc;
    while(p->adjvex!=w){
        p=p->nextarc;
        if(p==nullptr)return -1;
    }
    return p->adjvex;
}

/**
 * 广度优先搜索
 * 类似于树的层序遍历
 * 使用辅助队列和访问标志数组
 */
void BFSTraverse(ALGraph g,Status(*visit)(int v)){
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
    printf("%d\t",v);
    return OK;
}
int main(){
    //test
    ALGraph g;
    createGraph(g);
    cout<<"BFS result:"<<endl;
    BFSTraverse(g,visitG);
    cout<<"DFS result:"<<endl;
    DFSTraverse(g,visitG);
    return 0;
}
