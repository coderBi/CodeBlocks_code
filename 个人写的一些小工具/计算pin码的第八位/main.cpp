/*
    计算公式如下：
        ①：已知前 7 位
        ②; 计算 30 - 3 * （前七位奇数位之和） - （前七位偶数位之和）
        ③： 如果上面的结果是整数，那么这个整数的各位数就是第八位， 如果上面的结果是 负数， 那么相应的个位数加 10 就是第八位
*/

#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    int arr[7]= {0};
    cout << "input 7 bits in the front: " << endl;

    while(scanf("%1d", &arr[0])){
        int i = 1;
        while(i < 7 && scanf("%1d", &arr[i])){
            i++;
        }

        int bit8 = 30 - 3 * (arr[0] + arr[2] + arr[4] + arr[6]) - (arr[1] + arr[3] + arr[5]);
        bit8 %= 10;
        bit8 = bit8 < 0 ? (bit8 + 10) : bit8;
        cout << "bit8 : " << bit8 << endl;
    }
    return 0;
}
