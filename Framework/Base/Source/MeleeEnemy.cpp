#include "MeleeEnemy.h"
#include "EnemyIdle.h"
#include "MeshGenerator.h"

MeleeEnemy::MeleeEnemy()
{
}

MeleeEnemy::~MeleeEnemy()
{
	if (state)
		delete state;
}

void MeleeEnemy::Update(double dt)
{
	Enemy::Update(dt);
}

void MeleeEnemy::Attack(Player* player)
{
	if (attackCooldown < 0)
	{
		attackCooldown = timeBetweenAttack;
		player->TakeDamage(attackDamage);

		if (pos.x > player->pos.x)
		{
			player->vel.x -= 100;
			player->vel.y += 200;
		}
		else if (pos.x < player->pos.x)
		{
			player->vel.x += 100;
			player->vel.y += 200;
		}
	}
}