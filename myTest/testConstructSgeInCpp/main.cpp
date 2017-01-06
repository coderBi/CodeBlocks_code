#include <iostream>

using namespace std;


class CConstructSge
{
    /*
    {
        cout<<"CConstructSge!!!"<<endl;   //报错 C++中不存在构造代码块；java中才可以用
    }
    */
    public:
        CConstructSge()
        {
            cout<<"constructor method"<<endl;
        }
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
