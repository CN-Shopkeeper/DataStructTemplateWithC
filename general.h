#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define MAXSIZE 1000
#define MAX_TREE_SIZE 100
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

#define ERROR 0
#define OK 1
#define OVERFLOW -1
#define EQUARE 0
#define GREATER 1
#define LESSER -1
#define TRUE 1
#define FALSE 0

typedef int ElemType; //存储元素类型
typedef int TElemType; //树的元素类型
typedef int SElemType; //栈的元素类型
typedef int Status;

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