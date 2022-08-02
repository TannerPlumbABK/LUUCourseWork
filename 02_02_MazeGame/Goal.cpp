#include <iostream>

#include "Goal.h"
#include "AudioManager.h"
#include "Player.h"
#include "Game.h"

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

void Goal::HandleCollision(PlacableActor& player)
{
	Remove();
	player.SetPosition(GetPositionX(), GetPositionY());
	dynamic_cast<Player*>(&player)->AddMoney(levelCompleteMoneyReward);
}