#include "LightningBullet.h"
#include "StunStatus.h"
#include "Enemy.h"

LightningBullet::LightningBullet()
{
	bulletElement = LIGHTNING;
	bulletSpeed = 400.f;
	damage = 2;
}

LightningBullet::~LightningBullet()
{

}

void LightningBullet::Update(double dt)
{
	Bullet::Update(dt);
}

void LightningBullet::HandleInteraction(GameObject* go, double dt)
{
	Enemy* enemy = dynamic_cast<Enemy*>(go);
	if (enemy)
	{
		if (collider.CheckCollision(enemy->collider))
		{
			int chance = Math::RandIntMinMax(0, 10);
			if (chance <= 5)
			{
				Status* stun = new StunStatus();
				enemy->status.AddStatus(stun);
			}
			enemy->TakeDamage(damage);
			active = false;
		}
	}
}
