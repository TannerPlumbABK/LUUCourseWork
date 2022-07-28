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
	void SpendMoney(int money) { m_money -= money; }
	int GetMoney() { return m_money; }

	void DecrementLives(int lives = 1) { m_lives -= lives; }
	void AddLives(int lives = 1) { m_lives += lives; }
	int GetLives() { return m_lives; }

	void DisplayPlayerInfo();

	virtual ActorType GetType() override { return ActorType::Player; }
	virtual void Draw() override;
};