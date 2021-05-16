#include"general.h"

typedef struct{
    char * ch;
    int length;
}HString;

Status strInsert(HString &s,int pos,HString t);
Status strAssign(HString &t,char *chars);
int strLen(HString s);
int strCompare(HString t,HString s);
Status clearString(HString s);
Status concat(HString &t,HString s1,HString s2);
HString subString(HString s,int pos ,int len);

Status strInsert(HString &s,int pos,HString t){
    if (pos<0||pos>s.length){
        printf("插入位置不合法\n");
        return ERROR;
    }
    if (t.length){
        if (!(s.ch=(char*)realloc(s.ch,(s.length+t.length)*sizeof(char)))){
            return OVERFLOW;
        }
        for (int i=s.length-1;i>=pos;i--){
            s.ch[i+t.length]=s.ch[i];
        }
        for (int i=0;i<t.length;i++){
            s.ch[pos+i]=t.ch[i];
        }
        s.length+=t.length;
    }
    return OK;
}

Status strAssign(HString &t,char *chars){
    if (t.ch){
        free(t.ch);
    }
    char *p=chars;
    int i=0;
    for (;*p;p++,i++){}
    if (!i){
        t.ch=NULL;
        t.length=0;
    }else{
        t.ch=(char*)malloc(i*sizeof(char));
        for (int j=0;j<i;j++){
            t.ch[j]=chars[j];
        }
        t.length=i;
    }
    return OK;
}

int strLen(HString s){
    return s.length;
}

int strCompare(HString s,HString t){
    for (int i=0;i<t.length&&i<s.length;i++){
        if (s.ch[i]!=t.ch[i]){
            return s.ch[i]-t.ch[i];
        }
    }
    return s.length-t.length;
}

Status clearString(HString s){
    if (s.length){
        free(s.ch);
        s.ch=NULL;
        s.length=0;
    }
    return OK;
}

Status concat(HString &t,HString s1,HString s2){
    if (t.ch){
        free(t.ch);
    }
    if (!(t.ch=(char*)malloc((s1.length+s2.length)*sizeof(char)))){
        printf("溢出\n");
        exit(OVERFLOW);
    }
    for (int i=0;i<s1.length;i++){
        t.ch[i]=s1.ch[i];
    }
    for (int i=0;i<s2.length;i++){
        t.ch[i+s1.length]=s2.ch[i];
    }
    t.length=s1.length+s2.length;
    return OK;
}

HString subString(HString s,int pos ,int len){
    HString sub;
    if (sub.ch){
        free(sub.ch);
    }
    if (pos<0||pos>=s.length||len<0||len>s.length-pos){
        printf("位置错误！\n");
        sub.length=0;
        sub.ch=NULL;
        return sub;
    }
    if (!len){
        sub.ch=NULL;
        sub.ch=NULL;
        return sub;
    }else{
        sub.ch=(char*) malloc(len*sizeof(char));
        for (int i=0;i<len;i++){
            sub.ch[i]=s.ch[pos+i];
        }
        sub.length=len;
        return sub;
    }
}