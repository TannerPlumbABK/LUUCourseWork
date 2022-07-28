#pragma once

#include "PlacableActor.h"

class Key;

class Player : public PlacableActor
{
	Key* m_pCurrentKey;
	int m_money;
	int m_lives;

public:
	Player();
	virtual ActorType GetType() override;

	bool HasKey();
	bool HasKey(ActorColor color);
	void PickupKey(Key* key);
	void UseKey();
	void DropKey();

	void AddMoney(int money);
	void SpendMoney(int money);
	int GetMoney();

	void DecrementLives(int lives = 1);
	void AddLives(int lives = 1);
	int GetLives();

	void DisplayPlayerInfo();

	virtual void Draw() override;
};