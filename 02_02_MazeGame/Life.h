#pragma once
#include "PlacableActor.h"
class Life : public PlacableActor
{
public:
	Life(int x, int y, ActorColor color = ActorColor::Red);
	virtual ActorType GetType() override;
	virtual void Draw() override;
};

