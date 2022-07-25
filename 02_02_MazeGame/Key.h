#pragma once

#include <iostream>
#include <Windows.h>

#include "PlacableActor.h"

class Key : public PlacableActor
{
public:
	Key(int x, int y, ActorColor color)
		: PlacableActor(x, y, color)
	{}
	
	virtual void Draw() override;
};

