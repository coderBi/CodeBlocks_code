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
    printClassLoad(4);    //java����Զ�װ�仳��ֻ�ǽ��г�ʼ������
                        //��Ȼ���������printClassLoad(testAutoLoad& myClass) �β������õĻ��͵�ȷ���Զ�װ����
                        //��java�����������  Ӧ�����������ͣ�����ָ�룩 Ҳ��˵�����Զ�װ��Ĵ��ڣ�������
    return 0;
}

void printClassLoad(testAutoLoad myClass)
{
    cout<<myClass.num<<endl;
}

