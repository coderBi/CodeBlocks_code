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
    a1.show();     //�����������classC�����Է�����a1����show��ȥ��B�࣬�������Ҳ��ֻ��һ��virtu������Ȼ���ȥ����һ������C
    return 0;
}
