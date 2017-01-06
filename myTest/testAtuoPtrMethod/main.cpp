#include <iostream>

using namespace std;


class  test
{
    public:
        void  show()
        {
            cout<<"test.show"<<endl;
        }
};


class  CSmartPtr
{

    public:
        test* ts1;

        void  show()
        {
            cout<<"CSmartPtr.show"<<endl;
        }

        test* operator -> ()
        {
            return ts1;
        }
};



int main()
{
    CSmartPtr smartPtr1;
    smartPtr1.ts1=(test*)new test();
    smartPtr1->show();                 //这里存在不清楚 smartPtr1->解析为smartPtr1.operator ->()返回一个指针
                                        //show()  前面直接添加一个指针？？？这里编译器做了什么处理呢？？？
    cout << "Hello world!" << endl;
    return 0;
}
