#include"general.h"

typedef unsigned char SString[MAXSTRLEN+1];

/**
 * @brief 输出一个串
 * 
 * @param s 串
 */
void printString(SString s){
    for (int i=1;i<=s[0];i++){
        printf("%c",s[i]);
    }
    printf("\n");
}

/**
 * @brief 算法4.2 拼接两个串
 * 
 * @param t 新串
 * @param s1 串1
 * @param s2 串2
 * @return Status 操作结果
 */
Status concat(SString &t,SString s1,SString s2){
    if (s1[0]+s2[0]<=MAXSTRLEN){
        for (int i=1;i<=s1[0];i++){
            t[i]=s1[i];
        }
        for (int i=1;i<=s2[0];i++){
            t[i+s1[0]]=s2[i];
        }
        t[0]=s1[0]+s2[0];
        return OK;
    }else if(s1[0]<MAXSTRLEN){
        for (int i=1;i<=s1[0];i++){
            t[i]=s1[i];
        }
        for (int i=s1[0]+1;i<=MAXSTRLEN;i++){
            t[i]=s2[i-s1[0]];
        }
        t[0]=MAXSTRLEN;
        return OK;
    }else{
        for (int i=1;i<=MAXSTRLEN;i++){
            t[i]=s1[i];
        }
        t[0]=MAXSTRLEN;
        return OK;
    }
}

/**
 * @brief 算法4.3 求字串
 * 
 * @param sub 字串引用
 * @param s 源串
 * @param pos 截取位置
 * @param len 截取长度
 * @return Status 操作结果
 */
Status subString(SString &sub,SString s,int pos,int len){
    if (pos<1||pos>s[0]||len<0||len>s[0]-pos+1){
        printf("错误！\n");
        return ERROR;
    }
    sub[0]=len;
    for (int i=1;i<=len;i++){
        sub[i]=s[i+pos-1];
    }
    return OK;
}

/**
 * @brief 生成一个串
 * 
 * @param s 串
 * @return Status 操作结果
 */
Status initString(SString &s){
    printf("输入串长度：\n");
    scanf("%d",&s[0]);
    if (s[0]>MAXSTRLEN){
        printf("超出最大串长！\n");
        return ERROR;
    }
    getchar();
    for (int i=1;i<=s[0];i++){
        scanf("%c",&s[i]);
    }
    return OK;
}

int main(){
    SString s1,s2,s3,sub;
    initString(s1);
    initString(s2);
    concat(s3,s1,s2);
    subString(sub,s1,5,5);
    printString(s3);
    printString(sub);
    return 0;
}