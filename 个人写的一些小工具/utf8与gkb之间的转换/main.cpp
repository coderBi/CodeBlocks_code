#include <iostream>
#include <windows.h>

using namespace std;

void translateUtf82GBK(string & utf8){ //utf8转 GBK
    int length1 = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
    WCHAR * wGBK = new WCHAR[length1];
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, wGBK, length1);

    int length2 = WideCharToMultiByte(CP_ACP, 0, wGBK, -1, NULL, 0, NULL, NULL);
    char * gbk = new char[length2];
    WideCharToMultiByte(CP_ACP, 0, wGBK, -1, gbk, length2, NULL, NULL);

    utf8 = gbk;
    delete wGBK;
    delete gbk;
}

void translateGBK2Utf8(string & gbk){ //gbk转utf8
    int length1 = MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, NULL, 0);
    WCHAR * wUtf8 = new WCHAR[length1];
    MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, wUtf8, length1);

    int length2 = WideCharToMultiByte(CP_UTF8, 0, wUtf8, -1, NULL, 0, NULL, NULL);
    char * uft8 = new char[length2];
    WideCharToMultiByte(CP_UTF8, 0, wUtf8, -1, uft8, length2, NULL, NULL);

    gbk = uft8;
    delete wUtf8;
    delete uft8;
}



int main()
{
    string str = "uft页面的字符串";
    cout << "original: " << str << endl;
    translateUtf82GBK(str);
    cout << "utf 2 GBK :" << str << endl;
    translateGBK2Utf8(str);
    cout << "GBK 2 utf :" << str << endl;
    return 0;
}
