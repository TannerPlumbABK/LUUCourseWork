#pragma once
#include "PlacableActor.h"
class Wall : public PlacableActor
{
public:
	Wall(int x, int y);
	virtual ActorType GetType() override;
	virtual void Draw() override;
	virtual void HandleCollision(PlacableActor& player) override;
};

