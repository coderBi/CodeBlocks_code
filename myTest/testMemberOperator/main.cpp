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
    //CTestMemberOper.show();           //C++������ֱ��������Ա����������static   java����
    //CTestMemberOper.age;

    //CTestMemberOper.CChild  child1;   ///Ҳ�ǳ����


    CTestMemberOper::CChild child1;
    cout << "Hello world!" << endl;
    return 0;
}
