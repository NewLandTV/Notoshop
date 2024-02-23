#include "UI.h"

DropDown drawingTypeDropDown;
Text drawingSizeText;
Slider drawingSizeSlider;
Button saveBoardButton;

INPUT_RECORD inputRecord;
DWORD dwNumberOfEventsRead;

void SetupUI()
{
	int i;

	drawingTypeDropDown.position = (Vector2){ CONSOLE_WIDTH - 30, 12 };
	drawingTypeDropDown.scale = (Vector2){ 14, 5 };
	drawingTypeDropDown.contentButtons = (Button*)malloc(sizeof(Button) * 3);

	for (i = 0; i < _msize(drawingTypeDropDown.contentButtons) / sizeof(Button); i++)
	{
		drawingTypeDropDown.contentButtons[i].position = (Vector2){ CONSOLE_WIDTH - 45, 12 + (i * 5) };
		drawingTypeDropDown.contentButtons[i].scale = (Vector2){ 14, 5 };
	}

	drawingTypeDropDown.text = "Pencil";
	drawingTypeDropDown.arrowSprite = "¡å";

	drawingTypeDropDown.contentButtons[0].text = "Pencil";
	drawingTypeDropDown.contentButtons[1].text = "Eraser";
	drawingTypeDropDown.contentButtons[2].text = "Pen";

	drawingSizeText.position = (Vector2) { CONSOLE_WIDTH - 62, 3 };
	drawingSizeText.value = "Drawing Size";

	drawingSizeSlider.position = (Vector2) { CONSOLE_WIDTH - 62, 5 };
	drawingSizeSlider.scale = (Vector2) { 50, 3 };
	drawingSizeSlider.minValue = 1;
	drawingSizeSlider.maxValue = 50;
	drawingSizeSlider.currentValue = 1;
	drawingSizeSlider.backgroundSprite = '$';
	drawingSizeSlider.fillSprite = "¡á";
	drawingSizeSlider.handleSprite = "¡Û";

	saveBoardButton.position = (Vector2) { CONSOLE_WIDTH - 15, CONSOLE_HEIGHT - 18 };
	saveBoardButton.scale = (Vector2) { 14, 5 };
	saveBoardButton.text = "Save Board";
}

void DrawUI()
{
	int i;
	int j;
	char* board = 0;

	CheckDropDownUIClick(&drawingTypeDropDown);

	if (!drawingTypeDropDown.isOpen)
	{
		ClearDropDownContentsUI(&drawingTypeDropDown);
		DrawDropDownUI(&drawingTypeDropDown);
	}

	if (CheckButtonUIClick(&saveBoardButton))
	{
		GetBoard(&board);
		SaveBoard(board);
	}

	DrawSliderUI(&drawingSizeSlider);
	DrawTextUI(&drawingSizeText);
	DrawButtonUI(&saveBoardButton);

	if (drawingTypeDropDown.isOpen)
	{
		for (i = 0; i < _msize(drawingTypeDropDown.contentButtons) / sizeof(Button); i++)
		{
			if (CheckButtonUIClick(&drawingTypeDropDown.contentButtons[i]))
			{
				Gotoxy(drawingTypeDropDown.position.x + (ShortMax(drawingTypeDropDown.scale.x - strlen(drawingTypeDropDown.text), strlen(drawingTypeDropDown.text) - drawingTypeDropDown.scale.x) >> 1) - 1, drawingTypeDropDown.position.y + (drawingTypeDropDown.scale.y >> 1));

				for (j = 0; j < strlen(drawingTypeDropDown.text) + 1; j++)
				{
					printf(" ");
				}

				drawingTypeDropDown.isOpen = false;

				drawingTypeDropDown.text = GetDrawingTypeByIndexToCharPointer(i);

				SetDrawingType((DRAWING_TYPE)i);

				break;
			}
		}
	}

	HandlingSliderUI(&drawingSizeSlider);
	SetDrawingSize(drawingSizeSlider.currentValue);
}

void RemoveUI()
{
	free(drawingTypeDropDown.contentButtons);
}

void DrawSpriteUI(const Sprite* sprite)
{
	Gotoxy(sprite->position.x, sprite->position.y);
	printf("%c", sprite->source);
}

void DrawTextUI(const Text* text)
{
	Gotoxy(text->position.x, text->position.y);
	printf("%s", text->value);
}

void ClearTextUI(const Text* text)
{
	int i;

	Gotoxy(text->position.x, text->position.y);

	for (i = 0; i < strlen(text->value); i++)
	{
		printf(" ");
	}
}

void DrawButtonUI(const Button* button)
{
	int x;
	int y;

	Gotoxy(button->position.x - 1, button->position.y);
	printf("¦£");
	Gotoxy(button->position.x + button->scale.x - 1, button->position.y);
	printf("¦¤");
	Gotoxy(button->position.x - 1, button->position.y + button->scale.y - 1);
	printf("¦¦");
	Gotoxy(button->position.x + button->scale.x - 1, button->position.y + button->scale.y - 1);
	printf("¦¥");

	for (x = button->position.x; x < button->position.x + button->scale.x - 1; x += 2)
	{
		Gotoxy(x, button->position.y);
		printf("¦¡");
		Gotoxy(x, button->position.y + button->scale.y - 1);
		printf("¦¡");
	}

	for (y = button->position.y + 1; y < button->position.y + button->scale.y - 1; y++)
	{
		Gotoxy(button->position.x - 1, y);
		printf("¦¢");
		Gotoxy(button->position.x + button->scale.x - 1, y);
		printf("¦¢");
	}

	Gotoxy(button->position.x + (ShortMax(button->scale.x - strlen(button->text), strlen(button->text) - button->scale.x) >> 1), button->position.y + (button->scale.y >> 1));
	printf("%s", button->text);
}

void ClearButtonUI(const Button* button)
{
	int x;
	int y;

	for (y = button->position.y; y < button->position.y + button->scale.y; y++)
	{
		for (x = button->position.x - 1; x < button->position.x + button->scale.x; x++)
		{
			Gotoxy(x, y);
			printf(" ");
		}
	}
}

void DrawDropDownUI(const DropDown* dropDown)
{
	int x;
	int y;

	Gotoxy(dropDown->position.x - 1, dropDown->position.y);
	printf("¦£");
	Gotoxy(dropDown->position.x + dropDown->scale.x - 1, dropDown->position.y);
	printf("¦¤");
	Gotoxy(dropDown->position.x - 1, dropDown->position.y + dropDown->scale.y - 1);
	printf("¦¦");
	Gotoxy(dropDown->position.x + dropDown->scale.x - 1, dropDown->position.y + dropDown->scale.y - 1);
	printf("¦¥");

	for (x = dropDown->position.x; x < dropDown->position.x + dropDown->scale.x - 1; x += 2)
	{
		Gotoxy(x, dropDown->position.y);
		printf("¦¡");
		Gotoxy(x, dropDown->position.y + dropDown->scale.y - 1);
		printf("¦¡");
	}

	for (y = dropDown->position.y + 1; y < dropDown->position.y + dropDown->scale.y - 1; y++)
	{
		Gotoxy(dropDown->position.x - 1, y);
		printf("¦¢");
		Gotoxy(dropDown->position.x + dropDown->scale.x - 1, y);
		printf("¦¢");
	}

	Gotoxy(dropDown->position.x + (ShortMax(dropDown->scale.x - strlen(dropDown->text), strlen(dropDown->text) - dropDown->scale.x) >> 1) - 1, dropDown->position.y + (dropDown->scale.y >> 1));
	printf("%s", dropDown->text);
	Gotoxy(dropDown->position.x + dropDown->scale.x - strlen(dropDown->arrowSprite) - 2, dropDown->position.y + (dropDown->scale.y >> 1));
	printf("%s", dropDown->arrowSprite);
}

void ClearDropDownContentsUI(const DropDown* dropDown)
{
	int i;

	for (i = 0; i < _msize(dropDown->contentButtons) / sizeof(Button); i++)
	{
		ClearButtonUI(&dropDown->contentButtons[i]);
	}
}

void DrawSliderUI(const Slider* slider)
{
	int x;
	int y;

	for (y = slider->position.y; y < slider->position.y + slider->scale.y; y++)
	{
		for (x = slider->position.x - 1; x < slider->position.x + slider->scale.x + 1; x++)
		{
			Gotoxy(x, y);
			printf("%c", slider->backgroundSprite);
		}
	}

	Gotoxy(slider->position.x + slider->currentValue - slider->minValue, slider->position.y + (slider->scale.y >> 1));
	printf("%s", slider->handleSprite);
}

void HandlingSliderUI(Slider* slider)
{
	HANDLE consoleIn;
	DWORD mode;

	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &inputRecord, 1, &dwNumberOfEventsRead);

	if (inputRecord.EventType == MOUSE_EVENT)
	{
		if (inputRecord.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			int mouseX = inputRecord.Event.MouseEvent.dwMousePosition.X;
			int mouseY = inputRecord.Event.MouseEvent.dwMousePosition.Y;

			if (slider->position.x <= mouseX && mouseX <= slider->position.x + slider->scale.x && slider->position.y <= mouseY && mouseY <= slider->position.y + slider->scale.y)
			{
				slider->currentValue = ShortMin(ShortMax(mouseX, slider->minValue) - slider->position.x, slider->maxValue);
			}
		}
	}

	consoleIn = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(consoleIn, &mode);
	SetConsoleMode(consoleIn, mode | ENABLE_MOUSE_INPUT);
}

bool CheckButtonUIClick(const Button* button)
{
	HANDLE consoleIn;
	DWORD mode;

	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &inputRecord, 1, &dwNumberOfEventsRead);

	if (inputRecord.EventType == MOUSE_EVENT)
	{
		if (inputRecord.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			int mouseX = inputRecord.Event.MouseEvent.dwMousePosition.X;
			int mouseY = inputRecord.Event.MouseEvent.dwMousePosition.Y;

			if (button->position.x <= mouseX && mouseX <= button->position.x + button->scale.x && button->position.y <= mouseY && mouseY <= button->position.y + button->scale.y)
			{
				consoleIn = GetStdHandle(STD_INPUT_HANDLE);

				GetConsoleMode(consoleIn, &mode);
				SetConsoleMode(consoleIn, mode | ENABLE_MOUSE_INPUT);

				return true;
			}
		}
	}

	consoleIn = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(consoleIn, &mode);
	SetConsoleMode(consoleIn, mode | ENABLE_MOUSE_INPUT);

	return false;
}

bool CheckDropDownUIClick(DropDown* dropDown)
{
	int i;
	int x;
	int y;

	HANDLE consoleIn;
	DWORD mode;

	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &inputRecord, 1, &dwNumberOfEventsRead);

	if (inputRecord.EventType == MOUSE_EVENT)
	{
		if (inputRecord.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			int mouseX = inputRecord.Event.MouseEvent.dwMousePosition.X;
			int mouseY = inputRecord.Event.MouseEvent.dwMousePosition.Y;

			if (dropDown->position.x <= mouseX && mouseX <= dropDown->position.x + dropDown->scale.x && dropDown->position.y <= mouseY && mouseY <= dropDown->position.y + dropDown->scale.y)
			{
				consoleIn = GetStdHandle(STD_INPUT_HANDLE);

				GetConsoleMode(consoleIn, &mode);
				SetConsoleMode(consoleIn, mode | ENABLE_MOUSE_INPUT);

				dropDown->isOpen = true;

				for (i = 0; i < _msize(dropDown->contentButtons) / sizeof(Button); i++)
				{
					DrawButtonUI(&dropDown->contentButtons[i]);
				}

				return true;
			}
		}
	}

	consoleIn = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(consoleIn, &mode);
	SetConsoleMode(consoleIn, mode | ENABLE_MOUSE_INPUT);

	return false;
}