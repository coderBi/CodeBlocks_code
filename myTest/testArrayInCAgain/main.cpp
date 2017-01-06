#include <iostream>

using namespace std;

int main()
{
    int (*p)[3]=NULL;
    int a[3]={1,2,3};
    p=&a;
    cout<<p[0]<<"\t"<<*(p+1)<<"\t"<<*(p+2)<<"\t"<<endl;    //??????
    return 0;
}
