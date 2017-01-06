#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct myStruct
    {
        int age;
        char sex;
    };

    printf("myStruct的大小是： %d\n\n",sizeof(struct myStruct));
    return 0;
}
