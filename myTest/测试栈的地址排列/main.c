#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 0x1000ccff, b = 0x0100ddee;
    printf("%d %d\n", &a, &b);
    int c;
    printf("%d\n", &c);  //可以查看结果，后入栈的地址更小，也就是说栈顶更小

    int arr[5];
    printf("%d %d\n", &arr[0], &arr[1]);

    char * pChar = &a;
    printf("%d %d\n", pChar, *pChar);
    printf("%d %d\n", pChar + 1, *(pChar+1));
    return 0;
}
