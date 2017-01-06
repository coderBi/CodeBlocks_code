#include <iostream>
#include <limits>

using namespace std;

int main(){
	cout << "bool : " << numeric_limits<bool>::max() << "  " 
		<< numeric_limits<bool>::min() << endl;
	//cout << "byte : " << numeric_limits<byte>::max() << "  " 
		//<< numeric_limits<byte>::min() << endl;  //不存在byte类型
	cout << "char : " << numeric_limits<char>::max() << "  " 
		<< numeric_limits<char>::min() << endl;
	cout << "short : " << numeric_limits<short>::max() << "  " 
		<< numeric_limits<short>::min() << endl;
	cout << "int : " << numeric_limits<int>::max() << "  " 
		<< numeric_limits<int>::min() << endl;
	cout << "long : " << numeric_limits<long>::max() << "  " 
		<< numeric_limits<long>::min() << endl;

	//对于小数，好像取到的最小值是“最小的正数”
	cout << "float : " << numeric_limits<float>::max() << "  " 
		<< numeric_limits<float>::min() << endl;
	cout << "double : " << numeric_limits<double>::max() << "  " 
		<< numeric_limits<double>::min() << endl;
	cout << "long double : " << numeric_limits<long double>::max() << "  " 
		<< numeric_limits<long double>::min() << endl;
	return 0;
}