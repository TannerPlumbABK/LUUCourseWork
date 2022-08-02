#include <iostream>
#include "Wall.h"

using namespace std;

constexpr char WALL = (char)219;

Wall::Wall(int x, int y) : PlacableActor(x, y)
{
	//
}

ActorType Wall::GetType()
{
	return ActorType::Wall;
}

void Wall::Draw()
{
	cout << WALL;
}

void Wall::HandleCollision(PlacableActor& player)
{
	// wall, do nothing
}