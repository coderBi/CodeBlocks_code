#include <iostream>

using namespace std;

class testDeleteThis
{
    public:
        int num;
        testDeleteThis()
        {
            this->num=100;
        }

        void testMethod()
        {
            delete this;   //�Լ�ɱ�Լ�  �ǿ��е�.....
        }
};
int main()
{
    testDeleteThis* myTest=new testDeleteThis();
    myTest->testMethod();
    cout<<myTest->num<<endl;   //���Ӧ�û����  ��ʱmyTestָ������
    return 0;
}
