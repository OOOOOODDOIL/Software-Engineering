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
    sq word[M];
    sq t_word;
    int K,n=0,i,j;
    FILE *fp;
    char ch;
    fp=fopen("D://c++//ex.c","r");//��ȡ�ļ������Ϊ��Ҫ��ȡ���ļ��ľ���·��
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
                word[n]=t_word;//��Ϊ���൥�ʿ����µ�Ԫ
                n++;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        cout<<setiosflags(ios::left)<<setw(10)<<word[i].danci<<word[i].count<<endl;//setw()����������Ĭ���Ҷ���
    }
    return 0;
}
