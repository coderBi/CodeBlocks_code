#include <iostream>

using namespace std;

class parent
{
    public:
        virtual void show()=0;


};

class outer: public parent  //这里实验 leimingouter不可省
{
    private:
        class inner:parent       //内部类中的 类名inner可以省略  这边形成了匿名内部类....  但是当父类存在虚函数是  这里的inner类名不可省
                            //经过实验 这里跟java不同  C++中的匿名inner不需要一定是继承或实现一个类  也就是不需要继承parent才可以省去inner名
        {
            public:
                void show()
                {

                }

        };

        void show()
        {

        }

};

//C++中虽然没有 interface这一关键词  但是通过纯虚函数  可以一样实现接口  当然也可以通过定义宏自造一个interface

int main()
{
    /*  这里没有办法像java那样构建子类对象
    new parent()
    {
        void show()
        {

        }
    };
    */
    cout << "Hello world!" << endl;
    return 0;
}


