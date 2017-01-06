#include <stdio.h>
#include <stdlib.h>

int main()
{
    int grade;

    printf("Input the grade:");
    scanf("%d", &grade);

    if(grade > 100 || grade < 0)
    {
        printf("error");
    }
    else if(grade > 90)
    {
        printf("the result is: A");
    }
    else if(grade > 60)
    {
        printf("the result is: B");
    }
    else
    {
        printf("the result is: C");
    }
    return 0;
}
