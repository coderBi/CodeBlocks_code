#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    freopen("stdin.txt","r",stdin);
    freopen("stdout.txt","a",stdout);
    char getStr[10];

    /*while(scanf("%s", getStr) == EOF){}
    printf("%s\n",getStr);*/

    while(scanf("%s", getStr) != EOF){
        printf("%s\n",getStr);
    }

    //Ҫ�벻��ʾ����̨���ڣ���codeblocks����ֻ��Ҫ��project��������build target��������Ϊgui���������
    //ShowWindow(GetStdHandle(STD_OUTPUT_HANDLE),SW_HIDE);
    return 0;
}
