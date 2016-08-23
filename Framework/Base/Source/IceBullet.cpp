#include "IceBullet.h"
#include "SlowStatus.h"
#include "Enemy.h"

IceBullet::IceBullet()
{
	bulletElement = ICE;
	bulletSpeed = 500.f;
	damage = 2;
}

IceBullet::~IceBullet()
{

}

void IceBullet::Update(double dt)
{
	Bullet::Update(dt);
}

void IceBullet::HandleInteraction(GameObject* go, double dt)
{
	Enemy* enemy = dynamic_cast<Enemy*>(go);
	if (enemy)
	{
		float dist = (enemy->pos - pos).LengthSquared();
		float size = enemy->scale.x + scale.x;
		if (dist < size * size)
		{
			Status* slow = new SlowStatus();
			enemy->status.AddStatus(slow);
			enemy->TakeDamage(damage);
			active = false;
		}
	}
}
