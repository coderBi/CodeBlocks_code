#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    scanf("%d",&a);
    int b = 3;
    switch(a){
    case 1:
        //int b = 3; //���ﲻ���Խ����±����Ķ��壬��Ϊ���մ�����߼�����������b����������һֱ��switch����
                    //���ǲ�ͬswitch֮�����ǻ���ģ����������b�ĳ�ʼ�������case���ղ���
                    //�����Ҫ����ʹ�ã����Կ��ǽ��õ��ֲ������Ĳ���ȫ����{}����������������һ���µĴ���飬���Ʊ�����������
        printf("a + b= %d\n", a + b);
        break;
    case 2:
        printf("a = %d\n", a);
        break;
    default:
        printf("������δ�����ֵ\n");
        break;
    }
    return 0;
}
