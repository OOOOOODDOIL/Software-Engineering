#include<bits/stdc++.h>
using namespace std;

typedef struct
{
    char danci[19];//���浥��
    int count;//��¼���ʳ��ִ���
}sq;

void initialize_fsm(char fsm[7][256]);
void Delete()//ȥ��ע��
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
    fp=fopen("D://c++//result.txt","r");//��ȡ�ļ�
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
