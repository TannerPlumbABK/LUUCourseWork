#include <iostream>
#include <Windows.h>

#include "PortalEntrance.h"
#include "Player.h"

PortalEntrance::PortalEntrance(int x, int y, ActorColor color)
	: PlacableActor(x, y, color) 
{ 
	//
}

ActorType PortalEntrance::GetType()
{
	return ActorType::PortalEntrance;
}

void PortalEntrance::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);
	std::cout << (char)178;
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}