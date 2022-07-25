#pragma once

#include "PlacableActor.h"

class Door : public PlacableActor
{
private:
	bool m_isOpen;
	ActorColor m_closedColor;

public:
	Door(int x, int y, ActorColor color, ActorColor closedColor);
	virtual void Draw() override;

	bool IsOpen() { return m_isOpen; }
	void Open() { m_isOpen = true; }
};