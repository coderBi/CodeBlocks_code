#include <stdio.h>
#include <stdlib.h>

char*getmemory(void)
{
    char p[]="hello world";
    return p;
}

char*getmemory1(void)
{
    char* p ="hello world";
    return p;
}

int main()
{
    char *str=NULL;

    //�����ӡ��֮���������룬��Ϊ�������ڲ�char p[]��pָ����Ǻ����ڲ���һƬջ��������������ɺ�ջ�����ͷ���
    str=getmemory(); printf(str);
    printf("\n-------------------------------------\n");

    //������Ȼ���Եõ���ȷ��ӡ�������Ϊ�����char* p ="hello world";���շ�����һ����������ַ
    str=getmemory1(); printf(str);
    return 0;
}
