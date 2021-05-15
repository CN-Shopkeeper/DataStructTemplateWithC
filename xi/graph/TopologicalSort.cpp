#include"AdjacencyList.cpp"

void findInDegree(ALGraph g,int *inDegree);

/**
 * @brief 找每一个顶点的入度
 * 
 * @param g 图
 * @param inDegree 入度数组
 */
void findInDegree(ALGraph g,int *inDegree){
    memset(inDegree,0,sizeof(int)*g.vexNum);
    for (int i=0;i<g.vexNum;i++){
        ArcNode *p=g.vertices[i].firstArc->nextarc;
        while(p){
            inDegree[p->adjvex]++;
            p=p->nextarc;
        }
    }
}

/**
 * @brief 算法7.12 拓扑排序
 * 
 * @param g 图
 * @return Status 操作结果
 */
Status TopologicalSort(ALGraph g){
    int inDegree[MAX_VERTEX_NUM];
    findInDegree(g,inDegree);
    stack<int> s;//用任意一种数据结构存储皆可
    while (!s.empty()){
        s.pop();
    }
    for (int i=0;i<g.vexNum;i++){
        if (!inDegree[i]){
            s.push(i);
        }
    }
    int count=0;
    while (!s.empty()){
        int now=s.top();
        s.pop();
        printf("节点%d\n",g.vertices[now].data);
        count++;
        ArcNode *p=g.vertices[now].firstArc->nextarc;
        while(p){
            int k=p->adjvex;
            if (!--inDegree[k]){
                s.push(k);
            }
            p=p->nextarc;
        }
    }
    if (count<g.vexNum){
        printf("有回路！\n");
        return ERROR;
    }else{
        return OK;
    }
}

int main(){
    ALGraph g;
    createGraph(g);
    TopologicalSort(g);
    return 0;
}

/*
0
6
8
1 2 3 4 5 6
1 2
1 3
1 4
3 2
3 5
4 5
6 4
6 5
*/