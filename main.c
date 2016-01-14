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

char keyPressed = 0;
Node* list = NULL;

// Function which dispalys menu.
void displayMenu() {
	printf("1 - Display current playing track.\n");
	printf("2 - Display session history.\n");
	printf("ESC - Exit app and save session history to the file.\n");
}

int main(int argc, char* argv[])
{
	int* lpArgPtr = (int *)malloc(sizeof(int));
	HANDLE tHandle;
	DWORD ThreadId;

	tHandle = CreateThread(NULL, 0, SpotifyListener, lpArgPtr, 0, &ThreadId);

	if (tHandle == NULL) {
		printf("Could not create Thread for SpotifyListener\n");
	}
	else {
		printf("Thread %d was created\n", ThreadId);
	}

	// Run till user won't click ESC key.
	while (keyPressed != 27) {
		displayMenu();

		if (_kbhit()) {
			keyPressed = _getch();
		}

		system("CLS");
		printf("Keypressed: %d\n", keyPressed);

		if (keyPressed == 49) {
			printf("Music list:\n");
			DisplayList(list);
			system("PAUSE");
			keyPressed = 0;
		}
	}

	WaitForSingleObject(tHandle, INFINITE);
	return 0;
}