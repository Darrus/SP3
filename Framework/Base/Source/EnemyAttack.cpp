#include "EnemyAttack.h"
#include "EnemyChase.h"

EnemyAttack::EnemyAttack()
{

}

EnemyAttack::~EnemyAttack()
{

}

void EnemyAttack::Enter(Enemy* enemy, Player* player)
{
	this->enemy = enemy;
	this->player = player;
	enemy->vel.x = 0.f;
}

EnemyStates* EnemyAttack::CheckState()
{
	float dist = (player->pos - enemy->pos).LengthSquared();
	if (dist > enemy->GetAttackRange() * enemy->GetAttackRange())
		return new EnemyChase();
	return this;
}

void EnemyAttack::Update(double dt)
{
	enemy->Attack(player);
}