#include <iostream>
#include <string>
using namespace std;

class  CMyClass
{
    private:
    string name;
    int age;

    public:
    CMyClass(string name="",int age=0)
    {
        this->name=name;
        this->age=age;
    }
    void show()
    {
       cout<<name<<endl;
       cout<<age<<endl;
    }

    friend CMyClass operator+(CMyClass& myClass1,CMyClass& myClass2);
};


//其中 CMyClass t并没有在友元的函数申明中进行申明，但是这里看到的效果是局部变量t也是可以正常访问private变量的
CMyClass operator+(CMyClass& myClass1,CMyClass& myClass2)
{
    CMyClass t;
    t.name=myClass1.name+myClass2.name;
    t.age=myClass1.age+myClass2.age;
    return t;
}

int main()
{
    //cout << "Hello world!" << endl;
    CMyClass myClass("bww",24);
    myClass.show();
    cout<<"************************************"<<endl;
    CMyClass myClass1("bww",24);
    CMyClass myClass2("bww",24);

    myClass=operator+(myClass1,myClass2);
    myClass.show();
    return 0;
}
