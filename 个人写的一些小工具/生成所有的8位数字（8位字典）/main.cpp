/*
    最终得到的txt接近一个g，大小分析：
        ①： 在txt里面每一个8位的int，实际上是 8 个char。也就是8 字节。
        ②： 每一行默认是 \r\n ，占了 2 字节
        ③： 通过上面的分析文件总的大写：(8 + 2) * 100000000 = 1^9。这个数字除以 （1024 * 1024）结果是 953M
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

char * path = "dictionary8.txt";

void createDictionary8(){
    freopen(path,"w",stdout);

    for(unsigned int i = 0; i < 100000000; i++){
        cout.width(8);
        cout.fill('0');
        cout << i << endl;
    }
}

bool checkDictionary8(int low, int high){ //获取脚标low 到 high之间的数据，看看是否与预测的数字一致
    char cArr[1024] = {0};

    freopen(path, "r", stdin);
    for(int i = 0; i < high; ++i){
        cin.getline(cArr, 1024);
        if(i >= low){
            cout << cArr << endl;
            if(atoi(cArr) != i) //atoi 在stdlib.h里面
                return false;
        }
    }
    return true;
}

int main()
{
    cout << boolalpha << checkDictionary8(1000,1030) << endl; //利用boolalpha 输出正常的bool
    return 0;
}
