#include <stdio.h>
#include <stdlib.h>

#define DAYS 9   /*days����9 ��ζ�ŵ�ʮ��׼���Է���ֻ��һ��*/

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
