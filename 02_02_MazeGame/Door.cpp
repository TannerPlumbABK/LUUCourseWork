#include <iostream>
#include <Windows.h>

#include "Door.h"

Door::Door(int x, int y, ActorColor color, ActorColor closedColor)
	: PlacableActor(x, y, color)
	, m_isOpen(false)
	, m_closedColor(closedColor)
{
	//
}

ActorType Door::GetType() 
{ 
	return ActorType::Door; 
}

bool Door::IsOpen() 
{ 
	return m_isOpen; 
}

void Door::Open() 
{ 
	m_isOpen = true; 
}

void Door::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_isOpen) SetConsoleTextAttribute(console, (int)m_color); 
	else SetConsoleTextAttribute(console, (int)m_closedColor); 
	std::cout << "|";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}