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
    //���Է���strҲ���ǻ�������  ��������
    cout << str << endl;
    return 0;
}
