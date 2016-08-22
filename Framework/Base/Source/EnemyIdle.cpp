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
		sprite->SetAnimation(enemy->GetWalkRightAnim());
	else
		sprite->SetAnimation(enemy->GetWalkLeftAnim());

	enemy->vel.x = enemy->GetSpeed() * dir;
}

EnemyStates* EnemyIdle::CheckState()
{
	float dist = (enemy->pos - player->pos).LengthSquared();

	if (dist < enemy->GetAlertRange() * enemy->GetAlertRange())
		return new EnemyChase();

	return this;
}

void EnemyIdle::Update(double dt)
{
	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(enemy->mesh);
	enemy->vel.x = enemy->GetSpeed() * dir;
	if (enemy->collidedWall || patrolDistance > enemy->GetPatrolRange())
	{
		patrolDistance = 0.f;
		dir = -dir;
		if (dir > 0)
			sprite->SetAnimation(enemy->GetWalkRightAnim());
		else
			sprite->SetAnimation(enemy->GetWalkLeftAnim());
		enemy->vel.x = enemy->GetSpeed() * dir;
	}
	enemy->newPos.x += enemy->vel.x * dt;
	patrolDistance += enemy->vel.x * dt;
}