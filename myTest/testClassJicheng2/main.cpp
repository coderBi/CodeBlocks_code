#include <iostream>

using namespace std;

class A
{
    public:
        int a;

        class B      //�����࣬�������˴˶���������������ͨ��A�ҵ�B�� ���������� A B��ռһ��int
        {
            public:
            int a;
        };
};

int main()
{
    cout <<sizeof(class A) <<endl<<sizeof(class A::B)<<endl;
    return 0;
}
