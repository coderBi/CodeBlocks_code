/*
    通过测试，下面两种写法共同的地方：
        ①：读到末尾（结束标志）结束循环
        ②：读入出错，例如在输入中放入一个字符“x”，都会出错，
        ③：cin.peek可以预先感知到下一个是否满足需求。
*/

#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    int n;
    ///FILE * file = freopen("test.txt","w",stdout);

    /* 第一种情况： 直接在循环条件中写 cin >>
    cout << "------------------------------------------------------------" << endl;
     while(cin >> n){
        cout << "n: " << n << endl;
    }*/

    ///* 第二种情况：循环条件通过cin.peek
    cout << "------------------------------------------------------------" << endl;
    while(cin.peek() != EOF){
        cin >> n;
        cout << "n: " << n << endl;
    }//*/

    /* 补充测试： 查看cin.get
    while(cin.peek() != EOF){ //可以发现cin.get可以得到任意字符，包括空格跟换行
        char c;
        cin.get(c);
        cout << "c : " << c << endl;
    }
    */

    return 0;
}
