#include <iostream>

using namespace std;

class A {
    int a1;
public:
    int a2;
private:
    int a3;
};

int main()
{
    A a;
    cout << "a.a1: " << a.a1 << endl;
    cout << "a.a2: " << a.a2 << endl;
    return 0;
}
