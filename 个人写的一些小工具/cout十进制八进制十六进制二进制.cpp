/*
	注： std下面有 dec oct hex 但是没有像java里面的 bin。所以需要利用bitset
*/
#include <iostream> 
#include <bitset>

using namespace std;

int main(int argc, char ** args){
	int x = 10;
	cout << "10进制： " << dec << x << endl << "8进制： " << oct << x << endl << "16进制： " << hex << x << endl;
	cout << "2进制： " << bitset<sizeof(int)>(x) << endl; //bitset <>里面指定长度， 括号里面可以是unsigned long 和 string
	return 0;
}