#include <stdio.h>
#include "HeadFile.h"

int g_iVar2 = 1;
static int g_iVar4 = 100;
int g_iVar5 = 12;
//int g_iVar5;

//����Ĭ��ȫ�ֿɼ���Ĭ��extern����
void Source1_PrintGVarAddr(){
    printf("address = %u\n",(unsigned int)&g_iVar);
}
