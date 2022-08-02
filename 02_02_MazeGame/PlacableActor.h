#pragma once

#include "Point.h"

enum class ActorColor
{
	Regular = 7,
	Blue = 9,
	Green = 10,
	Red = 12,
	Pink = 13,
	Yellow = 14,
	SolidGreen = 34,
	SolidRed = 68,
	SolidBlue = 153
};

enum class ActorType
{
	Wall,
	Door,
	Enemy,
	Goal,
	Key,
	Money,
	Player,
	PortalEntrance,
	PortalExit,
	Life
};

class PlacableActor
{
protected:
	Point* m_pPosition;
	bool m_isActive;
	ActorColor m_color;
public:
	PlacableActor(int x, int y, ActorColor color = ActorColor::Regular);
	virtual ~PlacableActor();

	int GetPositionX();
	int GetPositionY();
	int* GetPositionXPointer();
	int* GetPositionYPointer();
	void SetPosition(int x, int y);

	ActorColor GetColor();

	void Remove();
	bool IsActive();
	void Place(int x, int y);

	virtual ActorType GetType() = 0;
	virtual void Draw() = 0;
	virtual void Update() { }
	virtual void HandleCollision(PlacableActor& player) { }
};