#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define W  50
#define H  20

#define QIANG  '#'		//ǽ
#define FOOD1  '*'		//��һ��ʳ��
#define FOOD2  '&'		//�ڶ���ʳ��
#define FOOD3  '$' 		//������ʳ��
#define SHITHEAD '@'  	//��ͷ
#define SHITBODY '+'	//������
#define SHITNULL ' '  	//������

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
int len=0;					//�ߵĳ���
enum _dir dir = RIGHT;   			//��ʾ�ߵķ���
enum _dir kdir = RIGHT;			//��ʾ �ĸ�����İ���������
enum _game_state gs;		//��Ϸ״̬
int level = 1;				//��ʾ�ڼ���
long score = 0;				//����
long maxscore = 0;			//��߷�

void HideTheCursor(void);
void SetColor(int ForgC);
void gotoXY(int x, int y);
void ConPrintAt(int x, int y, char *CharBuffer, int len);
void ShowTheCursor(void);
void ClearConsole(void);

void init();			//��ʼ����ͼ ʳ�� ����Ϸ����
void draw();  			//����������л�����ĺ���
void draw_map();  		//��Χǽ
void draw_shit();		//����
void draw_food();		//��ʳ��
void input();			//��������û�����
void update();			//���������Ϸ����
int check();			//�����Ϸ�Ƿ����
void eat_food();		//��ʳ������µ�ʳ��
int can_set_food(int x, int y);  //����Ƿ���Է�ʳ�����0��ʾ����
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
		printf("��Ϸ״̬");
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
			printf("��ǰ����:%ld", score);
			gotoXY(W+4,12);
			printf("��߷���:%ld", maxscore);


			gotoXY(W+4,14);
			printf("��ǰ�ȼ�:%d", level);
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

	//���������
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
	//�����ߵķ���
	dir = kdir;

	//����ʳ��
	eat_food();

}


int check()
{
	int x=shits[0].x, y=shits[0].y, i;


	//ײ��ǽ
	if(x<=0 || x>=W || y<=0 || y>=H)
	{
		gs = OVER;
		return 1;
	}

	//ײ���Լ�
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

/*����0 ��ʾ���Է�*/
int can_set_food(int x, int y)
{
	int i;
	//���ܳ�����ǽ��
	if(x<=0 || x>=W || y<=0 || y>=H) return 1;

	//���ܳ�����������
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
			//�Ե�ʳ��
			food.type=-1;
			//����䳤
			len++;

			//��������
			score += 10;
			if(score>maxscore)
				maxscore = score;

			level = score/50 + 1;
			if(level>10) level = 10;  //���10��
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

	printf("���������ʼ\n");
}

void show_over()
{
	printf("��Ϸ��������R���¿�ʼ\n");
}

void show_pause()
{
	printf("��Ϸ��ͣ�У��������\n");
}

void show_playing()
{
	printf("��Ϸ��,���ո���ͣ\n");
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
