/*
    1，这里尽管通过了测试，但是代码不正确，原因是找最大质因子，不应该是从 sqrt（） 开始往下找
    2，将会重开一个文件重写
*/
#include <stdio.h>
#include <math.h>

int IsPrime(long long num);

int main(){
    long long num, i;
    scanf("%lld", &num);

    long long max = (long long)sqrtl(num);
    for(i = max; i >= 2; i--){
        if(num%i == 0 && IsPrime(i) == 1){
            break;
        }
    }
    printf("%d", i);
    return 0;
}

int IsPrime(long long num){
    if(num < 2){
        return 0;
    }
    long long i;
    for(i = 2; i*i <= num; i++){
        if(num%i == 0){
            return 0;
        }
    }
    return 1;
}
