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
    cout<<myTest->num<<endl;   //结果应该会出错  这时myTest指针悬垂
    return 0;
}
