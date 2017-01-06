#include <stdio.h>
#include <stdlib.h>

/* m onday t uesday w ednesday t hursday f riday s aturday s unday */

int GetXingqi();
void PrintXingqi(int res);

int main()
{
    char ch;
    do
    {
        int res;

        res = GetXingqi();
        PrintXingqi(res);
        printf("continue?\nY: yes   N: no\n");

        /*此程序中多次刷新输入缓冲区 避免前后输入彼此影响*/
        fflush(stdin);
        scanf("%c", &ch);
    }while(ch == 'Y');
    return 0;
}

int GetXingqi()
{
    int res = 0;
    char ch;

    fflush(stdin);
    printf("Input first char:");
    scanf("%c", &ch);
    switch(ch)
    {
        case 'm': res = 1;
        break;
        case 't':
        {
            printf("Input second char:");
            fflush(stdin);
            scanf("%c", &ch);
            if(ch == 'u')
            {
                res = 2;
            }
            else if(ch == 'h')
            {
                res = 4;
            }
        }
        break;
        case 'w': res = 3;
        break;
        case 'f': res = 5;
        break;
        case 's':
        {
            printf("Input second char:");
            fflush(stdin);
            scanf("%c", &ch);
            if(ch == 'a')
            {
                res = 6;
            }
            else if(ch == 'u')
            {
                res = 7;
            }
        }
        break;
        default : break;
    } /*switch 结束*/
    return res;
}

void PrintXingqi(int res)
{
    switch(res)
    {
        case 0: printf("No such day!\n");
        break;
        case 1: printf("Monday\n");
        break;
        case 2: printf("Tuesday\n");
        break;
        case 3: printf("Wednesday\n");
        break;
        case 4: printf("Thursday\n");
        break;
        case 5: printf("Friday\n");
        break;
        case 6: printf("Saturday\n");
        break;
        case 7: printf("Sunday\n");
        break;
        default : break;
    }
}
