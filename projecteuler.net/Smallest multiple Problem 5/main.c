#include <stdio.h>

#define N 10

void Reduction(long long arr[], long long p1, long long p2);

int main(){
    long long i, j, res;
    long long arr[N];

    for(i = 0; i < N; i++){
        arr[i] = i +1;
    }
    for(i = 0; i < N; i++){
        for(j = i +1; j < N; j++){
            Reduction(arr, i, j);
        }
    }
    for(i = 0, res = 1; i < N; i++){
        res *= arr[i];
    }
    printf("%lld", res);
}

void Reduction(long long arr[], long long p1, long long p2){
    long long m = arr[p1], n = arr[p2];
    while(n%m != 0){
        int temp = m;
        m = n%m;
        n = temp;
    }
    arr[p1] /= m;
}
