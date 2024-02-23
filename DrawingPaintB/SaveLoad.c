#include "SaveLoad.h"

void CheckNoteMapFolder()
{
	char buffer[1024];
	char* dir = buffer;

	strcpy_s(buffer, 1024, DEFAULT_SAVE_FILE_PATH);

	buffer[1023] = '\0';

	while (*dir)
	{
		if (*dir == '/')
		{
			*dir = '\0';

			_mkdir(buffer);

			*dir = '/';
		}

		dir++;
	}
}

void SaveBoard(char* board)
{
	int x;
	int y;

	FILE* wfp;

	CheckNoteMapFolder();
	fopen_s(&wfp, DEFAULT_SAVE_FILE_PATH, "w");

	if (!wfp)
	{
		return;
	}

	for (y = 0; y < 54; y++)
	{
		for (x = 0; x < 115; x++)
		{
			fprintf(wfp, "%c", board[y + 115 * x]);
		}

		fprintf(wfp, "\n");
	}

	fclose(wfp);
}