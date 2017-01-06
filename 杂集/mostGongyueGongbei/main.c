#include <stdio.h>
#include <stdlib.h>

int GetMaxGongyue(int m, int n);

int main()
{
    int m, n;
    int maxGongyue, minGongbei;

    printf("Input your two numbers:\n");
    scanf("%d %d", &m, &n);
    maxGongyue = GetMaxGongyue(m, n);
    minGongbei = m*n/maxGongyue;
    printf("maxGongyue=%d   minGongbei=%d\n", maxGongyue, minGongbei);

    return 0;
}

int GetMaxGongyue(int m, int n)
{
    /*让m始终保存较大者*/
    if(m < n)
    {
        m = m + n;
        n = m - n;
        m = m - n;
    }
    while(m%n != 0)
    {
        int temp = m%n;
        m = n;
        n = temp;
    }
    return n;
}
