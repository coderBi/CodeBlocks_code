#include <stdio.h>
#include <stdlib.h>

char*getmemory(void)
{
    char p[]="hello world";
    return p;
}

char*getmemory1(void)
{
    char* p ="hello world";
    return p;
}

int main()
{
    char *str=NULL;

    //这里打印的之所以是乱码，因为，函数内部char p[]，p指向的是函数内部的一片栈区，函数调用完成后栈区被释放了
    str=getmemory(); printf(str);
    printf("\n-------------------------------------\n");

    //这里依然可以得到正确打印结果，因为这里的char* p ="hello world";最终返回了一个常量区地址
    str=getmemory1(); printf(str);
    return 0;
}
