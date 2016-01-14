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
	printf("ESC - Exit app and save session history to the file.\n");
}

int main(int argc, char* argv[])
{
	HANDLE tHandle;
	DWORD ThreadId;

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

		if (keyPressed == '1') {
			system("CLS");
			printf("Music list:\n");
			DisplayList(list);
			system("PAUSE");
			keyPressed = 0;
		}
	}

	if (tHandle != NULL) {
		WaitForSingleObject(tHandle, INFINITE);
		DeleteCriticalSection(&CriticalSection);
	}
	return 0;
}
