#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define MAXSIZE 1000
#define MAX_TREE_SIZE 100

#define ERROR 0
#define OK 1
#define OVERFLOW -1
#define EQUARE 0
#define GREATER 1
#define LESSER -1

typedef int ElemType; //存储元素类型
typedef int TElemType; //树的元素类型
typedef int Status;