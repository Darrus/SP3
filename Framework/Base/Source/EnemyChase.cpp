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
	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(enemy->mesh);

	dir = player->pos.x - enemy->pos.x;
	if (dir > 0)
		dir = 1;
	else
		dir = -1;

	sprite->SetAnimation(enemy->GetWalkAnim());
	enemy->view.x = dir;
	enemy->vel.x = enemy->GetSpeed() * dir;
}

EnemyStates* EnemyChase::CheckState()
{
	float dist = (enemy->pos - player->pos).LengthSquared();
	if (dist > enemy->GetAlertRange() * enemy->GetAlertRange())
		return new EnemyIdle();
	else if (dist < enemy->GetAttackRange() * enemy->GetAttackRange())
		return new EnemyAttack();
	return this;
}

void EnemyChase::Update(double dt)
{
	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(enemy->mesh);
	dir = player->pos.x - enemy->pos.x;

	if (dir > 0)
		dir = 1;
	else
		dir = -1;

	enemy->view.x = dir;
	enemy->vel.x = enemy->GetSpeed() * dir;
	enemy->newPos.x += enemy->vel.x * dt;
}