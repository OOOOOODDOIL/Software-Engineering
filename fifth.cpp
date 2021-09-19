#include<bits/stdc++.h>
using namespace std;
#define M 20000

typedef struct
{
    char danci[19];//储存单词
    int count;//记录单词出现次数
}sq;

void initialize_fsm(char fsm[7][256])
{
    int lenth=sizeof(char) * 256;
    memset(fsm[0],0,lenth);
    memset(fsm[1],0,lenth);
    memset(fsm[2],2,lenth);
    memset(fsm[3],3,lenth);
    memset(fsm[4],3,lenth);
    memset(fsm[5],5,lenth);
    memset(fsm[6],5,lenth);
    fsm[0]['"'] = 5;
    fsm[0]['/'] = 1;
    fsm[1]['/'] = 2;
    fsm[1]['*'] = 3;
    fsm[2]['\n'] = 7;
    fsm[3]['*'] = 4;
    fsm[4]['/'] = 7;
    fsm[5]['\\'] = 6;
    fsm[5]['"'] = 0;
}

int main()
{
    sq word[M];
    sq t_word;
    string str[M],temp;
    int K,n=0,i,j,keyword=0,switchnum=0,switchelse[100],flag=0;
    int ch,temp1 = 0;
    int state = 0;
    char fsm[7][256];
    FILE *pfin;
    pfin=fopen("文件路径","r");//读取文件
    initialize_fsm(fsm);
    while((ch=fgetc(pfin))!= EOF)
    {
        state=fsm[state][ch];
        temp1=ch;
        switch(state)
        {
            case 5:
            case 6:
            case 0:
            if(ch=='"')//忽略双引号
            {
                ch=fgetc(pfin);
                while(ch!='"')
                {
                    ch=fgetc(pfin);
                }
                continue;
            }
            if(ch==39)//忽略单引号
            {
                ch=fgetc(pfin);
                while(ch!=39)
                {
                    ch=fgetc(pfin);
                }
                continue;
            }
            if(ch==' '||ch==10)//ASCLL码中10为换行符，此条件为遇到空格或火车则跳过
            {
                continue;
            }
            if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))                      //发现一个单词
            {

                K=0;
                t_word.count=1;
                while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch=='_'))
                {
                    if(ch>='A'&&ch<='Z')
                    {
                        ch+=32;//转换成小写
                    }
                    t_word.danci[K++]=ch;//把当前字母存入该单词的数组
                    ch=fgetc(pfin);
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
            case 7:
            state = 0;
            break;
        }
    }
    cout<<"total num: "<<keyword<<endl;
    cout<<"switch num: "<<switchnum<<endl;
    cout<<"case num:";
    for(i=1;i<=switchnum;i++)
    {
        cout<<" "<<switchelse[i];
    }

    cout<<endl;
    for(i=0;i<n;i++)
    {
        cout<<word[i].danci<<" "<<word[i].count<<endl;
    }

    return 0;
}
