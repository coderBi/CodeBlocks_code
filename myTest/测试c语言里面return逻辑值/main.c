#include <stdio.h>
#include <stdlib.h>

int getLogical(int a, int b){ //c里面没有bool，只能用int返回。经过测试，c里面返回逻辑值就是 0 跟 1
    return a > b;
}

int main()
{
    int a, b;
    while(scanf("%d%d", &a, &b) == 2){
        printf("%d\n", getLogical(a, b));
    }

    return 0;
}
