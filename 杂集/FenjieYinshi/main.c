#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number;
    int i;

    printf("Input your number:");
    scanf("%d", &number);
    printf("The result is:%d=", number);
    for(i = 2; i <= number; i++)
    {
        if(number == i)
        {
            printf("%d", i);
            break;
        }

        while(number%i == 0)
        {
            printf("%d*", i);
            number = number/i;
        }

        /*����һ������պó�������*/
        if(number == 1)
        {
            printf("%d", number);
        }
    }
    return 0;
}
