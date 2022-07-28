#pragma once
#include "PlacableActor.h"
class PortalExit : public PlacableActor
{
public:
	PortalExit(int x, int y);
	virtual ActorType GetType() override;
	virtual void Draw() override;
};

