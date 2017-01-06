#include <iostream>
#include <stdio.h>

using namespace std;

int main(){
	int a;
	cout << "&a, a: " << &a << "  " << a << endl;
	//printf("&a, a: %d  %d\n", &a, a); //printf打印的值会变动，cout不会
	return 0;
}