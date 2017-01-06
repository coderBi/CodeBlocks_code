#include <iostream>

using namespace std;

class CTestMemberOper
{
    public:
        static int age;

        static void show()
        {
            cout<<age<<endl;
        }

        class CChild
        {

        };
};

int CTestMemberOper::age=6;
int main()
{
    CTestMemberOper::show();
    //CTestMemberOper.show();           //C++不可以直接类名成员操作符访问static   java可以
    //CTestMemberOper.age;

    //CTestMemberOper.CChild  child1;   ///也是出错的


    CTestMemberOper::CChild child1;
    cout << "Hello world!" << endl;
    return 0;
}
