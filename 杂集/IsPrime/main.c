#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int IsPrime(int num)
{
    int i;
    if(num < 2)
        return 0;
    for(i = 2; i <= sqrt(num); i++)   //这里曾经写过i <= sqrt(num) + 1；但考虑到 2 的情况改了回来。其实只要保证另一边比取得大就行
    {
        if(num%i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int num;
    while(scanf("%d", &num) != EOF)
    {
        if(IsPrime(num) == 1)
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}
