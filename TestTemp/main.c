#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Data{
    int x;
    int y;
};

int main()
{
    printf("%d", test13());
    return 0;
}

int test13() {
    int a = 1, b = 2;
    return a + b;
}

void test12() {
    printf("%10.3d", 21);  //����뾫�����ã�       021
}

void test11(){
    int a = 2147483648, b = 2147483648; //������ʵ���ڽ�λ�Ĺ�ϵ 2^31 ������-2^31
    printf("%d %d %d\n", a, b, a + b);
}

//���Է������ֻ������ĵ�һ��Ԫ�س�ʼ���������Ԫ�ػᱻĬ�ϸ���һ��Ԫ��һ���ĳ�ʼ��
void test10(){
    struct Data arr[10] = {{0, 0}};
    struct Data arr1[10];
    int i;
    for(i = 0; i < 10; i++){
        printf("%d %d\n", arr[i].x, arr[i].y);
    }
    printf("\n\n");
    for(i = 0; i < 10; i++){
        printf("%d %d\n", arr1[i].x, arr[i].y);
    }
    return;
}

void test9() //�Ա���һ��java�� java����d = 1.10 - 1.0; �����0.10000000000000009����һ���˽⵽java��float double����Ҫ��BigDecimal������ȶ�ʧ����
{
    double d = 1.10 - 1.0;
    printf("%lf", d);
}

void test8()
{
    double d1 = (double)110/100 - 1.0;
    double d2 = 110.0/100 - 1.0;
    double d3 = 110.0/100.0 - 1.0;
    double d4 = 110.0/100.0;
    printf("d1 = %lf, d2 = %lf, d3 = %lf, d4 = %lf", d1, d2, d3, d4);
}

void test7()  //������Ը�������ӡ���ܻ����-0.0�����
{
    float f = -0.04;
    printf("%.1f", f);
}

void test6()
{
    const int a;  //����Ҫ��ʼ����û����Ϊ�����������ʼ������һ�����ܸı������ֵ
    //a = 100;
    printf("%d", a);
}

void test5() //���ֿ����Ǳ������������⣬���������������������ʱ�򱻴������ָ�룬���ǰ���C/C++�淶 ջ�Ͽ��������ǲ����ã��ǳ�������������С��
{
    int a;
    scanf("%d", &a);
    const int b = a;
    int arr[b];
    printf("%d %d %d %d %d", arr[0], arr[1], arr[2], arr[3], arr[4]);
}

void test4()  //���������ܷ��ñ�������ʼ������
{
    int a = 5;
    int arr[a];
}

void test3()//������test2�Ա�
{
    int arr[5] = {0};
    printf("%d %d %d %d %d", arr[0], arr[1], arr[2], arr[3], arr[4]);
}

void test2()  //��֤C��Ĭ�ϳ�ʼ�������￪���ڴ治��ʼ���������ŵ�������ֵ��֮ǰʣ�����ģ�
{
    int arr[5];
    printf("%d %d %d %d %d", arr[0], arr[1], arr[2], arr[3], arr[4]);
}

void test1() // ��֤fflush������
{
    char arr[10];
    int num;
    int i = 0;
    scanf("%d", &num);
    while(i < 5)
    {
        fflush(stdin);
        scanf("%c %d", &arr[i], &num);
        printf("%c, %d\n", arr[i], num);
        i++;
    }

}
