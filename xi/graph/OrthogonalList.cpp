#include"general.h"

/**
 * @brief 弧
 * 
 */
typedef struct ArcBox{
    int tailVex,headVex;
    struct ArcBox *hlink,*tlink;
    InfoType *info;
    ArcBox(){}
    ArcBox(int tailVex,int headVex,ArcBox*tlink,ArcBox *hlink):tailVex(tailVex),headVex(headVex),hlink(hlink),tlink(tlink),info(NULL){}
}ArcBox;

/**
 * @brief 顶点
 * 
 */
typedef struct VexNode{
    VertexType data;
    ArcBox *firstIn,*firstOut;
}VexNode;

/**
 * @brief 十字链表
 * 
 */
typedef struct{
    VexNode xlist[MAX_VERTEX_NUM];
    int vexNum,arcNum;
    map<VertexType,int> mapping;//记录顶点名称和下标的映射
}OLGraph;

Status createDG(OLGraph &g);
int locateVex(OLGraph g,VertexType v);

/**
 * @brief 打印相邻矩阵
 * 
 * @param g 相邻矩阵
 */
void printGraph(OLGraph g){
    printf("有%d个节点，这些节点对应的弧为：",g.vexNum);
    for (int i=0;i<g.vexNum;i++){
        printf("\n%d\n",g.xlist[i].data);
        ArcBox *in=g.xlist[i].firstIn,*out=g.xlist[i].firstOut;
        printf("以%d为起点的弧有\n",g.xlist[i].data);
        while (out){
            printf("从%d到%d\n",g.xlist[out->tailVex].data,g.xlist[out->headVex].data);
            out=out->tlink;
        }
        printf("以%d为终点的弧有\n",g.xlist[i].data);
        while(in){
            printf("从%d到%d\n",g.xlist[in->tailVex].data,g.xlist[in->headVex].data);
            in=in->hlink;
        }
    }
}

/**
 * @brief 创建一个图
 * 
 * @param g 图
 * @return Status 操作结果 
 */
Status createDG(OLGraph &g){
    printf("输入节点数量:\n");
    scanf("%d",&g.vexNum);
    printf("输入弧数量:\n");
    scanf("%d",&g.arcNum);
    printf("输入各个节点名称:\n");
    for (int i=0;i<g.vexNum;i++){
        scanf("%d",&g.xlist[i].data);
        g.mapping[g.xlist[i].data]=i;
        g.xlist[i].firstIn=g.xlist[i].firstOut=NULL;
    }
    printf("输入各个弧（源节点 目标节点）:\n");
    for (int i=0;i<g.arcNum;i++){
        int s,d,w;
        scanf("%d%d",&s,&d);
        int is=locateVex(g,s);
        int id=locateVex(g,d);
        ArcBox *p=(ArcBox *)malloc(sizeof(ArcBox));
        p->tailVex=is;
        p->headVex=id;
        p->tlink=g.xlist[is].firstOut;
        p->hlink=g.xlist[id].firstIn;
        p->info=NULL;
        //mark：这里不能从栈中生成（作用域失效后被清空），只能从堆中分配空间
        // ArcBox arc=ArcBox(is,id,g.xlist[is].firstOut,g.xlist[id].firstIn);
        // g.xlist[is].firstOut=g.xlist[id].firstIn=&arc;
        g.xlist[is].firstOut=g.xlist[id].firstIn=p;
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
int locateVex(OLGraph g,VertexType v){
    return g.mapping[v];
}

int main(){
    OLGraph g;
    createDG(g);
    printGraph(g);
    return 0;
}

/*
3
3
1 2 3
1 2
2 3
3 1
*/