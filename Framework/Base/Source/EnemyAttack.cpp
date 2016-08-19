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
	enemy->vel.SetZero();
}

EnemyStates* EnemyAttack::CheckState()
{
	float dist = (player->pos - enemy->pos).LengthSquared();
	std::cout << enemy->AttackRange * enemy->AttackRange << std::endl;
	if (dist > enemy->AttackRange * enemy->AttackRange)
		return new EnemyChase();

	return this;
}

void EnemyAttack::Update(double dt)
{
	enemy->Attack(player);
}