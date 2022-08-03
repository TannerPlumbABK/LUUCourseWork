#pragma once

#include <vector>
#include <thread>

class PlacableActor;

class Level
{
private:
	int m_width;
	int m_height;

	std::vector<PlacableActor*> m_pActors;

	bool runThread;
	std::thread* enemyThread;

	bool Convert(int* playerX, int* playerY);

public:
	char* m_pLevelData;

	Level();
	~Level();

	bool Load(std::string levelName, int* playerX, int* playerY);
	void Draw();
	PlacableActor* UpdateActors(int x, int y);

	bool IsSpace(int x, int y);

	void StartEnemyMovement();

	int GetHeight();
	int GetWidth();
	std::vector<PlacableActor*> GetActors();
	void ClearActors();
	int GetIndexFromCoords(int x, int y);
};