#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
void setcolor(int fg, int bg);
void setcursor(bool visible);
void gotoxy(int x, int y);
void draw_ship(int x, int y);
void erase_ship(int x, int y);
void draw_fire(int x, int y);
void Pbullet(int x, int y, int number);
int main()
{
	setcursor(0);
	char ch = ' ' ;
	int x = 40, y = 20, direcship=0,
		fire=0,xfire=40,yfire=19,bullet=5;
	draw_ship(x, y);
	Pbullet(90, 0, bullet);
	do {
		if (_kbhit()) {
			ch = _getch();
			
			if (ch == 'd')
			{
				direcship = 1 ;
			}
			if (ch == 'a')
			{
				direcship = 2 ;
			}
			if (ch == 's')
			{
				direcship = 0;
			}
			if (ch == 'w'&&fire==0&&bullet>0)
			{
				fire = 1;
				yfire = y - 1;
				bullet--;
				Pbullet(90,0, bullet);
			}
			fflush(stdin);
		}
		if (direcship == 1 && x < 80)
		{
			erase_ship(x, y);
			draw_ship(++x, y);
			
		}
		if (direcship == 2 && x > 0)
		{
			erase_ship(x, y);
			draw_ship(--x, y);
			
		}
		if (fire == 0)
		{
			xfire = x;
		}
		if (fire == 1&&yfire>=0)
		{
			if (yfire<1)
			{
				erase_ship(xfire, yfire);
				fire = 0;
				
			}
			else
			{
				erase_ship(xfire, yfire);
				draw_fire(xfire, --yfire);
			}
			
		}
		
		Sleep(100);
	} while (ch != 'x');
	return 0;
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
	GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	setcolor(4, 15);
	gotoxy(x, y);
	printf(" <^I^> ");
}

void erase_ship(int x, int y)
{
	setcolor(0, 0);
	gotoxy(x, y);
	printf("       ");
}

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

void draw_fire(int x, int y)
{
	setcolor(7, 12);
	gotoxy(x+3, y);
	printf("^");
}

void Pbullet(int x, int y,int number)
{
	setcolor(1, 10);
	gotoxy(x, y);
	printf("Bullet %d",number);
}