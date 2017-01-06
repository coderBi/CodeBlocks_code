#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

bool JudgeStrIsHw(char* str);

int main()
{
    char str[MAX_SIZE];
    bool res;

    printf("Input your string:");
    scanf("%s", str);
    res = JudgeStrIsHw(str);
    (res == true) ? printf("true\n") : printf("false\n");
    return 0;
}

bool JudgeStrIsHw(char* str)
{
    int mid;
    int length = strlen(str);
    int i;

    mid = length/2;
    for(i = 0; i <= mid; i++)
    {
        if(str[i] != str[length - i -1])
        {
            return false;
        }
    }
    return true;
}
