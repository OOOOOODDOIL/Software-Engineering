#include<bits/stdc++.h>
using namespace std;
#define M 20000

typedef struct
{
    char danci[19];//���浥��
    int count;//��¼���ʳ��ִ���
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
    pfin=fopen("�ļ�·��","r");//��ȡ�ļ�
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
            if(ch=='"')//����˫����
            {
                ch=fgetc(pfin);
                while(ch!='"')
                {
                    ch=fgetc(pfin);
                }
                continue;
            }
            if(ch==39)//���Ե�����
            {
                ch=fgetc(pfin);
                while(ch!=39)
                {
                    ch=fgetc(pfin);
                }
                continue;
            }
            if(ch==' '||ch==10)//ASCLL����10Ϊ���з���������Ϊ�����ո���������
            {
                continue;
            }
            if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))                      //����һ������
            {

                K=0;
                t_word.count=1;
                while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch=='_'))
                {
                    if(ch>='A'&&ch<='Z')
                    {
                        ch+=32;//ת����Сд
                    }
                    t_word.danci[K++]=ch;//�ѵ�ǰ��ĸ����õ��ʵ�����
                    ch=fgetc(pfin);
                }
                t_word.danci[K++]='\0';//���������־
                                                                        //һ�����ʽ���
                j=n;
                for(i=0;i<j;i++)//��ǰ��ĵ��ʱȽ�
                {
                    if(strcmp(t_word.danci,word[i].danci)==0)//����е�����ͬ
                    {
                        word[i].count++;//����൥�ʼ�1
                        break;
                    }
                }
                if(n==0||i==j)//���ǰ��û����ͬ�ĵ���
                {
                    str[n]=t_word.danci;
                    word[n]=t_word;//��Ϊ���൥�ʿ����µ�Ԫ
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
