#define CurrentSongFilename L"Current Song.txt"
#define PlaylistHistoryFilename L"History.txt"

void SaveToFile(const wchar_t* currentSong);
void SaveListToFile(const Node* list);
void ReadListFromFile(Node* list);