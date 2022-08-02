#pragma once

#include "PlacableActor.h"

class Money : public PlacableActor
{
private:
	int m_worth;

public:
	Money(int x, int y, int worth, ActorColor color = ActorColor::Yellow);
	virtual ActorType GetType() override;
	int GetWorth() const;
	virtual void Draw() override;
	virtual void HandleCollision(PlacableActor& player) override;
};