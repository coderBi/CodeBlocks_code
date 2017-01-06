#include <iostream>

using namespace std;

int main()
{
    void test();
   // {

    //}
    void show(int,int);   //函数内部放申明 表示作用域  不可以放定义
    cout << "Hello world!" << endl;
    show(1,2);
    return 0;
}

void show(int a,int b)
{
    void test(int);
    cout<<a+b<<endl;
}
