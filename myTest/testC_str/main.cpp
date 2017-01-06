#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class MyString
{
    private:
        char* str;

    public:
        MyString(char* s)
        {
            int length=strlen(s);
            length++;

            str=new char[length];

            for(int i=0;i<length-1;i++)
            {
                str[i]=s[i];
            }

            str[length-1]='\0';
        }

        char* c_str()
        {
            return str;
        }
};


int main()
{
    MyString mys("bww");
    char* p=mys.c_str();

    //得到MyString类中的privat属性，间接操作类里面new的内存区
    strcpy(p,"b");

    cout<<p<<endl;


/*
    string str="bww";
    const char* p=str.c_str();
    cout << "str.c_str():" <<p<<endl;
    return 0;
*/



}
