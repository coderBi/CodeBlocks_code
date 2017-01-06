#ifndef _HEADER_FILE_H_
#define _HEADER_FILE_H_

int g_iVar;

//造成了一个全局变量被多次初始化的错误
//int g_iVar1 = 1;
int g_iVar2;

//static 变量可以在头文件初始化,这个时候，其实引用的每一个源文件中都分配了一个只属于自己的static变量
static int g_iVar3 = 99;

#endif // _HEADER_FILE_H_
