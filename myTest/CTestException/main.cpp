#include <iostream>

using namespace std;


class CMyException  //自定义异常类
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
                CMyException myExc(100);      //抛对象
                throw CMyException(myExc);
                //throw new CMyException(99);  //抛指针
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
        cout<<"由于除数为0，出异样。错误代码： "<<e.getNum()<<endl;

    }

    return 0;
}


