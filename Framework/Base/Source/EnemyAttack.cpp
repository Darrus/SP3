#include "EnemyAttack.h"

EnemyAttack::EnemyAttack()
{
	state = ENEMY_ATTACK;
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

void EnemyAttack::Update(double dt)
{
	float dir = player->pos.x - enemy->pos.x;
	enemy->view.x = dir;
	enemy->Attack(player);
}