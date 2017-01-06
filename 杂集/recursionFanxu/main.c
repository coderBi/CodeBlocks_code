#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintChar(char* ptr);

int main()
{
    int num;
    char* ptr = NULL;

    printf("Input how much numbers your want:");
    scanf("%d",&num);
    ptr = (char*)malloc(sizeof(char)*(num+1));
    printf("Input your string:");
    scanf("%s", ptr);
    PrintChar(ptr);
    //printf("%d  %d\n", num, strlen(ptr));
    free(ptr);
    return 0;
}

void PrintChar(char* ptr)
{
    if(ptr == NULL)
    {
        printf("NULL pointer");
        return;
    }
    else
    {
        int length = strlen(ptr);
        if(length > 0)
        {
            printf("%c", ptr[length-1]);
            //strncpy(ptr, ptr, length - 1);
            //strcat(ptr);

            /*修改最后一个为结束标志 这样下一次length就减少1了*/
            ptr[length-1] = '\0';
            PrintChar(ptr);
        }

    }
}
