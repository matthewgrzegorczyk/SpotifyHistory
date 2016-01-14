#include <Windows.h>
#include <wchar.h>
#include <stdio.h>
#include <time.h>

#include "list.h"

// Add new node to list, it will change list head.
void PushNode(Node** list, const wchar_t* songName, const wchar_t* artistName, struct tm localTime)
{
	Node* node = (Node*)malloc(sizeof(Node));
	wcscpy_s(node->SongName, MAX_PATH, songName);
	wcscpy_s(node->ArtistName, MAX_PATH, artistName);
	memcpy(&node->Time, &localTime, sizeof(struct tm));
	node->Next = *list;
	*list = node;
}

// Pop head from list.
void PopNode(Node** list)
{
	Node* tmp = (*list)->Next;
	free(*list);
	*list = tmp;
}

// Split song name to artist and song and add to list.
void SaveToList(const wchar_t* currentSong, Node** list)
{
	wchar_t		songName[MAX_PATH];
	wchar_t		artistName[MAX_PATH];
	int			currentSongLength = (int) wcslen(currentSong);
	time_t		rawTime = time(NULL);
	struct tm	localTime;

	// We have a raw time in rawTime variable, so now we will fill a time structure with it.
	localtime_s(&localTime, &rawTime);
	for (int i = 0; i < currentSongLength; ++i)
	{
		if (currentSong[i] == '-')
		{
			wcsncpy_s(artistName, MAX_PATH, currentSong, i - 1);
			wcsncpy_s(songName, MAX_PATH, currentSong + i + 2, currentSongLength - i - 2);
			artistName[i - 1] = 0;
			songName[currentSongLength - i - 2] = 0;
			break;
		}
	}
	PushNode(list, songName, artistName, localTime);
}

void DisplayList(Node* list) {
	Node* p = list;
	if (p == NULL) {
		printf("There is no current Spotify History present in this app session.");
	}

	while (p != NULL) {
		wprintf(L"%s - %s\n", p->ArtistName, p->SongName);
		p = p->Next;
	}
}

void SearchListByTitle(Node* list, const wchar_t* songName) 
{
	Node* p = list;
	int i = 0;

	while (list != NULL) {
		if (wcsstr(list->SongName, songName) != NULL) {
			wprintf(L"%s - %s\n", list->ArtistName, list->SongName);
			i++;
		}
		list = list->Next;
	}

	if (i == 0) {
		printf("There are no results to dislay.");
	}
}

void SearchListByArtist(Node* list, const wchar_t* artistName)
{
	Node* p = list;
	int i = 0;

	while (p != NULL) {
		if (wcsstr(p->ArtistName, artistName) != NULL) {
			wprintf(L"%s - %s\n", p->ArtistName, p->SongName);
			i++;
		}
		p = p->Next;
	}

	if (i == 0) {
		printf("There are no results to dislay.");
	}
}
