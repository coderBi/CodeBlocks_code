#include <stdio.h>

int IsPrime(long long num);

int main(){
    long long num, i;
    scanf("%lld", &num);

    for(i = 1; i <= num; i++){
        if(num%i == 0 && IsPrime(num/i) == 1){
            printf("%lld", num/i);  //·µ»ØµÄÊÇnum/i
            break;
        }
    }
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
