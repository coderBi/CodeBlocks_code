#include <iostream>

using namespace std;


class parent
{
    public:
        int num;


};

class children: public parent
{
    public:
        int num;
};

int main()
{
    children* ptr=new children();
    ptr->num=99;
    parent& par=*ptr;
    cout<<par.num<<endl;   //����Ǹ���� 0

    cout<<"------------------�ָ�----------------"<<endl;

    children* chr=(children*)(&par);
    cout<<chr->num<<endl;    //���Ϊ����� 99   ���ڱ���û��virtual����  ���Բ���˳����  ���丸�ൽ����  ���漰������
    return 0;
}
