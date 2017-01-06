/*
	这里判断是否存在中文的方法是看是否有连续两个字节的高位是 1. 网络上给出了中文编码的起始位，但是通过测试，这个编码又跟相应的编码是 utf8 还是ansi之类的有关。
	但是，他们都符合连续两字节都是高位是 1。 当然这样的判断因该说是判断了 “不是普通的assic”编码
*/
#include <iostream>

using namespace std;

bool chineseInCheck(const string & s){
	for(int i = 0; i < s.length(); ++i){
		if(s[i] & 0x80 && i + 1 < s.length() && s[i+1] & 0x80) //连续两个字节高位是 1. assic码表只是占用了 0 ~ 127
			return true;
	}
	return false;
}

int main(int argc, char ** args){   cout << 0xa1 << endl; return 0;
	string str1 = "there is no Chinese in this string";
	string str2 = "there are some 中文哈哈 in this string"; //多字节，“中文”两个字占了 4 字节(这里是ansi编码，如果是utf8编码，通过实验发现占6个)
	cout << boolalpha << chineseInCheck(str1) << endl << chineseInCheck(str2) << endl;
	cout << "-------------------------------" << endl;
	for(int i = 0; i < str2.length(); ++i){
		cout << "{ " << dec << i << " : " << hex << (int)str2[i] << " : " << str2[i] << " }";
	} cout << endl << str2 << endl;
	cout << "-------------------------------" << endl;
	return 0;
}