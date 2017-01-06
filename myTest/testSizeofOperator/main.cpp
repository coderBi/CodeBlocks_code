#include <iostream>

using namespace std;

void show(int i)
{
    cout<<i<<endl;
}

int main()
{
    int a;

    //cout << (sizeof int) << endl;  //error!!
    cout <<sizeof(int)<< endl;       //函数

    cout << (sizeof a) << endl;      //运算符

    //show(int i);    出错

    show(int);   //出错
    return 0;
}
