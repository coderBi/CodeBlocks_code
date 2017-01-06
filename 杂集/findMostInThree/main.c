#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x, y, z;
    printf("Input your three numbers:");
    scanf("%d %d %d", &x, &y, &z);
    if(x < y)
    {
        x ^= y;
        y ^= x;
        x ^= y;
    }
    if(x < z)
    {
        x ^= z;
        z ^= x;
        x ^= z;
    }
    printf("The max is:%d", x);
    return 0;
}
