#include <iostream>

using namespace std;


class parent   //C++ �ļ���Ҫ���Ⱥ�˳��  �����parent�ᵽouter����ͻ����ʧ�� ����C++�ı������
{

};
class outer: public parent
{
    private:
        static int outNum;
    public:
        class inner
        {
            public:
                int inNum;
                void showInner()
                {
                    cout<<outNum<<endl;    //ֻ��outNum��static �ſ�������ֱ������  ��Ϊ����innerʱ�����outer  ���ŵ���static
                                            //��java������ outer.this���õĴ���  ����Ҫ���ⲿʵ���ſ�����ʵ����innner

                }


        };
};

int outer::outNum=100;
int main()
{
    outer::inner inr;
    inr.showInner();
    return 0;
}
