#include <iostream>

using namespace std;

int getNum()
{
    return 3;
}
int main()
{
    int myNum=100;
    int iArray[myNum];

    int iArray2[getNum()];   //ʵ����  ������֧�ֱ���������Ǳ�  �������鶨���Ŷ
    for(int i=0;i<sizeof(iArray2)/sizeof(int);i++)
    {
        iArray2[i]=i;
    }

    for(int i=0;i<sizeof(iArray2)/sizeof(int);i++)
    {
        cout<<iArray2[i]<<endl;
    }
    return 0;
}
