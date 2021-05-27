// @Time    :   2021/05/27 21:20:20
// @FileName:   MatrixGraph.cpp
// @Author  :   yuan
// @Software:   VSCode

#include"general.h"

typedef struct ArcCell{
    VRType adj;//顶点关系类型
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct{
    VertexType vex[MAX_VERTEX_NUM];//顶点向量
    AdjMatrix arcs;//邻接矩阵
    int vexnum,arcnum;//图的当前顶点数和弧数
    GraphKind kind;//图的种类标志
}MGraph;