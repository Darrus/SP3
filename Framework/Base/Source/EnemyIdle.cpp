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

void EnemyIdle::Enter(Enemy* enemy, Player* player)
{
	patrolDistance = 100.f;
	this->enemy = enemy;
	this->player = player;
	Math::InitRNG();
	dir = Math::RandIntMinMax(-1, 1);

	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(enemy->mesh);

	if (dir == 0)
		dir = 1;

	if (dir > 0)
		sprite->SetAnimation(enemy->animWalkRight);
	else
		sprite->SetAnimation(enemy->animWalkLeft);

	enemy->vel.Set(enemy->EnemySpeed * dir, 0.f, 0.f);
}

EnemyStates* EnemyIdle::CheckState()
{
	float dist = (enemy->pos - player->pos).LengthSquared();

	if (dist < enemy->AlertRange * enemy->AlertRange)
		return new EnemyChase();

	return this;
}

void EnemyIdle::Update(double dt)
{
	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(enemy->mesh);

	if (enemy->collidedWall || patrolDistance > enemy->PatrolRange)
	{
		patrolDistance = 0.f;
		dir *= -1;
		if (dir > 0)
			sprite->SetAnimation(enemy->animWalkRight);
		else
			sprite->SetAnimation(enemy->animWalkLeft);
		enemy->vel.Set(enemy->EnemySpeed * dir, 0.f, 0.f);
	}
	enemy->newPos.x += enemy->vel.x * dt;
	patrolDistance += enemy->vel.x * dt;
}