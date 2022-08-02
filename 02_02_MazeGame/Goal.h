#pragma once

#include "PlacableActor.h"

class Goal : public PlacableActor
{
public:
	Goal(int x, int y);
	virtual ActorType GetType() override;
	virtual void Draw() override;
	virtual void HandleCollision(PlacableActor& player) override;
};