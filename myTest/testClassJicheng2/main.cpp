#include <iostream>

using namespace std;

class A
{
    public:
        int a;

        class B      //类中类，数据区彼此独立，代码区可以通过A找到B。 所以数据区 A B各占一个int
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
