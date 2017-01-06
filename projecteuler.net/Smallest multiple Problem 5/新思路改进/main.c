/*
    ���������Χ�����е������� �ٽ���Χ������ص������ݳ˵������
*/
#include <stdio.h>

int IsPrime(int num);

int main(){
    int max;
    long long res = 1;
    scanf("%d", &max);
    int i, j;

    for(i = 1; i <= max; i++){
        if(IsPrime(i) == 1){
            int mul = 1;
            while(mul * i <= max){
                mul *= i;
            }
            res *= mul;
        }
    }
    printf("%lld", res);

}

int IsPrime(int num){
    if(num < 2){
        return 0;
    }

    int i;
    for(i = 2; i*i <= num; i++){
        if(num%i == 0){
            return 0;
        }
    }
    return 1;
}
