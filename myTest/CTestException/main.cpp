#include <iostream>

using namespace std;


class CMyException  //�Զ����쳣��
{
    private:
        int num;
    public:
        int getNum()
        {
            return num;
        }
        CMyException(int num)
        {
            this->num=num;
        }
};

class CTestException
{
    public:
        int div(int a,int b)
        {
            if(b==0)
            {
                CMyException myExc(100);      //�׶���
                throw CMyException(myExc);
                //throw new CMyException(99);  //��ָ��
            }

           return a/b;
        }
};

int main()
{
    CTestException tsExc;
    try
    {
        cout<<tsExc.div(5,0)<<endl;

    }

    catch(CMyException e)
    {
        cout<<"���ڳ���Ϊ0����������������룺 "<<e.getNum()<<endl;

    }

    return 0;
}


