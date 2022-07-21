#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <assert.h>

#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"

using namespace std;

constexpr char WALL = (char)219;

Level::Level() 
	: m_pLevelData(nullptr)
	, m_width(0)
	, m_height(0) 
{ 
	//
}

Level::~Level() 
{ 
	if (m_pLevelData != nullptr)
	{
		delete[] m_pLevelData;
		m_pLevelData = nullptr;
	}

	while (!m_pActors.empty())
	{
		delete m_pActors.back();
		m_pActors.pop_back();
	}
}

bool Level::Load(string levelName, int* playerX, int* playerY)
{
	levelName.insert(0, "../02_02_MazeGame_Levels/");
	ifstream levelFile;
	levelFile.open(levelName);

	if (!levelFile)
	{
		cout << "Opening file failed." << endl;
		return false;
	}

	constexpr int tempSize = 25;
	char temp[tempSize];

	levelFile.getline(temp, tempSize, '\n');
	m_width = atoi(temp);

	levelFile.getline(temp, tempSize, '\n');
	m_height = atoi(temp);

	m_pLevelData = new char[m_width * m_height];
	levelFile.read(m_pLevelData, m_width * m_height);

	bool anyWarnings = Convert(playerX, playerY);
	if (anyWarnings)
	{
		cout << "There are some warnings in the level data, see above." << endl;
		system("pause");
	}

	return true;
}

void Level::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, regularColor);

	for (int y = 0; y < GetHeight(); y++)
	{
		for (int x = 0; x < GetWidth(); x++)
		{
			int indexToPrint = GetIndexFromCoords(x, y);
			cout << m_pLevelData[indexToPrint];
		}

		cout << endl;
	}

	COORD actorCursorPosition;

	for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor)
	{
		if ((*actor)->IsActive())
		{
			actorCursorPosition.X = (*actor)->GetPositionX();
			actorCursorPosition.Y = (*actor)->GetPositionY();
			SetConsoleCursorPosition(console, actorCursorPosition);
			(*actor)->Draw();
		}
	}
}

PlacableActor* Level::UpdateActors(int x, int y)
{
	PlacableActor* collidedActor = nullptr;

	for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor)
	{
		(*actor)->Update();

		if (x == (*actor)->GetPositionX() && y == (*actor)->GetPositionY())
		{
			assert(collidedActor == nullptr);
			collidedActor = (*actor);
		}
	}

	return collidedActor;
}

bool Level::IsSpace(int x, int y)
{
	return (m_pLevelData[GetIndexFromCoords(x, y)] == ' ');
}

bool Level::IsWall(int x, int y)
{
	return (m_pLevelData[GetIndexFromCoords(x, y)] == WALL);
}

bool Level::Convert(int* playerX, int* playerY)
{
	bool anyWarnings = false;

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			int index = GetIndexFromCoords(x, y);

			switch (m_pLevelData[index])
			{
			case '+':
			case '-':
			case '|':
				m_pLevelData[index] = WALL;
				break;
			case 'r':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, redColor));
				break;
			case 'g':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, greenColor));
				break;
			case 'b':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, blueColor));
				break;
			case 'R':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, redColor, redColorSolid));
				break;
			case 'G':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, greenColor, greenColorSolid));
				break;
			case 'B':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, blueColor, blueColorSolid));
				break;
			case 'X':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Goal(x, y));
				break;
			case '$':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Money(x, y, 1 + rand() % 5));
				break;
			case '@':
				m_pLevelData[index] = ' ';
				if (playerX != nullptr && playerY != nullptr)
				{
					*playerX = x;
					*playerY = y;
				}
				break;
			case 'e':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Enemy(x, y));
				break;
			case 'h':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Enemy(x, y, 3, 0));
				break;
			case 'v':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Enemy(x, y, 0, 2));
				break;
			case ' ':
				break;
			default:
				cout << "Invalid character in level file: " << m_pLevelData[index] << endl;
				anyWarnings = true;
				break;
			}
		}
	}

	return anyWarnings;
}