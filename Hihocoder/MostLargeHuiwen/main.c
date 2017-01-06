#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

int JudgeStrIsHw(char* str);

int main()
{
    char str[MAX_SIZE];
    char str1[MAX_SIZE];
    int length;
    int i, j;

    strcpy(str1, "\0");
    printf("Input your string:");
    scanf("%s", str);
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
                strcpy(str1, temp);
                goto loop1;
            }
        }
        length--;
    }

    loop1:
    printf("length=%d\nstring=%s", length, str1);
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
