#include <iostream>

using namespace std;

void testStatic();

class CTestStaticInClass
{
    public:
        const int noUseNum//=100;  //ISO C++ֻ����static ��constͬʱ �����ڳ�Ա����ʱ  �ſ�����������ֱ�ӳ�ʼ��
        static int testNum;   //ֻ��������������������Ա����һ���� ��Ҫ���ⲿ��ʼ��
                                //ISO C++ forbids in-class initialization of non-const static member!!!!!
        static void dispaly()
        {
            static int numb;
            cout<<"numb:  "<<numb<<endl;
            cout<<"testNum: "<<testNum<<endl;
        }

        CTestStaticInClass():noUseNum(100)  //�ڳ�ʼ���б��п��Խ��г�ʼ��noUseNum�Ĺ���
        {
            ///noUseNum=100;    //��ʾ������ ��ֻ��������
        }
};

int CTestStaticInClass::testNum=100;
int main()
{
    CTestStaticInClass::dispaly();

    cout<<endl<<endl<<endl;
    testStatic();              //�����漰��test3 �ڵ������ͷ�  �����staatic����  ����ֻ����һ��  �ʲ���������test1���Ӱ��
                                //�����������еĽ����ʾtest��ʾ����123  ��������statci������̣߳�ͬ����
    cout<<endl<<endl<<endl;


    CTestStaticInClass  test1;
    test1.dispaly();
    test1.testNum=999;


    cout<<endl<<endl<<endl;

    CTestStaticInClass  test2;   //�ڶ��ν�������ص�ʱ��  ���ھ�̬��ָ������µ�ָ�򣬲����½�����
    test2.dispaly();            //�������  ��̬�Ļ���ݼ������ͷ�????����ͨ������test3�Ĳ���˵��static�ܿ�������������ͬ����


    return 0;
}


void testStatic()
{
    CTestStaticInClass  test3;
    test3.testNum=123;
    test3.dispaly();
}
