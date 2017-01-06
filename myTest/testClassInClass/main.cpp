#include <iostream>

using namespace std;

class A
{
public:
    int a;
    class B
    {
    public:
        int b;

        B(int s):b(s){}

        B(B&s)
        {
            b=6;
        }

        void operator=(B& s)   //新建一个空类的时候，会有一个默认的重载=
        {
            b=s.b;
            cout<<"用了重载！"<<endl;
        }

    };
};


class B
{
public:
    int b;
    static int numb;

    B(int i):b(i){}

    const void setNumb()  //可以对static成员进行修改
    {
        //b=100;
        numb=10;
    }
};


class C
{
public:
    static int numb;

public:
    //C(int i):numb(i){}  //初始化列表的作用在于初始化，此处的numb在外部已经被初始化了。而在这里被理解为初始化处理

    const void setNumb()  //可以对static成员进行修改
    {
        //b=100;
        numb=100;
    }
};

int B::numb=0;
int C::numb=0;    //事实说明 static只有是public才有用，否则没法初始化，也就是没有办法分配内存了





class D
{
public:
    int a;

    class E
    {
    public:
        void show(B& d)
        {
            cout<<d.b<<endl;

        }
    };
};
int main()
{
    //A1.B.b=1;   //不合法的用法
    //A1.B B1;  //报错，B1之前应该有‘;’
    //B1.b=1;    //B1显示未定义
    //A1::B B2;    //报错，A1不是Class或者是namespace  所以不可以“：：”。B2之前应该有‘；’
    //B2.b=1;      //B2未定义
    A::B B3(1);
    A::B B4(5);
    B3=B4;   //通过运算符重载实现

    A::B B5=B4;

    B B6(10);
    //B6.b=100;
    B6.setNumb();
    cout<<"!!!"<<B6.numb<<"!!!"<<endl;
    cout<<B3.b<<endl<<B5.b<<endl<<B6.b<<endl;
    cout<<"***************************************"<<endl;

    //C c1(100);
    C c1;
    c1.setNumb();
    cout<<C::numb<<endl;  //这里的numb是static,要在外部进行初始化，否则setNumb会操作一个没有分配内存的数
    cout<<"***************************************"<<endl;
    cout<<endl<<endl<<endl;

    D d;
    d.a=555;
    D::E e;
    e.show(B6);
    cout<<"-----------------------------------------------"<<endl;

    return 0;
}
