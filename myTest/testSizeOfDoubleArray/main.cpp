#include <iostream>

using namespace std;

int main()
{
    //int[] a={0};   //����  ����   [ǰ���ϸ񣡣���   java������

    int a[2][3];

    //int a[3][]; //����ʧ��

    //int a[][3]; //����ʧ��  ԭ����sizeof unkown
    cout << sizeof(a) << endl;   //�����ʾΪ 24  ��ά����

    cout << sizeof(a[0]) << endl;   //�����ʾΪ 12  һλ����
    return 0;
}
