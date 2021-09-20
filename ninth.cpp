// 2021-2022�＾ѧ����ʵ����һ�θ��˱����ҵ
// Ŀ�꣺ʵ��һ�������ܣ������ԶԶ����C��C++�����ļ����в�ͬ�ȼ��Ĺؼ�����ȡ
// ����Ҫ������ؼ���ͳ����Ϣ
// ����Ҫ������м���switch case�ṹ��ͬʱ���ÿ���Ӧ��case����
// �θ�Ҫ������м���if else�ṹ
// �ռ�Ҫ������м���if��else if��else�ṹ
#include<bits/stdc++.h>
using namespace std;
// ��������
int ch;
// ��������
int keyword = 0, switch_else_num[100] = {0}, switch_num = 0, flag = 0;
// ��������
int if_else_count = 0, if_elseif_else_count = 0, flag2 = 0, flag3 = 0;
// ��������
string danci, mark;
// ��������
char fsm[7][256];
// ��������
FILE *pfin;
// ��������
stack <int> ifelse_stack;
void test1(string str)
{
	if (str == "auto" || str == "break" || str == "case" || str == "char"
    || str == "const" || str == "continue" || str == "default" || str == "do"
    || str == "double" || str == "else" || str == "enum" || str == "extern"
    || str == "float" || str == "for" || str == "goto" || str == "if"
    || str == "int" || str == "long" || str == "register" || str == "return"
    || str == "short" || str == "signed" || str == "sizeof" || str == "static"
    || str == "struct"|| str == "switch" || str == "typedef" || str == "union"
    || str == "unsigned" || str == "void" || str == "volatile" || str == "while")
    {
        keyword++;
        if (str == "switch")
        {
            flag = 1;
            switch_num++;
        }
        if (str == "case" && flag == 1)
        {
            switch_else_num[switch_num]++;
        }
        if (str == "default" && flag == 1)
        {
            flag = 0;
        }
        if (str == "if")
        {
            ifelse_stack.push(-1);
            ifelse_stack.push(1);
        }
        if (str == "else")
        {
            flag2 = 0;
            flag3 = 0;
            ch = fgetc(pfin);
            while (ch == ' ' || ch == 10)  // �����ո�ͻ��з�
            {
                ch = fgetc(pfin);
            }
            if (ch == 'i')
            {
                mark = "";
                mark += ch;
                ch = fgetc(pfin);
                mark += ch;
                if (mark == "if")
                {
                    keyword++;
                    ifelse_stack.push(-1);
                    ifelse_stack.push(1);
                    flag2 = 1;
                }
            }
            else
            {
                if (ch == '{')
                {
                    flag3 = 1;
                }
                if (ch == ' ' || ch == 10)
                {
                    flag2 = 1;
                }
            }
            if (flag2 == 0)
            {
                int ifelse_stack_count = 0;
                while (ifelse_stack.top() > 0 && !ifelse_stack.empty())
                {
                    ifelse_stack_count += ifelse_stack.top();
                    ifelse_stack.pop();
                }
                if (ifelse_stack_count > 1)
                {
                    if_elseif_else_count++;
                }
                else if (ifelse_stack_count == 1)
                {
                    if_else_count++;
                }
                if (flag3 == 1)
                {
                    ifelse_stack.push(0);
                }
            }
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
    int n = 0;
    int state = 0;
    int i, j;
    int level;
    char filename[100];
    gets(filename);
    cin>>level;
    if ((pfin=fopen(filename,"r"))==NULL)
    {
        cout << "�ļ��򿪴���";
        return 0;
    }
    initialize_fsm(fsm);
    while ((ch=fgetc(pfin)) != EOF)
    {
        state = fsm[state][ch];
        switch (state)
        {
            case 5:
            case 6:
            case 0:
            if (ch == '"')  // ����˫����
            {
                ch = fgetc(pfin);
                while (ch != '"')
                {
                    ch = fgetc(pfin);
                }
                continue;
            }
            if (ch == 39)  // ���Ե�����
            {
                ch = fgetc(pfin);
                while (ch != 39)
                {
                    ch = fgetc(pfin);
                }
                continue;
            }
            if (ch == ' ' || ch == 10)  // ���Կո�ͻ��з�
            {
                continue;
            }
            if (ch == '{')
            {
                ifelse_stack.push(0);
            }
            if (ch == '}')
            {
                while (ifelse_stack.top())
                {
                    ifelse_stack.pop();
                }
                ifelse_stack.pop();
            }
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))  // ����һ������
            {
                danci = "";
                while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')
                              || (ch == '_') || (ch == '/') || (ch == '.'))
                {
                    if (ch >= 'A' && ch <= 'Z')
                    {
                        ch += 32;  // ת����Сд
                    }
                    danci += ch;  // �ѵ�ǰ��ĸ����õ��ʵ�����
                    ch = fgetc(pfin);
                }  // һ�����ʽ���
                test1(danci);
            }
            case 7:
            state = 0;
            break;
        }
    }
    fclose(pfin);
    if(level >= 1)
    {
        cout << "total num: " << keyword << endl;
    }
    if(level >= 2)
    {
        cout << "switch num: " << switch_num << endl;
        cout << "case num:";
        if (switch_num == 0)
        {
            cout << " 0";
        }
        else
        {
            for (i = 1; i <= switch_num; i++)
            {
                cout << " " << switch_else_num[i];
            }
        }
        cout << endl;
    }
    if(level >= 3)
    {
        cout << "if-else num: " << if_else_count << endl;
    }
    if(level >= 4)
    {
        cout << "if-elseif-else num: " << if_elseif_else_count << endl;
    }
    return 0;
}

