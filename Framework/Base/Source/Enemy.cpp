#include "Enemy.h"


Enemy::Enemy() :
state(IDLE),
timeBetweenAttack(0.f),
attacked(false)
{
	sprite = dynamic_cast<SpriteAnimation*>(mesh);
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

void Enemy::SetState(ENEMY_STATE state)
{
	this->state = state;
	switch (state)
	{
	case IDLE:
		sprite->SetAnimation(animIdle);
		break;
	case ATTACK:
		sprite->SetAnimation(animAttack);
		break;
	}
}