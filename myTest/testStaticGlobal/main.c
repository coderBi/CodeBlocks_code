#include <stdio.h>
#include <stdlib.h>

#include "test.h"

int main()
{
    test();
    global=5;
    printf("main global:  %d\n",global);
    return 0;
}
