#include <iostream>

using namespace std;

class FuShu
{
    private:
        int real;
        int image;
    public:
        FuShu(int real=0,int image=0)
        {
            this->real=real;
            this->image=image;
        }

        friend  ostream& operator<<(ostream& ostr,FuShu fuShu)
        {
            ostr<<fuShu.real;
            ostr<<"+(";
            ostr<<fuShu.image;
            ostr<<"i)";
            return ostr;

        }
        template<class T>  friend void show(T t,FuShu fu);

};



template<class T> void show(T t,FuShu fu)
{
    cout<<"您输入的是： "<<t<<endl;
    cout<<"             "<<fu<<endl;
    cout<<"fu的实部是：  "<<fu.real;
}

int main()
{
    FuShu fu[]={FuShu(1,2),FuShu(3,4)};
    cout<<fu[0]<<endl<<fu[1]<<endl;
    show(5,fu[1]);
    return 0;
}
