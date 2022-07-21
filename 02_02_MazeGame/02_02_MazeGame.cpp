#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

constexpr char playerSymbol = '@';
constexpr char WAL = 219;
constexpr char KEY = 232;
constexpr char DOR = 179;
constexpr char GOL = 36;

int GetIndexFromCoords(int x, int y, int mazeWidth);
void DrawLevel(char level[], int mazeWidth, int mazeHeight, int playerX, int playerY);
bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int mazeWidth, bool& playerHasKey);
void PlaySoundDoorClosed();
void PlaySoundDoorOpened();
void PlaySoundPickupKey();
void PlaySoundWin();

int main()
{
	constexpr int mazeWidth = 25;
	constexpr int mazeHeight = 15;

	char levelArray[]{	WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,
						WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,' ',KEY,WAL,
						WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,' ',' ',WAL,
						WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,' ',' ',WAL,
						WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,WAL,' ',WAL,
						WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,
						WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,
						WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,
						WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,
						WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,
						WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,
						WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,
						WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,
						WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',DOR,' ',' ',' ',' ',' ',' ',' ',' ',GOL,WAL,
						WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL };

	int playerX = 1;
	int playerY = 1;
	bool playerHasKey = false;
	bool gameOver = false;

	while (!gameOver)
	{
		system("cls");
		DrawLevel(levelArray, mazeWidth, mazeHeight, playerX, playerY);
		gameOver = UpdatePlayerPosition(levelArray, playerX, playerY, mazeWidth, playerHasKey);
	}
	system("cls");
	DrawLevel(levelArray, mazeWidth, mazeHeight, playerX, playerY);
	cout << "You won!" << endl;
	PlaySoundWin();
}

int GetIndexFromCoords(int x, int y, int mazeWidth)
{
	return x + y * mazeWidth;
}

void DrawLevel(char level[], int mazeWidth, int mazeHeight, int playerX, int playerY)
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
				int index = GetIndexFromCoords(x, y, mazeWidth);
				cout << level[index];
			}
		}
		cout << endl;
	}
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
	Beep(500, 75);
	Beep(500, 75);
}

void PlaySoundDoorOpened()
{
	Beep(1397, 200);
}

void PlaySoundPickupKey()
{
	Beep(1568, 200);
}

void PlaySoundWin()
{
	Beep(1568, 200);
	Beep(1568, 200);
	Beep(1568, 200);
	Beep(1245, 1000);
	Beep(1397, 200);
	Beep(1397, 200);
	Beep(1397, 200);
	Beep(1175, 1000);
}