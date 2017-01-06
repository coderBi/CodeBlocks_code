#include <iostream>

using namespace std;

int main()
{
    string str1, str2;
    str1 = "xxx";
    str2 = "xxx1";
    str2.erase(3, 1);
    cout << boolalpha << (str1 == str2) << endl; //结果是true，说明说明 == 是比较的内部的内容，也就是相当于strcmp 两个string内部的char *
    return 0;
}
