#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 10*10*10*10*10*10
#define N 30

int JudgeStrIsHw(char* str);
int GetLength(char* str);

int main()
{
    char str[MAX_SIZE];
    int res[N], num;
    int i;

    scanf("%d", &num);
    for(i = 0; i < num; i++)
    {
        scanf("%s", str);
        //gets(str);  /*会将数字后面的换行当作一个空字符读入第一个字符串*/
        res[i] = GetLength(str);
    }
    for(i = 0; i < num; i++)
    {
        printf("%d\n", res[i]);
    }
    return 0;
}

int JudgeStrIsHw(char* str)
{
    int mid;
    int length = strlen(str);
    int i;

    mid = length/2;
    for(i = 0; i <= mid; i++)
    {
        if(str[i] != str[length - i -1])
        {
            return 0;
        }
    }
    return 1;
}

int GetLength(char* str)
{
    int length;
    int i, j;

    length = strlen(str);

    while(length != 0)
    {
        i = strlen(str) - length;
        char temp[length + 1];

        for(j = 0; j <= i; j++)
        {
            strncpy(temp, str + j, length);
            temp[length] = '\0';
            if(1 == JudgeStrIsHw(temp))
            {
                goto loop1;
            }
        }
        length--;
    }

    loop1:
    return length;
}
