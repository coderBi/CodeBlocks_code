#include <iostream>

#include <string>

#include <stdlib.h>

using namespace std;

int main()
{
    string str1="99bww100";
    const char* pCh=str1.c_str();
    int iStr;
    iStr=atoi(pCh);
    cout << iStr << endl;  //������99
    return 0;
}
