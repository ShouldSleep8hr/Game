#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y); printf(" <-0-> ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y); printf("^");
}
void draw_star(int x, int y)
{
	gotoxy(x, y); printf("*");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read)) return '\0';
	else return buf[0];
}
int main()
{
	char ch = '.';
	int x = 38, y = 20;
	int bx, by;
	int bullet = 0;
	setcursor(0);
	srand(time(NULL));
	int i = 1, t, score = 0;
	gotoxy(80, 0); printf("%d", score);
	while (i <= 20) {
		t = rand();
		if (t % 71 >= 10 && t % 6 >= 2 && cursor(t % 71, t % 6) != '*') {
			draw_star(t % 71, t % 6);
			i++;
		}
	}
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' && x-1 >= 0) { 
				draw_ship(--x, y); 
			}
			if (ch == 's' && x+1 <= 80) { 
				draw_ship(++x, y); 
			}
			if (bullet != 1 && ch == ' ') { 
				bullet = 1; 
				bx = x + 3; 
				by = y - 1;
			}
			fflush(stdin);
		}
		if (bullet == 1) {
			clear_bullet(bx, by);
			if (by == 2) { 
				bullet = 0; 
			}
			else { 
				if (cursor(bx, by - 1) == '*') {
					Beep(500, 100);
					draw_bullet(bx, by - 1);
					clear_bullet(bx, by - 1);
					score++;
					gotoxy(80, 0); printf("%d", score);
					bullet = 0;
					while (1) {
						t = rand();
						if (t % 71 >= 10 && t % 6 >= 2 && cursor(t % 71, t % 6) != '*') {
							draw_star(t % 71, t % 6);
							break;
						}
					}
				}
				else {
					Beep(2000, 2);
					draw_bullet(bx, --by);
				}
			}
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}