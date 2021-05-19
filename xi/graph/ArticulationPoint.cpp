#include"AdjacencyList.cpp"

int counts;
int visited[MAX_VERTEX_NUM];
int low[MAX_VERTEX_NUM];

void DFSArticul(ALGraph g,int v0);

void findArticul(ALGraph g){
    counts=1;
    memset(visited,0,sizeof(visited));
    visited[0]=1;
    ArcNode *p= g.vertices[0].firstArc->nextarc;
    //默认是连通图，即每一个节点的邻接表都不为空（p!=NULL）
    int v=p->adjvex;
    DFSArticul(g,v);
    if (counts<g.vexNum){//意味着生成树从根节点的一个儿子访问不了所有的节点（即有其它儿子，必须通过其它儿子访问剩余节点）
        printf("关键节点%d: %c\n",0,g.vertices[0].data);
        while(p->nextarc){
            p=p->nextarc;
            int v=p->adjvex;
            if (visited[v]==0){
                DFSArticul(g,v);
            }
        }
    }
}

void DFSArticul(ALGraph g,int v0){
    int min;
    visited[v0]=min=++counts;
    for (ArcNode *p=g.vertices[v0].firstArc->nextarc;p;p=p->nextarc){
        int w=p->adjvex;
        if (!visited[w]){
            DFSArticul(g,w);
            if (low[w]<min){
                min=low[w];
            }
            if(low[w]>=visited[v0]){
                printf("关键节点%d: %c\n",v0,g.vertices[v0].data);
            }
        }else if(visited[w]<min){
            min=visited[w];
        }
    }
    low[v0]=min;
}

int main(){
    ALGraph g;
    createGraph(g);
    findArticul(g);
    return 0;
}

/*
2
13
17
65 66 67 68 69 70 71 72 73 74 75 76 77
65 66
65 76
65 67
65 70
66 67
66 68
66 71
66 72
66 77
68 69
71 72
71 73
71 75
72 75
74 76
74 77
76 77
*/