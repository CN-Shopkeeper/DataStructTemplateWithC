#include"general.h"

typedef struct Chunk{
    char ch[CHUNKSIZE];
    struct Chunk *next;
}Chunk;

typedef struct{
    Chunk *head,*tail;
    int curlen;
}LString;