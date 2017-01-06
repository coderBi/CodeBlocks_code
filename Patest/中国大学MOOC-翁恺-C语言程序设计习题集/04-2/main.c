/**************************************************
这里的对其策略值得借鉴，即去最大输出宽度来打印所有输出
然后调整为左对齐即可
*****************************************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, i, j;
    scanf("%d", &N);
    for(i = 1; i <= N; i++)
    {
        for(j = 1; j <= i; j++)
        {
            printf("%d*%d=%-4d", j, i, j*i);
        }
        printf("\n");
    }
    return 0;
}
