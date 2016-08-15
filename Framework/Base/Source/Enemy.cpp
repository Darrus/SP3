#include "Enemy.h"


Enemy::Enemy() :
mesh(nullptr),
state(IDLE),
timeBetweenAttack(0.f),
attacked(false)
{

}

Enemy::~Enemy()
{
	if (mesh)
		delete mesh;
	mesh = NULL;
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
	mesh->SetAnimation(animIdle);
}

void Enemy::SetAttackAnimation(int start, int end, float time)
{
	animAttack.Set(start, end, time, false);
}

void Enemy::SetPlayer(Player* player)
{
	this->player = player;
}

SpriteAnimation* Enemy::GetMesh()
{
	return mesh;
}