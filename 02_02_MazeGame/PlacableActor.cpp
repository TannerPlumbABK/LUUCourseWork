#include "PlacableActor.h"

PlacableActor::PlacableActor(int x, int y, ActorColor color)
	: m_pPosition(new Point(x, y))
	, m_isActive(true)
	, m_color(color)
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

void PlacableActor::SetPosition(int x, int y)
{
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
}

bool PlacableActor::IsActive()
{ 
	return m_isActive; 
}

void PlacableActor::Place(int x, int y)
{
	m_pPosition->x = x;
	m_pPosition->y = y;
	m_isActive = true;
}