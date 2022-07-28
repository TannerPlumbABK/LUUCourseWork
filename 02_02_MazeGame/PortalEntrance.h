#pragma once
#include "PlacableActor.h"

class PortalEntrance : public PlacableActor
{
public:
	PortalEntrance(int x, int y, ActorColor color);
	virtual ActorType GetType() override;
	virtual void Draw() override;
};