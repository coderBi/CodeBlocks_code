#include <stdio.h>
#include <stdlib.h>

#define N 10

void SortNum(int num[], int length);
void PrintArr(int num[], int length);

int main()
{
    int num[N], i;

    printf("Inpur your %d numbers:\n", N);
    for(i = 0; i < N; i++)
    {
        scanf("%d", &num[i]);
    }
    SortNum(num, N);
    PrintArr(num, N);
    return 0;
}

void SortNum(int num[], int length)
{
    if(num == NULL)
    {
        printf("Null Array");
        return;
    }
    else
    {
        int i, j;

        for(i = 0; i < length; i++)
        {
            for(j = i + 1; j < length; j++)
            {
                if(num[i] > num[j])
                {
                    num[i] = num[i] ^ num[j];
                    num[j] = num[i] ^ num[j];
                    num[i] = num[i] ^ num[j];
                }
            }
        }
    }
    return;
}

void PrintArr(int num[], int length)
{
    if(num == NULL)
    {
    printf("Null Array");
    return;
    }
    else
    {
        int i, count = 0;
        for(i = 0; i < length; i++)
        {
            if(count != 0 && count%10 == 0)
            {
                printf("\n");
            }
            printf("%d  ", num[i]);
            count++;
        }
    }
}