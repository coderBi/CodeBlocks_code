#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a=1;
    int b;
    b=(++a)+(a++);     //���ƺ����ȼ�  �Ĵ����洢�������ؼ��ɡ�������datalock
    printf("b=  %d\n",b);
    printf("a=  %d\n",a);
    return 0;
}
