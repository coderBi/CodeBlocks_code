#include <iostream>
#include <string>

using namespace std;

class Animal
{
    public:
        int age;

        void setAge()
        {
            age=100;
        }

        virtual void show()
        {

            cout<<"Animal.age: "<<age<<endl;
        }
};

class Bird:public Animal
{
    public:
        string Name;

        void setName()
        {
            Name="Bird";
        }
        void show()
        {
            cout<<"Bird.Name: "<<Name<<endl;
        }
};


int main()
{
    Bird bird1;
    bird1.setName();
    Animal& animal1=bird1;
    animal1.show();
    cout<<"--------------------------------------"<<endl;

    Bird* pBird=(Bird*)&animal1;  //这里进行指针的强制转换，注意一下的是如果这里的animal
                                //之前没有用一个bird的对象进行赋值,如果只是一个单纯的animal对象的化。这里进行强制转换
                                //是不成功的（即使成功也应该出错），因为还需要再用malloc一部分新的内存空间才有相应的操作
                                //权限。这里只是指针赋值（内存空间未拓展，原本有权限才行）

    pBird->show();
    return 0;
}
