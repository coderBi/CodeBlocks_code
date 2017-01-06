#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a=1;
    int b;
    b=(++a)+(a++);     //控制好优先级  寄存器存储分析过关即可。不存在datalock
    printf("b=  %d\n",b);
    printf("a=  %d\n",a);
    return 0;
}
