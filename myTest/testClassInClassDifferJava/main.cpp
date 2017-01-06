#include <iostream>

using namespace std;


class parent   //C++ 文件中要求先后顺序  如果加parent搬到outer后面就会编译失败 这是C++的编译机制
{

};
class outer: public parent
{
    private:
        static int outNum;
    public:
        class inner
        {
            public:
                int inNum;
                void showInner()
                {
                    cout<<outNum<<endl;    //只有outNum是static 才可以这样直接引用  因为加载inner时会加载outer  随着的是static
                                            //而java中由于 outer.this引用的存在  必须要有外部实例才可以再实例化innner

                }


        };
};

int outer::outNum=100;
int main()
{
    outer::inner inr;
    inr.showInner();
    return 0;
}
