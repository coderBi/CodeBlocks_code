#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    scanf("%d",&a);
    int b = 3;
    switch(a){
    case 1:
        //int b = 3; //这里不可以进行新变量的定义，因为按照代码块逻辑这里申明的b的作用区域一直到switch结束
                    //可是不同switch之间又是互斥的，所以这里对b的初始化后面的case又收不到
                    //如果非要这样使用，可以考虑将用到局部变量的部分全部用{}包起来，这样构成一个新的代码块，限制变量的作用域
        printf("a + b= %d\n", a + b);
        break;
    case 2:
        printf("a = %d\n", a);
        break;
    default:
        printf("输入了未处理的值\n");
        break;
    }
    return 0;
}
