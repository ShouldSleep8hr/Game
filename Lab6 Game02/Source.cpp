#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(7, 8);
	printf(" <-0-> ");
}
void erase_ship(int x, int y)
{
	gotoxy(x-1, y);
	setcolor(0, 0);
	printf("       ");
	gotoxy(x, y);
	setcolor(0, 0);
	printf("       ");
	gotoxy(x+1, y);
	setcolor(0, 0);
	printf("       ");
}
void erase_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
	gotoxy(x, y + 1);
	setcolor(0, 0);
	printf(" ");
}
void bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(6, 0);
	printf("*");
}
int main()
{
	char ch = ' ',ch2 = ' ';
	int x = 40, y = 23,count=0;
	int x3[5], y3[5];
	bool check[5];
	for (int i = 0; i < 5; i++) {
		y3[i] = 0;
		check[i] = 0;
	}
	draw_ship(x, y);
	setcursor(0);
	do {
		if (_kbhit()) {
			ch = _getch();
			while (ch == 'a') {
				if (x > 0) x--;
				if (x >= 0) {
					erase_ship(x, y);
					draw_ship(x, y);
					Sleep(100);
				}
				for (int i = 0; i < 5; i++) {
					if (count > 0 && check[i] == 1) {
						if (y3[i] > 0) y3[i]--;
						if (y3[i] >= 0) {
							erase_bullet(x3[i], y3[i]);
							bullet(x3[i], y3[i]);
						}
						if (y3[i] <= 0) {
							erase_bullet(x3[i], y3[i]);
							check[i] = 0;
							count--;
						}
					}
				}
				if (_kbhit()) {
					ch2 = _getch();
					if (ch2 == 'x') return 0;
					if (ch2 == 's' || ch2 == 'd') break;
					if (count < 5) {
						if (ch2 == 32) {
							for (int i = 0; i < 5; i++) {
								if (y3[i] <= 0) {
									x3[i] = x;
									y3[i] = 23;
									check[i] = 1;
									break;
								}
							}
							count++;
						}
					}
				}
			}
			while (ch == 'd') {
				if (x < 80) x++;
				if (x <= 80) {
					erase_ship(x, y);
					draw_ship(x, y);
					Sleep(100);
				}
				for (int i = 0; i < 5; i++) {
					if (count > 0 && check[i] == 1) {
						if (y3[i] > 0) y3[i]--;
						if (y3[i] >= 0) {
							erase_bullet(x3[i], y3[i]);
							bullet(x3[i], y3[i]);
						}
						if (y3[i] <= 0) {
							erase_bullet(x3[i], y3[i]);
							check[i] = 0;
							count--;
						}
					}
				}
				if (_kbhit()) {
					ch2 = _getch();
					if (ch2 == 'x') return 0;
					if (ch2 == 's' || ch2 == 'a') break;
					if (count < 5) {
						if (ch2 == 32) {
							for (int i = 0; i < 5; i++) {
								if (y3[i] <= 0) {
									x3[i] = x;
									y3[i] = 23;
									check[i] = 1;
									break;
								}
							}
							count++;
						}
					}
				}
			}
			if (count < 5) {
				if (ch == 32) {
					for (int i = 0; i < 5; i++) {
						if (y3[i] <= 0) {
							x3[i] = x;
							y3[i] = 23;
							check[i] = 1;
							break;
						}
					}
					count++;
				}
			}
			while (ch == 's' || ch == 32 || ch2 == 'a' || ch2 == 'd' || ch2 == 's') {
				Sleep(100);
				for (int i = 0; i < 5; i++) {
					if (count > 0 && check[i] == 1) {
						if (y3[i] > 0) y3[i]--;
						if (y3[i] >= 0) {
							erase_bullet(x3[i], y3[i]);
							bullet(x3[i], y3[i]);
						}
						if (y3[i] <= 0) {
							erase_bullet(x3[i], y3[i]);
							check[i] = 0;
							count--;
						}
					}
				}
				if (_kbhit()) break;
			}
			fflush(stdin);
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}