#include <iostream>

using namespace std;


class parent
{
    public:
        void dislpay()
        {
            show();
        }

        void show()     //��������������show�����virtual ����ͻ���������  ������ø����
        {
            cout<<"parent: show()"<<endl;
        }
};

class child: public parent
{
    public:
        void show()
        {
            cout<<"child: show()"<<endl;
        }

        //const int num;    //const������г�ʼ��

};

int main()
{
    child ch1;
    ch1.dislpay();   //��ӡ������Ϸ���  ����ģ���diplay ���ø���ģ���show����  ֻ�����麯����ʱ��Ż��������ģ��

    cout<<"---------------------"<<endl;

    parent& par1=ch1;
    par1.dislpay();           //ͬjava��ͬ��Щ���෽���б���Ҫ����virtual���ܹ��γɶ�̬  ��java�п���Ĭ������virtual����������ģ������������ͳһ���ຯ��Ѱ���õ�˳��
    return 0;
}