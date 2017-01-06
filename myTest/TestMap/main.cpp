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

    cout << "测试通过修改cls1的内容两次将其添加到map里面的结果" << endl;
    cls1.nVar1 = 1;
    map1[cls1.nVar1] = cls1;
    cls1.nVar1 = 2;
    map1[cls1.nVar1] = cls1;
    PrintMap(map1);
    map1.clear();
    cout << "------------------分隔符------------------" << endl;

    cout << "测试cls1 cls2的内容相同添加到map里面的结果" << endl;
    cls1.nVar1 = 1;
    map1[cls1.nVar1] = cls1;
    cls2.nVar1 = 1;
    map1[cls2.nVar1] = cls2;
    PrintMap(map1);
    map1.clear();
    cout << "------------------分隔符------------------" << endl;

    cout << "测试cls1 cls2的内容不同添加到map里面的结果" << endl;
    cls1.nVar1 = 1;
    map1[cls1.nVar1] = cls1;
    cls2.nVar1 = 2;
    map1[cls2.nVar1] = cls2;
    PrintMap(map1);
    map1.clear();
    cout << "------------------分隔符------------------" << endl;
    return 0;
}
