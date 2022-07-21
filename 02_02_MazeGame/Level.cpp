#include "Level.h"

using namespace std;

constexpr char WALL = (char)219;
constexpr char KEY = (char)232;
constexpr char DOOR = (char)179;
constexpr char GOAL = (char)36;

Level::Level() 
	: m_pLevelData(nullptr)
	, m_width(0)
	, m_height(0) { }

Level::~Level() 
{ 
	if (m_pLevelData != nullptr)
	{
		delete[] m_pLevelData;
		m_pLevelData = nullptr;
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

void Level::Draw(int x, int y)
{
	int index = GetIndexFromCoords(x, y);
	cout << m_pLevelData[index];
}

bool Level::IsSpace(int x, int y)
{
	return (m_pLevelData[GetIndexFromCoords(x, y)] == ' ');
}

bool Level::IsKey(int x, int y)
{
	return (m_pLevelData[GetIndexFromCoords(x, y)] == KEY);
}

bool Level::IsDoor(int x, int y)
{
	return (m_pLevelData[GetIndexFromCoords(x, y)] == DOOR);
}

bool Level::IsGoal(int x, int y)
{
	return (m_pLevelData[GetIndexFromCoords(x, y)] == GOAL);
}

void Level::ClearSpace(int x, int y)
{
	m_pLevelData[GetIndexFromCoords(x, y)] = ' ';
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
			case '*':
				m_pLevelData[index] = KEY;
				break;
			case 'D':
				m_pLevelData[index] = DOOR;
				break;
			case 'X':
				m_pLevelData[index] = GOAL;
				break;
			case '@':
				m_pLevelData[index] = ' ';
				if (playerX != nullptr && playerY != nullptr)
				{
					*playerX = x;
					*playerY = y;
				}
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