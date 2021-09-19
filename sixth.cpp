#include<bits/stdc++.h>
using namespace std;
#define M 20000

typedef struct
{
    char danci[19];//储存单词
}sq;

sq word[M];
sq t_word;
string str[M],temp;
int K,n=0,i,j,keyword=0,switchnum=0,switchelse[100],flag=0;
int if_else_count=0,if_elseif_else_count=0;
int ch,temp1=0;
int state=0;
char fsm[7][256];
stack<int> ifelse_stack;

void test1(string str)
{
	if(str=="auto"||str=="break"||str=="case"||str=="char"||str=="const"||str=="continue"||str=="default"||str=="do"
    ||str=="double"||str=="else"||str=="enum"||str=="extern"||str=="float"||str=="for"||str=="goto"||str=="if"
    ||str=="int"||str=="long"||str=="register"||str=="return"||str=="short"||str=="signed"||str=="sizeof"||str=="static"
    ||str=="struct"||str=="switch"||str=="typedef"||str=="union"||str=="unsigned"||str=="void"||str=="volatile"||str=="while")
    {
        keyword++;
        if(str=="switch")
        {
            flag=1;
            switchnum++;
        }
        if(str=="case"&&flag==1)
        {
            switchelse[switchnum]++;
        }
        if(str=="default"&&flag==1)
        {
            flag=0;
        }

        if(str=="if")
        {
            ifelse_stack.push(-1);
            ifelse_stack.push(1);
        }
        if(str=="else")
        {
            int ifelse_stack_count=0;
            while(ifelse_stack.top()>0&&!ifelse_stack.empty())
            {
                ifelse_stack_count+=ifelse_stack.top();
                ifelse_stack.pop();
            }
            if(ifelse_stack_count>1) if_elseif_else_count++;
            else if(ifelse_stack_count==1) if_else_count++;
        }

    }
}

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
    fsm[0]['"']=5;
    fsm[0]['/']=1;
    fsm[1]['/']=2;
    fsm[1]['*']=3;
    fsm[2]['\n']=7;
    fsm[3]['*']=4;
    fsm[4]['/']=7;
    fsm[5]['\\']=6;
    fsm[5]['"']=0;
}

int main()
{
    FILE *pfin;
    pfin=fopen("D://c++//wyf.cpp","r");//读取文件
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
            if(ch==' '||ch==10)//忽略空格和换行符
            {
                continue;
            }

            if(ch=='{')
            {
                ifelse_stack.push(0);
            }
            if(ch=='}')
            {
                while(ifelse_stack.top()) ifelse_stack.pop();
                ifelse_stack.pop();
            }

            if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))                      //发现一个单词
            {

                K=0;
                while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch=='_')||(ch=='/')||(ch=='.'))
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
                temp=t_word.danci;
                test1(temp);
            }
            case 7:
            state = 0;
            break;
        }
    }
    cout<<"total num: "<<keyword<<endl;
    cout<<"switch num: "<<switchnum<<endl;
    cout<<"case num:";
    if(switchnum==0)
    {
        cout<<" 0";
    }
    else
    {
        for(i=1;i<=switchnum;i++)
        {
            cout<<" "<<switchelse[i];
        }
    }
    cout<<endl;
    cout<<"if-else num: "<<if_else_count<<endl;
    cout<<"if-elseif-else num: "<<if_elseif_else_count<<endl;
    return 0;
}
