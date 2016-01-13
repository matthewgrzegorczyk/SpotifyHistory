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

// static const wchar_t SpotifyWindowName[] = L"SpotifyMainWindow";


void displayMenu() {
	printf("1 - Display current playing track.");
	printf("2 - Display session history.");
	printf("ESC - Exit app and save session history to the file.");
}


int main(int argc, char* argv[])
{
	HWND	hWndSpotify	= FindWindow(SpotifyWindowName, NULL);
	Node*	list		= NULL;
	char	keyPressed	= 0;
	wchar_t	currentSong[MAX_PATH];
	wchar_t	lastSong[MAX_PATH];

	memset(currentSong, 0, sizeof(wchar_t) * MAX_PATH);
	memset(lastSong, 0, sizeof(wchar_t) * MAX_PATH);

	// Check SpotifyMainWindow Caption as long as window exists or User won't click ESC key.
	while (hWndSpotify && keyPressed != 27)
	{
		// Check if Spotify is still running and Window title is available.
		hWndSpotify = FindWindow(SpotifyWindowName, NULL);
		if (!hWndSpotify) {
			break;
		}

		// Get current song name.
		GetWindowText(hWndSpotify, currentSong, MAX_PATH);

		// If currentSong is different than lastSong then print it out.
		if (wcscmp(currentSong, lastSong) != 0)
		{
			// Save song details.
			wprintf(L"%s\n", currentSong);
			wcscpy_s(lastSong, MAX_PATH, currentSong);

			// Skip saving output of Window Title if music is not playing (window title is equal Spotify then).
			if (wcscmp(currentSong, L"Spotify") != 0)
			{
				SaveToList(currentSong, &list);
				SaveToFile(currentSong);
			}
		}

		// get asynchronously pressed key
		if (_kbhit()) {
			keyPressed = _getch();
		}

		// Run loop each 100ms. It may be a good idea to change it's value to even longer period of time.
		Sleep(100);
	}

	// Save history (history for each run will get appended to the file).
	SaveListToFile(list);

	while (list) {
		PopNode(&list);
	}

	return 0;
}