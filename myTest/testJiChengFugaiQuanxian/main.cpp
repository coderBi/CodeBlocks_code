#include <iostream>

using namespace std;

class parent
{
    public:
        void show()
        {

        }
};

class child:public parent
{
    private:
    int show()   //1、低权限覆盖高权限  C++可以  java不行
                 //2、C++重写的时候返回值类型可以不一样   java必须一致
    {

    }
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
