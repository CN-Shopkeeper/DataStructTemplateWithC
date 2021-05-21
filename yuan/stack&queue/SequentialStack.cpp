// @Time    :   2021/05/19 22:14:03
// @FileName:   SequentialStack.cpp
// @Author  :   yuan
// @Software:   VSCode

#include"general.h"

typedef struct {
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

//构造一个空栈
Status initStack(SqStack &s){
    s.base = (SElemType*)malloc(sizeof(SElemType)*STACK_INIT_SIZE);
    if(!s.base)exit(OVERFLOW);
    s.top=s.base;
    s.stacksize=STACK_INIT_SIZE;
    return OK;
}

//若栈不空，用e返回栈顶元素，返回OK，否则返回ERROR
Status getTop(SqStack s,SElemType &e){
    if(s.top==s.base)return ERROR;
    e=*(s.top-1);
    return OK;
}

//插入元素e为新的栈顶元素
Status push(SqStack &s,SElemType e){
    if(s.top-s.base>=s.stacksize){
        //栈满，再申请空间
        s.base = (SElemType*)realloc(s.base,sizeof(SElemType)*(s.stacksize+STACKINCREMENT));
        if(!s.base)exit(OVERFLOW);
        s.top=s.base+s.stacksize;//重置栈顶
        s.stacksize=s.stacksize+STACKINCREMENT;
    }
    *(s.top)=e;
    s.top++;
    return OK;
}

//若栈不空，删除栈顶元素，用e返回值返回OK；否则返回ERROR
Status pop(SqStack &s,SElemType &e){
    if(s.top==s.base)return ERROR;
    e=*(--s.top);
    return OK;
}

//判断栈是否为空
bool stackEmpty(SqStack s){
    return s.top==s.base;
}

//test
//对于输入的任意一个非负十进制整数，打印输出与其值相等的八进制数
void conversion(){
    int n;
    cout<<"enter a num (D to O):\n";
    cin>>n;
    SqStack s;
    initStack(s);
    while(n){
        push(s,n%8);
        n=n/8;
    }
    SElemType e;
    while(!stackEmpty(s)){
        pop(s,e);
        cout<<e;
    }
}

int main(){
    conversion();
    return 0;
}
