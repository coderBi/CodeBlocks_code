#include <stdio.h>
#include <stdlib.h>

#define Add(a,b) ((a) + (b))

int main()
{
    //调用用宏定义的函数
    printf("1 + 1 = %d\n", Add(1,1));
    return 0;
}
