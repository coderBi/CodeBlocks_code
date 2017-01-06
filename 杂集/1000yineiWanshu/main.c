#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    int sum, count = 0;

    for(i = 1; i <= 1000; i++)
    {
        int temp;
        sum = 0;
        for(temp = 1; temp < i; temp++)
        {
            if(i%temp == 0)
            {
                sum += temp;
            }
        }
        if(sum == i)
        {
            if(count != 0 && count%10 == 0)
            {
                printf("\n");
            }
            printf("%d  ", i);
            count++;
        }
    }
    printf("\ncount=%d\n",count);
    return 0;
}
