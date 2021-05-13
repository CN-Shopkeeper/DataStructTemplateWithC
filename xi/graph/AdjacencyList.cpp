#include"general.h"

/**
 * @brief 弧
 * 
 */
typedef struct ArcNode{
    int adjvex;
    struct ArcNode *nextarc;
    InfoType *info;
    ArcNode(){}
}ArcNode;

/**
 * @brief 顶点
 * 
 */
typedef struct VNode{
    VertexType data;
    ArcNode *firstArc;
}VNode,AdjList[MAX_VERTEX_NUM];

/**
 * @brief 邻接表
 * 
 */
typedef struct{
    AdjList vertices;
    int vexNum,arcNum;
    GraphKind kind;
    map<VertexType,int> mapping;//记录顶点名称和下标的映射
}ALGraph;

Status createGraph(ALGraph &g);
Status createUDG(ALGraph &g);
int locateVex(ALGraph g,VertexType v);

/**
 * @brief 打印相邻矩阵
 * 
 * @param g 相邻矩阵
 */
void printGraph(ALGraph g){
    printf("有%d个节点，节点名称为：\n",g.vexNum);
    for (int i=0;i<g.vexNum;i++){
        printf("%d ",g.vertices[i].data);
    }
    printf("\n有%d条弧，分别为:\n",g.arcNum);
    for (int i=0;i<g.vexNum;i++){
        ArcNode *p=g.vertices[i].firstArc;
        while (p->nextarc) {
            p=p->nextarc;
            printf("从%d到%d有一条弧\n",g.vertices[i].data,g.vertices[p->adjvex].data);
        }
    }
}

/**
 * @brief 创建一个图
 * 
 * @param g 图
 * @return Status 操作结果 
 */
Status createGraph(ALGraph &g){
    printf("构建一个有向图\n");
    return createUDG(g);
}

/**
 * @brief 创建一个有向图
 * 
 * @param g 图
 * @return Status 操作结果 
 */
Status createUDG(ALGraph &g){
    g.kind=UDG;
    printf("输入节点数量:\n");
    scanf("%d",&g.vexNum);
    printf("输入弧数量:\n");
    scanf("%d",&g.arcNum);
    printf("输入各个节点名称:\n");
    for (int i=0;i<g.vexNum;i++){
        g.vertices[i].firstArc=(ArcNode *)malloc(sizeof(ArcNode));
        g.vertices[i].firstArc->nextarc=NULL;
        g.vertices[i].firstArc->info=NULL;
        scanf("%d",&g.vertices[i].data);
        g.mapping[g.vertices[i].data]=i;
    }
    printf("输入各个弧（源节点 目标节点）:\n");
    for (int i=0;i<g.arcNum;i++){
        int s,d;
        scanf("%d%d",&s,&d);
        int is=locateVex(g,s);
        int id=locateVex(g,d);
        ArcNode *p=g.vertices[is].firstArc->nextarc;
        ArcNode *next=(ArcNode *)malloc(sizeof(ArcNode));
        next->nextarc=p;
        next->adjvex=id;
        g.vertices[is].firstArc->nextarc=next;
        //不输入弧信息
    }
    return OK;
}

/**
 * @brief 根据节点名称获取其在数据结构中的下标
 * 
 * @param g 图
 * @param v 节点名称
 * @return int 下标
 */
int locateVex(ALGraph g,VertexType v){
    return g.mapping[v];
}

int main(){
    ALGraph g;
    createGraph(g);
    printGraph(g);
    return 0;
}