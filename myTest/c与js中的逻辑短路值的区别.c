#include <stdio.h>

int main(){
    int a = 5, b = 1, c = 0;
    printf("a || ba: %d\n", a||b);  //c c++里面的逻辑运算返回的只能是false  或者true  也就是要么是0 要么是1
    printf("a && b: %d\n", a&&b);
    printf("a || c: %d\n", a||c);
    return 0;
}
