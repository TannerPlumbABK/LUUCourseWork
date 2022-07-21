#pragma once

#include "Point.h"

class Player
{
	Point m_position;
	bool m_hasKey;

public:
	Player();
	~Player();

	int GetPositionX() { return m_position.x; }
	int GetPositionY() { return m_position.y; }

	int* GetPositionXPointer() { return &m_position.x; }
	int* GetPositionYPointer() { return &m_position.y; }

	void SetPosition(int x, int y);

	bool HasKey() { return m_hasKey; }
	void PickupKey() { m_hasKey = true; }
	void UseKey() { m_hasKey = false; }

	void Draw();
};

