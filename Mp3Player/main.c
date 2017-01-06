/*
 * mp3.c
 *
 *  Created on: 2010-12-12
 *      Author: thankyouxue
 */

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <mmsystem.h>
#include <io.h>
//#include <tcconio.h>


void clrscr(HANDLE hConsole);
void gotoxy(/*HANDLE hOut, */int x, int y);

int _chdir(const char *dirname);
int enter_path();
void Usage();
void Play();
void Stop();
void Pause();
void Resume();
void Speed();
void Position(); /* Prototipi na vsichki funkci */
void GetAllSong();
void StatSong();
void CloseSong();
void init();
void AutoP_List();
void p_NextList();
void p_PrevList();
void GetOldColor();
void GetSongLength();
void GetTotalTimeAllSong();
void GetTimeAddSong();
void GetTimeDelSong();
void write_data();
void Quit();

#define max_num 1000
const char file_path[128] = "path.txt";
char old_path[128];

char NextSong[max_num][128];
char ShortPathName[max_num][80];
char LongFileName[max_num][128]; /* Vsichki 2-merni i 3-merni masivi */
char CompareNames[max_num][128];
char p_List[15][10][128];
char p_file[15][10][128];

char Label[128]; /* vischki ednomerni masivi */
char UserName[128];
char speed[128];
char dirname[128];

int i, s, p;
int a, b, v;
int err;
int isPlay; /* Vsichki celochisleni promenlivi */
int Control;
int TotalSong;
int p_count;
int a_uto;
int m_null;
int num;
int MAX;
unsigned getlen;

int number[max_num];
int mm_time;

int stop_flash;
int m_normal_text;

int p_change;
int y[1000];
int x = 25;

int h2, m2, s2;

int main(void) {
	int ret;
	FILE *in;
	struct _finddata_t f;
	system("CLS");//system("CLS");//clrscr();

	DWORD nUserName = sizeof(UserName); /* Vzemane na user name */

	if (GetUserName(UserName, &nUserName) == 0) {
		printf("Failed to lookup user name, error code "/*, GetLastError()*/);
	}

	system("CLS");//system("CLS");//clrscr();
	memset(dirname, '\0', sizeof(dirname));

	if ((ret = _findfirst("*.mp3", &f)) < 0) {

		for (;;) {
			GetCurrentDirectory(256, old_path);
			if ((in = fopen(file_path, "rb")) == NULL) {
				enter_path();
				break;
			}
			fread((void*) &dirname, sizeof(char), 128, in);
			fclose(in);
			break;
		}
	}

	GetAllSong(); /* Zarejdane na pesnite v masiva */
	init(); /* initializirane na play listata */

	FILE * p;

	if ((p = fopen("length.txt", "rb")) == NULL) {
		GetTotalTimeAllSong();
		goto label1;
	}

	if (p) {
		fscanf(p, "%d %d %d %d %d", &h2, &m2, &s2, &mm_time, &getlen);
		fclose(p);
	}

	if ((p = fopen("number.txt", "rb")) == NULL)
		goto label1;
	if (p) {
	    int f;
		for (f = 0; f < mm_time; f++) {
			fread((void*) &number[f], sizeof(int), 1, p);
		}
		fclose(p);
	}

	if ((p = fopen("names.txt", "rb")) == NULL)
		goto label1;
	if (p) {
        int f;
		for (f = 0; f < TotalSong; f++) {
			fread((void*) &CompareNames[f], sizeof(char), 1024, p);
		}
		fclose(p);
	}

	if (TotalSong > mm_time)
		GetTimeAddSong();
	if (TotalSong < mm_time)
		GetTimeDelSong();

	label1:

	Play(); /* Prosfirvane na parvia file ot masiva s dani */
	Usage(); /* glavno menu za user */
	return 0;
}

int enter_path() {

	int i;
	int a1, b1;
	int ret;
	char str[128];
	char ch;
	FILE *out;

	system("CLS");//clrscr();

	memset(str, '\0', sizeof(str));

	gotoxy(1, 25);
	printf("MP3 Pro v 2.0 copyright (C) 2002.Press Esc to exit.");
	gotoxy(1, 2);
	printf("Enter path to your mp3 song(s): ");

	i = 0;

	while (1) {

		ch = getch();
		if (ch == 27)
			return -1;
		if (ch == 13) {
			if (i == 0)
				continue;
			break;
		}

		if (ch == 8) {
			str[i] = '\0';
			i--;
			if (i < 0) {
				i = 0;
				continue;
			}
			system("CLS");//clrscr();
			gotoxy(1, 25);
			printf("Mp3 Pro v 2.0 copyright (C) 2003.Press Esc to exit.");
			gotoxy(1, 2);
			printf("Enter path to your mp3 song(s): ");

			for (a1 = 0; a1 < i; a1++)
				printf("%c", str[a1]);
		}

		if (ch != 8 && ch != 13 && ch != 27 && ch != 9) {

			str[i] = ch;
			i++;
			if (i > 20) {
				i = 20;
				continue;
			}
			gotoxy(33, 2);
			for (b1 = 0; b1 < i; b1++)
				printf("%c", str[b1]);
		}

	}

	if ((ret = _chdir(str)) < 0) { /* Provarka za validen pat example d:\music\2003 */

		gotoxy(33, 15);
		printf("Path is not valid!");
		getch();
		return -1;
	}

	_chdir(old_path);

	strcpy(dirname, str);

	if ((out = fopen(file_path, "wb")) == NULL)
		exit(1); /* Zapisvame dirname v path.txt */
	fprintf(out, "%s", dirname);
	fclose(out);

	return 0;

}

void Usage() {
	char ch;
	int max_len = 0;
	int i;
	FILE *in;
	system("CLS");//clrscr();
	textcolor(7);
	gotoxy(18, 1);
	printf("Mp3 Pro v 2.0 Programed by Nikolai Halachev BG.");
	gotoxy(18, 2);
	printf("Free MP3 player for windows (95,98)");

	gotoxy(1, 5);

	printf(" P = Play\n");
	printf(" S = Stop\n");
	printf(" W = Pause\n");
	printf(" X = Change Speed\n");
	printf(" C = Change Position\n");
	printf(" -> = Next Song\n");
	printf(" <- = Prev Song\n");
	printf(" L = Load Song(s)\n");
	printf(" Q = Quit");
	gotoxy(1, 20);
	printf(" TotalSong = %d", TotalSong);
	gotoxy(1, 15);
	printf(" Enter your choice: ");

	textcolor(12);
	gotoxy(39, 4);
	printf(" Play List");

	textcolor(7);

	if (TotalSong > 9) {

		textcolor(15);
		gotoxy(25, 15);
		printf("Press (+) to next Play List or (-) to prev Play List");
		textcolor(7);
	}

	max_len = TotalSong / 9;

	gotoxy(50, 4);
	printf("[%d]", p_count + 1);

    int q;
	for (q = 0; p_List[p_count][q][0]; q++) {
		y[q] = 5 + q;
		gotoxy(x, y[q]);
		clreol();
		printf("%d. %s", q + 1, p_List[p_count][q]);

	}

	while (1) {
		for (;;) {

			StatSong(); /* sledene sastoianieto na pesenta */
			GetSongLength();/*Vzimane na daljinata na pesenta */
			if (!isPlay) {

				if (p_count == max_len) {
					if (!strcmp(p_List[p_count][num + 1], "")) {

						p_count = -1;
						p_NextList();
						num = -1;
					}
				}
				if (a_uto) {

					AutoP_List();
					num = -1;
					a_uto = 0;
				}

				if (num == 8) {

					AutoP_List();
					num = -1;
				}
				GetOldColor();
				CloseSong();
				num++;
				Play();
			}

			textcolor(7);
			gotoxy(2, 21);
			printf("User Name: ");

			printf("%s", UserName);

			if (kbhit())
				break;

			sleep(100);

			if (Control) {

				gotoxy(1, 23);
				clreol();
				printf(" Stoped -> %s ", Label);
			}

			if (!Control) {
				gotoxy(1, 23);
				clreol();
				printf(" Playing -> %s ", Label);
			}
			gotoxy(55, 21);
			printf("Copyright (C) 2003");
		}

		ch = getch();

		int hot_key = 0;
		char *s_key;

		s_key = (char*) malloc(100);

		s_key[0] = ch;
		hot_key = atoi(s_key);

		if (p_count == max_len) {

			if (!strcmp(p_List[p_count][hot_key - 1], ""))
				goto label1;
		}

		if (hot_key > TotalSong)
			goto label1;

		if (hot_key) {

			if (hot_key == 9)
				a_uto = 1;

			if (hot_key < 9)
				a_uto = 0;

			num = hot_key - 1;
			CloseSong();
			Play();
			if (m_null)
				goto label1;
			GetOldColor();

		}

		label1: m_null = 0;

		Control = 0;

		if (tolower(ch) == 'p') {
			CloseSong();
			Play();
		}
		if (tolower(ch) == 's')
			Stop(); /* Izvikvane na funk Stop */
		if (tolower(ch) == 'w')
			Pause(); /* izvikvane na funk Pause */
		if (tolower(ch) == 'x')
			Speed(); /* Izvikvane na funk Speed */
		if (tolower(ch) == 'c')
			Position(); /* izvikvane na funk Position */

		if (tolower(ch) == 'l') { /* Zarejdane na nova diriktoria ot mp3-ki */

			_chdir(old_path);
			if ((i = enter_path()) < 0)
				Usage();

			_chdir(dirname);

			memset(NextSong, '\0', sizeof(NextSong));
			memset(CompareNames, '\0', sizeof(CompareNames));
			memset(ShortPathName, '\0', sizeof(ShortPathName));
			memset(LongFileName, '0', sizeof(LongFileName));
			memset(p_List, '\0', sizeof(p_List));
			memset(p_file, '\0', sizeof(p_file));
			p_count = 0;
			m_null = 0;
			mm_time = 0;

			GetAllSong();

			GetTotalTimeAllSong();
			init();
			_chdir(old_path);
			Play();
			Usage();
		}

		if (ch == '=')
			p_NextList(); /* Obhojdane na play listata napred */

		if (ch == '-')
			p_PrevList(); /* Obhojdane na play listata nazad */

		if (ch == 0x4d) {
			CloseSong();
			num++;
			int bc;
			for (bc = 0; p_List[p_count][bc][0]; bc++)
				;

			if (num > bc - 1) {
				p_NextList();
				p_change = 1;
				a_uto = 0;
				num = 0;
			}

			GetOldColor();
			isPlay = 0;
			Play();
		}

		if (ch == 0x4b) {
			CloseSong();
			num--;
			isPlay = 1;
			GetOldColor();
			Play();
		}

		if (tolower(ch) == 'q')
			Quit();
	}
}

void Play() {

	char FileName[128];
	_chdir(dirname);

	if (!isPlay) {

		strcpy(FileName, "open ");
		strcat(FileName, NextSong[num]);
		strcat(FileName, " alias song");
		strcpy(speed, "set song speed ");
		strcat(speed, "1000");
		strcpy(Label, p_List[p_count][num]);
	}

	if (isPlay) {

		if (num < 0)
			num = 0;
		strcpy(FileName, "open ");
		strcat(FileName, NextSong[num]);
		strcat(FileName, " alias song");
		strcpy(speed, "set song speed ");
		strcat(speed, "1000");
		strcpy(Label, p_List[p_count][num]);

	}

	err = mciSendString(FileName, 0, 0, 0);

	if (err > 0) {
		perror("error");
		exit(1);
	}

	err = mciSendString(speed, 0, 0, 0);

	if (err > 0) {
		perror("error");
		exit(1);
	}

	err = mciSendString("play song", 0, 0, 0);

	if (err > 0) {
		perror("error");
		exit(1);
	}

	if (p_change) {

		strcpy(Label, p_List[p_count][0]);
		p_change = 0;
	}

	if (!strcmp(Label, ""))
		strcpy(Label, LongFileName[0]);

}

void Stop() {

	err = mciSendString("stop song", 0, 0, 0);
	Control = 1;
	if (err > 0) {
		perror("error");
		exit(1);
	}
}

void Pause() {

	char ch;
	err = mciSendString("pause song", 0, 0, 0);

	if (err > 0) {
		perror("error");
		exit(1);
	}

	gotoxy(1, 23);
	clreol();
	printf(" Paused -> %s ", Label);

	while (1) {
		ch = getch();
		if (tolower(ch) == 'w') {
			gotoxy(1, 23);
			clreol();
			printf(" Playing -> %s ", Label);
			Resume();
			break;
		}

	}

}

void Resume() {
	err = mciSendString("resume song", 0, 0, 0);
	if (err > 0) {
		perror("error");
		exit(1);
	}
}

void Speed() {

	char Stat[20];
	char bit[128];
	char str[128];
	char ch;

	stop_flash = 1;

	memset(str, '\0', sizeof(str));

	system("CLS");//clrscr();
	strcpy(bit, "set song speed ");
	gotoxy(1, 25);
	printf("MP3 Pro v 2.0 copyright (C) 2002.Press Esc to exit.");
	gotoxy(1, 2);
	printf("Change speed: ");

	i = 0;

	while (1) {
		for (;;) {
			mciSendString("status song mode", Stat, 128, 0);
			StatSong();
			if (!isPlay)
				Usage();

			if (kbhit())
				break;
		}

		ch = getch();

		if (ch == 27) {
			stop_flash = 0;
			Usage();
		}

		if (ch == 13) {
			if (i == 0)
				continue;
			break;
		}

		if (ch == 8) {
			str[i] = '\0';
			i--;
			if (i < 0) {
				i = 0;
				continue;
			}

			system("CLS");//clrscr();
			gotoxy(1, 25);
			printf("MP3 Pro v 2.0 copyright (C) 2002.Press Esc to exit.");
			gotoxy(1, 2);
			printf("Change speed: ");

			for (a = 0; a < i; a++)
				printf("%c", str[a]);
		}

		if (ch != 8 && ch != 13 && ch != 27 && ch != 9) {

			str[i] = ch;
			i++;
			if (i > 3) {
				i = 3;
				continue;
			}
			gotoxy(15, 2);
			for (b = 0; b < i; b++)
				printf("%c", str[b]);
		}
	}

	if (i == 3)
		str[i] = '0';
	if (i == 2) {
		str[i + 1] = '\0';
		str[i] = '0';
	}
	strcat(bit, " ");
	strcat(bit, str);

	int song_length = atoi(str);

	song_length = song_length / 10;

	if (song_length > 200) {

		gotoxy(20, 10);
		printf("Speed is large maximum change of speed = 200");
		getch();
		Speed();
	}

	err = mciSendString(bit, 0, 0, 0);

	if (err > 0) {
		perror("error");
		exit(1);
	}

	stop_flash = 0;
	Usage();

}

void Position() {

	char Stat[20];
	char ch;
	char change[128];
	char str[128];

	memset(str, '\0', sizeof(str));

	system("CLS");//clrscr();
	stop_flash = 1;

	strcpy(change, "play song from ");
	gotoxy(1, 25);
	printf("MP3 Pro v 2.0 copyright (C) 2002.Press Esc to exit.");
	gotoxy(1, 2);
	printf("Enter value for position: ");

	i = 0;

	while (1) {

		for (;;) {
			err = mciSendString("status song mode", Stat, 128, 0);
			if (err > 0) {
				perror("error");
				exit(1);
			}
			StatSong();
			if (!isPlay)
				Usage();
			if (kbhit())
				break;
		}

		ch = getch();
		if (ch == 27) {
			stop_flash = 0;
			Usage();
		}
		if (ch == 13) {
			if (i == 0)
				continue;
			break;
		}

		if (ch == 8) {
			str[i] = '\0';
			i--;
			if (i < 0) {
				i = 0;
				continue;
			}
			system("CLS");//clrscr();
			gotoxy(1, 25);
			printf("MP3 Pro v 2.0 copyright (C) 2002.Press Esc to exit.");
			gotoxy(1, 2);
			printf("Enter value for position: ");

			for (a = 0; a < i; a++)
				printf("%c", str[a]);
		}

		if (ch != 8 && ch != 13 && ch != 27 && ch != 9) {

			str[i] = ch;
			i++;
			if (i > 3) {
				i = 3;
				continue;
			}
			gotoxy(27, 2);
			for (b = 0; b < i; b++)
				printf("%c", str[b]);
		}

	}

	if (i == 2) {
		str[i] = '0';
		str[i + 1] = '0';
		str[i + 2] = '0';
	}

	if (i == 3) {
		str[i] = '0';
		str[i + 1] = '0';
		str[i + 2] = '0';
	}

	int i;

	int song_len = atoi(str);
	song_len = song_len / 1000;
	int count = p_count;
	if (count > 0) {
		count++;
		count = count * 9;
		count = count - 9;
	}

	i = count + num;

	if (song_len > number[i]) {

		gotoxy(20, 10);
		printf("Length is large.Maximum change oflength = %d", number[i]);
		getch();
		Position();

	}

	strcat(change, str);

	err = mciSendString(change, 0, 0, 0);

	if (err > 0) {
		perror("Error");
		exit(1);
	}

	stop_flash = 0;
	Usage();

}

void GetAllSong() {

	struct _finddata_t f;
	long int r;
	long int RetVal;
	int Len;
	char Name[128];
	FILE *out;

	memset(NextSong, '\0', sizeof(NextSong));
	memset(LongFileName, '\0', sizeof(LongFileName));

	system("CLS");//clrscr();

	_chdir(dirname);

	r = _findfirst("*.mp3", &f);

	if (r < 0) {

		_chdir(old_path);
		if ((out = fopen(file_path, "rb")) == NULL) {
			gotoxy(20, 10);
			printf("Sorry no mp3 file(s) on this dirictory");
			gotoxy(20, 11);
			printf("Press eny key to continue");
			getch();
			exit(1);
		}

		gotoxy(20, 10);
		printf("-> %s Path is not valid", dirname);
		gotoxy(20, 11);
		printf("Press eny key to exit");
		getch();
		fclose(out);
		remove(file_path);
		exit(1);

	}

	while (1) {

		if (err < 0)
			break;
		sprintf(Name, "%s", f.name);
		strcpy(NextSong[num], Name);
		strcpy(LongFileName[num], NextSong[num]);
		err = _findnext(r, &f);

		Len = 255;
		RetVal = GetShortPathName(NextSong[num], ShortPathName[num], Len);
		if (RetVal < 0)
			exit(1);
		strcpy(NextSong[num], ShortPathName[num]);
		if (num > max_num) {
			system("CLS");//clrscr();
			gotoxy(28, 10);
			printf("MAX 1000 mp3 files");
			getch();
			exit(1);
		}
		num++;

	}

	TotalSong = num;
	num = 0;

	_chdir(old_path);

}

void StatSong() {

	char Stat[20];
	err = mciSendString("status song mode", Stat, 128, 0);

	if (err > 0) {
		perror("error");
		exit(1);
	}

	if (!strcmp(p_List[p_count][num], "")) {
		m_null = 1;
		return;
	}

	if (!strcmp(Stat, "playing")) {
		isPlay = 1;

		if (stop_flash)
			return;

		int i;

		int count = p_count;

		if (count > 0) {

			count++;
			count = (count * 9) - 9;

		}

		i = count + num;

		if (!strcmp(Label, LongFileName[i])) {

			m_normal_text = num;

			textcolor(14); /* cviat za migane 14 = jalt*/

			gotoxy(x, y[num]);/* flash na play listata */
			clreol();
			sleep(150);
			gotoxy(x, y[num]);
			printf("%d. %s", num + 1, Label);
			sleep(150);

		}

		return;
	}
	isPlay = 0;

	if (Control)
		isPlay = 1;

}

void CloseSong() {

	err = mciSendString("close song ", 0, 0, 0);

	if (err > 0) {
		perror("error");
		exit(1);

	}

}

void init() {

	int ret;
	int d, g, z;

	z = 0;

	for (d = 0; NextSong[d][0]; d++) { /* Zarejdane na parvata play lista */

		if (z == 9) {
			p_count++;
			z = 0;

		}
		/* Skasiavane na golemite imena */

		int len;
		for (len = 0; NextSong[len][0]; len++) {

			ret = strlen(LongFileName[len]);

			if (ret >= 50) {

				for (g = 50; LongFileName[len][g]; g++)
					LongFileName[len][g] = '\0';
			}
			/* premahvane na mp3 natpisa ot file */
			int v;
			for (v = 0; v < ret; v++) {

				if (LongFileName[len][v] == '.') {
				    int p;
					for (p = v; p < ret; p++)
						LongFileName[len][p] = '\0';
				}
			}
		}

		strcpy(p_List[p_count][z], LongFileName[d]);
		strcpy(p_file[p_count][z], NextSong[d]);
		z++;
	}

	MAX = p_count;
	p_count = 0;

}

void AutoP_List() {

	p_count++;

    int q;
	for (q = 0; p_List[p_count][q][0]; q++) {

		if (!strcmp(p_List[p_count][q + 1], "")) {
            int v;
			for (v = q; v < 9; v++) {

				y[v] = 5 + v;
				gotoxy(x, y[v]);
				clreol();
			}

		}

		y[q] = 5 + q;
		gotoxy(x, y[q]);
		clreol();
		textcolor(7);
		printf("%d. %s", q + 1, p_List[p_count][q]);
		strcpy(NextSong[q], p_file[p_count][q]);

	}

	gotoxy(50, 4);
	printf("[%d]", p_count + 1);
	m_normal_text = 0;

}

void p_NextList() {

	int q;

	if (p_count >= MAX) {
		stop_flash = 0;
		return;
	}

	for (q = 0; p_List[p_count][q][0]; q++) {

		y[q] = 5 + q;
		gotoxy(x, y[q]);
		clreol();
	}

	p_count++;

	if (!p_count) {

		for (q = 0; p_List[p_count][q][0]; q++) {

			y[q] = 5 + q;
			gotoxy(x, y[q]);
			clreol();
		}

	}

	for (q = 0; p_List[p_count][q][0]; q++) {

		y[q] = 5 + q;
		gotoxy(x, y[q]);

		printf("%d. %s", q + 1, p_List[p_count][q]);
		strcpy(NextSong[q], p_file[p_count][q]);
		strcpy(LongFileName[q], p_List[p_count][q]);

	}

	gotoxy(50, 4);
	printf("[%d]", p_count + 1);

}

void p_PrevList() {

	if (p_count <= 0)
		return;
    int q;
	for (q = 0; *p_List[p_count][q]; q++) {

		y[q] = 5 + q;
		gotoxy(x, y[q]);
		clreol();
	}

	p_count--;
    int t;
	for (t = 0; p_List[p_count][t][0]; t++) {

		y[t] = 5 + t;
		gotoxy(x, y[t]);

		printf("%d. %s", t + 1, p_List[p_count][t]);
		strcpy(NextSong[t], p_file[p_count][t]);
		strcpy(LongFileName[t], p_List[p_count][t]);

	}

	gotoxy(50, 4);
	printf("[%d]", p_count + 1);

}

void GetOldColor() {

	textcolor(7); /* return old color */

	gotoxy(x, y[m_normal_text]);
	printf("%d. %s", m_normal_text + 1, p_List[p_count][m_normal_text]);
	m_normal_text = 0;

}

void GetSongLength() {

	char lpszReturnString[128];
	char curr_time[128];
	int h, m, s;
	int h1, m1, s1;

	memset(lpszReturnString, '\0', sizeof(lpszReturnString));

	h = m = s = 0;
	h1 = m1 = s1 = 0;

	mciSendString("status song length", lpszReturnString, 128, 0);
	mciSendString("status song position", curr_time, 128, 0);

	if (lpszReturnString) { /* Get Total time */

		int len = atoi(lpszReturnString);
		len = len / 1000;
        int count;
		for (count = 0; count < len; count++) {

			if (s == 60) {
				s = 0;
				m++;
			}
			if (m == 60) {
				m = 0;
				h++;
			}

			s++;

		}

	}

	if (curr_time) { /* Get current time */

		int len1 = atoi(curr_time);
		len1 = len1 / 1000;

        int register count;
		for (count = 0; count < len1; count++) {

			if (s1 == 60) {
				s1 = 0;
				m1++;
			}
			if (m1 == 60) {
				m1 = 0;
				h1++;
			}

			s1++;

		}

	}

	textcolor(7);

	gotoxy(25, 19);
	printf("%s -> %02d:%02d:%02d", "Total Time", h2, m2, s2);

	gotoxy(25, 20);
	clreol();
	printf("%s = %02d:%02d", "Current Time", m1, s1);
	gotoxy(25, 21);
	printf("%s = %02d:%02d", "End Time", m, s);

	if (m >= 60) {
		gotoxy(25, 21);
		printf("%s %d:%d:%d", "End Time", h, m, s);
	}

}

void GetTotalTimeAllSong() {

	char TotalTime[128];
	char song[128];
	char FileName[128];
	unsigned int len;

	int h, m, s;

	h = m = s = 0;
	getlen = 0;

	memset(FileName, '\0', sizeof(FileName));
	memset(song, '\0', sizeof(song));
	memset(TotalTime, '\0', sizeof(TotalTime));
    int n;
	for (n = 0; n < MAX; n++)
		number[n] = 0;

	_chdir(dirname);

	gotoxy(25, 10);
	printf("Please wait... Load Songs");
    int start;
	for (start = 0; start < TotalSong; start++) {

		strcpy(song, "status ");
		strcat(song, NextSong[start]);
		strcat(song, " length");

		strcpy(FileName, "open ");
		strcat(FileName, NextSong[start]);
		strcat(FileName, " alias song");

		gotoxy(25, 14);
		clreol();
		printf("%s", LongFileName[start]);

		mciSendString(FileName, 0, 0, 0);

		mciSendString(song, TotalTime, 128, 0);

		len = atoi(TotalTime);
		len = len / 1000;
		number[start] = len;
		strcpy(CompareNames[start], LongFileName[start]);
		getlen = getlen + len;

		mciSendString("close song", 0, 0, 0);

		if (kbhit())
			exit(1);

	}

	for (start = 0; start < getlen; start++) {

		if (s == 60) {
			s = 0;
			m++;
		}
		if (m == 60) {
			m = 0;
			h++;
		}

		if (h == 24)
			h = 0;

		s++;

	}

	h2 = h;
	m2 = m;
	s2 = s;

}

void GetTimeAddSong() {

	char lpszReturnString[128];
	char FileName[128];
	int count[1000];
	int i;
	unsigned len = 0;
	;
	int m_getlen = 0;
	int m_count;
	int put_name = 0;

	_chdir(dirname);

	gotoxy(25, 10);
	printf("Please wait... Load New Songs");

	m_count = 0;

	for (i = 0; i < TotalSong; i++) {
        int st;
		for (st = i; i < TotalSong; i++) {

			if (put_name)
				st = st - m_count;

			if (!strcmp(LongFileName[i], CompareNames[st]))
				break;

			strcpy(FileName, "open ");
			strcat(FileName, NextSong[i]);
			strcat(FileName, " alias song");

			mciSendString(FileName, 0, 0, 0);
			mciSendString("status song length", lpszReturnString, 128, 0);

			gotoxy(25, 14);
			clreol();
			printf("%s", LongFileName[i]);

			len = atoi(lpszReturnString);
			len = len / 1000;
			number[i] = len;
			m_getlen = m_getlen + len;

			mciSendString("close song", 0, 0, 0);
			m_count++;
			put_name = 1;
			break;

		}

	}
    int start;
	for (start = 0; start < m_getlen; start++) {

		if (s2 == 60) {
			s2 = 0;
			m2++;
		}
		if (m2 == 60) {
			m2 = 0;
			h2++;
		}

		if (h2 == 24)
			h2 = 0;

		s2++;

	}

}

void GetTimeDelSong() {

	char lpszReturnString[128];
	char FileName[128];
	char DeleteSongs[max_num][128];
	unsigned len = 0;
	;
	int newTime = 0;
	int m_count = 0;
	int g;
	int a, b = 0;
	int put_name = 0;

	_chdir(dirname);
    int i;
	for (i = 0; i < max_num; i++)
		DeleteSongs[i][0] = '\0';

	gotoxy(25, 10);
	printf("Please wait... Geting new time of songs");

	for (g = 0; g < mm_time; g++) {
        int st;
		for (st = g; TotalSong; st++) {

			if (put_name)
				st = st - m_count;

			if (!strcmp(CompareNames[g], LongFileName[st]))
				break;

			strcpy(DeleteSongs[m_count], CompareNames[g]);
			len = number[g];

			newTime = newTime + len;
			m_count++;
			put_name = 1;
			break;

		}

	}

	getlen = getlen - newTime;
	int h, m, s;

	h = m = s = 0;
	int start;
	for (start = 0; start < getlen; start++) {

		if (s == 60) {
			s = 0;
			m++;
		}
		if (m == 60) {
			m = 0;
			h++;
		}

		if (h == 24)
			h = 0;

		s++;

	}

	h2 = h;
	m2 = m;
	s2 = s;

	if (g <= 1) {
		strcpy(DeleteSongs[g], CompareNames[g]);
		printf("Cannot %s", DeleteSongs[g]);

	}

	system("CLS");//clrscr();
	gotoxy(20, 10);
	printf("some mp3 file(s) missing on your dirictory");

	int a1, b1;

	a1 = 20;
	b1 = 11;

	for (h = 0; h < m_count; h++) {

		gotoxy(a1, b1 + h);
		printf("%s", DeleteSongs[h]);

	}

	getch();

}

void write_data() {

	FILE * p;
	int i;

	_chdir(old_path);

	mm_time = TotalSong;

	if ((p = fopen("length.txt", "wb")) == NULL)
		exit(1);

	fprintf(p, "%d %d %d %d %d", h2, m2, s2, mm_time, getlen);

	fclose(p);

	system("CLS");//clrscr();
	if ((p = fopen("number.txt", "wb")) == NULL)
		exit(1);
    int f;
	for (f = 0; f < TotalSong; f++) {

		fwrite((void*) &number[f], sizeof(int), 1, p);

	}

	fclose(p);

	num = 0;

	GetAllSong();

	init();

	if ((p = fopen("names.txt", "wb")) == NULL)
		exit(1);

	for (f = 0; f < TotalSong; f++)
		fwrite((void*) &LongFileName[f], sizeof(char), 1024, p);

	fclose(p);
}

void Quit() {

	int x, y, z;
	char *about[128] = {
			"Programed by Nikolai Halachev BG E-mail:Jakomen@abv.bg",
			"This programe a freeware.Thank You,copyright (C) 2002" };

	system("CLS");//clrscr();

	x = 15;
	y = 15;

	mciSendString("close song", 0, 0, 0);
    int i;
	for (i = 0; i < 2; i++) {
		for (z = 5; z < y; z++) {
			gotoxy(x, z);
			printf("%s", about[i]);
			gotoxy(x, z - 1);
			clreol();
			sleep(50);
		}
		y = 14;

	}
	write_data();

	sleep(500);
	exit(1);
}


void gotoxy(/*HANDLE hOut, */int x, int y)
{
 COORD pos;
 pos.X = x;
 pos.Y = y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); /* 设置光标位置 */
}

