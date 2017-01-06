#include <iostream>

#include <vector>   //C++  内置模板是每一个模板一个文件； c++中内置的类首字母都是小写的
using namespace std;

class A
{
public:
    int a;
    A()
    {
       this->a=100;
       cout<<a<<"@@"<<endl;
    }

    A(int i)
    {
       a=i;
       cout<<a<<"!!"<<endl;

    }

};
int main()
{
    vector<int> v;
    vector<int>:: iterator iter;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    for(iter=v.begin();iter<v.end();iter++)
    {
        cout<<*iter<<endl;
    }

    //cout<<v.at(100);


    A A1;
    cout<<"A1.a="<<A1.a<<endl;

    cout<<"sizeof(vector<int>):  "<<sizeof(vector<int>);


    return 0;
}
