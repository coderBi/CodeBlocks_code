/*
	�����ж��Ƿ�������ĵķ����ǿ��Ƿ������������ֽڵĸ�λ�� 1. �����ϸ��������ı������ʼλ������ͨ�����ԣ���������ָ���Ӧ�ı����� utf8 ����ansi֮����йء�
	���ǣ����Ƕ������������ֽڶ��Ǹ�λ�� 1�� ��Ȼ�������ж����˵���ж��� ��������ͨ��assic������
*/
#include <iostream>

using namespace std;

bool chineseInCheck(const string & s){
	for(int i = 0; i < s.length(); ++i){
		if(s[i] & 0x80 && i + 1 < s.length() && s[i+1] & 0x80) //���������ֽڸ�λ�� 1. assic���ֻ��ռ���� 0 ~ 127
			return true;
	}
	return false;
}

int main(int argc, char ** args){   cout << 0xa1 << endl; return 0;
	string str1 = "there is no Chinese in this string";
	string str2 = "there are some ���Ĺ��� in this string"; //���ֽڣ������ġ�������ռ�� 4 �ֽ�(������ansi���룬�����utf8���룬ͨ��ʵ�鷢��ռ6��)
	cout << boolalpha << chineseInCheck(str1) << endl << chineseInCheck(str2) << endl;
	cout << "-------------------------------" << endl;
	for(int i = 0; i < str2.length(); ++i){
		cout << "{ " << dec << i << " : " << hex << (int)str2[i] << " : " << str2[i] << " }";
	} cout << endl << str2 << endl;
	cout << "-------------------------------" << endl;
	return 0;
}