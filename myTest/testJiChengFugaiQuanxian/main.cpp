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
    int show()   //1����Ȩ�޸��Ǹ�Ȩ��  C++����  java����
                 //2��C++��д��ʱ�򷵻�ֵ���Ϳ��Բ�һ��   java����һ��
    {

    }
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
