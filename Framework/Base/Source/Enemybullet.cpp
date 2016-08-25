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
			/*float dir = player->pos.x - pos.x;
			if (dir > 0)
				dir = 1;
			else if (dir < 0)
				dir = -1;
			else
				dir = 0;
			player->vel += Vector3(200.f * dir, 100.f, 0.f);*/
			active = false;
		}
	}
}