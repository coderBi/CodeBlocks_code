#include <stdio.h>

int IsPalindrome(int num);

int main(){
    int i, j;
    int res, max = 0, f1, f2;

    for(i = 999; i >= 100; i--){
        for(j = 999; j >= i; j--){
            res = i * j;
            if(IsPalindrome(res) == 1 && res > max){
                f1 = i;
                f2 = j;
                max = res;
            }
        }
    }
    printf("%d * %d = %d", f1, f2, max);
    return 0;
}

int IsPalindrome(int num){
    int arr[7], length = 0, i;

    while(num/10 != 0){
        arr[length++] = num%10;
        num /= 10;
    }
    arr[length++] = num;

    for(i = 0; i <= (length - 1)/2; i++){
        if(arr[i] != arr[length - 1 - i]){
            return 0;
        }
    }
    return 1;
}
