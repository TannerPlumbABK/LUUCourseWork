#pragma once

#include "PlacableActor.h"

class Door : public PlacableActor
{
private:
	bool m_isOpen;
	int m_closedColor;

public:
	Door(int x, int y, int color, int closedColor);
	virtual void Draw() override;

	bool IsOpen() { return m_isOpen; }
	void Open() { m_isOpen = true; }
};