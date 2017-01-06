#include <stdio.h>
#include <iostream>
using namespace std;

class Test
{
	public:
		int x, y, z;
};

int main(){
	Test test;
	cout << "&x,&y,&z: " << &test.x << "  " << &test.y << "  " << &test.z << endl;
	cout << "x,y,z: " << test.x << "  " << test.y << "  " << test.z << endl;
	 //测试发现如果将上面的cout注释掉运行这两行代码值也是变动的，但是如果上面的cout不注释这两行同时运行结果会保持一致。
	//printf("&x,&y,&z: %d %d %d\n", &test.x, &test.y, &test.z);
	//printf("x,y,z: %d %d %d\n", test.x, test.y, test.z);
	return 0;
}