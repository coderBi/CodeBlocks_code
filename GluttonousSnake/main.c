#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define W  50
#define H  20

#define QIANG  '#'		//墙
#define FOOD1  '*'		//第一种食物
#define FOOD2  '&'		//第二种食物
#define FOOD3  '$' 		//第三种食物
#define SHITHEAD '@'  	//蛇头
#define SHITBODY '+'	//蛇身体
#define SHITNULL ' '  	//空身体

struct
{
	int x;
	int y;
} shits[W*H];

struct
{
	int x;
	int y;
	int type;
} food;

enum _dir{UP=0, RIGHT=1, DOWN=2, LEFT=3};
enum _game_state{START, PLAYING, PAUSE, OVER};
int len=0;					//蛇的长度
enum _dir dir = RIGHT;   			//表示蛇的方向
enum _dir kdir = RIGHT;			//表示 哪个方向的按键被按下
enum _game_state gs;		//游戏状态
int level = 1;				//表示第几关
long score = 0;				//分数
long maxscore = 0;			//最高分

void HideTheCursor(void);
void SetColor(int ForgC);
void gotoXY(int x, int y);
void ConPrintAt(int x, int y, char *CharBuffer, int len);
void ShowTheCursor(void);
void ClearConsole(void);

void init();			//初始化地图 食物 等游戏数据
void draw();  			//负责调用所有画界面的函数
void draw_map();  		//画围墙
void draw_shit();		//画蛇
void draw_food();		//画食物
void input();			//负责接受用户输入
void update();			//负责更新游戏数据
int check();			//检测游戏是否结束
void eat_food();		//吃食物，设置新的食物
int can_set_food(int x, int y);  //检测是否可以放食物，返回0表示可以
void show_start();
void show_over();
void show_pause();
void show_playing();

int main()
{
	DWORD otime=0, ctime=0;
BEGIN:
	ctime = GetTickCount();
	init();
	while(1)
	{
		ctime = GetTickCount();
		input();
		if (ctime-otime<550-50*level)
		{
			Sleep(10);
			continue;
		}
		gotoXY(W+4,2);
		printf("游戏状态");
		gotoXY(W+2, 3);

		if(gs == START)
		{
			show_start();
		}
		else if(gs==PAUSE)
		{
			show_pause();
		}
		else if(gs==OVER)
		{
			show_over();
			goto BEGIN;
		}
		else if(gs==PLAYING)
		{
			show_playing();
			update();
			if(check()) continue;
			draw();

			gotoXY(W+4,10);
			printf("当前分数:%ld", score);
			gotoXY(W+4,12);
			printf("最高分数:%ld", maxscore);


			gotoXY(W+4,14);
			printf("当前等级:%d", level);
		}
		otime = ctime;
	}
	return 0;
}


void init()
{
	memset(shits, 0, sizeof(shits));
	shits[0].x = 8;
	shits[0].y = 8;

	shits[1].x = 7;
	shits[1].y = 8;

	shits[2].x = 6;
	shits[2].y = 8;

	score = 0;
	level=1;
	len = 3;
	dir = RIGHT;
	kdir = RIGHT;
	food.type = 0;
	eat_food();

	gs = START;
	ClearConsole();
	HideTheCursor();

	SetColor(4);
	draw_map();
}


void input()
{
	if(!_kbhit()) return;

	switch(getch())
	{
	case 'W':
	case 'w':
		kdir = UP;
		break;
	case 'D':
	case 'd':
		kdir = RIGHT;
		break;
	case 'S':
	case 's':
		kdir = DOWN;
		break;
	case 'A':
	case 'a':
		kdir = LEFT;
		break;
	case 'R':
	case 'r':
		if(gs==OVER)
			gs=START;
	case ' ':
		if(gs==PLAYING)
			gs = PAUSE;
		else
			gs = PAUSE;
		break;
	default:
		gs = PLAYING;
		break;
	}
}


void draw()
{
	static int i=0;

	SetColor(15);
	draw_shit();
	SetColor(2);
	draw_food();
}

void draw_map()
{
	int x, y;
	for(x=0; x<=W; x++)
	{
		gotoXY(x,0);
		putchar(QIANG);
		gotoXY(x,H);
		putchar(QIANG);
	}
	for(y=0; y<=H; y++)
	{
		gotoXY(0, y);
		putchar(QIANG);
		gotoXY(W, y);
		putchar(QIANG);
	}
}



void draw_shit()
{
	int i=0;
	while(i<len)
	{
		gotoXY(shits[i].x, shits[i].y);
		if(i==0)
		{
			putchar(SHITHEAD);
		} else {
			putchar(SHITBODY);
		}
		i++;
	}
	if(shits[len].x!=0)
	{
		gotoXY(shits[len].x, shits[len].y);
		putchar(SHITNULL);
	}

}

void draw_food()
{
	char fch;

	switch(food.type)
	{
	case 1:
		fch = FOOD1;
		break;
	case 2:
		fch = FOOD2;
		break;
	case 3:
		fch = FOOD3;
		break;
	default:
		return;
	}
	gotoXY(food.x, food.y);
	putchar(fch);
}



void update()
{
	int i=len;
	while(i--)
	{
		shits[i+1].x = shits[i].x;
		shits[i+1].y = shits[i].y;
	}

	//不能向后走
	if(kdir == (dir+2)%4)
		kdir = (kdir+2)%4;

	switch(kdir)
	{
	case UP:
		shits[0].y--;
		break;
	case RIGHT:
		shits[0].x++;
		break;
	case DOWN:
		shits[0].y++;
		break;
	case LEFT:
		shits[0].x--;
		break;
	default:
	break;
	}
	//更新蛇的方向
	dir = kdir;

	//检测吃食物
	eat_food();

}


int check()
{
	int x=shits[0].x, y=shits[0].y, i;


	//撞到墙
	if(x<=0 || x>=W || y<=0 || y>=H)
	{
		gs = OVER;
		return 1;
	}

	//撞到自己
	for(i=1; i<len; i++)
	{
		if(x == shits[i].x && y == shits[i].y)
		{
			gs = OVER;
			return 1;
		}
	}

	return 0;
}

/*返回0 表示可以放*/
int can_set_food(int x, int y)
{
	int i;
	//不能出现在墙里
	if(x<=0 || x>=W || y<=0 || y>=H) return 1;

	//不能出现在蛇身上
	for(i=0; i<len; i++)
	{
		if(x==shits[i].x && y==shits[i].y)
			return 1;
	}

	return 0;
}

void eat_food()
{
	int fx, fy, ft;

	if(food.type > 0)
	{
		if(food.x==shits[0].x && food.y==shits[0].y)
		{
			//吃掉食物
			food.type=-1;
			//身体变长
			len++;

			//分数增加
			score += 10;
			if(score>maxscore)
				maxscore = score;

			level = score/50 + 1;
			if(level>10) level = 10;  //最多10级
		}
		return;
	}

	srand((int)time(NULL));
	while(1)
	{
		int t,i;
		fx = rand()%W;
		fy = rand()%H;
		ft = rand()%3+1;
		if(!can_set_food(fx, fy)) break;
	}

	food.x = fx;
	food.y = fy;
	food.type = ft;
}


void show_start()
{

	printf("按任意键开始\n");
}

void show_over()
{
	printf("游戏结束，按R重新开始\n");
}

void show_pause()
{
	printf("游戏暂停中，按任意键\n");
}

void show_playing()
{
	printf("游戏中,按空格暂停\n");
}

void gotoXY(int x, int y)
{
   //Initialize the coordinates
   COORD coord = {x, y};
   //Set the position
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void SetColor(int ForgC)
{
   WORD wColor;
   //We will need this handle to get the current background attribute
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   //We use csbi for the wAttributes word.
   if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
   {
      //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
   }
}



void ConPrintAt(int x, int y, char *CharBuffer, int len)
{
   DWORD count;
   COORD coord = {x, y};
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleCursorPosition(hStdOut, coord);
   WriteConsole(hStdOut, CharBuffer, len, &count, NULL);
}

void ClearConsole()
{
   //Get the handle to the current output buffer...
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   //This is used to reset the carat/cursor to the top left.
   COORD coord = {0, 0};
   //A return value... indicating how many chars were written
   //   not used but we need to capture this since it will be
   //   written anyway (passing NULL causes an access violation).
   DWORD count;
   //This is a structure containing all of the console info
   // it is used here to find the size of the console.
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   //Here we will set the current color
   if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
   {
      //This fills the buffer with a given character (in this case 32=space).
      FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
      FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
      //This will set our cursor position for the next print statement.
      SetConsoleCursorPosition(hStdOut, coord);
   }
}

void HideTheCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//Shows the console cursor
void ShowTheCursor()
{
   CONSOLE_CURSOR_INFO cciCursor;
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

   if(GetConsoleCursorInfo(hStdOut, &cciCursor))
   {
      cciCursor.bVisible = TRUE;
   }
}
