#include <thread>

#include "PlacableActor.h"

PlacableActor::PlacableActor(int x, int y, ActorColor color)
	: m_pPosition(new Point(x, y))
	, m_pPrevPosition(new Point(x, y))
	, m_isActive(true)
	, m_color(color)
	, m_respawnTimer(-1)
{

}

PlacableActor::~PlacableActor()
{
	delete m_pPosition;
	m_pPosition = nullptr;
}

int PlacableActor::GetPositionX()
{
	return m_pPosition->x;
}

int PlacableActor::GetPositionY()
{
	return m_pPosition->y;
}

int* PlacableActor::GetPositionXPointer()
{
	return &(m_pPosition->x);
}

int* PlacableActor::GetPositionYPointer()
{
	return &(m_pPosition->y);
}

int PlacableActor::GetLastPositionX()
{
	return m_pPrevPosition->x;
}

int PlacableActor::GetLastPositionY()
{
	return m_pPrevPosition->y;
}

void PlacableActor::SetPosition(int x, int y)
{
	m_pPrevPosition->x = m_pPosition->x;
	m_pPrevPosition->y = m_pPosition->y;

	m_pPosition->x = x;
	m_pPosition->y = y;
}

ActorColor PlacableActor::GetColor()
{ 
	return m_color; 
}

void PlacableActor::Remove()
{ 
	m_isActive = false; 
	if (m_respawnTimer > 0) SetRespawn();
}

bool PlacableActor::IsActive()
{ 
	return m_isActive; 
}

void PlacableActor::MakeActive()
{
	m_isActive = true;
}

void PlacableActor::Place(int x, int y)
{
	m_pPosition->x = x;
	m_pPosition->y = y;
	m_isActive = true;
}

void PlacableActor::SetRespawn()
{
	std::thread RespawnThread(&PlacableActor::RespawnTimer, this);
	RespawnThread.detach();
}

void PlacableActor::RespawnTimer()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(m_respawnTimer * 1000));
	MakeActive();
}