#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> test;
    for(int i = 0; i < 10000; ++i){
        test.insert(test.begin()+0, i);
    }
    for(int i = 0; i < test.size(); i += 1000){  //程序正常运行 说明向空的vector起始位循环插入数据，空间开销内部维护ok。
        cout << test[i] << endl;
    }
    return 0;
}
