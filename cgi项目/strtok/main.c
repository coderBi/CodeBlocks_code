#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char str[] = "c:/web/upload/a.txt";
    char *str1 ="c:/web";
    char *res = strtok(str,str1);
    while(res != NULL){
        printf("%s\n",res);
        res = strtok(NULL,str1);
    }
    return 0;
}
