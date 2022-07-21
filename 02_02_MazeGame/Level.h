#pragma once

#include <string>
#include <iostream>
#include <fstream>

class Level
{
	char* m_pLevelData;
	int m_width;
	int m_height;

public:
	Level();
	~Level();

	bool Load(std::string levelName, int* playerX, int* playerY);
	void Draw(int x, int y);

	bool IsSpace(int x, int y);
	bool IsKey(int x, int y);
	bool IsDoor(int x, int y);
	bool IsGoal(int x, int y);

	void ClearSpace(int x, int y);

	int GetHeight() { return m_height; }
	int GetWidth() { return m_width; }

private:
	bool Convert(int* playerX, int* playerY);
	int GetIndexFromCoords(int x, int y) { return x + y * m_width; }
};