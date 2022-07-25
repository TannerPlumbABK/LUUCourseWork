#pragma once
#include "PlacableActor.h"
class PortalEntrance : public PlacableActor
{
public:
	PortalEntrance(int x, int y, ActorColor color) : PlacableActor(x, y, color) { }
	virtual ActorType GetType() override { return ActorType::PortalEntrance; }
	virtual void Draw() override;
};