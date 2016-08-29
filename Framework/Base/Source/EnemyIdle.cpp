#include "EnemyIdle.h"

EnemyIdle::EnemyIdle()
{
	state = ENEMY_IDLE;
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

	sprite->SetAnimation(enemy->GetWalkAnim());
	enemy->view.x = dir;
	enemy->vel.x = enemy->GetSpeed() * dir;
}

void EnemyIdle::Update(double dt)
{
	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(enemy->mesh);
	enemy->vel.x = enemy->GetSpeed() * dir;
	if (enemy->collidedWall || patrolDistance > enemy->GetPatrolRange())
	{
		patrolDistance = 0.f;
		dir = -dir;
		enemy->view.x = dir;
		enemy->vel.x = enemy->GetSpeed() * dir;
	}
	enemy->newPos.x += enemy->vel.x * dt;
	patrolDistance += enemy->vel.x * dt;
}