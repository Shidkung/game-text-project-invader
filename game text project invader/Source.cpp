
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void erase_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf("       ");
}
void draw_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 4);
	printf("<[|o|]>");
}
void erase_enemies(int x, int y)
{
	gotoxy(x, y);

	printf("       ");
}
void draw_enemies(int x, int y)
{
	gotoxy(x, y);
	printf(" ((0o0)) ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(15, 0);
	printf("^");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}
bool bullet[5];
int bx[5], by[5], i;
int bulletnow = 0;
int direction = 0;
int main()
{

	char ch = ' ';
	int x = 40, y = 15;

	setcursor(0);
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();

			/*if (ch == 'a' && x > 0) { erase_ship(x, y); draw_ship(--x, y); }
			if (ch == 'd' && x < 80) {erase_ship(x, y); draw_ship(++x, y); }
			if (ch == 'w' && y > 0) { erase_ship(x, y); draw_ship(x, --y); }
			if (ch == 's' && y < 30) { erase_ship(x, y); draw_ship(x, ++y); }*/
			if (ch == 'a') { direction = -1; }
			if (ch == 'd') { direction = 1; }
			if (ch == 's') { direction = 0; }
			if (bullet[bulletnow] != 1 && ch == ' ') {
				bullet[bulletnow] = 1;
				bx[bulletnow] = x + 3;
				by[bulletnow] = y - 1;
				bulletnow++;
				bulletnow %= 5;
			}

			fflush(stdin);
		}
		erase_ship(x, y);
		x += direction;
		if (x < 0)
			x = 0;
		if (x > 80)
			x = 80;
		draw_ship(x, y);



		for (i = 0; i < 5; i++) {
			if (bullet[i] == 1) {
				clear_bullet(bx[i], by[i]);
				if (by[i] > 0) {
					draw_bullet(bx[i], --by[i]);
				}
				else {
					bullet[i] == 0;
				}

			}
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}