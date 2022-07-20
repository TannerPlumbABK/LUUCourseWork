#include "Player.h"
#include <iostream>

using namespace std;

Player::Player() : m_level(1) { }

Player::~Player() { }

void Player::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

int Player::GetPositionX()
{
	return m_position.x;
}

int Player::GetPositionY()
{
	return m_position.y;
}

void Player::SetLevel(int level)
{
	m_level = level;
}

void Player::LevelUp()
{
	m_level += 1;
}

int Player::GetLevel()
{
	return m_level;
}

void Player::DisplayPosition()
{
	cout << "X: " << GetPositionX() << endl;
	cout << "Y: " << GetPositionY() << endl;
}

void Player::DisplayLevel()
{
	cout << "Level: " << GetLevel() << endl;
}