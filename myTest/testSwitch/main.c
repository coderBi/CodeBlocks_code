#include <stdio.h>
#include <stdlib.h>

int main()
{
    float a;
    scanf("%f",a);


    switch(a)    //ֻ��int char short  long  byte  ö��
    {
        case 1:
            printf("case1:%f\n",a);

        case 2:
            printf("case2:%f\n",a);

        case 3:
            printf("case3:%f\n",a);
    }
    return 0;
}
