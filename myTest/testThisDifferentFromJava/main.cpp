#include <iostream>

using namespace std;

class  testThis
{
    public:

    testThis(int test)
    {
        cout<<"testThis()"<<endl;
    }
    testThis(int test,int testNumb)
    {
        this(1);    //提示：this can not be used as a function......说明只有java中可以这样用
        cout<<"testThis():"<<testNumb<<endl;
    }


};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
