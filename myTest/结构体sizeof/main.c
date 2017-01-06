#include <stdio.h>
#include <stdlib.h>

struct A{
 char c1, c2;
 long a1;
 short a2;
 int a3;
 int *a4;
 char c3;
 double d1;
};

int main()
{
    printf("sizeof struct A = %d\n", sizeof(struct A));
    printf("print the address of each member of A:\n");

    struct A s1;
    printf("&c1: %d\n", &s1.c1);
    printf("&c2: %d\n", &s1.c2);
    printf("&a1: %d\n", &s1.a1);
    printf("&a2: %d\n", &s1.a2);
    printf("&a3: %d\n", &s1.a3);
    printf("&a4: %d\n", &s1.a4);
    printf("&c3: %d\n", &s1.c3);

    printf("&d1: %d\n", &s1.d1);
    return 0;
}
