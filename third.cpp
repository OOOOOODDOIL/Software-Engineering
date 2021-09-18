#include<bits/stdc++.h>
using namespace std;
#define M 20000

typedef struct
{
    char danci[19];//储存单词
    int count;//记录单词出现次数
}sq;

int main()
{
    sq word[32];
    sq t_word;
    string str[M],temp;
    int K,n=0,i,j,keyword=0,switchnum=0,switchelse[100],flag=0;
    FILE *fp;
    char ch;
    fp=fopen("D://c++//ex.c","r");//读取文件
    while(!feof(fp))//feof()检测是否达到文件尾部
    {

        ch=getc(fp);//获取当前字符
        if(ch==' '||ch==10)//ASCLL码中10为换行符，此条件为遇到空格或火车则跳过
        {
            continue;
        }
        if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))                      //发现一个单词
        {
            K=0;
            t_word.count=1;
            while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
            {
                if(ch>='A'&&ch<='Z')
                {
                    ch+=32;//转换成小写
                }
                t_word.danci[K++]=ch;//把当前字母存入该单词的数组
                ch=getc(fp);
            }
            t_word.danci[K++]='\0';//补充结束标志
                                                                        //一个单词结束
            j=n;
            for(i=0;i<j;i++)//与前面的单词比较
            {
                if(strcmp(t_word.danci,word[i].danci)==0)//如果有单词相同
                {
                    word[i].count++;//则此类单词加1
                    break;
                }
            }
            if(n==0||i==j)//如果前面没有相同的单词
            {
                str[n]=t_word.danci;
                word[n]=t_word;//则为此类单词开辟新单元
                n++;
            }
            temp=t_word.danci;
            if(temp=="auto"||temp=="break"||temp=="case"||temp=="char"||temp=="const"||temp=="continue"||temp=="default"||temp=="do"
               ||temp=="double"||temp=="else"||temp=="enum"||temp=="extern"||temp=="float"||temp=="for"||temp=="goto"||temp=="if"
               ||temp=="int"||temp=="long"||temp=="register"||temp=="return"||temp=="short"||temp=="signed"||temp=="sizeof"||temp=="static"
               ||temp=="struct"||temp=="switch"||temp=="typedef"||temp=="union"||temp=="unsigned"||temp=="void"||temp=="volatile"||temp=="while")
            {
                keyword++;
                if(temp=="switch")
                {
                    flag=1;
                    switchnum++;
                }
                if(temp=="case"&&flag==1)
                {
                    switchelse[switchnum]++;
                }
                if(temp=="default"&&flag==1)
                {
                    flag=0;
                }
            }
        }
    }
    cout<<"total num: "<<keyword<<endl;
    cout<<"switch num: "<<switchnum<<endl;
    cout<<"case num:";
    for(i=1;i<=switchnum;i++)
    {
        cout<<" "<<switchelse[i];
    }
    /*for(i=0;i<n;i++)
    {
        cout<<word[i].danci<<" "<<word[i].count<<endl;
    }*/
    return 0;
}

