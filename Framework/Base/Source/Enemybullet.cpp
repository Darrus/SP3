#include "EnemyBullet.h"
#include "Player.h"
EnemyBullet::EnemyBullet()
{

}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::Update(double dt)
{
	Bullet::Update(dt);
}

void EnemyBullet::HandleInteraction(GameObject* go, double dt)
{
	Player* player = dynamic_cast<Player*>(go);
	if (player)
	{
		float dist = (player->pos - pos).LengthSquared();
		float combinedRadius = player->scale.x + scale.x;
		if (dist < combinedRadius * combinedRadius)
		{
			player->TakeDamage(damage);
			active = false;
		}
	}
}