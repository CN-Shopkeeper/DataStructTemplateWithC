#include"AdjacencyList.cpp"

int ve[MAX_VERTEX_NUM];
int vl[MAX_VERTEX_NUM];

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
 * @brief 算法7.13 修改过的拓扑排序
 * 
 * @param g 图
 * @return Status 操作结果
 */
Status TopologicalOrder(ALGraph g,stack<int> &t){
    int inDegree[MAX_VERTEX_NUM];
    findInDegree(g,inDegree);
    stack<int> s;//用任意一种数据结构存储皆可
    while (!s.empty()){
        s.pop();
    }
    while (!t.empty()){
        t.pop();
    }
    memset(ve,0,sizeof(int)*g.vexNum);
    for (int i=0;i<g.vexNum;i++){
        if (!inDegree[i]){
            s.push(i);
        }
    }
    int count=0;
    while (!s.empty()){
        int now=s.top();
        s.pop();
        t.push(now);
        count++;
        ArcNode *p=g.vertices[now].firstArc->nextarc;
        while(p){
            int k=p->adjvex;
            if (!--inDegree[k]){
                s.push(k);
            }
            ve[k]=ve[k]>ve[now]+p->info?ve[k]:ve[now]+p->info;
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

/**
 * @brief 算法7.14 求关键活动
 * 
 * @param g 图
 * @return Status 操作结果
 */
Status criticalPath(ALGraph g){
    stack<int>t;
    if (!TopologicalOrder(g,t)){
        return ERROR;
    }
    for (int i=0;i<g.vexNum;i++){
        vl[i]=ve[g.vexNum-1];
    }
    while (!t.empty()){
        int now =t.top();
        t.pop();
        ArcNode *p=g.vertices[now].firstArc->nextarc;
        while (p){
            int k=p->adjvex;
            vl[now]=vl[now]<vl[k]-p->info?vl[now]:vl[k]-p->info;
            p=p->nextarc;
        }
    }
    printf("\nve:\n");
    for (int i=0;i<g.vexNum;i++){
        printf("%d ",ve[i]);
    }
    printf("\nvl:\n");
    for (int i=0;i<g.vexNum;i++){
        printf("%d ",vl[i]);
    }
    printf("\n%5s%5s%5s%5s%5s%5s\n","v1\0","v2\0","dul\0","ee\0","el\0","c?\0");
    for (int i=0;i<g.vexNum;i++){
        ArcNode *p=g.vertices[i].firstArc->nextarc;
        while(p){
            int k=p->adjvex;
            int dut=p->info;
            int ee=ve[i];
            int el=vl[k]-dut;
            printf("%5d%5d%5d%5d%5d%5c\n",g.vertices[i].data,g.vertices[k].data,dut,ee,el,ee==el?'*':0);
            p=p->nextarc;
        }
    }
    return OK;
}

int main(){
    ALGraph g;
    createGraph(g);
    criticalPath(g);
    return 0;
}

/*
图7.29
1
9
11
1 2 3 4 5 6 7 8 9
1 2 6
1 3 4
1 4 5
2 5 1
3 5 1
4 6 2
5 7 9
5 8 7
6 8 4
7 9 2
8 9 4

图7.30
1
6
8
1 2 3 4 5 6
1 2 3
1 3 2
2 4 2
2 5 3
3 4 4
3 6 3
4 6 2
5 6 1
*/