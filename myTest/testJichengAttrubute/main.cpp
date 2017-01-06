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
    cout<<par.num<<endl;   //结果是父类的 0

    cout<<"------------------分割----------------"<<endl;

    children* chr=(children*)(&par);
    cout<<chr->num<<endl;    //结果为子类的 99   由于变量没有virtual修饰  所以查找顺序是  从其父类到本类  不涉及其子类
    return 0;
}
