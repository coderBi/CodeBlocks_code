#include <stdio.h>
#include "HeadFile.h"

//一个变量只能初始化一次
//int g_iVar2 = 0;
int g_iVar5;

void PrintGVarAddr(){
    printf("address = %u\n",(unsigned int)&g_iVar);
}
