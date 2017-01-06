#include <stdio.h>
#include <stdlib.h>

int GetAge(int num, int age1);

int main()
{
    int num = 5;
    int age, age1 = 10;

    age = GetAge(num, age1);
    printf("age1=%d  num=%d  age=%d\n", age1, num, age);
    return 0;
}

int GetAge(int num, int age1)
{
    int age = 0;

    if(num == 1)
    {
        age = age1;
    }
    else if(num > 1)
    {
        age = 2 + GetAge(num - 1, age1);
    }
    return age;
}
