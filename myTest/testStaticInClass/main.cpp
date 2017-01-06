#include <iostream>

using namespace std;

void testStatic();

class CTestStaticInClass
{
    public:
        const int noUseNum//=100;  //ISO C++只允许static 跟const同时 出现在成员修饰时  才可以在申明是直接初始化
        static int testNum;   //只是申明。。。。（跟成员变量一样） 需要在外部初始化
                                //ISO C++ forbids in-class initialization of non-const static member!!!!!
        static void dispaly()
        {
            static int numb;
            cout<<"numb:  "<<numb<<endl;
            cout<<"testNum: "<<testNum<<endl;
        }

        CTestStaticInClass():noUseNum(100)  //在初始化列表中可以进行初始化noUseNum的工作
        {
            ///noUseNum=100;    //提示操作了 “只读”数据
        }
};

int CTestStaticInClass::testNum=100;
int main()
{
    CTestStaticInClass::dispaly();

    cout<<endl<<endl<<endl;
    testStatic();              //里面涉及的test3 在调用完释放  如果是staatic计数  这里只存在一次  故不会对下面的test1造成影响
                                //可是这里运行的结果显示test显示的是123  基本猜想statci与程序（线程）同周期
    cout<<endl<<endl<<endl;


    CTestStaticInClass  test1;
    test1.dispaly();
    test1.testNum=999;


    cout<<endl<<endl<<endl;

    CTestStaticInClass  test2;   //第二次进行类加载的时候  对于静态的指挥添加新的指向，不会新建副本
    test2.dispaly();            //个人理解  静态的会根据计数器释放????（（通过上面test3的测试说明static很可能与整个程序同周期


    return 0;
}


void testStatic()
{
    CTestStaticInClass  test3;
    test3.testNum=123;
    test3.dispaly();
}
