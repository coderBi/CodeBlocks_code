#include <stdio.h>
#include <stdlib.h>

int main()
{
    int dividend;
    int flag = 0;

    printf("Input your number:");
    scanf("%d", &dividend);

    /*判断一下被除数是哪一种情况*/
    if(dividend%3 == 0 && dividend%5 == 0)
    {
        flag = 35;
    }
    else if(dividend%3 == 0)
    {
        flag = 3;
    }
    else if(dividend%5 == 0)
    {
        flag = 5;
    }

    /*根据判断都表示flag数值进行打印输出*/
    switch(flag)
    {
        case 35 :
        printf("%d-->%d,%d", dividend, 3, 5);
        break;
        case 3 :
        printf("%d-->%d", dividend, 3);
        break;
        case 5 :
        printf("%d-->%d", dividend, 5);
        break;
        default:
        printf("%d-->None", dividend);
        break;
    }

    return 0;
}
