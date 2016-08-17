#include "Enemy.h"


Enemy::Enemy() :
state(IDLE),
timeBetweenAttack(0.f),
attacked(false)
{

}

Enemy::~Enemy()
{
	
}

void Enemy::Init()
{
}

void Enemy::Update(double dt)
{
}

void Enemy::SetIdleAnimation(int start, int end, float time)
{
	animIdle.Set(start, end, time, true, 1, true);
}

void Enemy::SetAttackAnimation(int start, int end, float time)
{
	animAttack.Set(start, end, time, false);
}

void Enemy::SetPlayer(Player* player)
{
	this->player = player;
}