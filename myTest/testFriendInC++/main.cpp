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


//���� CMyClass t��û������Ԫ�ĺ��������н����������������￴����Ч���Ǿֲ�����tҲ�ǿ�����������private������
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
