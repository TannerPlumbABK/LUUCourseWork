#include "Key.h"

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