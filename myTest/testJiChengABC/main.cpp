#include <iostream>

using namespace std;


class A
{
    public:
        virtual void show()
        {
            cout<<"class A"<<endl;
        }
};

class B:public A
{
   
};

class C:public B
{
    public:
        int a;
        C(int a=5)
        {
            this->a=a;
        }

        void show()
        {
            cout<<"class C"<<endl;
            cout<<"C.a="<<a<<endl;
        }

};

int main()
{
    C c1;
    c1.show();

    cout<<"-----------------------------"<<endl;

    A& a1=c1;
    a1.show();     //这里输出的是classC，可以分析出a1调用show是去找B类，结果里面也是只有一个virtu函数，然后就去找下一个子类C
    return 0;
}
