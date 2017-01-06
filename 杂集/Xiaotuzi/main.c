#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i = 1;
    int j = 1, temp;
    int month;

    printf("Please input the month:");
    scanf("%d", &month);
    if(month <= 2)
    {
        printf("%d", i);
    }
    else
    {
        for(temp = 3; temp <= month; temp++)
        {
            j = j + i;
            i = j - i;  /* 这里将j和i都后移一个月，j作为最新值存在*/
        }
        printf("%d", j);
    }
    return 0;
}
