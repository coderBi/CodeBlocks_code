#include <iostream>

using namespace std;

void show(int i)
{
    cout<<"show()"<<endl;
}

/*
void show(char c1='a',int i,char c2)   //����Ҳ�����������������Ĭ�ϳ�ʼֵ�������ֻ�ܹ���ĳһ����ʼ�������ȫ��Ҫ��Ĭ��ֵ����
{
    cout<<"show(char c1,int i,char c2)"<<endl;
}

*/
void show(char c1='a',int i=0,char c2='a')   //����Ҳ�����������������Ĭ�ϳ�ʼֵ�������ֻ�ܹ���ĳһ����ʼ�������ȫ��Ҫ��Ĭ��ֵ����
{
    cout<<"show(char c1,int i,char c2)"<<endl;
}


int main()
{
    //show(1);
    show('a',1,'a');
    show('w',5);
    return 0;
}
