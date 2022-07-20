#pragma once

#include "Point.h"

class Player
{
private:
	Point m_position;
	int m_level;

public:
	Player();
	~Player();

	void SetPosition(int x, int y);
	int GetPositionX();
	int GetPositionY();

	void SetLevel(int level);
	void LevelUp();
	int GetLevel();

	void DisplayPosition();
	void DisplayLevel();
};