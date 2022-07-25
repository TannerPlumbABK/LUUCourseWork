#include <iostream>
#include <Windows.h>
#include "PortalEntrance.h"

void PortalEntrance::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);
	std::cout << (char)178;
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}