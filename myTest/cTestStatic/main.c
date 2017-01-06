#include <stdio.h>
#include <stdlib.h>


typedef struct
{

}myStruct;

int *test();

int main()
{
    printf("%d\n%x\n%c\n", *test(),test(),*test);
    return 0;
}



int *test()
{
static int num = 100;
int *ptr = &num;
return ptr;
}
