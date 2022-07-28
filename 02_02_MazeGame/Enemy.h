#pragma once

#include "PlacableActor.h"

class Enemy : public PlacableActor
{
private:
	int m_movementInX;
	int m_movementInY;
	int m_currentMovementX;
	int m_currentMovementY;
	int m_directionX;
	int m_directionY;

	void UpdateDirection(int& current, int& direction, int& movement);

public:
	Enemy(int x, int y, int deltaX = 0, int deltaY = 0);
	virtual ActorType GetType() override;
	virtual void Draw() override;
	virtual void Update() override;
};