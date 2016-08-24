#include "NetBullet.h"
#include "Player.h"
#include "Enemy.h"

NetBullet::NetBullet()
{
	bulletSpeed = 250.f;
}

NetBullet::~NetBullet()
{

}

void NetBullet::Update(double dt)
{
	Bullet::Update(dt);
}

void NetBullet::HandleInteraction(GameObject* go, double dt)
{
	Enemy* enemy = dynamic_cast<Enemy*>(go);
	if (enemy)
	{
		if (collider.CheckCollision(enemy->collider))
		{
			if ((float)enemy->GetHealth() / (float)enemy->GetMaxHealth() < 0.4f)
			{
				enemy->active = false;
				player->AddBullet(enemy->GetElement(), enemy->GetWorth());
			}
			active = false;
		}
	}
}

void NetBullet::SetPlayer(Player* player)
{
	this->player = player;
}