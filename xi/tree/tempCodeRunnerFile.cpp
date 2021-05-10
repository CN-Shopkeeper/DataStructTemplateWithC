Status createBiTree(BiTree &bt){
    printf("按照先序遍历的顺序构造该二叉树：\n");
    int d;
    scanf("%d",&d);
    if(d==-1){
        bt=NULL;
    }else{
        if(!(bt=(BiTree)malloc(sizeof(BiTNode)))){
            exit(OVERFLOW);
        }
        bt->data=d;
        createBiTree(bt->lchild);
        createBiTree(bt->rchild);
    }
    return OK;
}