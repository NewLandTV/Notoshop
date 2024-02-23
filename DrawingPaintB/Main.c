#include "System.h"
#include "UI.h"
#include "Pen.h"

int main(void)
{
	Init();
	SetupUI();
	SetupBoard();
	DrawPenInputBorder();

	while (1)
	{
		DrawUI();
		Drawing();
	}

	RemoveBoard();
	RemoveUI();

	return 0;
}