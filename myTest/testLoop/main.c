#include <stdio.h>
#include <stdlib.h>

int main()
{



    int i=10;
    loopwwe:
    //命个名便于 goto 等调用
    {
        int hah;        //测试会不会是重定义  必须放到大括号内部
                        //a label can only be part of a statement and a declaration is not a statement
        printf("我在poop下面！！！\n");

    }

    int hah;   //swith loop 后面不要直接跟申明  但是隔一条语句是可以的
    if(i>0)
    {

        printf("loop%d生效了！！！\n",i);
        i--;
        goto loopwwe;

    }
    printf("Hello world!\n");
    return 0;
}
