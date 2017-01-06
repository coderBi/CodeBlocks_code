#include<iostream>

using namespace std;
int i=1;
class MyCls{
public:
    MyCls():m_nFor(m_nThd),m_nSec(i++),m_nFir(i++),m_nThd(i++){
        m_nThd=i;
        cout << "m_nFir = " << m_nFir << endl; //最先初始化为 1， i为 2
        cout << "m_nSec = " << m_nSec << endl; //第二初始化 2 。 i 为 3
        cout << "m_nThd = " << m_nThd << endl; //第三初始化  3。 i 为 4
        cout << "m_nFor = " << m_nFor << endl; //第四初始化为 m_nThd 的引用。 在初始化列表之后会执行初始化函数，导致m_nThd 为 4
    }
    void echo(){
        cout<<"result:"<<m_nFir+m_nSec+m_nThd+m_nFor<<endl;  //结果是 11 = 1 + 2 + 4 + 4
    }
private:
    int m_nFir;
    int m_nSec;
    int m_nThd;
    int &m_nFor;
};
int main()
{
    MyCls oCls;
    oCls.echo();
    return 0;
}
