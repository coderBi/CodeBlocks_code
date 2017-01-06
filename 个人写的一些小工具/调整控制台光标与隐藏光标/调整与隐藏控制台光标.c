#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main(){
	int c;
	HANDLE hout; //控制台句柄
	COORD coord; //屏幕坐标
	CONSOLE_SCREEN_BUFFER_INFO csbi; //控制台屏幕缓冲区信息

	//得到控制台句柄
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	//隐藏光标
	//CONSOLE_CURSOR_INFO cci = {1,0}; // CONSOLE_CURSOR_INFO结构体第一位表示光标宽度，第二位表示光标是否显示
	//SetConsoleCursorInfo(hout, &cci);
	
	while((c= getch()) != EOF){ //利用getch输入，不会自动打印到控制台
		//得到当前坐标
		GetConsoleScreenBufferInfo(hout,&csbi);
		coord.X = csbi.dwCursorPosition.X;
		coord.Y = csbi.dwCursorPosition.Y;
		if(c == 0xE0){ //特殊键
			c = getch(); //获取缓冲区里面的另一部分

			if(c == 0x48){ //向上
				coord.Y = (coord.Y -1 >= 0) ? (coord.Y - 1) : 0;
			} else if(c == 0x50){//向下
				coord.Y++;
			} else if(c == 0x4b){//向左
				coord.X = (coord.X == 0) ? 0 : (coord.X -1);
			} else if(c == 0x4d){ //向右
				coord.X++;
			}
			//重新设置光标
			SetConsoleCursorPosition(hout,coord);
		} else if(c == 0x0d){ //如果是回车就输出换行
			coord.X = 0;
			coord.Y++;
			SetConsoleCursorPosition(hout,coord);
		} else { //其他键，直接打印输出
			printf("%c",c);
		}
	}
	return 0;
}