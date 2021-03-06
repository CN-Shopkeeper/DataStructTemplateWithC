#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<iostream>
#include <map>
#include <stack>
#include <queue>
using namespace std;

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define MAXSIZE 1000
#define MAX_TREE_SIZE 100
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define MAXQSIZE 100
#define INFINITY 0x3f3f3f3f
#define MAX_VERTEX_NUM 20
#define MAXSTRLEN 255
#define CHUNKSIZE 80
#define MAX_NUM_OF_KEY 8
#define RADIX 10
#define MAX_SPACE 1000

#define ERROR false
#define OK true
#define OVERFLOW -1
#define EQUAL 0
#define GREATER 1
#define LESSER -1
#define TRUE 1
#define FALSE 0

#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))
#define LH 1
#define EH 0
#define RH -1

typedef int ElemType; //存储元素类型
typedef int TElemType; //树的元素类型
typedef int SElemType; //栈的元素类型
typedef int QElemType; //队列的元素类型
typedef int InfoType;
typedef int VertexType;
typedef bool Status;
typedef int VRType;
typedef int KeyType;
typedef int KeysType;

typedef enum {DG,DN,UDG,UDN} GraphKind;

/**
 * @brief 树中的visit函数
 * 
 * @param e 树中要访问的元素
 * @return Status 操作结果
 */
Status printTElement(TElemType e){
    printf("%d ",e);
    return OK;
}

/**
 * @brief 栈中的visit函数
 * 
 * @param e 栈中要访问的元素
 * @return Status 操作结果
 */
Status printSElement(SElemType e){
    printf("%d ",e);
    return OK;
}

/**
 * @brief 队列中的visit函数
 * 
 * @param e 队列中要访问的元素
 * @return Status 操作结果
 */
Status printQElement(QElemType e){
    printf("%d ",e);
    return OK;
}

/*先序遍历顺序构建二叉树
1
2
3
-1
-1
4
5
-1
7
-1
-1
10
-1
-1
-1
*/