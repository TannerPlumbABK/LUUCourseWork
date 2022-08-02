#include "Key.h"
#include "AudioManager.h"
#include "Player.h"

Key::Key(int x, int y, ActorColor color)
	: PlacableActor(x, y, color)
{
	//
}

ActorType Key::GetType()
{
	return ActorType::Key;
}

void Key::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);
	std::cout << "+";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}

void Key::HandleCollision(PlacableActor& player)
{
	if (!dynamic_cast<Player*>(&player)->HasKey())
	{
		AudioManager::GetInstance()->PlayKeyPickupSound();
		dynamic_cast<Player*>(&player)->PickupKey(this);
		Remove();
		player.SetPosition(GetPositionX(), GetPositionY());
	}
}