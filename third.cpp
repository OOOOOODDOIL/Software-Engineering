#include<bits/stdc++.h>
using namespace std;
#define M 20000

typedef struct
{
    char danci[19];//���浥��
    int count;//��¼���ʳ��ִ���
}sq;

int main()
{
    sq word[32];
    sq t_word;
    string str[M],temp;
    int K,n=0,i,j,keyword=0,switchnum=0,switchelse[100],flag=0;
    FILE *fp;
    char ch;
    fp=fopen("D://c++//ex.c","r");//��ȡ�ļ�
    while(!feof(fp))//feof()����Ƿ�ﵽ�ļ�β��
    {

        ch=getc(fp);//��ȡ��ǰ�ַ�
        if(ch==' '||ch==10)//ASCLL����10Ϊ���з���������Ϊ�����ո���������
        {
            continue;
        }
        if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))                      //����һ������
        {
            K=0;
            t_word.count=1;
            while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
            {
                if(ch>='A'&&ch<='Z')
                {
                    ch+=32;//ת����Сд
                }
                t_word.danci[K++]=ch;//�ѵ�ǰ��ĸ����õ��ʵ�����
                ch=getc(fp);
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

