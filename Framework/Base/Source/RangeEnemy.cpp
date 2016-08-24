#include "RangeEnemy.h"
#include "EnemyStates.h"
#include "EnemyIdle.h"
#include "BulletFactory.h"

RangeEnemy::RangeEnemy()
{

}

RangeEnemy::~RangeEnemy()
{

}

void RangeEnemy::Update(double dt)
{
	Enemy::Update(dt);
}

void RangeEnemy::HandleInteraction(GameObject* go, double dt)
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
void RangeEnemy::Attack(Player* player)
{
	if (attackCooldown < 0)
	{
		attackCooldown = timeBetweenAttack;
		Bullet* bullet = BulletFactory::CreateEnemyBullet("Image//Bullet.tga", map);
		bullet->pos = pos;
		bullet->bulletSpeed = 400.f;
		bullet->damage = attackDamage;
		bullet->vel = (player->pos - pos).Normalized() * bullet->bulletSpeed;
	}
}