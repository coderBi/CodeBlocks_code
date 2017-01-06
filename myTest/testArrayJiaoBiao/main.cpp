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

    int iArray2[getNum()];   //实验结果  这里是支持变量做数组角标  进行数组定义的哦
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
