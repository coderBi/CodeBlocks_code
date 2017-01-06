#include <stdio.h>
#include <stdlib.h>

int GetFanxu(int num, int bit);

int main()
{
    int num, bit;
    int res;

    printf("Input how much bits your want:");
    scanf("%d", &bit);
    printf("Input your number:");
    scanf("%d", &num);
    res = GetFanxu(num, bit);

    //printf("res=%d\n", res);
    if(res == num)
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
    return 0;
}

int GetFanxu(int num, int bit)
{
    int res = 0;
    if(bit <= 0)
    {
        return -1;
    }
    else
    {
        int temp1 = 1, temp2 = 1, i;

        for(i = 2; i <= bit; i++)
        {
            temp1 *= 10;
        }
        while(num != 0)
        {
            res += temp2 * (num/temp1); /*这里必须将num/temp1括起来 否则先*了就会扩大数值*/
            num = num%temp1;
            temp1 /= 10;
            temp2 *= 10;
        }
        return res;
    }
}
