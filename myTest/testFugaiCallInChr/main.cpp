#include <iostream>

using namespace std;


class parent
{
    public:
        void dislpay()
        {
            show();
        }

        void show()     //这里如果将父类的show定义成virtual 下面就会调用子类的  否则调用父类的
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

        //const int num;    //const必须进行初始化

};

int main()
{
    child ch1;
    ch1.dislpay();   //打印结果符合分析  父类模块的diplay 调用父类模块的show（）  只有是虚函数的时候才会访问子类模块

    cout<<"---------------------"<<endl;

    parent& par1=ch1;
    par1.dislpay();           //同java不同这些父类方法中必须要加上virtual才能够形成多态  而java中可以默认是有virtual、这样理解的（这样理解可以统一父类函数寻调用的顺序）
    return 0;
}
