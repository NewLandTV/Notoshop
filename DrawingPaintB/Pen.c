#include "Pen.h"

 const Vector2 penInputLeftTop =
{
	5, 3
};

const Vector2 penInputRightBottom =
{
	(CONSOLE_WIDTH >> 1) + 20, CONSOLE_HEIGHT - 3
};

INPUT_RECORD inputRecord;
DWORD dwNumberOfEventsRead;

DRAWING_TYPE currentDrawingType;

int drawingR;
char drawingSprite;
char* board;

void SetupBoard()
{
	int x;
	int y;

	board = (char*)calloc((penInputRightBottom.x - penInputLeftTop.x) * (penInputRightBottom.y - penInputLeftTop.y), (penInputRightBottom.x - penInputLeftTop.x) * (penInputRightBottom.y - penInputLeftTop.y));

	puts("");
	FillBoard(' ');
}

void RemoveBoard()
{
	free(board);
}

void DrawPenInputBorder()
{
	int x;
	int y;

	Gotoxy(penInputLeftTop.x - 2, penInputLeftTop.y - 1);
	printf("¦£");
	Gotoxy(penInputRightBottom.x + 1, penInputLeftTop.y - 1);
	printf("¦¤");
	Gotoxy(penInputLeftTop.x - 2, penInputRightBottom.y + 1);
	printf("¦¦");
	Gotoxy(penInputRightBottom.x + 1, penInputRightBottom.y + 1);
	printf("¦¥");

	for (x = penInputLeftTop.x; x < penInputRightBottom.x + 1; x += 2)
	{
		Gotoxy(x, penInputLeftTop.y - 1);
		printf("¦¡");
		Gotoxy(x, penInputRightBottom.y + 1);
		printf("¦¡");
	}

	for (y = penInputLeftTop.y; y < penInputRightBottom.y + 1; y++)
	{
		Gotoxy(penInputLeftTop.x - 2, y);
		printf("¦¢");
		Gotoxy(penInputRightBottom.x + 1, y);
		printf("¦¢");
	}
}

void FillBoard(char sprite)
{
	int i;

	for (i = 0; i < _msize(board); i++)
	{
		board[i] = sprite;
	}
}

void EditBoard(int x, int y)
{
	board[y + (penInputRightBottom.x - penInputLeftTop.x) * x] = drawingSprite;
}

void Drawing()
{
	HANDLE consoleIn;
	DWORD mode;

	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &inputRecord, 1, &dwNumberOfEventsRead);

	if (inputRecord.EventType == MOUSE_EVENT)
	{
		if (inputRecord.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			int i;
			int j;
			int x;
			int y;
			int p;
			int mouseX = inputRecord.Event.MouseEvent.dwMousePosition.X;
			int mouseY = inputRecord.Event.MouseEvent.dwMousePosition.Y;

			if (penInputLeftTop.x <= mouseX && mouseX <= penInputRightBottom.x && penInputLeftTop.y <= mouseY && mouseY <= penInputRightBottom.y)
			{
				x = 0;
				y = drawingR;
				p = drawingR - 1;

				Gotoxy(mouseX, mouseY);

				switch (currentDrawingType)
				{
				case DT_Pencil:
					drawingSprite = '*';

					break;
				case DT_Eraser:
					drawingSprite = ' ';

					break;
				case DT_Pen:
					drawingSprite = '+';

					break;
				}

				for (; x < y; )
				{
					if (p < 0)
					{
						p += x + x + 1;
					}
					else
					{
						p += x + x + 1 - y - y;

						y--;

						for (i = 0; i < x; i++)
						{
							Gotoxy(IntMax(IntMin(i + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							printf("%c", drawingSprite);
							Gotoxy(IntMax(IntMin(i + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							printf("%c", drawingSprite);
							Gotoxy(IntMax(IntMin(-i + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							printf("%c", drawingSprite);
							Gotoxy(IntMax(IntMin(-i + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							printf("%c", drawingSprite);
							Gotoxy(IntMax(IntMin(y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(i + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							printf("%c", drawingSprite);
							Gotoxy(IntMax(IntMin(y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-i + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							printf("%c", drawingSprite);
							Gotoxy(IntMax(IntMin(-y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(i + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							printf("%c", drawingSprite);
							Gotoxy(IntMax(IntMin(-y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-i + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							printf("%c", drawingSprite);

							EditBoard(IntMax(IntMin(i + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							EditBoard(IntMax(IntMin(i + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							EditBoard(IntMax(IntMin(-i + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							EditBoard(IntMax(IntMin(-i + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							EditBoard(IntMax(IntMin(y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(i + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							EditBoard(IntMax(IntMin(y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-i + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							EditBoard(IntMax(IntMin(-y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(i + mouseY, penInputRightBottom.y), penInputLeftTop.y));
							EditBoard(IntMax(IntMin(-y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-i + mouseY, penInputRightBottom.y), penInputLeftTop.y));
						}
					}

					Gotoxy(IntMax(IntMin(x + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					printf("%c", drawingSprite);
					Gotoxy(IntMax(IntMin(x + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					printf("%c", drawingSprite);
					Gotoxy(IntMax(IntMin(-x + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					printf("%c", drawingSprite);
					Gotoxy(IntMax(IntMin(-x + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					printf("%c", drawingSprite);
					Gotoxy(IntMax(IntMin(y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(x + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					printf("%c", drawingSprite);
					Gotoxy(IntMax(IntMin(y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-x + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					printf("%c", drawingSprite);
					Gotoxy(IntMax(IntMin(-y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(x + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					printf("%c", drawingSprite);
					Gotoxy(IntMax(IntMin(-y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-x + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					printf("%c", drawingSprite);

					EditBoard(IntMax(IntMin(x + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					EditBoard(IntMax(IntMin(x + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					EditBoard(IntMax(IntMin(-x + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					EditBoard(IntMax(IntMin(-x + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-y + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					EditBoard(IntMax(IntMin(y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(x + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					EditBoard(IntMax(IntMin(y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-x + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					EditBoard(IntMax(IntMin(-y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(x + mouseY, penInputRightBottom.y), penInputLeftTop.y));
					EditBoard(IntMax(IntMin(-y + mouseX, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(-x + mouseY, penInputRightBottom.y), penInputLeftTop.y));

					x++;
				}

				for (i = mouseY - y + 1; i < mouseY + y; i++)
				{
					for (j = mouseX - y + 1; j < mouseX + y; j++)
					{
						Gotoxy(IntMax(IntMin(j, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(i, penInputRightBottom.y), penInputLeftTop.y));
						printf("%c", drawingSprite);

						EditBoard(IntMax(IntMin(j, penInputRightBottom.x), penInputLeftTop.x), IntMax(IntMin(i, penInputRightBottom.y), penInputLeftTop.y));
					}
				}

				consoleIn = GetStdHandle(STD_INPUT_HANDLE);

				GetConsoleMode(consoleIn, &mode);
				SetConsoleMode(consoleIn, mode | ENABLE_MOUSE_INPUT);
			}
		}
	}

	consoleIn = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(consoleIn, &mode);
	SetConsoleMode(consoleIn, mode | ENABLE_MOUSE_INPUT);
}

char* GetDrawingTypeByIndexToCharPointer(int index)
{
	switch ((DRAWING_TYPE)index)
	{
	case DT_Pencil:
		return "Pencil";
	case DT_Eraser:
		return "Eraser";
	case DT_Pen:
		return "Pen";
	}
}

void GetBoard(char** out)
{
	*out = board;
}

void SetDrawingType(const DRAWING_TYPE newDrawingType)
{
	currentDrawingType = newDrawingType;
}

void SetDrawingSize(const int newDrawingSize)
{
	drawingR = newDrawingSize;
}