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
	}
}

void MeleeEnemy::HandleInteraction(GameObject* go, double dt)
{
	Player* player = dynamic_cast<Player*>(go);
	if (player)
	{
		if (state)
		{
			EnemyStates* tempState = state->CheckState();
			if (state != tempState)
			{
				delete state;
				state = tempState;
				state->Enter(this, player);
			}
		}
		else
		{
			state = new EnemyIdle();
			state->Enter(this, player);
		}
	}
	
}