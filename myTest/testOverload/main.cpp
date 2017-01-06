#include <iostream>

using namespace std;

void show(int i)
{
    cout<<"show()"<<endl;
}

/*
void show(char c1='a',int i,char c2)   //报错，也就是如果函数出现了默认初始值的情况，只能够从某一个开始，后面的全部要做默认值处理
{
    cout<<"show(char c1,int i,char c2)"<<endl;
}

*/
void show(char c1='a',int i=0,char c2='a')   //报错，也就是如果函数出现了默认初始值的情况，只能够从某一个开始，后面的全部要做默认值处理
{
    cout<<"show(char c1,int i,char c2)"<<endl;
}


int main()
{
    //show(1);
    show('a',1,'a');
    show('w',5);
    return 0;
}
