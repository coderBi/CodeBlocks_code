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

    //要想不显示控制台窗口，在codeblocks里面只需要把project属性里面build target里面设置为gui程序就行了
    //ShowWindow(GetStdHandle(STD_OUTPUT_HANDLE),SW_HIDE);
    return 0;
}
