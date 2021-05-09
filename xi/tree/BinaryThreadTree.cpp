#include"general.h"

typedef enum PointerTag {Link,Thread};

typedef struct BiThrNode{
    TElemType data;
    BiThrTree lchild,rchild;
    PointerTag lTag,rTag;
}BiThrNode,* BiThrTree;
