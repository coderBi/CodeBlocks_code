/*
    ����Ӣ��һ��ʼ�����ף���Ŀ��find the sum of the even-valued terms ������� the even-valued terms
    ԭ��ָ����ż���ĺ�
*/
#include <stdio.h>

int main(){
    int n = 4000000;
    int x1 = 1, x2 = 2, x;
    double sum = 0;

    sum = 2;
    x = x1 + x2;
    while(x <= n){
        if(x%2 == 0){
            sum += x;
        }
        x1 = x2;
        x2 = x;
        x = x1 + x2;
    }
    printf("%.0lf", sum);
    return 0;
}
