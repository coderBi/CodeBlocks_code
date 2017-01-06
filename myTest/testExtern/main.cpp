//#define UNICODE

#ifdef UNICODE
#pragma message("used  UNICODE")
#else
#pragma message("used ANSI")
#endif

#include <iostream>

//#include "addFile.h"
using namespace std;

#include <windows.h>

extern int Numb1;

void show1()
{
    Numb1=100;
    cout<<"the numb is:  "<<Numb1<<endl;
}

//int Numb1;    ÖØ¶¨Òå
void show2()
{
    int Numb1;
    Numb1=99;
    cout<<"the numb is:  "<<Numb1<<endl;
}

void show3()
{
    //extern int Numb1;
    cout<<"the numb is:  "<<Numb1<<endl;
}
int main()
{
    show1();
    show2();
    show3();
    //#pragma message("used  UNICODE")
    return 0;
}
