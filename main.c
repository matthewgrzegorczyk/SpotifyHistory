#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <conio.h>
#include <time.h>

// Custom libraries.
#include "list.h"
#include "ListFileManager.h"
#include "SpotifyListener.h"
#include "main.h"

char keyPressed = 0;
Node* list = NULL;
CRITICAL_SECTION CriticalSection;

// Function which dispalys menu.
void displayMenu() {
	system("CLS");
	printf("1 - Display current playing track.\n");
	printf("2 - Display session history.\n");
	printf("3 - Search session history by artist name.\n");
	printf("4 - Search session history by track title.\n");
	printf("ESC - Exit app and save session history to the file.\n");
}

int main(int argc, char* argv[])
{
	HANDLE tHandle;
	DWORD ThreadId;
	wchar_t artistName[MAX_PATH];
	wchar_t songName[MAX_PATH];

	memset(artistName, 0, sizeof(wchar_t) * MAX_PATH);
	memset(songName, 0, sizeof(wchar_t) * MAX_PATH);

	tHandle = CreateThread(NULL, 0, SpotifyListener, NULL, 0, &ThreadId);

	if (tHandle == NULL) {
		printf("Could not create Thread for SpotifyListener\n");
	}
	else {
		InitializeCriticalSection(&CriticalSection);
		printf("Thread %d was created\n", ThreadId);
	}

	// Run till user won't click ESC key.
	while (keyPressed != 27) {
		displayMenu();
		keyPressed = _getch();

		switch (keyPressed) {
			case '1':
				system("CLS");
				if (list != NULL) {
					wprintf(L"Currently playing track: %s - %s\n", list->ArtistName, list->SongName);
				}
				_getch();
				break;
			case '2':
				system("CLS");
				printf("Music list:\n");
				DisplayList(list);
				_getch();
				break;
			case '3':
				system("CLS");
				printf("Please type in Artist name: ");
				wscanf_s(L"%ls", artistName, MAX_PATH);
				printf("\n\nMusic list:\n");
				SearchListByArtist(list, artistName);
				_getch();
				break;
			case '4':
				system("CLS");
				printf("Please type in Track title: ");
				wscanf_s(L"%ls", songName, MAX_PATH);
				printf("\n\nMusic list:\n");
				SearchListByTitle(list, songName);
				_getch();
				break;
			case '27':
				printf("You pressed ESC. App will close.\n");
				break;
			default:
				printf("Wrong option. Choose again.");
		}
	}

	if (tHandle != NULL) {
		WaitForSingleObject(tHandle, INFINITE);
		DeleteCriticalSection(&CriticalSection);
	}

	return 0;
}
