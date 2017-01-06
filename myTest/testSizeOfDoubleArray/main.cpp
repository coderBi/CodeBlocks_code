#include <iostream>

using namespace std;

int main()
{
    //int[] a={0};   //错误  报错   [前不合格！！！   java可以用

    int a[2][3];

    //int a[3][]; //定义失败

    //int a[][3]; //定义失败  原因是sizeof unkown
    cout << sizeof(a) << endl;   //结果显示为 24  二维数组

    cout << sizeof(a[0]) << endl;   //结果显示为 12  一位数组
    return 0;
}
