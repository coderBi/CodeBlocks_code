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
    smartPtr1->show();                 //������ڲ���� smartPtr1->����ΪsmartPtr1.operator ->()����һ��ָ��
                                        //show()  ǰ��ֱ�����һ��ָ�룿�����������������ʲô�����أ�����
    cout << "Hello world!" << endl;
    return 0;
}
