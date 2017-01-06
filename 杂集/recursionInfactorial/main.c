#include <stdio.h>
#include <stdlib.h>

int GetRecursion(int num);

int main()
{
    int num = 5;
    printf("%d!=%d\n", num, GetRecursion(num));
    return 0;
}

int GetRecursion(int num)
{
    if(num == 1)
    {
        return 1;
    }
    else
    {
        return num*GetRecursion(num-1);
    }
}
