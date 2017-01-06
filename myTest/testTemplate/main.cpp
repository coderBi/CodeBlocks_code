#include <iostream>

using namespace std;

template<class T,class V> class FuShu
{
    private:
        T real;
        V image;
    public:
        FuShu(T real=0,V image=0)
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
        template<class X>  friend void show(X t,FuShu<int,int>& fu);

};



template<class X> void show(X t,FuShu<int,int>& fu)
{
    cout<<"您输入的是： "<<t<<endl;
    cout<<"             "<<fu<<endl;
    cout<<"fu的实部是：  "<<fu.real;
}

int main()
{
    FuShu<int,int> fu[]={FuShu<int,int>(1,2),FuShu<int,int>(3,4)};
    cout<<fu[0]<<endl<<fu[1]<<endl;
    show(5,fu[1]);

    //FuShu<int,int>* p=new FuShu<int,int>(100,100);  //经过试验，两边的<int，int>都不可以省略，否则是模糊的
    return 0;
}
