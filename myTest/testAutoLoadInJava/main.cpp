#include <iostream>

using namespace std;

class testAutoLoad
{
    public:
        int num;
        testAutoLoad(int num)
        {
            this->num=num;
        }
};

void printClassLoad(testAutoLoad myClass);
int main()
{
    printClassLoad(4);    //java里的自动装箱怀疑只是进行初始化而已
                        //当然如果里面是printClassLoad(testAutoLoad& myClass) 形参是引用的话就的确是自动装箱了
                        //而java里参数经分析  应该是引用类型（智能指针） 也就说明了自动装箱的存在！！！！
    return 0;
}

void printClassLoad(testAutoLoad myClass)
{
    cout<<myClass.num<<endl;
}

