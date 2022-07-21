#pragma once

#include "Point.h"

constexpr int greenColor = 10;
constexpr int greenColorSolid = 34;
constexpr int redColor = 12;
constexpr int redColorSolid = 68;
constexpr int blueColor = 9;
constexpr int blueColorSolid = 153;
constexpr int regularColor = 7;

class PlacableActor
{
protected:
	Point* m_pPosition;
	bool m_isActive;
	int m_color;
public:
	PlacableActor(int x, int y, int color = regularColor);
	virtual ~PlacableActor();

	int GetPositionX();
	int GetPositionY();
	int* GetPositionXPointer();
	int* GetPositionYPointer();
	void SetPosition(int x, int y);

	int GetColor() { return m_color; }

	void Remove() { m_isActive = false; }
	bool IsActive() { return m_isActive; }
	void Place(int x, int y);

	virtual void Draw() = 0;
	virtual void Update() { }
};