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
    show();                //���ö�������
}

int main()
{
    myClass mys;
    mys.display();
    return 0;
}
