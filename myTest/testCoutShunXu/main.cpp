#include <iostream>

using namespace std;

int main()
{
    int a=10;
    cout <<((a++)+3)<<endl<<a<<endl<<(++a)+3<<endl<<a<<endl;  //好像不同编译器处理不一样
    return 0;
}
