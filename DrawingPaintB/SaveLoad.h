#ifndef __SAVE_LOAD_H__
#define __SAVE_LOAD_H__

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <direct.h>

#define DEFAULT_SAVE_FILE_PATH "C:/NewLand/DrawingPaintB/save.ndpb"

void CheckNoteMapFolder();
void SaveBoard(char* board);

#endif