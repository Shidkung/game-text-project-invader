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
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void erase_ship(int x, int y)
{
	gotoxy(x, y);
	printf("           ");
}
void draw_ship(int x, int y)
{
	gotoxy(x, y);
	printf(" (<[|o|]>) ");
}
void erase_enemies(int x, int y)
{
	gotoxy(x, y);  
	printf("              ");
}
void draw_enemies(int x, int y)
{
	gotoxy(x, y);
	printf(" ().(0)(0).() ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y); printf("  ^  ");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); printf("      ");
}
int main()
{
	char ch = ' ';
	int x = 40, y = 15;
	int bx, by, i;
	int bullet = 0;
	setcursor(0);
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();

			if (ch == 'a' && x > 0) { draw_ship(--x, y); }
			if (ch == 'd' && x < 80) { draw_ship(++x, y); }
			if (ch == 'w' && y > 0) { draw_ship(x, --y); erase_ship(x, ++y); draw_ship(x, --y); }
			if (ch == 's' && y < 30) { draw_ship(x, ++y); erase_ship(x, --y); draw_ship(x, ++y); }
			if (bullet != 1 && ch == 'f') { bullet = 1; bx = x + 3; by = y - 1; }
			fflush(stdin);
		}
		if (bullet == 1) {
             clear_bullet(bx, by);
			if (by == 2) { bullet = 0; }
			else { draw_bullet(bx, --by); }

		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}