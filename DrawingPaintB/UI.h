#ifndef __UI_H__
#define __UI_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include "System.h"
#include "Pen.h"
#include "Vector2.h"
#include "Math.h"

typedef struct _Sprite
{
	Vector2 position;
	char source;
} Sprite;

typedef struct _Text
{
	Vector2 position;
	char* value;
} Text;

typedef struct _Button
{
	Vector2 position;
	Vector2 scale;
	char* text;
} Button;

typedef struct _DropDown
{
	Vector2 position;
	Vector2 scale;
	Button* contentButtons;
	char* text;
	char* arrowSprite;
	bool isOpen;
} DropDown;

typedef struct _Slider
{
	Vector2 position;
	Vector2 scale;
	int minValue;
	int maxValue;
	int currentValue;
	char backgroundSprite;
	char* fillSprite;
	char* handleSprite;
} Slider;

void SetupUI();
void DrawUI();
void RemoveUI();
void DrawSpriteUI(const Sprite* sprite);
void DrawTextUI(const Text* text);
void ClearTextUI(const Text* text);
void DrawButtonUI(const Button* button);
void ClearButtonUI(const Button* button);
void DrawDropDownUI(const DropDown* dropDown);
void ClearDropDownContentsUI(const DropDown* dropDown);
void DrawSliderUI(Slider* slider);
void HandlingSliderUI(const Slider* slider);
bool CheckButtonUIClick(const Button* button);
bool CheckDropDownUIClick(DropDown* dropDown);

#endif