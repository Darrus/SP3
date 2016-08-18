#include "EnemyIdle.h"
#include "EnemyChase.h"
#include "MeleeEnemy.h"
#include "RangeEnemy.h"

EnemyIdle::EnemyIdle()
{

}

EnemyIdle::~EnemyIdle()
{

}

void EnemyIdle::Enter(Enemy& enemy, Player& player)
{
	patrolDistance = 100.f;
	Math::InitRNG();
	dir = Math::RandIntMinMax(-1, 1);
	if (dir > 0)
		enemy.sprite->SetAnimation(enemy.animWalkRight);
	else
		enemy.sprite->SetAnimation(enemy.animWalkLeft);
	MeleeEnemy* melee = dynamic_cast<MeleeEnemy*>(&enemy);
	enemy.vel.Set(melee->EnemySpeed * dir, 0.f, 0.f);
	patrolPos.Set(enemy.pos.x + patrolDistance * dir, enemy.pos.y, enemy.pos.z);

	this->enemy = &enemy;
}

EnemyStates* EnemyIdle::CheckState(Enemy& enemy, Player& player)
{
	float dist = (enemy.pos - player.pos).LengthSquared();
	MeleeEnemy* melee = dynamic_cast<MeleeEnemy*>(&enemy);
	RangeEnemy* range = dynamic_cast<RangeEnemy*>(&enemy);

	if (melee)
	{
		if (dist < melee->AlertRange * melee->AlertRange)
		{
			return new EnemyChase();
		}
	}
	else if (range)
	{
		
	}

	return this;
}

void EnemyIdle::Update(double dt)
{
	if (enemy->collidedWall)
	{
		MeleeEnemy* melee = dynamic_cast<MeleeEnemy*>(enemy);
		dir *= -1;
		if (dir > 0)
			enemy->sprite->SetAnimation(enemy->animWalkRight);
		else
			enemy->sprite->SetAnimation(enemy->animWalkLeft);
		enemy->vel.Set(melee->EnemySpeed * dir, 0.f, 0.f);
	}
	enemy->newPos.x += enemy->vel.x * dt;
}