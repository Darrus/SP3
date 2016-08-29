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

void RangeEnemy::Attack(Player* player)
{
	if (attackCooldown < 0)
	{
		attackCooldown = timeBetweenAttack;
		Bullet* bullet = BulletFactory::CreateEnemyBullet("Image//Bullet.tga", map);
		bullet->pos = pos;
		bullet->bulletSpeed = 500.f;
		bullet->damage = attackDamage;
		Vector3 dir = (player->pos - pos).Normalized();
		bullet->vel = dir * bullet->bulletSpeed;
	}
}