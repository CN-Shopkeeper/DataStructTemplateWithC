#include"MatrixGraph.cpp"

typedef bool PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];

//记录路径，path[i][j]为前往节点i的第j步的节点
int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM+1];

/**
 * @brief 算法 7.15 dijksta算法
 * 
 * @param g 图
 * @param v0 要测距离的顶点
 * @param p 路径
 * @param d 距离
 */
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

/**
 * @brief dijkstra（改进记录路径方式）
 * 
 * @param g 图
 * @param v0 开始顶点
 * @param d 距离
 */
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


int pathF[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM+1];
int dis[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

/**
 * @brief 算法7.16 Floyd算法（路径记录算法被改进）
 * 
 * @param g 图
 */
void floyd(MGraph g){
    memset(pathF,-1,sizeof(pathF));
    for (int i=0;i<g.vexNum;i++){
        for (int j=0;j<g.vexNum;j++){
            dis[i][j]=g.arcs[i][j].adj;
            if (g.arcs[i][j].adj!=INFINITY){
                pathF[i][j][0]=i;
                pathF[i][j][1]=j;
            }
        }
    }
    for (int i=0;i<g.vexNum;i++){
        for (int j=0;j<g.vexNum;j++){
            for (int k=0;k<g.vexNum;k++){
                if (dis[i][k]+dis[k][j]<dis[i][j]){
                    dis[i][j]=dis[i][k]+dis[k][j];
                    int w=0;
                    while (pathF[i][k][w]!=-1){
                        pathF[i][j][w]=pathF[i][k][w];
                        w++;
                    }
                    pathF[i][j][w]=j;
                }
            }
        }
    }

    printf("用floyd算法：\n");
    for (int i=0;i<g.vexNum;i++){
        for (int j=0;j<g.vexNum;j++){
            if (i!=j){
                if (dis[i][j]!=INFINITY){
                    printf("从%d到%d的距离为: %d，路径为：",i,j,dis[i][j]);
                    int w=0;
                    while (pathF[i][j][w]!=-1){
                        printf("%d ",pathF[i][j][w]);
                        w++;
                    }
                    printf("\n");
                }else {
                    printf("从%d到%d无法连通\n",i,j);
                }
            }
        }
    }
}

int main(){
    MGraph g;
    // PathMatrix p;
    // ShortPathTable d;
    createGraph(g);
    // dijkstra(g,0,p,d);
    // dijkstra(g,0,d);
    
    floyd(g);
    return 0;
}

/*
图7.34 dijkstra测试样例
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

/*
图 7.36 floyd算法测试样例
1
3
5
0 1 2
0 1 4
0 2 11
1 0 6
1 2 2
2 0 3
*/