#include <iostream>
#include <Windows.h>

#include "Money.h"

Money::Money(int x, int y, int worth, ActorColor color)
	: PlacableActor(x, y, color)
	, m_worth(worth)
{
	//
}

ActorType Money::GetType()
{
	return ActorType::Money;
}

int Money::GetWorth() const
{ 
	return m_worth; 
}

void Money::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);
	std::cout << "$";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}