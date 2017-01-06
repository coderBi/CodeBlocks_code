/****************************************
两队队员配对问题 要用数字表达才行
这里我将第一对三个队员编号为 10，20，30
第二对编号为 1，2，3 这样每一种配对二者编号
相加出现不同的表示
****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* GetCast(int pei);

int main()
{
    int x = 10, y = 20, z = 30;
    int a, b, c;
    int xPei, yPei, zPei;

    for(a = 1; a <= 3; a++)
    {
        xPei = x + a;
        for(b = 1; b <= 3; b++)
        {
            if(a == b)
            {
                continue;
            }
            yPei = y + b;
            for(c = 1; c <= 3; c++)
            {
                if(c == a || c == b)
                {
                    continue;
                }
                zPei = z + c;
                if(xPei != 11 && zPei != 31 && zPei != 33)
                {
                    char* ptrx;
                    char* ptry;
                    char* ptrz;

                    ptrx = GetCast(xPei);
                    ptry = GetCast(yPei);
                    ptrz = GetCast(zPei);
                    printf("managed find:%d %d  %d\n", xPei, yPei, zPei);
                    printf("cast group:%s   %s   %s\n", ptrx, ptry, ptrz);
                    free(ptrx);
                    free(ptry);
                    free(ptrz);
                }
            }
        }
    }
    return 0;
}

char* GetCast(int pei)
{
    char* ptr=(char*)malloc(sizeof(char)*10);
    if(pei/10 == 1)
    {
        ptr = strcpy(ptr, "x-");
    }
    else if(pei/10 == 2)
    {
        ptr = strcpy(ptr, "y-");
    }
    else if(pei/10 == 3)
    {
        ptr = strcpy(ptr, "z-");
    }

    if(pei%10 == 1)
    {
        ptr = strcat(ptr, "a");
    }
    else if(pei%10 == 2)
    {
        ptr = strcat(ptr, "b");
    }
     else if(pei%10 == 3)
    {
        ptr = strcat(ptr, "c");
    }
    return ptr;

}
