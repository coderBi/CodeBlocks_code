#include <stdio.h>
#include <stdlib.h>

int main()
{
    int dividend;
    int flag = 0;

    printf("Input your number:");
    scanf("%d", &dividend);

    /*�ж�һ�±���������һ�����*/
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

    /*�����ж϶���ʾflag��ֵ���д�ӡ���*/
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
