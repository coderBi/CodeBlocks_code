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

    Bird* pBird=(Bird*)&animal1;  //�������ָ���ǿ��ת����ע��һ�µ�����������animal
                                //֮ǰû����һ��bird�Ķ�����и�ֵ,���ֻ��һ��������animal����Ļ����������ǿ��ת��
                                //�ǲ��ɹ��ģ���ʹ�ɹ�ҲӦ�ó�������Ϊ����Ҫ����mallocһ�����µ��ڴ�ռ������Ӧ�Ĳ���
                                //Ȩ�ޡ�����ֻ��ָ�븳ֵ���ڴ�ռ�δ��չ��ԭ����Ȩ�޲��У�

    pBird->show();
    return 0;
}
