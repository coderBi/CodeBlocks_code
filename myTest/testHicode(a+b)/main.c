#include <stdio.h>

int getSum(int a,int b)
{
    return a+b;
}

int main()
{
    int a,b;
    printf("Please input your numbers:");
    while(scanf("%d %d",&a,&b)!=EOF)
    {
        printf("%d\n",getSum(a,b));
        printf("Please input your numbers:");
    }


    return 0;
}
