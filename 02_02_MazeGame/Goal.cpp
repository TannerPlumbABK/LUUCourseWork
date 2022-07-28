#include <iostream>

#include "Goal.h"

Goal::Goal(int x, int y)
	: PlacableActor(x, y)
{
	//
}

ActorType Goal::GetType() 
{ 
	return ActorType::Goal; 
}

void Goal::Draw()
{
	std::cout << "X";
}