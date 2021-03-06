#include "FireBullet.h"
#include "BurnStatus.h"
#include "Enemy.h"

FireBullet::FireBullet()
{
	bulletElement = FIRE;
	bulletSpeed = 600.f;
	damage = 0;
}

FireBullet::~FireBullet()
{

}

void FireBullet::HandleInteraction(GameObject* go, double dt)
{
	Enemy* enemy = dynamic_cast<Enemy*>(go);
	if (enemy)
	{
		if (collider.CheckCollision(enemy->collider))
		{
			Status* burn = new BurnStatus();
			enemy->status.AddStatus(burn);
			enemy->TakeDamage(damage);
			active = false;
		}
	}
}

void FireBullet::Update(double dt)
{
	Bullet::Update(dt);
}
