#include <iostream>
#include <string>
#include "main.h"

using namespace std;

void show()
{
    cout<<"display -->  show"<<endl;
}

void myClass::display()
{
    show();                //调用独立函数
}

int main()
{
    myClass mys;
    mys.display();
    return 0;
}
