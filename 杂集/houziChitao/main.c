#include <stdio.h>
#include <stdlib.h>

#define DAYS 9   /*days设置9 意味着第十天准备吃发现只有一个*/

int main()
{
    int i, sum = 1;
    for(i = 1; i <= DAYS; i++)
    {
        sum = 2*(sum + 1);
    }
    printf("day=%d  sum=%d\n", DAYS, sum);
    return 0;
}
