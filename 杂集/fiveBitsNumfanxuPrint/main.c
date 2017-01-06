#include <stdio.h>
#include <stdlib.h>

int PrintNum(int num, int maxBit);

int main()
{
    int num, maxBit = 10;
    int bitNumFind;

    printf("Input your number:");
    scanf("%d", &num);
    printf("fanxuNum=");
    bitNumFind = PrintNum(num, maxBit);
    printf("\nbit=%d\n", bitNumFind);
    return 0;
}

int PrintNum(int num, int maxBit)
{
    int bitNumFind = maxBit;
    if(maxBit == 1)
    {
        printf("%d", num);
        return 1;
    }
    else
    {
        int fenmu = 1, i;
        for(i = 2; i <= maxBit; i++)
        {
            fenmu *= 10;
        }
        while(num/fenmu == 0)
        {
            fenmu /= 10;
            bitNumFind--;
        }
        PrintNum(num%fenmu, bitNumFind - 1);
        printf("%d", num/fenmu);
        return bitNumFind;
    }
}
