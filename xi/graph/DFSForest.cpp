#include"MatrixGraph.cpp"

/**
 * @brief 儿子兄弟树
 * 
 */
typedef struct CSNode{
    ElemType data;
    struct CSNode *firstChild,*nextSibling;
}CSNode,*CStree;

bool visited[MAX_VERTEX_NUM];

void DFSForest(MGraph g, CStree &t);
void DFSTree(MGraph g,int v,CStree &t);

/**
 * @brief 先序遍历生成树
 * 
 * @param t 生成树
 * @param visit 访问函数
 * @return Status 操作结果
 */
Status preOrderTraverse(CStree t,Status(*visit)(TElemType e)){
    if (t){
        if(visit(t->data)){
            if(preOrderTraverse(t->firstChild,visit)){
                if(preOrderTraverse(t->nextSibling,visit)){
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
 * @brief 遍历无向图（森林）
 * 
 * @param g 无向图
 * @param t 生成树
 */
void DFSForest(MGraph g, CStree &t){
    for (int i=0;i<g.vexNum;i++){
        visited[i]=false;
    }
    t=NULL;
    CStree q;//用于存储前一棵树的根
    for (int i=0;i<g.vexNum;i++){
        if (!visited[i]){
            visited[i]=true;
            CStree p=(CStree)malloc(sizeof(CSNode));
            p->data=g.vexs[i];
            p->firstChild=NULL;
            p->nextSibling=NULL;
            if (!t){
                t=p;
            }else{
                q->nextSibling=p;
            }
            q=p;
            DFSTree(g,i,p);
        }
    }
}

/**
 * @brief 遍历每一个连通分量（树）
 * 
 * @param g 无向图
 * @param v 当前节点
 * @param t 生成树
 */
void DFSTree(MGraph g,int v,CStree &t){
    CStree q;
    for (int i=0;i<g.vexNum;i++){
        if (g.arcs[v][i].adj&&!visited[i]){
            visited[i]=true;
            CStree p=(CStree)malloc(sizeof(CSNode));
            p->data=g.vexs[i];
            p->firstChild=NULL;
            p->nextSibling=NULL;
            if (!t->firstChild){
                t->firstChild=p;
            }else{
                q->nextSibling=p;
            }
            q=p;
            DFSTree(g,i,p);
        }
    }
}

int main(){
    MGraph g;
    CStree t;
    printf("请构造一个无向图！\n");
    createGraph(g);
    DFSForest(g,t);
    preOrderTraverse(t,printTElement);
    return 0;
}

/*
测试数据
2
5
3
1 2 3 4 5
1 2
2 3
4 5

即有两个连通分量{1,2,3} {4,5}
构成的生成树应该是
        1
    2       4
3         5

测试数据
2
5
2
1 2 3 4 5
1 4
3 2

即有三个连通分量{1,4} {2,3} {5}
构成的生成树应该是
        1
    4       2
         3      5
*/