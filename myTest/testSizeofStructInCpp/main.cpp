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
    cout << "struct myStruct的大小是： " <<sizeof(struct myStruct)<< endl;
    cout << "class myClass的大小是： " <<sizeof(class myClass)<< endl;     //显示都是“8”，说明了内存对齐机制的普遍性
    return 0;
}
