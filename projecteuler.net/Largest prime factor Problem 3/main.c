/*
    1�����ﾡ��ͨ���˲��ԣ����Ǵ��벻��ȷ��ԭ��������������ӣ���Ӧ���Ǵ� sqrt���� ��ʼ������
    2�������ؿ�һ���ļ���д
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
