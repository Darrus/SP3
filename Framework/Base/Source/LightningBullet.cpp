#include "LightningBullet.h"
#include "StunStatus.h"
#include "Enemy.h"

LightningBullet::LightningBullet()
{
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
		float dist = (enemy->pos - pos).LengthSquared();
		float size = enemy->scale.x + scale.x;
		if (dist < size * size)
		{
			Status* stun = new StunStatus();
			enemy->status.AddStatus(stun);
			active = false;
		}
	}
}
