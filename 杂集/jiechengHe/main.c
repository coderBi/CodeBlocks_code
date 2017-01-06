#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sum = 0;
    int i;
    int num = 20;

    for(i = 1; i <= num; i++)
    {
        int j;
        int temp = 1;

        for(j = 1; j <= i; j++)
        {
            temp *= j;
        }
        sum += temp;
        if(i == num)
        {
            printf("%d!=", i);
        }
        else
        {
            printf("%d! + ", i);
        }
    }
    printf("%d\n",sum);
    //printf("%d\n", sizeof(int));
    return 0;
}
