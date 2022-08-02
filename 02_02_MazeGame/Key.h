#pragma once

#include <iostream>
#include <Windows.h>

#include "PlacableActor.h"

class Key : public PlacableActor
{
public:
	Key(int x, int y, ActorColor color);
	
	virtual ActorType GetType() override;
	virtual void Draw() override;
	virtual void HandleCollision(PlacableActor& player) override;
};

