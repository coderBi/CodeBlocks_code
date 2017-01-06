#include <iostream>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory>

using namespace std;

//typedef unsigned int byte;

int WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow){
	char szFileName[] = "test.png";
	FILE * pFile = fopen(szFileName,"rb");
	if(NULL == pFile)
	{
		printf("文件打开出错，请检查文件是否已经存在或被删除\n");
		return 0;
	}
	//将文件指针从末尾的位置移动0，也即是将文件指针移动到文件末尾
	fseek(pFile,0,SEEK_END);
	//ftell得到文件内部指针相对于文件首的偏移
	int length = ftell(pFile);
	byte * buff = new byte[length + 1];
	memset(buff,0,length+1);
	//移动指针到起始位置
	fseek(pFile,0,SEEK_SET);
	//fread,第一个参数是void*,第二个参数是指的每一次读取的数据占的字节数，第三个参数指一次最多读取多少个
	cout << fread(buff,sizeof(byte),length,pFile) << endl;
	cout << buff << endl;
	fclose(pFile);
}