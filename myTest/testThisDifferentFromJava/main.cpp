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
        this(1);    //��ʾ��this can not be used as a function......˵��ֻ��java�п���������
        cout<<"testThis():"<<testNumb<<endl;
    }


};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
