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

	bool HasKey();
	bool HasKey(ActorColor color);
	void PickupKey(Key* key);
	void UseKey();
	void DropKey();

	void AddMoney(int money) { m_money += money; }
	int GetMoney() { return m_money; }

	void DecrementLives() { m_lives -= 1; }
	int GetLives() { return m_lives; }

	virtual void Draw() override;
};

