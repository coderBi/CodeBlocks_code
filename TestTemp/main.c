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
    printf("%10.3d", 21);  //宽度与精度设置：       021
}

void test11(){
    int a = 2147483648, b = 2147483648; //这里其实由于进位的关系 2^31 都成了-2^31
    printf("%d %d %d\n", a, b, a + b);
}

//可以发现如果只对数组的第一个元素初始化，后面的元素会被默认跟第一个元素一样的初始化
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

void test9() //对比了一下java， java里面d = 1.10 - 1.0; 结果是0.10000000000000009。进一步了解到java中float double运算要用BigDecimal解决精度丢失问题
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

void test7()  //这里测试浮点数打印可能会出现-0.0的情况
{
    float f = -0.04;
    printf("%.1f", f);
}

void test6()
{
    const int a;  //必须要初始化，没有人为操作，结果初始化成了一个不能改变的垃圾值
    //a = 100;
    printf("%d", a);
}

void test5() //发现可能是编译器处理问题，这里的数组名称在申明的时候被处理成了指针，但是按照C/C++规范 栈上开辟数组是不能用（非常）变量给定大小的
{
    int a;
    scanf("%d", &a);
    const int b = a;
    int arr[b];
    printf("%d %d %d %d %d", arr[0], arr[1], arr[2], arr[3], arr[4]);
}

void test4()  //测试数组能否用变量来初始化长度
{
    int a = 5;
    int arr[a];
}

void test3()//用于与test2对比
{
    int arr[5] = {0};
    printf("%d %d %d %d %d", arr[0], arr[1], arr[2], arr[3], arr[4]);
}

void test2()  //验证C的默认初始化，这里开辟内存不初始化，里面存放的是垃圾值（之前剩下来的）
{
    int arr[5];
    printf("%d %d %d %d %d", arr[0], arr[1], arr[2], arr[3], arr[4]);
}

void test1() // 验证fflush的作用
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
