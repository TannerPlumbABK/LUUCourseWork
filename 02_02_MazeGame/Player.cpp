#include <iostream>
#include "Player.h"

using namespace std;

constexpr char playerSymbol = '@';

Player::Player() : m_hasKey(false) { }
Player::~Player() { }

void Player::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

void Player::Draw()
{
	cout << playerSymbol;
}