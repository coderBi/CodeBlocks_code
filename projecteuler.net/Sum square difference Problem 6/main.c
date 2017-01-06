#include <stdio.h>
#include <stdlib.h>

int main(){
    int num = 100;
    int sum1 = 0, sum2 = 0;
    int i;
    for(i = 1; i <= num; i++){
        sum1 += i*i;
        sum2 += i;
    }
    sum2 = sum2*sum2;
    printf("%d\n", sum2 - sum1);
}
