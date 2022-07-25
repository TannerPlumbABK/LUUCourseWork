#pragma once
#include "PlacableActor.h"
class PortalExit : public PlacableActor
{
public:
	PortalExit(int x, int y) : PlacableActor(x, y) { }
	virtual ActorType GetType() override { return ActorType::PortalExit; }
	virtual void Draw() override;
};

