#include<bits/stdc++.h>
using namespace std;

typedef struct
{
    char danci[19];//储存单词
    int count;//记录单词出现次数
}sq;

void initialize_fsm(char fsm[7][256]);
void Delete()//去除注释
{
    int cha, temp = 0;
    int state = 0;
    char fsm[7][256];
    FILE *pfin;
    if((pfin = fopen("D://c++//ex.c", "r"))==NULL)
    {
        printf("cannnot open the file");
        exit(0);
    }
    FILE *pfout;
    pfout=fopen("D://c++//result.txt", "w");
    initialize_fsm(fsm);
    while((cha = fgetc(pfin)) != EOF)
    {
        state = fsm[state][cha];
        temp = cha;
        switch(state)
        {
            case 5:
            case 6:
            case 0:
            fputc(cha, pfout);
            break;
            case 7:
            state = 0;
            break;
        }
    }
}
void initialize_fsm(char fsm[7][256])
{
    int lenth = sizeof(char) * 256;
    memset(fsm[0], 0, lenth);
    memset(fsm[1], 0, lenth);
    memset(fsm[2], 2, lenth);
    memset(fsm[3], 3, lenth);
    memset(fsm[4], 3, lenth);
    memset(fsm[5], 5, lenth);
    memset(fsm[6], 5, lenth);
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
    Delete();
    sq word[32];
    sq t_word;
    int K,n=0,i,j;
    FILE *fp;
    char ch;
    fp=fopen("D://c++//result.txt","r");//读取文件
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
                word[n]=t_word;//则为此类单词开辟新单元
                n++;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        cout<<setiosflags(ios::left)<<setw(10)<<word[i].danci<<word[i].count<<endl;//setw()设置输出域宽，默认右对齐
    }
    return 0;
}
