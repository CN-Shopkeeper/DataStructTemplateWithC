#include"MatrixGraph.cpp"

typedef bool PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];

//记录路径，path[i][j]为前往节点i的第j步的节点
int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM+1];

void dijkstra(MGraph g,int v0,PathMatrix &p,ShortPathTable &d){
    bool final[MAX_VERTEX_NUM];
    for (int i=0;i<g.vexNum;i++){
        final[i]=false;
        d[i]=g.arcs[v0][i].adj;
        for (int j=0;j<g.vexNum;j++){
            p[i][j]=false;//使用书上的数组记录的路径最后是无序的
        }
        if (d[i]!=INFINITY){
            p[i][v0]=true;
            p[i][i]=true;
        }
    }
    d[v0]=0;
    final[v0]=true;
    for (int i=1;i<g.vexNum;i++){
        int min=INFINITY;
        int position=-1;
        for(int j=0;j<g.vexNum;j++){
            if (!final[j]){
                if (min>d[j]){
                    min=d[j];
                    position=j;
                }
            }
        }
        if (position==-1){//说明并不能到达剩下来的点
            printf("\n有剩余节点不可到达！\n");
            break;
        }
        final[position]=true;
        for (int j=0;j<g.vexNum;j++){
            if (!final[j]&&(d[j]>d[position]+g.arcs[position][j].adj)){
                d[j]=d[position]+g.arcs[position][j].adj;
                //更新书上的path数组
                for(int k=0;k<g.vexNum;k++){
                    p[j][k]=p[position][k];
                    p[j][j]=true;
                }
            }
        }
    }

    //打印结果
    printf("\n%d到其它点的情况是:\n",v0);
    for (int i=1;i<g.vexNum;i++){
        printf("%d: ",g.vexs[i]);
        if (d[i]==INFINITY){
            printf("不可到达！\n");
        }else{
            printf("距离为: %d 路径（无序）为：",d[i]);
            for (int j=0;j<g.vexNum;j++){
                if (p[i][j]){
                    printf("%d ",g.vexs[j]);
                }
            }
            printf("\n");
        }
    }
}

void dijkstra(MGraph g,int v0,ShortPathTable &d){
    bool final[MAX_VERTEX_NUM];
    memset(path,-1,sizeof(path));
    for (int i=0;i<g.vexNum;i++){
        final[i]=false;
        d[i]=g.arcs[v0][i].adj;
        if (d[i]!=INFINITY){
            path[i][0]=v0;
            path[i][1]=i;
        }
    }
    d[v0]=0;
    final[v0]=true;
    path[v0][0]=v0;
    for (int i=1;i<g.vexNum;i++){
        int min=INFINITY;
        int position=-1;
        for(int j=0;j<g.vexNum;j++){
            if (!final[j]){
                if (min>d[j]){
                    min=d[j];
                    position=j;
                }
            }
        }
        if (position==-1){//说明并不能到达剩下来的点
            printf("\n有剩余节点不可到达！\n");
            break;
        }
        final[position]=true;
        for (int j=0;j<g.vexNum;j++){
            if (!final[j]&&(d[j]>d[position]+g.arcs[position][j].adj)){
                d[j]=d[position]+g.arcs[position][j].adj;
                int k=0;
                while (path[position][k]!=-1){
                    path[j][k]=path[position][k];
                    k++;
                }
                path[j][k]=j;
            }
        }
    }

    printf("\n%d到其它点的情况是:\n",v0);
    for (int i=1;i<g.vexNum;i++){
        printf("%d: ",g.vexs[i]);
        if (d[i]==INFINITY){
            printf("不可到达！\n");
        }else{
            printf("距离为: %d 路径（有序）为：",d[i]);
            int j=0;
            while (path[i][j]!=-1){
                printf("%d ",g.vexs[path[i][j]]);
                j++;
            }
            printf("\n");
        }
    }
}

int main(){
    MGraph g;
    PathMatrix p;
    ShortPathTable d;
    createGraph(g);
    dijkstra(g,0,p,d);
    dijkstra(g,0,d);
    
    return 0;
}

/*
1
6
8
0 1 2 3 4 5
0 5 100
0 4 30
0 2 10
1 2 5
2 3 50
3 5 10
4 3 20
4 5 60
*/