#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct myStruct
    {
        int age;
        char sex;
    };

    printf("myStruct�Ĵ�С�ǣ� %d\n\n",sizeof(struct myStruct));
    return 0;
}
