#include "EnemyChase.h"
#include "EnemyIdle.h"
#include "EnemyAttack.h"

EnemyChase::EnemyChase()
{

}

EnemyChase::~EnemyChase()
{

}

void EnemyChase::Enter(Enemy* enemy, Player* player)
{
	this->enemy = enemy;
	this->player = player;

	float dir = player->pos.x - enemy->pos.x;
	if (dir > 0)
	{
		dir = 1;
		enemy->sprite->SetAnimation(enemy->animWalkRight);
	}
	else
	{
		dir = -1;
		enemy->sprite->SetAnimation(enemy->animWalkLeft);
	}

	enemy->vel.Set(enemy->EnemySpeed * dir, 0.f, 0.f);
}

EnemyStates* EnemyChase::CheckState()
{
	float dist = (enemy->pos - player->pos).LengthSquared();
	if (dist > enemy->AlertRange * enemy->AlertRange)
		return new EnemyIdle();
	else if (dist < enemy->AttackRange * enemy->AttackRange)
		return new EnemyAttack();
	return this;
}

void EnemyChase::Update(double dt)
{
	enemy->newPos.x += enemy->vel.x * dt;
}