#include "PortalExit.h"

#include <iostream>

PortalExit::PortalExit(int x, int y)
	: PlacableActor(x, y)
{
	//
}

ActorType PortalExit::GetType()
{
	return ActorType::PortalExit;
}

void PortalExit::Draw()
{
	std::cout << (char)176;
}

void PortalExit::HandleCollision(PlacableActor& player)
{
	player.SetPosition(GetPositionX(), GetPositionY());
}