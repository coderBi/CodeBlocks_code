#include <iostream>

using namespace std;

void show(int i)
{
    cout<<i<<endl;
}

int main()
{
    int a;

    //cout << (sizeof int) << endl;  //error!!
    cout <<sizeof(int)<< endl;       //����

    cout << (sizeof a) << endl;      //�����

    //show(int i);    ����

    show(int);   //����
    return 0;
}
