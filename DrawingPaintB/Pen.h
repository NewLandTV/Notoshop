#ifndef __PEN_H__
#define __PEN_H__

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "System.h"
#include "UI.h"
#include "SaveLoad.h"
#include "Math.h"
#include "Vector2.h"

typedef enum _DRAWING_TYPE
{
	DT_Pencil,
	DT_Eraser,
	DT_Pen
} DRAWING_TYPE;

void SetupBoard();
void RemoveBoard();
void DrawPenInputBorder();
void FillBoard(char sprite);
void EditBoard(int x, int y);
void Drawing();
char* GetDrawingTypeByIndexToCharPointer(int index);
void GetBoard(char** out);
void SetDrawingType(const DRAWING_TYPE newDrawingType);
void SetDrawingSize(const int newDrawingSize);

#endif