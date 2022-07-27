#include "Enemy.h"

using namespace std;

Enemy::Enemy(float health, int x, int y)
	: Character(health, x, y)
{
	//
}

void Enemy::Draw()
{
	cout << "*" << std::endl;
}

void Enemy::OutputInfo()
{
	cout << "Health: " << m_Health << endl;
	cout << "X: " << m_Position.x << endl;
	cout << "Y: " << m_Position.y << endl;
	Draw();
}