#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <windows.h>
#include "HeadFile.h"

extern int g_iVar2;
extern int g_iVar3;
extern int g_iVar4;

//���ﱻ������Ҳ���������ɹ����У���������ڶ���֮�ⶼ��extern����
int g_iVar5;
extern void PrintGVarAddr();
extern void Source1_PrintGVarAddr();

int main()
{
    PrintGVarAddr();
    Source1_PrintGVarAddr();
    printf("g_iVar2 = %d\n",g_iVar2);
    printf("g_iVar3 = %d\n",g_iVar3);

    //����g_iVar4 ��static���� �������䱾��ֻ��������Ӧ��Դ�ļ��ɼ������������g_iVar4��δ�����
    //printf("g_iVar4 = %d\n",g_iVar4);
    printf("g_iVar5 = %d\n",g_iVar5);

    return 0;
}
