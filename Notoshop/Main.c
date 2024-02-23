#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

int main(void)
{
	srand((unsigned int)time(NULL));
	system("title Notoshop Version 1.0.0");

	HWND hWnd;
	HDC hDc;
	CONSOLE_CURSOR_INFO consoleCursorInfo;

	int i;
	int j;
	int r;
	int g;
	int b;

	hWnd = GetForegroundWindow();
	hDc = GetWindowDC(hWnd);

	consoleCursorInfo.dwSize = 1;
	consoleCursorInfo.bVisible = 0;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);

	for ( ; ; )
	{
		for (i = 0; i < 1024; i++)
		{
			for (j = 0; j < 2048; j++)
			{
				r = rand() % 256;
				g = rand() % 256;
				b = rand() % 256;

				SetPixel(hDc, j, i, RGB(r, g, b));
			}
		}
	}

	return 0;
}