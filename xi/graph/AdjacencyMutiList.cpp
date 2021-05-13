#include"general.h"

typedef enum{unvisited,visited} VisitIf;
typedef struct EBox{
    VisitIf mark;
    int ivex,jvex;
    struct EBox *ilink,*jLink;
    InfoType *info;
}EBox;

typedef struct VexBox{
    VertexType data;
    EBox *firstedge;
}VexBox;

typedef struct{
    VexBox adjmulist[MAX_VERTEX_NUM];
    int vexNum,edgeNum;
}AMLGraph;