#include "LifeStealBullet.h"

#include "Player.h"
#include "Enemy.h"

LifeStealBullet::LifeStealBullet() :
player(NULL)
{
	bulletSpeed = 750.f;
	lifeStealRate = 1.f;
	damage = 5.f;
}

LifeStealBullet::~LifeStealBullet()
{

}

void LifeStealBullet::Update(double dt)
{
	Bullet::Update(dt);
}

void LifeStealBullet::HandleInteraction(GameObject* go, double dt)
{
	Enemy* enemy = dynamic_cast<Enemy*>(go);
	Player* temp = dynamic_cast<Player*>(go);
	if (temp)
		this->player = temp;


	if (enemy)
	{
		if (collider.CheckCollision(enemy->collider))
		{
			int playerTmpHP = player->GetPlayerHealth();
			playerTmpHP += lifeStealRate;
			if (playerTmpHP > 200)
			{
				playerTmpHP = 200;
			}
			player->SetPlayerHealth(playerTmpHP);

			if ((float)enemy->GetHealth()  < 0.f)
			{
				enemy->active = false;
			}
			active = false;
		}
	}
}

void LifeStealBullet::SetPlayer(Player* player)
{
	this->player = player;
}