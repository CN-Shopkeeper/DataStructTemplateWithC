// @Time    :   2021/05/21 10:32:54
// @FileName:   SequentialString.cpp
// @Author  :   yuan
// @Software:   VSCode

#include"general.h"
typedef unsigned char SString[MAXSTRLEN+1];//0号单元存放串的长度
//MAXSTRLEN 255

//生成一个值为chars的串
Status strAssign(SString &t,string chars){
    if(chars.size()>MAXSTRLEN)return ERROR;
    //对数据结构理解不深，你在干嘛啊，什么是数组？数组初始化？
    // t=(SString*)malloc(sizeof(SString)*MAXSTRLEN);
    t[0]=chars.size();
    for(int i=1;i<=t[0];i++){
        t[i]=chars[i-1];
    }
    return OK;
}

//复制串s得串t
Status strCopy(SString &t,SString s){
    for(int i=0;i<s[0]+1;i++){
        t[i]=s[i];
    }
    return OK;
}

Status strEmpty(SString s){
    return s[0]==0;
}


int strCompare(SString s,SString t){
    for(int i=1;i<s[0]&&i<t[0];i++){
        if(!(s[i]==t[i]))return s[i]-t[i];
    }
    return s[0]-t[0];
}

int strLength(SString s){
    return s[0];//可以吗？？？总感觉不太对？
}

//太简单粗暴了吧。。。
Status clearString(SString &s){
    s[0]=0;
    return OK;
}

//未截断则返回true，否则返回false
Status concat(SString &t,SString s1,SString s2){
    bool cut;
    if(s1[0]+s2[0]<=MAXSTRLEN){
        t[0]=s1[0]+s2[0];
        for(int i=1;i<=s1[0];i++){
            t[i]=s1[i];
        }
        for(int i=1;i<=s2[0];i++){
            t[s1[0]+i]=s2[i];
        }
        cut= true;
    }else if(s1[0]<MAXSTRLEN){
        t[0]=MAXSTRLEN;
        for(int i=1;i<=s1[0];i++){
            t[i]=s1[i];
        }
        for(int i=1;i<=MAXSTRLEN-s1[0];i++){
            t[s1[0]+i]=s2[i];
        }
        cut= false;
    }else{
        t[0]=MAXSTRLEN;
        for(int i=1;i<=MAXSTRLEN;i++){
            t[i]=s1[i];
            cut= false;
        }
    }
    return cut;
}

//用sub返回s的第pos个字符起长度为len的子串
Status subString(SString &sub,SString s,int pos,int len){
    if(pos>s[0]||pos+len>s[0]||pos<1||len<0)return ERROR;
    sub[0]=len;
    for(int i=0;i<len;i++){
        sub[i+1]=s[pos+i];
    }
    return OK;
}

//若主串s存在和串t相同的子串，则返回它在主串s中第pos个字符之后第一次出现的位置，否则函数值为0
int index(SString s,SString t,int pos){
    if(pos>s[0]||pos<1)return 0;
    //借助上面的函数
    for(int i=pos;i<=s[0]-t[0]+1;i++){
        SString sub;
        subString(sub,s,i,t[0]);
        if(strCompare(t,sub)==0)return i;
    }
    return 0;
}

//t非空，用v替换主串s中出现的所有与t相等的不重叠的子串
// Status replace(SString &s,SString t,SString v){
//     if(t[0]>s[0]||v[0]>s[0])return ERROR;
//     int pos;
//     while(pos=index(s,t,0)){

//     }
// }//不想写这个了。。。要判断好多东西嘞

//在串s的第pos个字符之前插入t
Status strInsert(SString &s,int pos,SString t){
    if(pos<1||pos>s[0]||s[0]+t[0]>MAXSTRLEN)return ERROR;
    for(int i=s[0],j=t[0];i>=pos&&j>0;i--){
        //为t的插入腾开位置
        s[i+t[0]]=s[i];
        //腾开的空位放置t
        s[i]=t[j--];
    }
    s[0]+=t[0];
    return OK;
}

//删除第pos个字符起长度为len的子串
Status strDelete(SString &s,int pos,int len){

}

Status destroyString(SString &s){

}