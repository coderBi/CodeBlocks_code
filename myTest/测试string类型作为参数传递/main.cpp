#include <iostream>
#include <string>

using namespace std;

void func(string str){
    cin >> str;
    cout << str << endl;
}

int main()
{
    string str("it is just a simple string in c++");
    cout << str << endl;
    func(str);
    //可以发现str也算是基本类型  不是引用
    cout << str << endl;
    return 0;
}
