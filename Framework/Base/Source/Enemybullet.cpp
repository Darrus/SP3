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
		if (collider.CheckCollision(player->collider))
		{
			player->TakeDamage(damage);

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
			active = false;
		}
	}
}