#include <Windows.h>
#include <stdio.h>
#include <time.h>

#include "list.h"
#include "ListFileManager.h"

// Save current song to file.
void SaveToFile(const wchar_t* currentSong)
{
	FILE* file = _wfopen(CurrentSongFilename, L"wb");
	fwprintf(file, L"%s", currentSong);
	fclose(file);
}

// Save whole list to history file.
void SaveListToFile(const Node* list)
{
	FILE*	file = _wfopen(PlaylistHistoryFilename, L"ab");
	const Node*	p = list;
	wchar_t	bufferTime[64];

	while (p)
	{
		_wcsftime_l(bufferTime, 64, L"[%Y-%m-%d %H:%M:%S]", &p->Time, NULL);
		fwprintf(file, L"%s %s - %s\r\n", bufferTime, p->ArtistName, p->SongName);
		p = p->Next;
	}
	fclose(file);
}

// Reads whole list from history file.
void ReadListFromFile(Node* list) 
{
	FILE*	file = _wfopen(PlaylistHistoryFilename, L"rb");
	Node* head = list;
}