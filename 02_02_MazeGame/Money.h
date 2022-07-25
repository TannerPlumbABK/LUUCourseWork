#pragma once

#include "PlacableActor.h"

class Money : public PlacableActor
{
private:
	int m_worth;

public:
	Money(int x, int y, int worth);
	virtual ActorType GetType() override { return ActorType::Money; }
	int GetWorth() const { return m_worth; }
	virtual void Draw() override;
};