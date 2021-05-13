#include"general.h"

/**
 * @brief 弧的信息
 * 
 */
typedef struct ArcCell{
    VRType adj;
    InfoType *info;
    ArcCell(){}
    ArcCell(VRType adj,InfoType *info):adj(adj),info(info){}
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

/**
 * @brief 相邻矩阵
 * 
 */
typedef struct{
    VertexType vexs[MAX_VERTEX_NUM];
    AdjMatrix arcs;
    int vexNum,arcNum;
    GraphKind kind;
    map<VertexType,int> mapping;//记录顶点名称和下标的映射
}MGraph;

Status createGraph(MGraph &g);
Status createUDN(MGraph &g);
int locateVex(MGraph g,VertexType v);

/**
 * @brief 打印相邻矩阵
 * 
 * @param g 相邻矩阵
 */
void printGraph(MGraph g){
    printf("有%d个节点，节点名称为：\n",g.vexNum);
    for (int i=0;i<g.vexNum;i++){
        printf("%d ",g.vexs[i]);
    }
    printf("\n有%d条弧，分别为:\n",g.arcNum);
    for (int i=0;i<g.vexNum;i++){
        for (int j=0;j<g.vexNum;j++){
            if (g.arcs[i][j].adj!=INFINITY){
                printf("从%d到%d有一条权重为%d的弧\n",g.vexs[i],g.vexs[j],g.arcs[i][j].adj);
            }
        }
    }
}

/**
 * @brief 算法7.1 创建一个图（有向网）
 * 
 * @param g 图
 * @return Status 操作结果 
 */
Status createGraph(MGraph &g){
    printf("构建一个有向网（无弧信息）\n");
    return createDN(g);
}

/**
 * @brief 算法7.2 创建一个有向网（不是无向网）
 * 
 * @param g 网
 * @return Status 操作结果 
 */
Status createDN(MGraph &g){
    printf("输入节点数量:\n");
    scanf("%d",&g.vexNum);
    printf("输入弧数量:\n");
    scanf("%d",&g.arcNum);
    printf("输入各个节点名称:\n");
    for (int i=0;i<g.vexNum;i++){
        scanf("%d",&g.vexs[i]);
        g.mapping[g.vexs[i]]=i;
    }
    for (int i=0;i<MAX_VERTEX_NUM;i++){
        for (int j=0;j<MAX_VERTEX_NUM;j++){
            g.arcs[i][j]=ArcCell(INFINITY,NULL);
        }
    }
    printf("输入各个弧（源节点 目标节点 权重）:\n");
    for (int i=0;i<g.arcNum;i++){
        int s,d,w;
        scanf("%d%d%d",&s,&d,&w);
        int is=locateVex(g,s);
        int id=locateVex(g,d);
        g.arcs[is][id].adj=w;
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
int locateVex(MGraph g,VertexType v){
    return g.mapping[v];
}

int main(){
    MGraph g;
    createGraph(g);
    printGraph(g);
    return 0;
}