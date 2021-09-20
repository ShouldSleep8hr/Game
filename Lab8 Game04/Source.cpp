#include <stdio.h>
#include <windows.h>
#include <time.h>
#define screen_x 80
#define screen_y 25
HANDLE rHnd;
HANDLE wHnd;
DWORD fdwMode;
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD bufferSize = { screen_x,screen_y };
COORD characterPos = { 0,0 };
COORD star;
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
int setConsole(int x, int y)
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	return 0;
}
int setMode()
{
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
		ENABLE_MOUSE_INPUT;
	SetConsoleMode(rHnd, fdwMode);
	return 0;
}
void fill_data_to_buffer(int posx,int posy,int temp)
{
	consoleBuffer[posx + screen_x * posy].Char.AsciiChar = '<';
	consoleBuffer[(posx + screen_x * posy) + 1].Char.AsciiChar = '-';
	consoleBuffer[(posx + screen_x * posy) + 2].Char.AsciiChar = '0';
	consoleBuffer[(posx + screen_x * posy) + 3].Char.AsciiChar = '-';
	consoleBuffer[(posx + screen_x * posy) + 4].Char.AsciiChar = '>';
	consoleBuffer[posx + screen_x * posy].Attributes = temp;
	consoleBuffer[(posx + screen_x * posy) + 1].Attributes = temp;
	consoleBuffer[(posx + screen_x * posy) + 2].Attributes = temp;
	consoleBuffer[(posx + screen_x * posy) + 3].Attributes = temp;
	consoleBuffer[(posx + screen_x * posy) + 4].Attributes = temp;
}
void fill_star_to_buffer()
{
	star = { rand() % screen_x, rand() % screen_y };
	consoleBuffer[star.X + screen_x * star.Y].Char.AsciiChar = '*';
	consoleBuffer[star.X + screen_x * star.Y].Attributes = 7;
}
void fill_buffer_to_console()
{
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos, &windowSize);
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
int main()
{
	setcursor(0);
	srand(time(NULL));
	bool play = true; int posx = 0, posy = 0; int temp = 7, count = 0;
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	setConsole(screen_x, screen_y);
	setMode();
	fill_star_to_buffer();
	fill_buffer_to_console();
	while (play)
	{
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) {
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
			for (DWORD i = 0; i < numEventsRead; ++i) {
				if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown == true) {
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
						play = false;
					}
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'c') {
						while (1) {
							temp = rand() % 16;
							if (temp != 0) break;
						}
						fill_data_to_buffer(posx, posy, temp);
						fill_buffer_to_console();
					}
				}
				else if (eventBuffer[i].EventType == MOUSE_EVENT) {
					if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
							while (1) {
								temp = rand()%16;
								if (temp != 0) break;
							}
					}
					else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED) {
						consoleBuffer[posx + screen_x * posy].Char.AsciiChar = ' ';
						consoleBuffer[(posx + screen_x * posy) + 1].Char.AsciiChar = ' ';
						consoleBuffer[(posx + screen_x * posy) + 2].Char.AsciiChar = ' ';
						consoleBuffer[(posx + screen_x * posy) + 3].Char.AsciiChar = ' ';
						consoleBuffer[(posx + screen_x * posy) + 4].Char.AsciiChar = ' ';
						fill_buffer_to_console();
						posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
						posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
						fill_data_to_buffer(posx, posy, temp);
						fill_buffer_to_console();
						if (posx + screen_x * posy == star.X + screen_x * star.Y || (posx + screen_x * posy) + 1 == star.X + screen_x * star.Y || (posx + screen_x * posy) + 2 == star.X + screen_x * star.Y || (posx + screen_x * posy) + 3 == star.X + screen_x * star.Y || (posx + screen_x * posy) + 4 == star.X + screen_x * star.Y) {
							Beep(700, 50);
							count++;
							if (count >= 10) play = false;
							fill_star_to_buffer();
							fill_buffer_to_console();
						}
					}
				}
			}
			delete[] eventBuffer;
		}
		Sleep(100);
	}
	return 0;
}