#include <stdio.h>
#include <stdlib.h>

int IsPrimeNum(int num);

int main()
{
    int i, count = 0;

    for(i = 1; i < 100; i++)
    {
        int res;

        res = IsPrimeNum(i);
        if(res > 0)
        {
            if(count != 0 && count%10 == 0)
            {
                printf("\n");
            }
            printf("%d  ", res);
            count++;
        }
    }
    printf("\ncount=%d", count);
    return 0;
}

int IsPrimeNum(int num)
{
    int i;
    if(num < 0)
    {
        return -2;
    }
    else if(num == 0 || num == 1)
    {
        return -1;
    }
    else
    {
        for(i = 2; i < num; i++)
        {
            if(num%i == 0)
            {
                return 0;
            }
        }
        return num;
    }
}
