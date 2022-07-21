#include "PlacableActor.h"

PlacableActor::PlacableActor(int x, int y, int color = regularColor)
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

void PlacableActor::Place(int x, int y)
{
	m_pPosition->x = x;
	m_pPosition->y = y;
	m_isActive = true;
}