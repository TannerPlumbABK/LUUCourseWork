#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>

using namespace std;

constexpr char playerSymbol = '@';
constexpr char WAL = 219;
constexpr char KEY = 232;
constexpr char DOR = 179;
constexpr char GOL = 36;

constexpr int openDoorColor = 10;
constexpr int closedDoorColor = 12;
constexpr int regularColor = 7;

int GetIndexFromCoords(int x, int y, int mazeWidth);
void DrawLevel(char level[], int mazeWidth, int mazeHeight, int playerX, int playerY, bool playerHasKey);
bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int mazeWidth, bool& playerHasKey);
void PlaySoundDoorClosed();
void PlaySoundDoorOpened();
void PlaySoundPickupKey();
void PlaySoundWin();
char* LoadLevel(string levelName, int& width, int& height);
bool ConvertLevel(char* level, int width, int height, int& playerX, int& playerY);

int main()
{
	int mazeWidth = 25;
	int mazeHeight = 15;

	char* levelArray = LoadLevel("Level1.txt", mazeWidth, mazeHeight);

	int playerX = 1;
	int playerY = 1;
	
	bool anyWarnings = ConvertLevel(levelArray, mazeWidth, mazeHeight, playerX, playerY);
	if (anyWarnings)
	{
		cout << "There are some warnings in the level data, see above." << endl;
		system("pause");
	}

	bool playerHasKey = false;
	bool gameOver = false;

	while (!gameOver)
	{
		system("cls");
		DrawLevel(levelArray, mazeWidth, mazeHeight, playerX, playerY, playerHasKey);
		gameOver = UpdatePlayerPosition(levelArray, playerX, playerY, mazeWidth, playerHasKey);
	}
	system("cls");
	DrawLevel(levelArray, mazeWidth, mazeHeight, playerX, playerY, playerHasKey);
	cout << "You won!" << endl;
	PlaySoundWin();

	delete[] levelArray;
	levelArray = nullptr;
}

int GetIndexFromCoords(int x, int y, int mazeWidth)
{
	return x + y * mazeWidth;
}

void DrawLevel(char level[], int mazeWidth, int mazeHeight, int playerX, int playerY, bool playerHasKey)
{
	for (int y = 0; y < mazeHeight; y++)
	{
		for (int x = 0; x < mazeWidth; x++)
		{
			if (playerX == x && playerY == y)
			{
				cout << playerSymbol;
			}
			else
			{
				int indexToPrint = GetIndexFromCoords(x, y, mazeWidth);
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

				if (level[indexToPrint] == DOR)
				{
					if (playerHasKey)
					{
						SetConsoleTextAttribute(console, openDoorColor);
					}
					else
					{
						SetConsoleTextAttribute(console, closedDoorColor);
					}
				}
				else
				{
					SetConsoleTextAttribute(console, regularColor);
				}

				cout << level[indexToPrint];
			}
		}
		cout << endl;
	}
}

char* LoadLevel(string levelName, int& width, int& height)
{
	levelName.insert(0, "../02_02_MazeGame_Levels/");
	ifstream levelFile;
	levelFile.open(levelName);
	
	if (!levelFile)
	{
		cout << "Opening file failed." << endl;
		return nullptr;
	}

	constexpr int tempSize = 25;
	char temp[tempSize];

	levelFile.getline(temp, tempSize, '\n');
	width = atoi(temp);

	levelFile.getline(temp, tempSize, '\n');
	height = atoi(temp);

	char* levelData = new char[width * height];
	levelFile.read(levelData, width * height);

	return levelData;
}

bool ConvertLevel(char* level, int width, int height, int& playerX, int& playerY)
{
	bool anyWarnings = false;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = GetIndexFromCoords(x, y, width);

			switch (level[index])
			{
			case '+':
			case '-':
			case '|':
				level[index] = WAL;
				break;
			case '*':
				level[index] = KEY;
				break;
			case 'D':
				level[index] = DOR;
				break;
			case 'X':
				level[index] = GOL;
				break;
			case '@':
				level[index] = ' ';
				playerX = x;
				playerY = y;
				break;
			case ' ':
				break;
			default:
				cout << "Invalid character in level file: " << level[index] << endl;
				anyWarnings = true;
				break;
			}
		}
	}

	return anyWarnings;
}

bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int mazeWidth, bool& playerHasKey)
{
	char input = _getch();

	int newPlayerX = playerX;
	int newPlayerY = playerY;

	switch (input)
	{
	case 'W':
	case 'w':
		newPlayerY--;
		break;
	case 'S':
	case 's':
		newPlayerY++;
		break;
	case 'A':
	case 'a':
		newPlayerX--;
		break;
	case 'D':
	case 'd':
		newPlayerX++;
		break;
	default:
		break;
	}

	int index = GetIndexFromCoords(newPlayerX, newPlayerY, mazeWidth);
	if (level[index] == ' ')
	{
		playerX = newPlayerX;
		playerY = newPlayerY;
	}
	else if (level[index] == KEY)
	{
		playerX = newPlayerX;
		playerY = newPlayerY;
		playerHasKey = true;
		level[index] = ' ';
		PlaySoundPickupKey();
	}
	else if (level[index] == DOR)
	{
		if (playerHasKey)
		{
			playerX = newPlayerX;
			playerY = newPlayerY;
			playerHasKey = false;
			level[index] = ' ';
			PlaySoundDoorOpened();
		}
		else
		{
			PlaySoundDoorClosed();
		}
	}
	else if (level[index] == GOL)
	{
		playerX = newPlayerX;
		playerY = newPlayerY;
		level[index] = ' ';
		return true;
	}

	return false;
}

void PlaySoundDoorClosed()
{
	Beep(500, 35);
	Beep(500, 35);
}

void PlaySoundDoorOpened()
{
	Beep(1397, 100);
}

void PlaySoundPickupKey()
{
	Beep(1568, 100);
}

void PlaySoundWin()
{
	Beep(1568, 100);
	Beep(1568, 100);
	Beep(1568, 100);
	Beep(1245, 500);
	Beep(1397, 100);
	Beep(1397, 100);
	Beep(1397, 100);
	Beep(1175, 500);
}