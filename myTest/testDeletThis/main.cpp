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
            delete this;   //自己杀自己  是可行的.....
        }
};
int main()
{
    testDeleteThis* myTest=new testDeleteThis();
    myTest->testMethod();
    cout<<myTest->num<<endl;   //本来以为结果应该会出错  这时myTest指针悬垂。但是实际测试发现运行正常，也就是说操作系统并不能保证回收了的还没被重新分配的堆不能被读取。
    return 0;
}
