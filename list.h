// List structure.
typedef struct __node
{
	wchar_t			ArtistName[MAX_PATH];
	wchar_t			SongName[MAX_PATH];
	struct tm		Time;
	struct __node*	Next;
} Node;

// Prototypes.
void PushNode(Node** list, const wchar_t* songName, const wchar_t* artistName, struct tm localTime);
void PopNode(Node** list);
void DisplayList(Node* list);
void SearchListByTitle(Node * list, const wchar_t * songName);
void SearchListbyArtist(Node * list, const wchar_t * artistName);
void SaveToList(const wchar_t* currentSong, Node** list);
