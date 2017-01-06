#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <windows.h>
#include "HeadFile.h"

extern int g_iVar2;
extern int g_iVar3;
extern int g_iVar4;

//这里被解析成也是申明，成功运行，但是最好在定义之外都用extern修饰
int g_iVar5;
extern void PrintGVarAddr();
extern void Source1_PrintGVarAddr();

int main()
{
    PrintGVarAddr();
    Source1_PrintGVarAddr();
    printf("g_iVar2 = %d\n",g_iVar2);
    printf("g_iVar3 = %d\n",g_iVar3);

    //由于g_iVar4 被static修饰 ，所以其本身只能在其相应的源文件可见，所以这里的g_iVar4是未定义的
    //printf("g_iVar4 = %d\n",g_iVar4);
    printf("g_iVar5 = %d\n",g_iVar5);

    return 0;
}
