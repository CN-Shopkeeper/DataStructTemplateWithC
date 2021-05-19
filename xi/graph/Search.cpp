#include"MatrixGraph.cpp"
#define MAX 100

bool visited[MAX];
Status (*visitFunc)(int v);
void DFSTraverse(MGraph g,Status (*visit)(int v));
void DFS(MGraph g,int v);

/**
 * @brief 算法7.4 对图进行深度优先搜索
 * 
 * @param g 图
 * @param visit 访问函数
 */
void DFSTraverse(MGraph g,Status (*visit)(int v)){
    visitFunc=visit;
    for (int i=0;i<g.vexNum;i++){
        visited[i]=false;
    }
    for (int i=0;i<g.vexNum;i++){
        if (!visited[i]){
            visited[i]=true;
            DFS(g,i);
        }
    }
}

/**
 * @brief 算法7.5 深搜函数
 * 
 * @param g 图
 * @param v 当前访问的节点
 */
void DFS(MGraph g,int v){
    visitFunc(v);
    for (int i=0;i<g.vexNum;i++){
        if (g.arcs[v][i].adj!=INFINITY&&!visited[i]){
            visited[i]=true;
            DFS(g,i);
        }
    }
}

/**
 * @brief 算法7.6 对图进行非递归的宽度优先搜索
 * 
 * @param g 图
 * @param visit 访问函数
 */
void BFSTraverse(MGraph g,Status (*visit)(int v)){
    for (int i=0;i<g.vexNum;i++){
        visited[i]=false;
    }
    stack<int> s;
    while(!s.empty()){
        s.pop();
    }
    for (int i=0;i<g.vexNum;i++){
        if (!visited[i]){
            visited[i]=true;
            visit(i);
            s.push(i);
            while(!s.empty()){
                int now=s.top();
                s.pop();
                for (int j=0;j<g.vexNum;j++){
                    if (g.arcs[now][j].adj!=INFINITY&&!visited[j]){
                        visited[j]=true;
                        visit(j);
                        s.push(j);
                    }
                }
            }
        }
    }
}