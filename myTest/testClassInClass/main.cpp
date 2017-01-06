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

        void operator=(B& s)   //�½�һ�������ʱ�򣬻���һ��Ĭ�ϵ�����=
        {
            b=s.b;
            cout<<"�������أ�"<<endl;
        }

    };
};


class B
{
public:
    int b;
    static int numb;

    B(int i):b(i){}

    const void setNumb()  //���Զ�static��Ա�����޸�
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
    //C(int i):numb(i){}  //��ʼ���б���������ڳ�ʼ�����˴���numb���ⲿ�Ѿ�����ʼ���ˡ��������ﱻ���Ϊ��ʼ������

    const void setNumb()  //���Զ�static��Ա�����޸�
    {
        //b=100;
        numb=100;
    }
};

int B::numb=0;
int C::numb=0;    //��ʵ˵�� staticֻ����public�����ã�����û����ʼ����Ҳ����û�а취�����ڴ���





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
    //A1.B.b=1;   //���Ϸ����÷�
    //A1.B B1;  //����B1֮ǰӦ���С�;��
    //B1.b=1;    //B1��ʾδ����
    //A1::B B2;    //����A1����Class������namespace  ���Բ����ԡ���������B2֮ǰӦ���С�����
    //B2.b=1;      //B2δ����
    A::B B3(1);
    A::B B4(5);
    B3=B4;   //ͨ�����������ʵ��

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
    cout<<C::numb<<endl;  //�����numb��static,Ҫ���ⲿ���г�ʼ��������setNumb�����һ��û�з����ڴ����
    cout<<"***************************************"<<endl;
    cout<<endl<<endl<<endl;

    D d;
    d.a=555;
    D::E e;
    e.show(B6);
    cout<<"-----------------------------------------------"<<endl;

    return 0;
}
