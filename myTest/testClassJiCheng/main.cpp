#include <iostream>

using namespace std;

class A
{
    public:
        int a;

        A()
        {

        }

        A(int s)
        {
            a=s;
        }

        virtual void show()
        {
            cout<<a<<endl;
        }

        virtual void Seta()
        {
            a=998;
            cout<<"hello A"<<endl;
        }
};


class B:public A
{
    public:
        int a;

        A AA;

        B(){}

        B(int s):AA(s)
        {

        }

        void show()
        {
            cout<<this->a<<endl;
        }

        void Seta()
        {
            a=999;
            cout<<"hello B"<<endl;
        }
};

int main()
{
    B b1;
    b1.A::a=10;
    b1.a=100;
    b1.show();
    b1.A::show();       //A:: ������������Ϊǰ���ж���������ʵ�Ƕ�����ã����������
    //cout<<A::a<<endl;
    //A::show();       //û�ж���û�����ã�����static

    B b2(1000);
    b2.AA.show();

    cout<<"**************************************************"<<endl<<endl;

    A& A3=b1;
    A3.show();
    A3.A::show();

    cout<<"**************************************************"<<endl<<endl;
    A3.Seta();
    A3.show();
    A3.A::Seta();
    A3.A::show();
    cout<<"??????????????????????????????????????????????????"<<endl<<endl;
    b1.show();
    cout<<"**************************************************"<<endl<<endl;

    A A2;
    A2=b1;
    A2.show();   //�����ƣ��������ָ̬��ָ��
    return 0;
}
