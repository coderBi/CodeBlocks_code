#include <iostream>
#include <map>

using namespace std;

class MyClass{
public:
    int nVar1;
    void PrintVar(){
        cout << nVar1 << endl;
    }
};

void PrintMap(map<int,MyClass> map1){
    map<int,MyClass>::iterator it;
    for(it = map1.begin(); it != map1.end(); it++){
        cout<< it->first << " " << it->second.nVar1 << endl;
    }
}

int main()
{
    MyClass cls1, cls2;
    map<int,MyClass> map1;

    cout << "����ͨ���޸�cls1���������ν�����ӵ�map����Ľ��" << endl;
    cls1.nVar1 = 1;
    map1[cls1.nVar1] = cls1;
    cls1.nVar1 = 2;
    map1[cls1.nVar1] = cls1;
    PrintMap(map1);
    map1.clear();
    cout << "------------------�ָ���------------------" << endl;

    cout << "����cls1 cls2��������ͬ��ӵ�map����Ľ��" << endl;
    cls1.nVar1 = 1;
    map1[cls1.nVar1] = cls1;
    cls2.nVar1 = 1;
    map1[cls2.nVar1] = cls2;
    PrintMap(map1);
    map1.clear();
    cout << "------------------�ָ���------------------" << endl;

    cout << "����cls1 cls2�����ݲ�ͬ��ӵ�map����Ľ��" << endl;
    cls1.nVar1 = 1;
    map1[cls1.nVar1] = cls1;
    cls2.nVar1 = 2;
    map1[cls2.nVar1] = cls2;
    PrintMap(map1);
    map1.clear();
    cout << "------------------�ָ���------------------" << endl;
    return 0;
}
