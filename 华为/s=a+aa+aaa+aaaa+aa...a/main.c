#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, m;
    int sum = 0;
    int i ,temp;
    i = 0;

    printf("Input \"a\" and \"m\":");
    scanf("%d %d", &a, &m);
    while(i <= m)
    {
        if(m == 0)
        {
            printf("0");
        }
        if(i == 0)
        {
            temp = sum = 0;

        }
        else if(i == 1)
        {
            temp = sum = a;
            printf("%d", a);
        }
        else
        {
            sum += temp*10 + a;
            temp = temp*10 + a;
            printf("+%d", temp);
        }
        i++;
    }
    printf("=%d", sum);
    return 0;
}
