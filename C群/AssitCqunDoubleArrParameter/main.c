#include <stdio.h>
#include <stdlib.h>

#define m 3
#define n 3

void PrintArr(int a[m][n]);
void p(int a[3][3]);

int main()
{
    int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    p(a);
    return 0;
}

void PrintArr(int a[m][n])
{
    int i, j;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%d", a[i][j]);
        }
    }
}

void p(int a[3][3])
{
    int i, j, k, s, r, flag;

    for(i = 0; i < m; i++)
    {
        flag = 0;

        for(j = 0, s = 0, r = a[i][0]; j < n; j++)
        {
            if(a[i][j] < r)
            {
                r = a[i][j];
                s = j;
            }
        }
        for(k = 0; k < m; k++)
        {
            if(a[s][k] < r)
            {
                flag = 1;
                break;
            }
        }
        if(flag)
        {
            continue;
        }
        printf("A=[%d,%d]\n", i, s);
    }
}
