#include <iostream>

using namespace std;
struct myStruct
{
    int age;
    char sex;
};

class myClass
{
    public:
        int age;
        char sex;
};

int main()
{
    cout << "struct myStruct�Ĵ�С�ǣ� " <<sizeof(struct myStruct)<< endl;
    cout << "class myClass�Ĵ�С�ǣ� " <<sizeof(class myClass)<< endl;     //��ʾ���ǡ�8����˵�����ڴ������Ƶ��ձ���
    return 0;
}
